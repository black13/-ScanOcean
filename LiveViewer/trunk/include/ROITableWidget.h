/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef ROI_TABLE_WIDGET_H
#define ROI_TABLE_WIDGET_H

/*---------------------------------------------------------------------------*/

#include <ColorListComboBoxDelegate.h>
#include <Preferences.h>

#include <QCheckBox>
#include <QCoreApplication>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QVBoxLayout>
#include <QModelIndexList>
#include <QItemSelectionModel>
#include <QStringList>
#include <QWidget>

namespace gstar {
   class ROITableModel;
}

/*---------------------------------------------------------------------------*/

class ROITableWidget
: public QWidget
{

   Q_OBJECT

public:

   /**
    * Constructor
    *
    * @param model - ROI model on to which this object is a view
    * @param parent - parent Qt widget
    * @param pref   - System wide preferences object.
    *
    */
   ROITableWidget(gstar::ROITableModel* model, QWidget* parent = 0);

   /**
    * Clear the model and view
    */
   void clear();

   /**
    * Disable the ROI portion of the widget. The enable checkbox will still
    * function.
    */
   void disable();

   /**
    * Enable the ROI portion of the widget.
    */
   void enable();

   /**
    * Get the limit on number of ROIs that can be created.
    *
    * @return maximum number of ROIs
    */
   int getMaxROIs();

   /**
    * Get the model associated with this view.
    *
    * @return the model associated with this view
    */
   gstar::ROITableModel* getModel();

   /**
    * Get the base-name of the PVs that are added to the table.
    *
    * @return base name for PVs.
    */
   QString& getPVBaseName();

   /**
    * Hide the add, remove and copy buttons.
    */
   void hideButtons();

   /**
    * Indicate whether ROIs are enabled or not.
    */
   bool isEnabled();

   /**
    * Set the limit on number of ROIs that can be created.
    *
    * @param limit - maximum number of ROIs, default is unlimited.
    */
   void setMaxROIs(int limit);

   /**
    * Set the model associated with this view.
    *
    * @param model - the new model for this view
    */
   void setModel(gstar::ROITableModel* model);

   /**
    * Set the default base-name of the PVs that are added to the table.
    *
    * @param basename - base name for PVs.
    */
   void setPVBaseName(QString& basename);

   /**
    * Set the selection model for this view.
    *
    * @param selectionModel - the new selection model for this view
    */
   void setSelectionModel(QItemSelectionModel* selectionModel);

signals:

   /**
    * Signal emitted when ROIs are enabled or disabled.
    *
    * @param state - true when ROIs become enabled, false when ROIs become
    *                disabled.
    */
   void enabledROI(bool state);

private:

   /**
      * Make a call to underlying model for adding a ROI to the table.
      *
      * @param color - ROI color name
      * @param x - x position
      * @param y - y position
      * @param w - width
      * @param h - height
      */
   void addROI(QString color,
               double x, double y,
               double w, double h);

   /**
    * Check ROI count limit.
    *
    * @return true if we haven't exceeded the ROI count limit, false otherwise.
   */
   bool canAddROI();

private slots:

   /**
    * Internal slot to add a ROI. Called by the add ROI button.
    */
   void addROI();

   /**
    * Internal slot to copy the selected ROI. Called by the copy ROI button.
    */
   void copyROI();

   /**
    * Internal slot to enable/disable ROIs called by the enable check box.
    *
    * @param state - true to enable, false to disable.
    */
   void enabled(bool state);

   /**
    * Internal slot to remove the selected ROI. Called by the remove
    * ROI button.
    */
   void removeROI();

   /**
    * Internal slot called when the selection model indicates the selection
    * is changed. This slot changes the view to reflect the new selection.
    */
   void selectionChanged(const QItemSelection &selected,
                         const QItemSelection &deselected);

private:

   /**
    * Color box
    */
   ColorListComboBoxDelegate* m_delegate;

   /**
    * Model
    */
   gstar::ROITableModel* m_model;

   /**
    * Enabled
    */
   QCheckBox* m_ckEnable;

   /**
    * Table view
    */
   QTableView* m_table;

   /**
    * Add button
    */
   QPushButton* m_btnAdd;

   /**
    * Remove button
    */
   QPushButton* m_btnRemove;

   /**
    * Copy button
    */
   QPushButton* m_btnCopy;
   
   /**
    * Small list of colors to cycle through when new ROI is added
    */
   QStringList m_colors;

   /**
    * Index into color list for picking the next color
    */
   int m_colorIndex;

   /**
    * Total number of ROIs that can be defined using this widget.
    */
   int m_roiCountLimit;

   /**
    * Default base name for PVs.
    */
   QString m_pvBaseName;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
