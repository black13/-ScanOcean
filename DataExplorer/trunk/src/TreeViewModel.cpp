/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <TreeViewModel.h>

using namespace dstar;
using boost::shared_ptr;

/*---------------------------------------------------------------------------*/

TreeViewModel::TreeViewModel(QObject* parent)
: QAbstractItemModel(parent)
{
}

/*---------------------------------------------------------------------------*/

TreeViewModel::~TreeViewModel()
{
}

/*---------------------------------------------------------------------------*/

void TreeViewModel::addData(boost::shared_ptr<dstar::AbstractObject> data)
{

   // Indicate that rows are begin added
   beginInsertRows(QModelIndex(), m_data.size(), m_data.size());

   // Add row to end of model
   m_data.push_back(data);

   // Indicate done adding rows
   endInsertRows();

}

/*---------------------------------------------------------------------------*/

int TreeViewModel::columnCount(const QModelIndex& parent) const
{

   Q_UNUSED(parent)

   // There's only one column
   return 1;

}

/*---------------------------------------------------------------------------*/

QVariant TreeViewModel::data(const QModelIndex& index, int role) const
{

   // Check for a valid index
   if (!index.isValid())
      return QVariant();

   //if (role == Qt::DecorationRole)
   //   return QColor(Qt::blue);

   // Return an empty QVariant for other roles
   if (role != Qt::DisplayRole)
      return QVariant();

   // Get the data object for the index
   AbstractObject* item =
      static_cast<AbstractObject*>(index.internalPointer());

   // Return the data object's name for display
   return (item -> getName()).c_str();

}

/*---------------------------------------------------------------------------*/

Qt::ItemFlags TreeViewModel::flags(const QModelIndex& index) const
{

   // Check for valid index
   if (!index.isValid())
      return 0;

   // Return appropriate flags
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

}

/*---------------------------------------------------------------------------*/

QVariant TreeViewModel::headerData(int section,
                                   Qt::Orientation orientation,
                                   int role) const
{

   Q_UNUSED(section)
   Q_UNUSED(orientation)
   Q_UNUSED(role)

   // No header data
   return QVariant();

}

/*---------------------------------------------------------------------------*/

QModelIndex TreeViewModel::index(int row, int column,
                                 const QModelIndex& parent) const
{

   // Check that the index is real
   if (!hasIndex(row, column, parent)) {
      return QModelIndex();
   }

   // If parent index is not valid the current location in the root list
   if (!parent.isValid()) {
      return createIndex(row, column, (void*) m_data.at(row).get());
   }

   // Get parent item
   AbstractObject* item =
      static_cast<AbstractObject*>(parent.internalPointer());

   // Determine if the item is a Group or not
   AbstractGroup* group = NULL;
   try {
      group = dynamic_cast<AbstractGroup*>(item);
   }
   catch(...) {
   }

   // If it's a group get the child given by row and create an index for it
   if (group != NULL) {
      shared_ptr<const AbstractObject> child = group -> getChild(row);
      if (child.get() != NULL) {
         return createIndex(row, column, (void*) child.get());
      }
   }

   // parent has no children
   return QModelIndex();

}

/*---------------------------------------------------------------------------*/

QModelIndex TreeViewModel::parent(const QModelIndex& index) const
{

   // Check for valid index
   if (!index.isValid()) {
      return QModelIndex();
   }

   // Get item in index
   AbstractObject* childItem =
      static_cast<AbstractObject*>(index.internalPointer());

   // Get item's parent
   shared_ptr<const AbstractObject> parentItem = (childItem -> getParent());

   // Check if the parent is the root item and return a default index
   if (parentItem.get() == NULL) {
      return QModelIndex();
   }

   // Check if the parent is without a parent.
   if ((parentItem -> getParent()).get() == NULL) {
      return createIndex(index.row(), 0, (void*) parentItem.get());
   }

   // Get child's row entry in its parent
   int row =
     (dynamic_cast<const AbstractGroup*>((parentItem -> getParent()).get())) ->
         getChildIndex(parentItem);

   // Create an index for the item and return it; it contains the row of the
   // item under parentItem
   return createIndex(row, 0, (void*) parentItem.get());

}

/*---------------------------------------------------------------------------*/

void TreeViewModel::removeData(boost::shared_ptr<dstar::AbstractObject> obj)
{

   // Find and erase element
   for (int i = 0 ; i < m_data.size() ; i++) {
      if (m_data[i] == obj) {

         // Indicate that rows are begin removed
         QModelIndex index;
         //beginRemoveRows(index, i, i);
         beginResetModel();

         // Remove data
         m_data.erase(m_data.begin() + i);

         // Indicate done removing rows
         //endRemoveRows();
         endResetModel();

         break;
      }
   }

}

/*---------------------------------------------------------------------------*/

int TreeViewModel::rowCount(const QModelIndex& parent) const
{

   // If parent index is not valid the current location is the root
   // Otherwise, get the requested data object
   AbstractObject* item = NULL;
   if (!parent.isValid()) {
      return m_data.size();
   }
   else {
      item = static_cast<AbstractObject*>(parent.internalPointer());
   }

   // Determine if item is a Group
   try {

      // Determine if item is a Group; if so, return its number of children
      AbstractGroup* group = dynamic_cast<AbstractGroup*>(item);
      if (group != NULL) {
         return group -> getNumberOfChildren();
      }

   }
   catch(...) {

   }

   // Item has no children
   return 0;

}

/*---------------------------------------------------------------------------*/
