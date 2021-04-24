/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TABLE_VIEW_MODEL_H
#define TABLE_VIEW_MODEL_H

/*---------------------------------------------------------------------------*/

#include <DStar.h>

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

/*---------------------------------------------------------------------------*/

/**
 * @brief The TableViewModel class provides the Qt model for use with
 * QTableView in the TableView class.
 *
 * TableViewModel inherits from QAbstractTableModel and provides the model for
 * use with a Qt view. It is used internally by TableView as the model
 * required by QTableView for displaying selections of DStar data objects in a
 * table.
 *
 * The Qt method QAbstractItemModel::setData() is not reimplemented. Use the
 * overridden setData() instead. QAbstractItemModel::setData() may be
 * implemented in the future.
 */
class TableViewModel
: public QAbstractTableModel
{

   Q_OBJECT

public:

   /**
    * Constructor.
    *
    * @param parent the parent Qt object for this object.
    */
   TableViewModel(QObject* parent = 0);

   /**
    * Destructor
    */
   ~TableViewModel();

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
   int rowCount(const QModelIndex& parent = QModelIndex()) const;

   /**
    * Set data storage order to column major.
    */
   void setColumnMajor();

   /**
    * Set the data used in the model.
    *
    * Data is passed to the model as a 1D array of chars in row-major order.
    * The model determines the number of chars that create one element using
    * the type passed in as the second parameter. The width and height are
    * determined via the parameters to setDisplayDimensions().
    *
    * Use this instead of QAbstractItemModel::setData().
    *
    * @param arr array of data elements for the model
    * @param type type of data elements in the array
    */
   void setData(boost::shared_array<char> arr, dstar::DataType type);

   /**
    *
    *
    * @param v the vertical extent
    * @param h the horizontal extent
    */
   void setDisplayDimensions(int v, int h);

   /**
    * Set data storage order to row major.
    */
   void setRowMajor();

private:

   /**
    * The actual data as an array of chars.
    */
   boost::shared_array<char> m_data;

   /**
    * Height and width of the data.
    * m_displayDims[0] = height
    * m_displayDims[1] = width
    */
   int m_displayDims[2];

   /**
    * Data is column major, not row major
    */
   bool m_isColumnMajor;

   /**
    * Data type stored in m_data.
    */
   dstar::DataType m_type;

   /**
    * Is the data valid?
    */
   bool m_validFlag;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
