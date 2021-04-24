/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

/*---------------------------------------------------------------------------*/

#include <DStar.h>
#include <ComboBox.h>
#include <RangeWidget.h>
#include <Selection.h>
#include <TableViewModel.h>

#include <QApplication>
#include <QHeaderView>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <utility>
#include <vector>

/*---------------------------------------------------------------------------*/

/**
 * @brief The TableView class ...
 */
class TableView
: public QWidget, public dstar::AbstractView
  {

   Q_OBJECT

public:

   /**
    * Constructor
    *
    * @param parent the Qt parent widget.
    */
   TableView(QWidget* parent = 0);

   /**
    * Destructor
    */
   ~TableView();

   /**
    * Adds a DStar data object to the list of subjects it is observing. This
    * method reads the data object's properties via
    * AbstracObject::getProperties() and displays them.
    *
    * This method is called internally by AbstractView when a data object is
    * added via AbstractView::addDataObject(). It is implemented so the
    * subclass can update appropriately.
    *
    * This is the implementation specified by AbstractView.
    *
    * @param obj The data object being added.
    */
   void dataAdded(boost::shared_ptr<dstar::AbstractObject> obj);

   /**
    * Removes a DStar data object from the list of subjects it is observing.
    * This simply calls clear().
    *
    * This method is called internally by AbstractView when a data object is
    * removed via AbstractView::removeDataObject(). It is implemented so the
    * subclass can update appropriately.
    *
    * This is the implementation specified by AbstractView.
    *
    * For TableView, it doesn't actually do anything.
    *
    * @param obj The data object being removed.
    */
   void dataRemoved(boost::shared_ptr<dstar::AbstractObject> obj);

private slots:

   /**
    * Handle change to a ComboBox. Update value in corresponding ComboBox
    * so there's no overlaps and update the rank list.
    *
    * @param id id of ComboBox that was changed.
    * @param oldI the old selected index value.
    * @param newI the new selected index value.
    */
   void updateCombo(int id, int oldI, int newI);

   /**
    * Update min and max extents in all RangeWidgets.
    */
   void updateRange();

   /**
    * Handle RangeWidget change.
    *
    * @param value the new value of the RangeWidget.
    * @param id the id of the widget that changed.
    */
   void rangeChanged(int value, int id);

   /**
    * Update the table with the current selection.
    */
   void update();

   /**
    * Update the selection based on values in ComboBoxes and RangeWidgets
    * stored in the rank list.
    */
   void updateSelection();

private:

   /**
    * Shared pointer to actual data
    */
   boost::shared_ptr<dstar::AbstractData> m_data;

   /**
    * Data dimension extents; deleted by ~TableView()
    */
   unsigned long long* m_dims;

   /**
    * Flag to ignore the next widget update. This should be removed and
    * disconnect/connect called.
    */
   bool m_ignore;

   /**
    * List of combo boxes for dimension choices
    */
   QList<ComboBox*> m_listCombo;

   /**
    * List of range widgets
    */
   QList<RangeWidget*> m_listRange;

   /**
    * Ranks in the order in which they are displayed.
    */
   QList<unsigned long> m_listRank;

   /**
    * Table model
    */
   TableViewModel* m_model;

   /**
    * Table to display data properties
    */
   QTableView* m_propertiesTable;

   /**
    * Rank
    */
   unsigned long m_rank;

   /**
    * Current selection in data
    */
   dstar::Selection m_selCur;

   /**
    * Full extents of data as selection
    */
   dstar::Selection m_selFull;

   /**
    * Table to display data
    */
   QTableView* m_table;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
