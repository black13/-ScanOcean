/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef ROI_TABLE_WIDGET_H
#define ROI_TABLE_WIDGET_H

/*---------------------------------------------------------------------------*/

#include <ColorListComboBoxDelegate.h>
#include <ROITableModel.h>

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
    */
   ROITableWidget(ROITableModel* model, QWidget* parent = 0);

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
    * Hide the add, remove and copy buttons.
    */
   void hideButtons();

   /**
    * Indicate whether ROIs are enabled or not.
    */
   bool isEnabled();

   /**
    * Get the model associated with this view.
    *
    * @return the model associated with this view
    */
   ROITableModel* getModel();

   /**
    * Set the model associated with this view.
    *
    * @param model - the new model for this view
    */
   void setModel(ROITableModel* model);

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
   ROITableModel* m_model;

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

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
