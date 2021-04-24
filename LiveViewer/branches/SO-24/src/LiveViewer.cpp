/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <LiveViewer.h>

/*---------------------------------------------------------------------------*/

LiveViewer::LiveViewer(QWidget* parent, Qt::WFlags flags)
: QMainWindow(parent, flags)
{

   // Initialize all pointers to NULL
   initializeToNULL();
	
   // Initialize GUI
   initializeGUI();

}

/*---------------------------------------------------------------------------*/

void LiveViewer::closeEvent(QCloseEvent* event)
{
	
   Q_UNUSED(event);
	
   // Quit
   QCoreApplication::quit();
	
}

/*---------------------------------------------------------------------------*/

void LiveViewer::createActions()
{
	
   // Preferences action
   m_preferencesAction = new QAction(tr("Preferences..."), this);
   connect(m_preferencesAction, SIGNAL(triggered()),
           this, SLOT(showPreferences()));
	
   // Exit action
   m_exitAction = new QAction(tr("Exit"), this);
   connect(m_exitAction, SIGNAL(triggered()),
           this, SLOT(exitApplication()));
	
   // Help menu actions
   m_aboutAction = new QAction(tr("About..."), this);
   connect(m_aboutAction, SIGNAL(triggered()),
           this, SLOT(showAbout()));

   // Tool bar start action
   m_startAction = new QAction(QIcon(":images/start.png"),
                               tr("Start"), this);
   connect(m_startAction, SIGNAL(triggered()),
           this, SLOT(startThread()));

   // Tool bar stop action
   m_stopAction = new QAction(QIcon(":images/stop.png"),
                              tr("Stop"), this);
   connect(m_stopAction, SIGNAL(triggered()),
           this, SLOT(stopThread()));

   //color transfer function change actions
   connect(m_colorTransferFunctionEditorWidget, SIGNAL(requestAutoLevels()),
		   this, SLOT(updateAutoLevels()));
   connect(m_colorTransferFunctionEditorWidget,
		   SIGNAL(requestPredefinedColor(QString)),
		   this, SLOT(setPredefindedColor(QString)) );
   connect(m_colorTransferFunctionEditorWidget, SIGNAL(transferFunctionUpdated(ColorTransferFunction)),
		   this, SLOT(updateColorTransferFunction(ColorTransferFunction)));
}

/*---------------------------------------------------------------------------*/

void LiveViewer::createDockWidgets()
{
	   m_dockColorWidget = new QDockWidget(tr("Color Editor"), this);
	   m_dockColorWidget -> setEnabled(true);
	   m_dockColorWidget -> setAllowedAreas(Qt::AllDockWidgetAreas);
	   m_dockColorWidget -> setWidget(m_colorTransferFunctionEditorWidget);
	   m_menuView -> addAction(m_dockColorWidget -> toggleViewAction());
	   addDockWidget(Qt::LeftDockWidgetArea, m_dockColorWidget);
      m_dockColorWidget->resize(200,800);
}

/*---------------------------------------------------------------------------*/

void LiveViewer::createMenuBar()
{
	
   // Menu bar
   m_menu = new QMenuBar(this);

   // File menu
   m_menuFile = new QMenu(tr("File"));
   m_menuFile -> addAction(m_preferencesAction);
   m_menuFile -> addSeparator();
   m_menuFile -> addAction(m_exitAction);

   // View menu
   m_menuView = new QMenu(tr("View"));

   // Help menu
   m_menuHelp = new QMenu(tr("Help"));
   m_menuHelp -> addAction(m_aboutAction);

   // Add menus
   m_menu -> addMenu(m_menuFile);
   m_menu -> addMenu(m_menuView);
   m_menu -> addMenu(m_menuHelp);
	
   // Set menu bar
   setMenuBar(m_menu);

}

/*---------------------------------------------------------------------------*/

void LiveViewer::createStatusBar()
{

   // Create status bar
   m_statusBar = new QStatusBar();

   // Add status bar
   setStatusBar(m_statusBar);

}

/*---------------------------------------------------------------------------*/

void LiveViewer::createToolBar()
{

   // Create toolbar
   m_toolbar = new QToolBar(this);
   m_toolbar -> setFloatable(false);
   m_toolbar -> setMovable(false);

   // Add toolbar actions
   m_toolbar -> addAction(m_startAction);
   m_toolbar -> addAction(m_stopAction);

   // Set toolbar
   addToolBar(m_toolbar);

}

/*---------------------------------------------------------------------------*/

void LiveViewer::exitApplication()
{

   // Quit
   close();
	
}

/*---------------------------------------------------------------------------*/

void LiveViewer::initializeGUI()
{
   Q_INIT_RESOURCE(GStar);
   // Set wait cursor
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

   // Set window title and icon
   setWindowTitle(tr("ScanOcean - LiveViewer Prototype"));

   // Make window a decent size
   resize(1024, 768);

   // Show window and force update the view
   show();

   // Splash screen
   Splash splash(this);
   splash.show();
   splash.appendMessage(tr("Initializing..."));
   QCoreApplication::processEvents();
   splash.appendMessage(tr("Creating GUI..."));
   QCoreApplication::processEvents();

   //Create the Color Transfer Function
   m_colorTransferFunctionEditorWidget = new ColorTransferFunctionEditor();
   m_colorTransferFunctionEditorWidget -> setTotalRange(0.0, 255.0);
   m_colorTransferFunctionEditorWidget -> setMaximumWidth(250);

   // Create actions
   createActions();
	
   // Create menu bar
   createMenuBar();

   // Create status bar
   createStatusBar();

   // Create tool bar
   createToolBar();

   // Create dock widgets
   createDockWidgets();

   // Central widget - this is where area detector images are shown
   m_iview = new ImageViewWidget();
   setCentralWidget(m_iview);

   // Update controls
   m_startAction -> setEnabled(true);
   m_stopAction -> setEnabled(false);

   // Force a redraw
   repaint();
   QCoreApplication::processEvents();

   // Show message
   splash.appendMessage(tr("Ready..."));
   QCoreApplication::processEvents();

   // Hide splash screen and restore cursor
   splash.hide();
   QApplication::restoreOverrideCursor();

}

/*---------------------------------------------------------------------------*/

void LiveViewer::initializeToNULL()
{

   m_preferencesAction = NULL;
   m_exitAction = NULL;
   m_aboutAction = NULL;
   m_startAction = NULL;
   m_stopAction = NULL;
	
   m_menu = NULL;
   m_menuFile = NULL;
   m_menuView = NULL;
   m_menuWindow = NULL;
   m_menuHelp = NULL;

   m_splashAbout = NULL;
   m_statusBar = NULL;
   m_toolbar = NULL;

   m_iview = NULL;

   m_sourceStage = NULL;
   m_processStage = NULL;
   m_displayStage = NULL;

   m_sourceBuffer = NULL;
   m_rgbaBuffer = NULL;

}

/*---------------------------------------------------------------------------*/

void LiveViewer::resizeEvent(QResizeEvent* event)
{
	
   Q_UNUSED(event)

}

/*---------------------------------------------------------------------------*/

void LiveViewer::showAbout()
{

   // New about screen
   if (m_splashAbout == NULL) {
      m_splashAbout = new Splash(this, Qt::Popup, true);
   }

   // Show and add message
   m_splashAbout -> setWindowModality(Qt::ApplicationModal);
   m_splashAbout -> show();
   m_splashAbout -> clear();
   m_splashAbout -> appendMessage(tr("Created by"));
   m_splashAbout -> appendMessage(tr("Software Services Group"));
   m_splashAbout -> appendMessage(tr("Advanced Photon Source"));
   m_splashAbout -> appendMessage(tr("Argonne National Laboratory"));
   m_splashAbout -> appendMessage(tr(""));
   m_splashAbout -> appendMessage(tr("Copyright (c) 2012"));
   m_splashAbout -> appendMessage(tr("UChicago Argonne, LLC"));
   m_splashAbout -> appendMessage(tr(""));
   m_splashAbout -> appendMessage(tr("Credits"));
   m_splashAbout -> appendMessage(tr("Nicholas Schwarz"));
   m_splashAbout -> appendMessage(tr("Faisal Khan"));
   m_splashAbout -> appendMessage(tr("John Hammonds"));

}

/*---------------------------------------------------------------------------*/

void LiveViewer::showPreferences()
{

   // Show preferences dialog with current settings
   PreferencesDialog* dialog = new PreferencesDialog(this, Qt::Dialog);
   dialog -> setPreferences(&m_preferences);
   dialog -> exec();

//   // Update with current settings
//   if (dialog -> exec() == QDialog::Accepted) {
//
//      // Update things if user clicks OK
//      QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
//      QApplication::restoreOverrideCursor();
//
//   }

   // Delete dialog
   delete dialog;

}

/*---------------------------------------------------------------------------*/

void LiveViewer::startThread()
{

   // Set wait cursor
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

   // Create data buffers for pipeline
   m_sourceBuffer = new Buffer(25, 5000000);
   m_rgbaBuffer = new Buffer(25, 5000000);

   // Create detector source stage
   m_sourceStage = new DemoSourceStage();
   m_sourceStage -> setOutputBuffer(m_sourceBuffer);

   // Create processing stage
   m_processStage = new ColorLevelsProcessStage();
   m_processStage -> setInputBuffer(m_sourceBuffer);
   m_processStage -> setOutputBuffer(m_rgbaBuffer);
   m_processStage -> setColorTransferFunction(m_colorTransferFunctionEditorWidget->getColorTransferFunction());

   // Create final stage for display
   m_displayStage = new DisplayStage();
   m_displayStage -> setInputBuffer(m_rgbaBuffer);

   // Connect display stage to slot
   connect(m_displayStage, SIGNAL(newFrame()),
           this, SLOT(updateFrame()));

   // Start everything, in reverse order
   m_displayStage -> start();
   m_processStage -> start();
   m_sourceStage -> start();

   // Update controls
   m_startAction -> setEnabled(false);
   m_stopAction -> setEnabled(true);

   // Restore cursor
   QApplication::restoreOverrideCursor();

}

/*---------------------------------------------------------------------------*/

void LiveViewer::stopThread()
{

   // Set wait cursor
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

   // Disconnect display stage from slot
   connect(m_displayStage, SIGNAL(newFrame()),
           this, SLOT(updateFrame()));

   // Stop everything
   m_sourceStage -> stop();
   m_processStage -> stop();
   m_displayStage -> stop();

   // Clean-up stages
   if (m_sourceStage != NULL) {
      delete m_sourceStage;
      m_sourceStage = NULL;
   }
   if (m_processStage != NULL) {
      delete m_processStage;
      m_processStage = NULL;
   }
   if (m_displayStage != NULL) {
      delete m_displayStage;
      m_displayStage = NULL;
   }

   // Clean up buffers
   if (m_sourceBuffer != NULL) {
      delete m_sourceBuffer;
      m_sourceBuffer = NULL;
   }
   if (m_rgbaBuffer != NULL) {
      delete m_rgbaBuffer;
      m_rgbaBuffer = NULL;
   }

   // Update controls
   m_startAction -> setEnabled(true);
   m_stopAction -> setEnabled(false);

   // Restore cursor
   QApplication::restoreOverrideCursor();

}

/*---------------------------------------------------------------------------*/

void LiveViewer::updateFrame()
{

   // Get image from source
   QImage img = m_displayStage -> getImage();

   // Create pixmap from image
   m_iview -> scene() -> setPixmap(
      QPixmap::fromImage(img.convertToFormat(QImage::Format_RGB32)));

}

/*---------------------------------------------------------------------------*/

void LiveViewer::updateAutoLevels(){
   if (m_processStage != NULL)
   {
      double imageMin = m_processStage->getImageMin();
      double imageMax = m_processStage->getImageMax();
      double rangeMin = m_processStage->getRangeMin();
      double rangeMax = m_processStage->getRangeMax();

      m_colorTransferFunctionEditorWidget->setTotalRange(rangeMin, rangeMax);
      m_colorTransferFunctionEditorWidget->setSubRange(imageMin, imageMax);
   }
}

/*---------------------------------------------------------------------------*/

void LiveViewer::setPredefindedColor(QString color){
	printf("set a predefined color \n");
}

/*---------------------------------------------------------------------------*/

void LiveViewer::updateColorTransferFunction(ColorTransferFunction ctf){
   if (m_processStage != NULL)
   {
	   m_processStage -> setColorTransferFunction(m_colorTransferFunctionEditorWidget->getColorTransferFunction());
   }
}
