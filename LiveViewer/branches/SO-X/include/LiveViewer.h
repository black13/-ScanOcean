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
#include <QItemSelectionModel>
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
#include <AverageIntensityProcessStage.h>
#include <Buffer.h>
#include <ColorLevelsProcessStage.h>
#include <DemoSourceStage.h>
#include <DisplayStage.h>
#include <ColorTransferFunctionEditor.h>
#include <ColorTransferFunction.h>
#include <ROITableWidget.h>
#include <ROITableModel.h>
#include <PVFinalStage.h>

using gstar::ColorTransferFunction;
using gstar::ColorTransferFunctionEditor;

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
    * Set the color transfer function to a predefined map
    */
   void setPredefindedColor(QString color);

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

   /**
    * Update the auto levels for the color transfer function
    */
   void updateAutoLevels();

   /**
    * Update the color transfer function
    */
   void updateColorTransferFunction(ColorTransferFunction ctf);

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

   bool m_isCapturing;

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


   // Main GUI components

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

   /**
    * Image view for displaying detector images
    */
   ImageViewWidget* m_iview;

   /**
    * Splash screen
    */
   gstar::Splash* m_splashAbout;


   // GUI components

   /**
    * Widget for CTF
    */
   ColorTransferFunctionEditor* m_colorTransferFunctionEditorWidget;

   /**
    * Dock widget for area detector controls
    */
   QDockWidget* m_dockColorWidget;

   /**
    * ROI table model
    */
   ROITableModel* m_roiTableModel;

   /**
    * ROI table widget
    */
   ROITableWidget* m_roiTableWidget;

   /**
    * ROI selection model
    */
   QItemSelectionModel* m_roiSelectionModel;

   /**
    * Dock widget for ROIs
    */
   QDockWidget* m_dockROI;

   /**
    * Image properties widget
    */
   ImagePropertiesWidget* m_imagePropertiesWidget;

   /**
    * Dock widget for image properties.
    */
   QDockWidget* m_dockImageProps;


   // Pipeline components

   /**
    * Source
    */
   AreaDetectorSourceStage* m_sourceStage;

   /**
    * Process
    */
   ColorLevelsProcessStage* m_processStage;

   /**
    * Average intensity process stage
    */
   AverageIntensityProcessStage* m_averageIntensityStage;

   /**
    * PV write-out stage.
    */
   PVFinalStage* m_pvFinalStage;

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
    * Average intensity buffer
    */
   Buffer* m_avgIntBuffer;

   /**
    * ROI masks
    */
   std::vector<Array*> m_roiMasks;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
