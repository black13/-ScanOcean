/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef LIVE_VIEWER_H
#define LIVE_VIEWER_H

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

#include <ImageViewWidget.h>
#include <Preferences.h>
#include <PreferencesDialog.h>
#include <Splash.h>
#include <ImagePropertiesWidget.h>

#include <AreaDetectorSourceStage.h>
#include <Array.h>
#include <Buffer.h>
#include <ColorLevelsProcessStage.h>
#include <DemoSourceStage.h>
#include <DisplayStage.h>


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
   LiveViewer(QWidget* parent = 0, Qt::WFlags flags = 0);

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

   /**
    * Start capture threads
    */
   void startThread();

   /**
    * Stop capture threads
    */
   void stopThread();

   /**
    * Update frame slot
    */
   void updateFrame(const Array* imageData);

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
   QAction* m_startAction;
   QAction* m_stopAction;

   // Menu
   QMenuBar* m_menu;
   QMenu* m_menuFile;
   QMenu* m_menuView;
   QMenu* m_menuWindow;
   QMenu* m_menuHelp;

   /**
    * Application preferences/settings
    */
   Preferences m_preferences;

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
    * Image view for displaying detector images
    */
   ImageViewWidget* m_iview;

   /**
    * Source
    */
   AreaDetectorSourceStage* m_sourceStage;

   /**
    * Process
    */
   ColorLevelsProcessStage* m_processStage;

   /**
    * Display stage
    */
   DisplayStage* m_displayStage;

   /**
    * Source buffer
    */
   Buffer* m_sourceBuffer;

   /**
    * RGBA buffer
    */
   Buffer* m_rgbaBuffer;

   /**
    * Dock widget for image properties.
    */
   QDockWidget* m_dockImageProps;

   /**
    * Image properties widget.
    */
   ImagePropertiesWidget* m_imagePropertiesWidget;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
