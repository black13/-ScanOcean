/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ROITableWidget.h>
#include <ROITableModel.h>
#include <ROI.h>

using gstar::ROITableModel;
using gstar::ROI;

/*---------------------------------------------------------------------------*/

ROITableWidget::ROITableWidget(ROITableModel* model, QWidget* parent)
: QWidget(parent)
{

   // Set the limit on number of ROIs
   m_roiCountLimit = 0;

   // Specify the default value for the default base name for PVs.
   m_pvBaseName = "ROI:";

   // Background color
   QPalette pal = this -> palette();
   pal.setColor(this -> backgroundRole(), Qt::white);
   this -> setPalette(pal);

   // Autofill background
   setAutoFillBackground(true);

   // Set model
   m_model = model;

   // Enabled check box
   m_ckEnable = new QCheckBox(tr("Enable ROIs"));
   connect(m_ckEnable, SIGNAL(toggled(bool)), 
           this, SLOT(enabled(bool)));

   // Setup table view
   m_table = new QTableView;
   m_table -> setModel(m_model);
   m_table -> setSelectionBehavior(QAbstractItemView::SelectRows);
   m_table -> verticalHeader() -> hide();
   m_table -> setSelectionMode(QAbstractItemView::MultiSelection);
   m_table -> horizontalHeader() -> setResizeMode(QHeaderView::Stretch);
   for (int i = 2 ; i < m_model -> columnCount(QModelIndex()) ; i++) {
      m_table -> hideColumn(i);
   }

   // Color list combo box delegate
   ColorListComboBoxDelegate* m_delegate = new ColorListComboBoxDelegate();
   m_table -> setItemDelegateForColumn(1, m_delegate);

   // Add ROI button
   m_btnAdd = new QPushButton;
   m_btnAdd -> setIcon(QIcon(":images/list-add.png"));
   m_btnAdd -> setFlat(true);
   m_btnAdd -> setFixedSize(32, 32);
   connect(m_btnAdd, SIGNAL(clicked()),
           this, SLOT(addROI()));

   // Remove ROI button
   m_btnRemove = new QPushButton;
   m_btnRemove -> setIcon(QIcon(":images/list-remove.png"));
   m_btnRemove -> setFlat(true);
   m_btnRemove -> setEnabled(false);
   m_btnRemove -> setFixedSize(32, 32);
   connect(m_btnRemove, SIGNAL(clicked()),
           this, SLOT(removeROI()));

   // Copy ROI button
   m_btnCopy = new QPushButton;
   m_btnCopy -> setIcon(QIcon(":images/list-copy.png"));
   m_btnCopy -> setFlat(true);
   m_btnCopy -> setEnabled(false);
   m_btnCopy -> setFixedSize(32, 32);
   connect(m_btnCopy, SIGNAL(clicked()),
           this, SLOT(copyROI()));

   // Layout for buttons
   QHBoxLayout* buttonLayout = new QHBoxLayout;
   buttonLayout -> addWidget(m_btnAdd);
   buttonLayout -> addWidget(m_btnRemove);
   buttonLayout -> addWidget(m_btnCopy);
   buttonLayout -> addStretch();
   buttonLayout -> setSpacing(0);
   buttonLayout -> setContentsMargins(0, 0, 0, 0);

   // Vertical layout
   QVBoxLayout* verticalLayout = new QVBoxLayout;
   verticalLayout -> addWidget(m_ckEnable);
   verticalLayout -> addWidget(m_table);
   verticalLayout -> addLayout(buttonLayout);
   //verticalLayout -> setSpacing(0);
   //verticalLayout -> setContentsMargins(0, 0, 0, 0);

   // Create small color list
   m_colors.append(tr("cornflowerblue"));
   m_colors.append(tr("goldenrod"));
   m_colors.append(tr("indianred"));
   m_colors.append(tr("olivedrab"));
   m_colors.append(tr("plum"));
   m_colors.append(tr("gold"));

   // Index into color list
   m_colorIndex = 0;

   // Set layout
   setLayout(verticalLayout);

   // Initially disabled
   enabled(false);

}

/*---------------------------------------------------------------------------*/

void ROITableWidget::addROI()
{

   // Add data
   addROI(m_colors.at(m_colorIndex), -1.0, -1.0, -1.0, -1.0);

}

/*---------------------------------------------------------------------------*/

void ROITableWidget::addROI(QString color,
                          double x, double y,
                          double w, double h)
{

   // Check valid model
   if (m_model == NULL) {
      return;
   }

   // Create text description
   int row = m_model -> rowCount(QModelIndex()) + 1;
   QString text;

   // For the first row construct roi name based on the default name
   if (row == 1) {
      text = m_pvBaseName;
   }
   else {
      // Copy the name of the last added PV for user convenience.
      ROI roi = m_model -> getROIs().at(row - 2);
      text = QString("%1:").arg(roi.getText().section(':', 0, -2));
   }

   int row2 = m_model -> addROI(text, color, x, y, w, h);

   // Next color index
   m_colorIndex++;
   m_colorIndex = m_colorIndex % m_colors.size();

   // Enable remove ROI button
   if (m_model->rowCount(QModelIndex()) > 0) {
      m_btnCopy->setEnabled(true);
      m_btnRemove->setEnabled(true);
   }

   // Select newly added ROI
   m_table->selectionModel()->clearSelection();
   m_table->selectRow(row2);

   // Check to see if more ROIs can be added
   if (!canAddROI()) {
      m_btnAdd->setEnabled(false);
      m_btnCopy->setEnabled(false);
   }

}

/*---------------------------------------------------------------------------*/

bool ROITableWidget::canAddROI()
{

   // Default is unlimited ROIs.
   if (m_roiCountLimit == 0)
      return true;

   // Create text description
   int rows = m_model -> rowCount(QModelIndex());

   if (rows == m_roiCountLimit)
      return false;

   return true;

}

/*---------------------------------------------------------------------------*/

void ROITableWidget::clear()
{

   // Check for model
   if (m_model == NULL) {
      return;
   }

   // Get number of rows in model
   int count = m_model -> rowCount(QModelIndex());

   // Delete each row
   for (int i = count - 1 ; i >= 0 ; i--) {

      // Remove from model
      m_model -> removeRows(i, 1);

   }

   //TODO: Handle button states.

}

/*---------------------------------------------------------------------------*/

void ROITableWidget::copyROI()
{

   // Get current selection
   QModelIndexList list = m_table -> selectionModel() -> selectedIndexes();

   // Check for selected indexes
   if (list.size() < 1) {
      return;
   }

   // Get first one
   QModelIndex index = list.at(0);

   // Get row of current selection
   int row = index.row();

   // If row is valid
   if (row >= 0 && row < m_model -> rowCount(QModelIndex())) {

      // Get data from model for currently selected ROI
      index = m_model -> index(row, 2);
      double x = m_model -> data(index, Qt::DisplayRole).toDouble();
      index = m_model -> index(row, 3);
      double y = m_model -> data(index, Qt::DisplayRole).toDouble();
      index = m_model -> index(row, 4);
      double w = m_model -> data(index, Qt::DisplayRole).toDouble();
      index = m_model -> index(row, 5);
      double h = m_model -> data(index, Qt::DisplayRole).toDouble();

      // Add data
      addROI(m_colors.at(m_colorIndex), x, y, w, h);

   }

}

/*---------------------------------------------------------------------------*/

void ROITableWidget::disable()
{

   m_ckEnable -> setChecked(false);

}

/*---------------------------------------------------------------------------*/

void ROITableWidget::enable()
{

   m_ckEnable -> setChecked(true);

}

/*---------------------------------------------------------------------------*/

void ROITableWidget::enabled(bool state)
{

   // Enable/disable controls
   m_table -> setEnabled(state);
   m_btnAdd -> setEnabled(state);
   //m_btnRemove -> setEnabled(state);
   //m_btnCopy -> setEnabled(state);

   // Clear selection
   if (state == false) {
      m_table -> selectionModel() -> clearSelection();
   }

   // Emit state change
   emit enabledROI(state);

}

/*---------------------------------------------------------------------------*/

int ROITableWidget::getMaxROIs()
{

   return m_roiCountLimit;

}

/*---------------------------------------------------------------------------*/

ROITableModel* ROITableWidget::getModel()
{

   // Return ROITableModel
   return m_model;

}

/*---------------------------------------------------------------------------*/

QString& ROITableWidget::getPVBaseName()
{

   return m_pvBaseName;

}

/*---------------------------------------------------------------------------*/

void ROITableWidget::hideButtons()
{

   // Hide buttons
   m_btnAdd -> hide();
   m_btnRemove -> hide();
   m_btnCopy -> hide();

}

/*---------------------------------------------------------------------------*/

bool ROITableWidget::isEnabled()
{

   return m_ckEnable -> isChecked();

}

/*---------------------------------------------------------------------------*/

void ROITableWidget::removeROI()
{

   // Check valid model
   if (m_model == NULL) {
      return;
   }

   // Get current selection
   QModelIndexList list = m_table -> selectionModel() -> selectedIndexes();

   // Check for selected indexes
   if (list.size() < 1) {
      return;
   }

   // Get first one
   QModelIndex index = list.at(0);

   // Get row of current selection
   int row = index.row();

   // Remove row if it's valid
   if (row >= 0 && row < m_model -> rowCount(QModelIndex())) {

      // Remove from model
      m_model -> removeRows(row, 1);

   }

   // Update selected row
   if (m_model -> rowCount(QModelIndex()) > 0) {

      // If row removed was last row in model
      if (row >= m_model -> rowCount(QModelIndex()))
          row = m_model -> rowCount(QModelIndex()) - 1;

      // Select newly added ROI
      m_table -> selectionModel() -> clearSelection();
      m_table -> selectRow(row);

   }

   // Disable remove ROI button
   if (m_model -> rowCount(QModelIndex()) <= 0) {
      m_btnCopy -> setEnabled(false);
      m_btnRemove -> setEnabled(false);
   }

   if (canAddROI()) {
      m_btnAdd -> setEnabled(true);
   }

}

/*---------------------------------------------------------------------------*/

void ROITableWidget::selectionChanged(const QItemSelection &selected,
                                      const QItemSelection &deselected)
{

   // Mark unused
   Q_UNUSED(selected)
   Q_UNUSED(deselected)

   // Member function parameters pass what has changed, not current state.

   // Get current selection
   QModelIndexList list = m_table -> selectionModel() -> selectedIndexes();

   // Enable/disable copy and remove buttons based on selection
   if (list.size() == m_model -> columnCount(QModelIndex())) {
      if (canAddROI()) {
         m_btnCopy -> setEnabled(true);
      }
      m_btnRemove -> setEnabled(true);
   }
   else {
      m_btnCopy -> setEnabled(false);
      m_btnRemove -> setEnabled(false);
   }

}

/*---------------------------------------------------------------------------*/

void ROITableWidget::setMaxROIs(int limit)
{

   m_roiCountLimit = limit;

}

/*---------------------------------------------------------------------------*/

void ROITableWidget::setModel(ROITableModel* model)
{

   // Set model
   m_model = model;

}

/*---------------------------------------------------------------------------*/

void ROITableWidget::setSelectionModel(QItemSelectionModel* selectionModel)
{

   // Connect selection changed signal
   connect(selectionModel, 
           SIGNAL(selectionChanged(const QItemSelection&, 
                                   const QItemSelection&)),
           this, 
           SLOT(selectionChanged(const QItemSelection&,
                                 const QItemSelection&)));

   // Set selection model
   m_table -> setSelectionModel(selectionModel);

}

/*---------------------------------------------------------------------------*/
