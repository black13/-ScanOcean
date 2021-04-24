/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef PREFERENCES_ROI_H
#define PREFERENCES_ROI_H

/*---------------------------------------------------------------------------*/

#include <QWidget>
#include <QHash>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QModelIndex>
#include <QItemSelection>

/*---------------------------------------------------------------------------*/

/**
 * @brief Preferences page for specifying mapping between ROI intensity values
 * and PV names for writing.
 */
class PreferencesROI
: public QWidget
{

   Q_OBJECT

public:

   /**
    * Constructor for creating preferences page.
    *
    * @param parent - the Qt parent widget
    */
   PreferencesROI(QWidget* parent = 0);

   /**
    * Destroy the instance
    */
   ~PreferencesROI();

   /**
    * Return a mapping between ROI regions and corresponding PVs.
    *
    * @return Sequential list of PVs for each region.
    */
   QList<QVariant> getROIPVs();

   /**
    * Set the PV names with index number referring to the ROI region.
    *
    * @param pvs - List of QVariant strings for PV names.
    */
   void setROIPVs(QList<QVariant> pvs);

private slots:

   /**
    * Add an empty row to the table.
    */
   void addTableRow();

   /**
    * Remove selected rows.
    *
    */
   void delTableRows();

   /**
    * Handle changes in user selection of table.
    */
   void selectionChanged(const QItemSelection& selected,
                         const QItemSelection& deselected);

private:

   /**
    * Layout the interface for this preferences page.
    */
   void setupGUI();

private:

   /**
    * Preferences table for assigning mapping between ROIs and PVs.
    */
   QTableView* m_pvTable;

   /**
    * A simple model supporting preferences table.
    */
   QStandardItemModel* m_pvTableModel;

   /**
    * Button for adding a new row.
    */
   QPushButton* m_addROIrow;

   /**
    * Button for removing selected rows.
    */
   QPushButton* m_delROIrow;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
