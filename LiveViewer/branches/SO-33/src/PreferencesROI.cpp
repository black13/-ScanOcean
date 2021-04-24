/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <QGridLayout>
#include <QLabel>
#include <QHeaderView>
#include <QDebug>

#include <PreferencesROI.h>

/*---------------------------------------------------------------------------*/
PreferencesROI::PreferencesROI(QWidget* parent)
: QWidget(parent)
{

   setupGUI();

}

/*---------------------------------------------------------------------------*/

PreferencesROI::~PreferencesROI()
{

}

/*---------------------------------------------------------------------------*/

void PreferencesROI::setupGUI()
{

   m_pvTable = new QTableView();
   m_pvTable -> horizontalHeader() -> setResizeMode(QHeaderView::Stretch);
   m_pvTable -> horizontalHeader() -> setVisible(false);
   //standard table model
   m_pvTableModel = new QStandardItemModel(0, 1);
   m_pvTable -> setModel(m_pvTableModel);

   m_addROIrow = new QPushButton(tr("+"));
   m_addROIrow -> setMaximumWidth(20);
   m_delROIrow = new QPushButton(tr("-"));
   m_delROIrow -> setMaximumWidth(20);
   m_delROIrow -> setEnabled(false);

   connect(m_pvTable -> selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection&,
                                    const QItemSelection&)),
            this,
            SLOT(selectionChanged(const QItemSelection&,
                                    const QItemSelection&)));
   connect(m_addROIrow, SIGNAL(pressed()), this, SLOT(addTableRow()));
   connect(m_delROIrow, SIGNAL(pressed()), this, SLOT(delTableRows()));

   QGridLayout* layout = new QGridLayout();
   layout -> addWidget(m_pvTable, 0, 0, 1, 3);
   layout -> addWidget(new QLabel(tr("Add/Remove mappings:")), 1, 0);
   layout -> addWidget(m_addROIrow, 1, 1);
   layout -> addWidget(m_delROIrow, 1, 2);

   setLayout(layout);

}

/*---------------------------------------------------------------------------*/

QList<QVariant> PreferencesROI::getROIPVs()
{

   QList<QVariant> dataItems = QList<QVariant>();

   int rows = m_pvTableModel -> rowCount();
   for (int i=0; i<rows; i++) {
      QVariant data = m_pvTableModel -> item(i, 0) -> data(Qt::DisplayRole);
      dataItems.append(data);
   }

   return dataItems;

}

/*---------------------------------------------------------------------------*/

void PreferencesROI::setROIPVs(QList<QVariant> pvs)
{

   if (m_pvTable == NULL || m_pvTableModel == NULL)
      return;

   for (int i = 0; i < pvs.size(); i++) {
      QStandardItem* item = new QStandardItem(pvs.at(i).toString());
      m_pvTableModel -> appendRow(item);
   }

}

/*---------------------------------------------------------------------------*/

void PreferencesROI::addTableRow()
{

   QStandardItem* item = new QStandardItem();
   m_pvTableModel -> appendRow(item);

}

/*---------------------------------------------------------------------------*/

void PreferencesROI::delTableRows()
{

   QModelIndexList selection = m_pvTable -> selectionModel() ->
      selectedIndexes();
   for (int i = 0; i < selection.size(); i++) {
      m_pvTableModel -> removeRow(selection.at(i).row());
   }

}

/*---------------------------------------------------------------------------*/

void PreferencesROI::selectionChanged(const QItemSelection& selected,
                                      const QItemSelection& deselected)
{

   if (selected.indexes().size() > 0) {
      m_delROIrow -> setEnabled(true);
   }
   else {
      m_delROIrow -> setEnabled(false);
   }

}

/*---------------------------------------------------------------------------*/

