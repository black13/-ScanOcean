/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TREE_VIEW_MODEL_H
#define TREE_VIEW_MODEL_H

/*---------------------------------------------------------------------------*/

#include <DStar.h>

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <boost/shared_ptr.hpp>
#include <vector>

/*---------------------------------------------------------------------------*/

/**
 * @brief The TreeViewModel class provides the Qt model for use with QTreeView
 * in the TreeView class.
 *
 * TreeViewModel inherits from QAbstractItemModel and provides the model for
 * use with a Qt view. It is used internally by TreeView as the model
 * required by QTreeView for displaying DStar data objects as a tree. The
 * TreeViewModel specific methods addData() and removeData() are used to add
 * and remove DStar data objects from the model.
 *
 * The Qt method QAbstractItemModel::setData() is not reimplemented. Use
 * addData() instead. QAbstractItemModel::setData() may be implemented in
 * the future.
 */
class TreeViewModel
: public QAbstractItemModel
{

   Q_OBJECT

public:

   /**
    * Constructor.
    *
    * @param parent the parent Qt object for this object.
    */
   TreeViewModel(QObject* parent = 0);

   /**
    * Destructor
    */
   ~TreeViewModel();

   /**
    * Add a DStar data object to the model.
    *
    * Use this instead of QAbstractItemModel::setData().
    *
    * @param data the DStar data object to add.
    */
   void addData(boost::shared_ptr<dstar::AbstractObject> data);

   /**
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   int columnCount(const QModelIndex& parent = QModelIndex()) const;

   /**
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   QVariant data(const QModelIndex& index, int role) const;

   /**
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   Qt::ItemFlags flags(const QModelIndex& index) const;

   /**
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   QVariant headerData(int section,
                       Qt::Orientation orientation,
                       int role = Qt::DisplayRole) const;

   /**
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   QModelIndex index(int row,
                     int column,
                     const QModelIndex& parent = QModelIndex()) const;

   /**
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   QModelIndex parent(const QModelIndex& index) const;

   /**
    * Remove a DStar data object from the model.
    *
    * @param data the DStar data object to remove.
    */
   void removeData(boost::shared_ptr<dstar::AbstractObject> obj);

   /**
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   int rowCount(const QModelIndex& parent = QModelIndex()) const;

private:

   /**
    * Master list of data objects.
    */
   std::vector<boost::shared_ptr<dstar::AbstractObject> > m_data;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
