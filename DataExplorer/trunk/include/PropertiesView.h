/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef PROPERTIES_VIEW_H
#define PROPERTIES_VIEW_H

/*---------------------------------------------------------------------------*/

#include <DStar.h>

#include <QLabel>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QString>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>
#include <QHeaderView>

#include <string>
#include <vector>

/*---------------------------------------------------------------------------*/

/**
 * @brief The PropertiesView class displays DStar object properties.
 *
 * The PropertiesView class inherits from dstar::AbstractView. It can only
 * display properties from one data object at a time. Users should remove the
 * previous data object before adding a new one.
 */
class PropertiesView
: public QWidget, public dstar::AbstractView
{

   Q_OBJECT

public:

   /**
    * Constructor
    *
    * @param parent the Qt parent widget.
    */
   PropertiesView(QWidget* parent = 0);

   /**
    * Destructor
    */
   ~PropertiesView();

   /**
    * Clear the PropertiesView display.
    */
   void clear();

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
    * @param obj The data object being removed.
    */
   void dataRemoved(boost::shared_ptr<dstar::AbstractObject> obj);

private:

   /**
    * The model used to store properties as strings.
    */
   QStandardItemModel* m_model;

   /**
    * The table used to display properties. It uses a QStandardItemModel.
    */
   QTableView* m_table;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
