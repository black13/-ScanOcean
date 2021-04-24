/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <TreeView.h>

using namespace dstar;
using boost::shared_ptr;

/*---------------------------------------------------------------------------*/

TreeView::TreeView(QWidget* parent)
: QTreeView(parent), AbstractView()
{

   // Hide headers
   header() -> hide();

   // Create a new model for the tree
   m_model = new TreeViewModel();

   // Set the model
   setModel(m_model);

   // Handle selections
   connect(selectionModel(),
           SIGNAL(selectionChanged(const QItemSelection&,
                                   const QItemSelection&)),
           this,
           SLOT(selectionUpdated(const QItemSelection&,
                                 const QItemSelection&)));

}

/*---------------------------------------------------------------------------*/

TreeView::~TreeView()
{
}

/*---------------------------------------------------------------------------*/

void TreeView::closeData()
{

   AbstractObject* parent = NULL;
   AbstractObject* item =
      static_cast<AbstractObject*>(m_index.internalPointer());

   // Find root item
   while (item != NULL) {
      parent = item;
      item = const_cast<AbstractObject*>((item -> getParent()).get());
   }

   // Emit dataClosed signal with root data item
   shared_ptr<AbstractObject> sptr = parent -> getAsSharedPtr();

   emit dataClosed(sptr);

}

/*---------------------------------------------------------------------------*/

void TreeView::contextMenuEvent(QContextMenuEvent* event)
{

   // Get item under click
   m_index = this -> indexAt(event -> pos());
   if (m_index.isValid()) {

      QMenu menu(this);

      QAction* openAction = new QAction(tr("Open Table View..."), this);
      connect(openAction, SIGNAL(triggered()),
              this, SLOT(tableViewClicked()));
      menu.addAction(openAction);

      AbstractData* castItem = NULL;
      try {
         castItem = dynamic_cast<AbstractData*>((AbstractObject*)
               m_index.internalPointer());
      }
      catch (...) {
         ;
      }
      if (castItem == NULL) {
         openAction -> setEnabled(false);
      }

      QAction* openImageAction = new QAction(tr("Open Image View..."), this);
      connect(openImageAction, SIGNAL(triggered()),
              this, SLOT(imageViewClicked()));
      menu.addAction(openImageAction);

      castItem = NULL;
      try {
         castItem = dynamic_cast<AbstractData*>((AbstractObject*)
               m_index.internalPointer());
      }
      catch (...) {
         ;
      }
      if (castItem == NULL) {
         openImageAction -> setEnabled(false);
      }
      else {
         if (castItem -> getRank() < 2) {
            openImageAction -> setEnabled(false);
         }
         if (castItem -> getType() == dstar::String) {
            openImageAction -> setEnabled(false);
         }
      }

      menu.addSeparator();

      QAction* expandAction = new QAction(tr("Expand All"), this);
      connect(expandAction, SIGNAL(triggered()), this, SLOT(expandAll()));
      menu.addAction(expandAction);

      QAction* collapseAction = new QAction(tr("Collapse All"), this);
      connect(collapseAction, SIGNAL(triggered()), this, SLOT(collapseAll()));
      menu.addAction(collapseAction);

      menu.addSeparator();

      QAction* closeAction = new QAction(tr("Close"), this);
      connect(closeAction, SIGNAL(triggered()), this, SLOT(closeData()));
      menu.addAction(closeAction);

      menu.exec(event -> globalPos());

   }

}

/*---------------------------------------------------------------------------*/

void TreeView::dataAdded(shared_ptr<AbstractObject> obj)
{

   // Add data to model
   m_model -> addData(obj);

}

/*---------------------------------------------------------------------------*/

void TreeView::dataRemoved(shared_ptr<AbstractObject> obj)
{

   // Remove item from data model
   m_model -> removeData(obj);

}

/*---------------------------------------------------------------------------*/

void TreeView::imageViewClicked()
{

   // Check for valid QModelIndex set in contextMenuEvent
   if (m_index.isValid()) {

      // Get the data object for the index
      AbstractObject* dataItem =
         static_cast<AbstractObject*>(m_index.internalPointer());

      // Emit view requested signal with shared_ptr
      emit imageViewRequested(dataItem -> getAsSharedPtr());

   }

}

/*---------------------------------------------------------------------------*/

void TreeView::selectionUpdated(const QItemSelection& selected,
                                const QItemSelection& deselected)
{

   // Check for selection
   if (selected.indexes().size() <= 0) {
      //emit selectionChanged(NULL);
      return;
   }

   // Get first selected index
   QModelIndex index = (selected.indexes()).at(0);

   // Get internal pointer
   AbstractObject* item =
      static_cast<AbstractObject*>(index.internalPointer());

   // Emit new selection
   shared_ptr<AbstractObject> sptr = item -> getAsSharedPtr();
   emit selectionChanged(sptr);

}


/*---------------------------------------------------------------------------*/

void TreeView::tableViewClicked()
{

   // Check for valid QModelIndex set in contextMenuEvent
   if (m_index.isValid()) {

      // Get the data object for the index
      AbstractObject* dataItem =
         static_cast<AbstractObject*>(m_index.internalPointer());

      // Emit view requested signal with shared_ptr
      emit tableViewRequested(dataItem -> getAsSharedPtr());

   }

}

/*---------------------------------------------------------------------------*/
