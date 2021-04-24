/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef PREFERENCES_DIALOG_H
#define PREFERENCES_DIALOG_H

/*---------------------------------------------------------------------------*/

#include <QDialog>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

class Preferences;
class PreferencesPV;
class PreferencesROI;
class PreferencesDialog;
class PreferencesHist;

/*---------------------------------------------------------------------------*/

/**
 * @brief Dialog for displaying detailed preferences pages.
 */
class PreferencesDialog
: public QDialog
{

   Q_OBJECT

public:

   /**
    * Constructor
    *
    * @param parent - the Qt parent widget
    * @param f - Qt window flags
    */
   PreferencesDialog(QWidget* parent = 0, Qt::WindowFlags f = 0);

   /**
    * Set preferences object
    *
    * @param preferences - preferences object
    */
   void setPreferences(Preferences* preferences);

protected slots:

   /**
    * This internal slot is called when the item in the category list is
    * changed.
    *
    * @param current - the current preferences item selected in the category
    *                  list on the left of the dialog
    * @param previous - the previously selected item in the category list
    */
   void changePage(QListWidgetItem* current, QListWidgetItem* previous);

private slots:

   /**
    * Overridden accept() method.
    *
    * Process changes when user clicks 'OK' button.
    */
   void accept();

   /**
    * Overridden reject() method.
    *
    * Process when user clicks 'Cancel' button.
    */
   void reject();

private:

   /**
    * OK button
    */
   QPushButton* m_btnOK;

   /**
    * Cancel button
    */
   QPushButton* m_btnCancel;

   /**
    * Main layout
    */
   QVBoxLayout* m_layout;

   /**
    * Contents
    */
   QListWidget* m_contentsWidget;

   /**
    * Page for individual categories
    */
   QStackedWidget* m_pagesWidget;

   /**
    * Preferences page for process variables
    */
   PreferencesPV* m_pvPage;

   /**
    * Preferences page for histogram
    */
   PreferencesHist* m_histPage;

   /**
    * Preferences page for ROI settings.
    */
   //PreferencesROI* m_roiPage;

   /**
    * Preferences
    */
   Preferences* m_preferences;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
