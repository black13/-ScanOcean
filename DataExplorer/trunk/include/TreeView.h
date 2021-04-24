/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TREE_VIEW_H
#define TREE_VIEW_H

/*---------------------------------------------------------------------------*/

#include <DStar.h>
#include <TreeViewModel.h>

#include <QAction>
#include <QContextMenuEvent>
#include <QHeaderView>
#include <QMenu>
#include <QModelIndex>
#include <QTreeView>
#include <QTreeWidgetItem>
#include <QWidget>

#include <boost/shared_ptr.hpp>

/*---------------------------------------------------------------------------*/

/**
 * @brief The TreeView class provides a tree view for DStar objects.
 */
class TreeView
: public QTreeView, public dstar::AbstractView
{

   Q_OBJECT

public:

   /**
    * Constructor
    *
    * @param parent the parent Qt widget.
    */
   TreeView(QWidget* parent = 0);

   /**
    * Destructor
    */
   ~TreeView();

   /**
    * Adds a DStar data object to the list of subjects it is observing. This
    * method is called internally by AbstractView when a data object is added
    * via AbstractView::addDataObject(). It is implemented so the subclass
    * can update appropriately.
    *
    * This is the implementation specified by AbstractView.
    *
    * @param obj The data object being added.
    */
   void dataAdded(boost::shared_ptr<dstar::AbstractObject> obj);

   /**
    * Removes a DStar data object from the list of subjects it is observing.
    * This method is called internally by AbstractView when a data object is
    * removed via AbstractView::removeDataObject(). It is implemented so the
    * subclass can update appropriately.
    *
    * This is the implementation specified by AbstractView.
    *
    * @param obj The data object being removed.
    */
   void dataRemoved(boost::shared_ptr<dstar::AbstractObject> obj);

protected:

   /**
    * Display context menu for the selected item. This is overridden from
    * QTreeView::contextMenuEvent().
    *
    * @param event the QContextMenuEvent from Qt.
    */
   void contextMenuEvent(QContextMenuEvent* event);

private slots:

   /**
    * Handle Close from context menu.
    */
   void closeData();

   /**
    * Handle Open Image View from context menu.
    */
   void imageViewClicked();

   /**
    * Handle updated selection from QTreeView. This is overridden from
    * QTreeView.
    *
    * @param selected the currently selected items
    * @param deselected the recenetly deselected items
    */
   void selectionUpdated(const QItemSelection& selected,
                         const QItemSelection& deselected);

   /**
    * Handle Open Table View from context menu.
    */
   void tableViewClicked();

signals:

   /**
    * Request that the specified data object be closed.
    *
    * @param obj the data object to close.
    */
   void dataClosed(boost::shared_ptr<dstar::AbstractObject> obj);

   /**
    * Open an ImageView with the specified data object as its source.
    *
    * @param obj the data object to view with a ImageView.
    */
   void imageViewRequested(boost::shared_ptr<dstar::AbstractObject> obj);

   /**
    * Notify the selection has been changed to the specified data object.
    * Other views, such as the PropertiesView, should be updated.
    *
    * @param obj the currently selected data object in the tree.
    */
   void selectionChanged(boost::shared_ptr<dstar::AbstractObject> obj);

   /**
    * Open a TableView with the specified data object as its source.
    *
    * @param obj the data object to view with a TableView.
    */
   void tableViewRequested(boost::shared_ptr<dstar::AbstractObject> obj);

private:

   /**
    * Model index for currently selected item
    */
   QModelIndex m_index;

   /**
    * The tree view model
    */
   TreeViewModel* m_model;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
