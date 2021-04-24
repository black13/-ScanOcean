/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TOMO_UI_H
#define TOMO_UI_H

/*---------------------------------------------------------------------------*/

#include <QAction>
#include <QApplication>
#include <QCoreApplication>
#include <QDockWidget>
#include <QFileDialog>
#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>

#include <Preferences.h>
#include <PreferencesDialog.h>
#include <Splash.h>

/*---------------------------------------------------------------------------*/

/**
 * @brief The main LiveViewer user interface window.
 */
class LiveViewer
: public QMainWindow
{
	
   Q_OBJECT
	
public:
	
   /**
    * Constructor
    *
    * @param parent Qt's parent widget
    * @param Qt flags for window borders
    */
   LiveViewer(QWidget *parent = 0, Qt::WFlags flags = 0);

protected slots:

   /**
    * Reimplemented from QMainWindow. See Qt documentation.
    */
   void closeEvent(QCloseEvent* event);

   /**
    * Reimplemented from QMainWindow. See Qt documentation.
    */
   void resizeEvent(QResizeEvent* event);
	
private slots:

   /**
    * Slot that exits the application.
    */
   void exitApplication();

   /**
    * Show the about dialog.
    */
   void showAbout();

   /**
    * Show the preferences dialog.
    */
   void showPreferences();

private:
	
   /**
    * Create standard actions used on the menu bar.
    */
   void createActions();
	
   /**
    * Create dock widgets for standard tools that are always shown, including
    * the tree view and properties display.
    */
   void createDockWidgets();
	
   /**
    * Create and setup the menu bar and connections for standard actions.
    */
   void createMenuBar();
	
   /**
    * Create and setup the status bar.
    */
   void createStatusBar();

   /**
    * Create and setup the tool bar and connections for standard actions.
    */
   void createToolBar();

   /**
    * Initialize and setup all GUI components. Make certain initializeToNULL()
    * is called first. This method calls a number of create methods. It should
    * be called in the constructor.
    */
   void initializeGUI();
	
   /**
    * Initialize all pointers used in this class to NULL. This should be the
    * first thing called in the constructor.
    */
   void initializeToNULL();
  
private:
	
   // Menu actions
   QAction* m_preferencesAction;
   QAction* m_exitAction;
   QAction* m_aboutAction;

   // Menu
   QMenuBar* m_menu;
   QMenu* m_menuFile;
   QMenu* m_menuView;
   QMenu* m_menuWindow;
   QMenu* m_menuHelp;
   
   /**
    * Application preferences/settings
    */
   //Preferences m_preferences;

   /**
    * Splash screen
    */
   Splash* m_splashAbout;

   /**
    * Status bar
    */
   QStatusBar* m_statusBar;

   /**
    * Tool bar
    */
   QToolBar* m_toolbar;

   /**
    * Application preferences/settings
    */
   Preferences m_preferences;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
