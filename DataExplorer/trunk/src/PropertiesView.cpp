/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/
#include <PropertiesView.h>

using namespace dstar;
using boost::shared_ptr;
using std::string;
using std::vector;

#include <iostream>

/*---------------------------------------------------------------------------*/

PropertiesView::PropertiesView(QWidget* parent)
: QWidget(parent), AbstractView()
{

   m_table = new QTableView();
   (m_table -> horizontalHeader()) -> setStretchLastSection(true);
   (m_table -> horizontalHeader()) ->
     setResizeMode(QHeaderView::ResizeToContents);
   (m_table -> verticalHeader()) ->
     setDefaultSectionSize(m_table -> verticalHeader() -> minimumSectionSize());
   m_table -> verticalHeader() -> hide();
   m_table -> horizontalHeader() -> hide();
   m_table -> setAlternatingRowColors(true);
   m_table -> setShowGrid(false);
   m_table -> setSelectionMode(QAbstractItemView::NoSelection);
   m_table -> setSelectionBehavior(QAbstractItemView::SelectRows);
   m_table -> setEditTriggers(QAbstractItemView::NoEditTriggers);

   QVBoxLayout* layout = new QVBoxLayout();
   layout -> setContentsMargins(0, 0, 0, 0);
   layout -> setSpacing(0);
   layout -> setAlignment(Qt::AlignTop);
   layout -> addWidget(m_table);

   setLayout(layout);

}

/*---------------------------------------------------------------------------*/

PropertiesView::~PropertiesView()
{
}

/*---------------------------------------------------------------------------*/

void PropertiesView::clear()
{

   // Replace model with an empty model
   m_model = new QStandardItemModel(0, 2);
   m_table -> setModel(m_model);

}

/*---------------------------------------------------------------------------*/

void PropertiesView::dataAdded(shared_ptr<AbstractObject> obj)
{

   vector<std::pair<string, string> > props = obj -> getProperties();

   m_model = new QStandardItemModel(props.size(), 2);
   for (int row = 0; row < props.size(); ++row) {
      QStandardItem* item =
            new QStandardItem(QString(props[row].first.c_str()));
      m_model -> setItem(row, 0, item);
      item = new QStandardItem(QString(props[row].second.c_str()));
      m_model -> setItem(row, 1, item);
   }
   m_table -> setModel(m_model);

}

/*---------------------------------------------------------------------------*/

void PropertiesView::dataRemoved(boost::shared_ptr<dstar::AbstractObject> obj)
{

   clear();

}

/*---------------------------------------------------------------------------*/
