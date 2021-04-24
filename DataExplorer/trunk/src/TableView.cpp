/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <TableView.h>

using namespace dstar;
using boost::dynamic_pointer_cast;
using boost::shared_array;
using boost::shared_ptr;
using std::pair;
using std::string;
using std::vector;

#include <iostream>

/*---------------------------------------------------------------------------*/

TableView::TableView(QWidget* parent)
: QWidget(parent), AbstractView()
{

   // Initialize everything
   m_dims = NULL;
   m_model = NULL;
   m_propertiesTable = NULL;
   m_rank = 0;
   m_table = NULL;

   m_ignore = false;

}

/*---------------------------------------------------------------------------*/

TableView::~TableView()
{

   // Clean up dimension extents
   if (m_dims != NULL) {
      delete [] m_dims;
   }

}

/*---------------------------------------------------------------------------*/

void TableView::dataAdded(shared_ptr<AbstractObject> obj)
{

   // Initial data setup

   // Convert to AbstractData and store
   m_data = dynamic_pointer_cast<AbstractData>(obj);

   // Get selection
   m_selCur = m_data -> getSelection();
   m_selFull = m_data -> getSelection();

   // Get data's rank
   m_rank = m_data -> getRank();

   // Allocate memory for dimension extents
   m_dims = new unsigned long long[m_rank];
   for (unsigned long d = 0 ; d < m_rank ; d++) {
      m_dims[d] = 0;
   }

   // Get data dimension extents
   m_data -> getDims(m_dims, m_rank);

   // Select full extents for final dimensions
   for (int d = m_rank - 1 ; d >= 0 ; d--) {
      m_selCur.setStart((unsigned long long) 0, (unsigned long) d);
      //m_selCur.setCount((unsigned long long) 1, d - 2);
   }


   // Create main layout for widget
   QVBoxLayout* layout = new QVBoxLayout();
   layout -> setContentsMargins(0, 0, 0, 0);
   layout -> setSpacing(0);
   layout -> setAlignment(Qt::AlignLeft | Qt::AlignTop);


   // Setup range widgets

   // Create range widgets for all dimensions > 2
   for (unsigned long d = 2 ; d < m_rank ; d++) {

      // ComboBox for this dimension/range mapping
      ComboBox* combo = new ComboBox((int) d - 2);
      combo -> setMaximumWidth(75);
      combo -> setMinimumWidth(75);
      for (unsigned long i = 0 ; i < m_rank ; i++) {
         combo -> addItem(tr("dim %1").arg(i));
      }
      combo -> setCurrentIndex(d - 2);
      connect(combo, SIGNAL(indexChanged(int, int, int)),
              this, SLOT(updateCombo(int, int, int)));
      m_listCombo.append(combo);

      // RangeWidget for this dimension
      RangeWidget* range = new RangeWidget();
      range -> setId(d - 2);
      range -> setMaximum(m_dims[d - 2] - 1);
      range -> setMinimum(0);
      connect(range, SIGNAL(valueChanged(int, int)),
              this, SLOT(rangeChanged(int, int)));
      m_listRange.append(range);

      // Create range window layout
      QHBoxLayout* rlayout = new QHBoxLayout();
      rlayout -> setContentsMargins(0, 0, 0, 0);
      rlayout -> setSpacing(3);
      rlayout -> setAlignment(Qt::AlignLeft | Qt::AlignTop);
      rlayout -> addWidget(combo);
      rlayout -> addWidget(range);

      // Setup current selection for this dimension
      m_selCur.setStart((unsigned long long) 0, (unsigned long) d - 2);
      m_selCur.setCount((unsigned long long) 1, (unsigned long) d - 2);

      // Add range layout to main layout
      layout -> addLayout(rlayout);

   }


   // Setup table and table widgets

   // Create model for QTableView
   m_model = new TableViewModel();
   if (m_data -> getType() == dstar::String) {
      m_model -> setDisplayDimensions(1, 1);
   }
   else if (m_rank == 0) {
      m_model -> setDisplayDimensions(1, 1);
   }
   else if (m_rank == 1) {
      m_model -> setDisplayDimensions(m_dims[0], 1);
   }
   else {
      m_model -> setDisplayDimensions(m_dims[m_rank - 2], m_dims[m_rank - 1]);
   }

   // Create table for data
   m_table = new QTableView();
   m_table -> setModel(m_model);
   (m_table -> horizontalHeader()) -> setStretchLastSection(false);
   (m_table -> verticalHeader()) -> setDefaultSectionSize(m_table ->
      verticalHeader() -> minimumSectionSize());

   // Layout for table and combo boxes
   QHBoxLayout* tlayout = new QHBoxLayout();
   tlayout -> setContentsMargins(0, 0, 0, 0);
   tlayout -> setSpacing(3);
   tlayout -> setAlignment(Qt::AlignLeft | Qt::AlignTop);

   // If there's more than one dimension, create combo boxes for
   // dimension choices
   if (m_rank > 1) {

      // ComboBox for table columns (width)
      ComboBox* comboCol = new ComboBox((int) (m_rank - 2));
      comboCol -> setMaximumWidth(75);
      comboCol -> setMinimumWidth(75);
      m_listCombo.append(comboCol);
      for (unsigned long d = 0 ; d < m_rank ; d++) {
         comboCol-> addItem(tr("dim %1").arg(d));
      }
      comboCol -> setCurrentIndex(m_rank - 2);
      connect(comboCol, SIGNAL(indexChanged(int, int, int)),
              this, SLOT(updateCombo(int, int, int)));

      // ComboBox for table rows (height)
      ComboBox* comboRow = new ComboBox((int) (m_rank - 1));
      comboRow -> setMaximumWidth(75);
      comboRow -> setMinimumWidth(75);
      m_listCombo.append(comboRow);
      for (unsigned long d = 0 ; d < m_rank ; d++) {
         comboRow-> addItem(tr("dim %1").arg(d));
      }
      comboRow -> setCurrentIndex(m_rank - 1);
      connect(comboRow, SIGNAL(indexChanged(int, int, int)),
              this, SLOT(updateCombo(int, int, int)));

      // Layout for two combo boxes
      QVBoxLayout* vlayout = new QVBoxLayout();
      vlayout -> addWidget(comboCol);
      vlayout -> addWidget(comboRow);
      vlayout -> setContentsMargins(0, 0, 0, 0);
      vlayout -> setSpacing(3);
      vlayout -> setAlignment(Qt::AlignLeft | Qt::AlignTop);
      tlayout -> addLayout(vlayout);

   }

   // Add table to table layout
   tlayout -> addWidget(m_table);

   // Create a widget simply to contain the table layout
   // This is used for the QSplitter later
   QWidget* tableWidgets = new QWidget();
   tableWidgets -> setLayout(tlayout);


   // Properties display widgets

   // Create properties table
   m_propertiesTable = new QTableView();
   (m_propertiesTable -> horizontalHeader()) -> setStretchLastSection(true);
   (m_propertiesTable -> horizontalHeader()) ->
     setResizeMode(QHeaderView::ResizeToContents);
   (m_propertiesTable -> verticalHeader()) ->
     setDefaultSectionSize(m_table -> verticalHeader() -> minimumSectionSize());
   m_propertiesTable -> verticalHeader() -> hide();
   m_propertiesTable -> horizontalHeader() -> hide();
   m_propertiesTable -> setAlternatingRowColors(true);
   m_propertiesTable -> setShowGrid(false);
   m_propertiesTable -> setSelectionMode(QAbstractItemView::NoSelection);
   m_propertiesTable -> setSelectionBehavior(QAbstractItemView::SelectRows);
   m_propertiesTable -> setEditTriggers(QAbstractItemView::NoEditTriggers);

   // Set model for properties table
   vector<pair<string, string> > props = obj -> getProperties();
   QStandardItemModel* propertiesModel =
      new QStandardItemModel(props.size(), 2);
   for (unsigned int row = 0; row < props.size(); ++row) {
      QStandardItem* item =
         new QStandardItem(QString(props[row].first.c_str()));
      propertiesModel -> setItem(row, 0, item);
      item = new QStandardItem(QString(props[row].second.c_str()));
      propertiesModel -> setItem(row, 1, item);
   }
   m_propertiesTable -> setModel(propertiesModel);


   // Add everything to the widget

   // Splitter for data and properties tables
   QSplitter* splitter = new QSplitter();
   splitter -> setOrientation(Qt::Vertical);
   splitter -> addWidget(tableWidgets);
   splitter -> addWidget(m_propertiesTable);
   splitter -> setStretchFactor(0, 1);
   splitter -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   layout -> addWidget(splitter);

   // Set widget's layout
   setLayout(layout);

   // Create initial list of ranks
   for (unsigned long i = 0 ; i < m_rank ; i++) {
      m_listRank.append(i);
   }

   // Set major order
   if (m_rank >= 2) {
      if (m_listRank[m_listRank.size() - 1] <
          m_listRank[m_listRank.size() - 2]) {
         m_model -> setRowMajor();
      }
      else {
         m_model -> setColumnMajor();
      }
   }

   // Show it
   show();

   // Update the model and display
   update();

}

/*---------------------------------------------------------------------------*/

void TableView::dataRemoved(shared_ptr<AbstractObject> obj)
{
}

/*---------------------------------------------------------------------------*/

void TableView::rangeChanged(int value, int id)
{

   // Ignore nested updates
   if (m_ignore == true) {
      return;
   }

   // Update the model and display
   updateSelection();
   update();

}

/*---------------------------------------------------------------------------*/

void TableView::update()
{

   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

   // Update selection
   m_data -> setSelection(m_selCur);

   // Get the data
   shared_array<char> arr = m_data -> getData();

   // Add data to the model for QTreeView
   m_model -> setData(arr, m_data -> getType());

   // Update table's dimensions
   if (m_data -> getType() == dstar::String) {
      m_model -> setDisplayDimensions(1, 1);
   }
   else if (m_rank == 0) {
      m_model -> setDisplayDimensions(1, 1);
   }
   else if (m_rank == 1) {
      m_model -> setDisplayDimensions(m_dims[0], 1);
   }
   else {
      m_model -> setDisplayDimensions(m_dims[m_listRank[m_rank - 1]],
                                      m_dims[m_listRank[m_rank - 2]]);
   }

   QApplication::restoreOverrideCursor();

}

/*---------------------------------------------------------------------------*/

void TableView::updateCombo(int id, int oldI, int newI)
{

   // Ignore nested updates
   if (m_ignore == true) {
      return;
   }

   // Find existing combo box with the updated value and change it to the
   // updated box's old value.
   for (int j = 0 ; j < m_listCombo.size() ; j++) {
      if (j != id) {
         if (m_listCombo[j] -> currentIndex() == newI) {
            m_ignore = true;
            m_listCombo[j] -> setCurrentIndex(oldI);
            m_ignore = false;
            break;
         }
      }
   }

   // Update dimension list
   for (int i = 0 ; i < m_listCombo.size() ; i++) {
      m_listRank[i] = m_listCombo[i] -> currentIndex();
   }

   // Set major order
   if (m_rank >= 2) {
      if (m_listRank[m_listRank.size() - 1] <
          m_listRank[m_listRank.size() - 2]) {
         m_model -> setRowMajor();
      }
      else {
         m_model -> setColumnMajor();
      }
   }

   // Now, update the range widgets
   updateRange();

}

/*---------------------------------------------------------------------------*/

void TableView::updateRange()
{

   // Update range widgets based on rank list
   for (int i = 0 ; i < m_listRange.size() ; i++) {
      m_ignore = true;
      unsigned long ind = m_listRank[i];
      m_listRange[i] -> setId(ind);
      m_listRange[i] -> setMaximum(m_dims[ind] - 1);
      m_listRange[i] -> setMinimum(0);
      m_ignore = false;
   }

   // Update selection and display
   updateSelection();
   update();

}

/*---------------------------------------------------------------------------*/

void TableView::updateSelection()
{

   if (m_rank >= 2) {

      for (int i = 0 ; i < m_listRange.size() ; i++) {
         unsigned long d = (unsigned long) m_listCombo[i] -> currentIndex();
         unsigned long long s = m_listRange[i] -> value();

         m_selCur.setStart(s, d);
         m_selCur.setCount(1, d);
      }

      unsigned long d =
        (unsigned long) m_listCombo[m_rank - 2] -> currentIndex();
      unsigned long long c = m_dims[d];

      m_selCur.setStart((unsigned long long) 0, d);
      m_selCur.setCount(c, d);

      d = (unsigned long) m_listCombo[m_rank - 1] -> currentIndex();
      c = m_dims[d];

      m_selCur.setStart((unsigned long long) 0, d);
      m_selCur.setCount(c, d);

   }

}

/*---------------------------------------------------------------------------*/
