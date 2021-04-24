/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <LiveViewer.h>

#include <AreaDetectorSourceStage.h>
#include <AverageIntensityProcessStage.h>
#include <Buffer.h>
#include <ColorLevelsProcessStage.h>
#include <DemoSourceStage.h>
#include <DisplayStage.h>
#include <PVFinalStage.h>
#include <ROI.h>
#include <Histogram.h>
#include <Array.h>
#include <ROITableWidget.h>
#include <PreferencesDialog.h>
#include <ImagePropertiesWidget.h>
#include <ColorTransferFunctionEditor.h>
#include <Splash.h>
#include <ImageViewWidget.h>
#include <ROITableModel.h>
#include <ROI.h>

using gstar::Array;
using gstar::Splash;
using gstar::ColorTransferFunctionEditor;
using gstar::ImageViewWidget;
using gstar::ROITableModel;
using gstar::ROI;

using std::vector;

/*---------------------------------------------------------------------------*/

LiveViewer::LiveViewer(QWidget* parent, Qt::WFlags flags)
: QMainWindow(parent, flags),
  m_isCapturing(false)
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
   connect(m_colorTransferFunctionEditorWidget, SIGNAL(transferFunctionUpdated(gstar::ColorTransferFunction)),
		   this, SLOT(updateColorTransferFunction(gstar::ColorTransferFunction)));

}

/*---------------------------------------------------------------------------*/

void LiveViewer::createDockWidgets()
{

   // Color dock
   m_dockColorWidget = new QDockWidget(tr("Color Editor"), this);
   m_dockColorWidget -> setEnabled(true);
   m_dockColorWidget -> setAllowedAreas(Qt::AllDockWidgetAreas);
   m_dockColorWidget -> setWidget(m_colorTransferFunctionEditorWidget);
   m_menuView -> addAction(m_dockColorWidget -> toggleViewAction());
   addDockWidget(Qt::LeftDockWidgetArea, m_dockColorWidget);
   m_dockColorWidget->resize(200,800);

   // ROI dock
   m_dockROI = new QDockWidget(tr("ROI"), this);
   m_dockROI -> setEnabled(true);
   m_dockROI -> setAllowedAreas(Qt::AllDockWidgetAreas);
   m_dockROI -> setWidget(m_roiTableWidget);
   m_menuView -> addAction(m_dockROI -> toggleViewAction());
   addDockWidget(Qt::RightDockWidgetArea, m_dockROI);

   // Image properties dock
   m_dockImageProps = new QDockWidget(tr("Image Properties"), this);
   m_dockImageProps -> setEnabled(true);
   m_dockImageProps -> setAllowedAreas(Qt::RightDockWidgetArea);
   m_dockImageProps -> setWidget(m_imagePropertiesWidget);
   m_menuView -> addAction(m_dockImageProps -> toggleViewAction());
   addDockWidget(Qt::RightDockWidgetArea, m_dockImageProps);

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

   // Use resources from GStar
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
   Splash splash(this, Qt::Popup, tr("LiveViewer"), false);
   splash.show();
   splash.appendMessage(tr("Initializing..."));
   splash.appendMessageAndProcess(tr("Creating GUI..."));

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

   // Central widget - this is where area detector images are shown
   m_iview = new ImageViewWidget();
   setCentralWidget(m_iview);

   // Widget for displaying image properties
   m_imagePropertiesWidget = new ImagePropertiesWidget(this);

   // ROI table model and widget
   m_roiTableModel = new ROITableModel();
   m_roiSelectionModel = new QItemSelectionModel(m_roiTableModel);
   m_roiTableWidget = new ROITableWidget(m_roiTableModel);
   m_roiTableWidget -> setSelectionModel(m_roiSelectionModel);
   m_roiTableWidget -> setMaxROIs(4);
   connect(m_roiTableWidget, SIGNAL(enabledROI(bool)),
           m_iview -> scene(), SLOT(enableROIs(bool)));

   // Add ROI model to scene
   m_iview -> scene() -> setROIModel(m_roiTableModel);
   m_iview -> scene() -> setROISelectionModel(m_roiSelectionModel);

   // Create dock widgets, add it after the central image.
   // That will ensure that dock does not take up much of the central space.
   createDockWidgets();

   // Update controls
   m_startAction -> setEnabled(true);
   m_stopAction -> setEnabled(false);

   // Force a redraw
   repaint();
   QCoreApplication::processEvents();

   // Show message
   splash.appendMessageAndProcess(tr("Ready..."));

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

   m_statusBar = NULL;
   m_toolbar = NULL;
   m_iview = NULL;
   m_splashAbout = NULL;

   m_colorTransferFunctionEditorWidget = NULL;
   m_dockColorWidget = NULL;
   m_roiTableModel = NULL;
   m_roiTableWidget = NULL;
   m_roiSelectionModel = NULL;
   m_dockROI = NULL;
   m_imagePropertiesWidget = NULL;
   m_dockImageProps = NULL;

   m_sourceStage = NULL;
   m_processStage = NULL;
   m_averageIntensityStage = NULL;
   m_displayStage = NULL;
   m_pvFinalStage = NULL;
   m_sourceBuffer = NULL;
   m_rgbaBuffer = NULL;
   m_avgIntBuffer = NULL;

   m_histogram = NULL;

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
      m_splashAbout = new Splash(this, Qt::Popup, tr("LiveViewer"), true);
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
   m_splashAbout -> appendMessageAndProcess(tr("Claude Saunders"));

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

   // Get number of ROIs
   int numberOfROIs = m_roiTableModel -> rowCount(QModelIndex());

   // Source buffer
   m_sourceBuffer = new Buffer(25, 5000000);

   // RGBA buffer
   m_rgbaBuffer = new Buffer(25, 10000000);

   // ROI mask buffers
   m_roiMasks.clear();
   for (int i = 0 ; i < numberOfROIs ; i++) {
      m_roiMasks.push_back(new Array(5000000));
   }

   // Average intensity buffers
   m_avgIntBuffer = new Buffer(25, numberOfROIs * sizeof(double));

   // Get masks
   for (int i = 0 ; i < numberOfROIs ; i++) {
      m_iview -> scene() -> getROIMask(i, *m_roiMasks[i]);
   }

   // Create detector source stage
   QString imagePV = m_preferences.readValueKey(
      Preferences::PVPrefixString).toString();
   m_sourceStage = new AreaDetectorSourceStage(imagePV.toAscii().constData());
   m_sourceStage -> setOutputBuffer(m_sourceBuffer);

   // Create histogram data strucutre
   double bins = m_preferences.readValueKey(Preferences::HISTBins).toDouble();
   m_histogram = new Histogram(bins);

   // Create processing stage
   m_processStage = new ColorLevelsProcessStage();
   m_processStage -> setInputBuffer(m_sourceBuffer);
   m_processStage -> setOutputBuffer(m_rgbaBuffer);
   m_processStage -> setColorTransferFunction(
      m_colorTransferFunctionEditorWidget->getColorTransferFunction());
   m_processStage->setHistogram(m_histogram);

   // Create average intensity stage
   m_averageIntensityStage = new AverageIntensityProcessStage();
   m_averageIntensityStage -> setInputBuffer(m_sourceBuffer);
   m_averageIntensityStage -> setOutputBuffer(m_avgIntBuffer);
   m_averageIntensityStage -> setMasks(m_roiMasks);

   // Create final stage for display
   m_displayStage = new DisplayStage();
   m_displayStage -> setInputBuffer(m_rgbaBuffer);

   // Create PV writing stage
   QList<ROI> roilist = m_roiTableModel -> getROIs();
   m_pvFinalStage = new PVFinalStage(roilist);
   m_pvFinalStage -> setInputBuffer(m_avgIntBuffer);


   // Connect display stage to slot
   connect(m_displayStage, SIGNAL(newFrame(const gstar::Array*)),
           this, SLOT(updateFrame(const gstar::Array*)));

   // Start everything, in reverse order
   m_displayStage -> start();
   if (m_roiTableWidget -> isEnabled()) {
      m_averageIntensityStage -> start();
      m_pvFinalStage -> start();
   }
   m_processStage -> start();
   m_sourceStage -> start();

   // Update controls
   m_startAction -> setEnabled(false);
   m_stopAction -> setEnabled(true);
   m_roiTableWidget -> setEnabled(false);
   m_iview -> scene() -> lockROIs(true);

   // Restore cursor
   QApplication::restoreOverrideCursor();

   m_isCapturing = true;

}

/*---------------------------------------------------------------------------*/

void LiveViewer::stopThread()
{

	m_isCapturing = false;

   // Set wait cursor
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

   // Disconnect display stage from slot
   disconnect(m_displayStage, SIGNAL(newFrame(const gstar::Array*)),
              this, SLOT(updateFrame(const gstar::Array*)));

   // Stop everything
   m_sourceStage -> stop();
   m_processStage -> stop();
   if (m_roiTableWidget -> isEnabled()) {
      m_averageIntensityStage -> stop();
      m_pvFinalStage -> stop();
   }
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
   if (m_averageIntensityStage != NULL) {
      delete m_averageIntensityStage;
      m_averageIntensityStage = NULL;
   }
   if (m_displayStage != NULL) {
      delete m_displayStage;
      m_displayStage = NULL;
   }
   if (m_pvFinalStage != NULL) {
      delete m_pvFinalStage;
      m_pvFinalStage = NULL;
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
   if (m_avgIntBuffer != NULL) {
      delete m_avgIntBuffer;
      m_avgIntBuffer = NULL;
   }
   for (unsigned int i = 0 ; i < m_roiMasks.size() ; i++) {
      if (m_roiMasks[i] != NULL) {
         delete m_roiMasks[i];
      }
   }
   if (m_histogram != NULL) {
      delete m_histogram;
      m_histogram = NULL;
   }

   m_roiMasks.clear();

   // Update controls
   m_startAction -> setEnabled(true);
   m_stopAction -> setEnabled(false);
   m_roiTableWidget -> setEnabled(true);
   m_iview -> scene() -> lockROIs(false);

   // Restore cursor
   QApplication::restoreOverrideCursor();

}

/*---------------------------------------------------------------------------*/

void LiveViewer::updateFrame(const Array* imageData)
{

   if(m_isCapturing)
   {

	   if (imageData == NULL)
	      return;

	   // Get rank
	   unsigned long rank = imageData -> getRank();

	   // Get type
	   Array::DataType type = imageData -> getType();

	   // Get dimensions
	   unsigned long long dims[2];
	   imageData -> getDims(dims, 2);

	   // Check image properties; only process BGRA32 images
	   if (rank != 2)
	      return;

	   if (dims[0] <= 0 || dims[1] <= 0)
	      return;

	   if (type != Array::BGRA32)
	      return;

	   // Create image
	   QImage img = QImage((uchar*) imageData -> getBuffer(),
	                       dims[1],
	                       dims[0],
	                       QImage::Format_ARGB32);

	   // Create pixmap from image
	   m_iview -> scene() -> setPixmap(
	      QPixmap::fromImage(img.convertToFormat(QImage::Format_RGB32)));

	   // Update the image properties in the properties widget.
	   m_imagePropertiesWidget -> updateHeight(img.height());
	   m_imagePropertiesWidget -> updateWidth(img.width());
	   m_imagePropertiesWidget -> updateDataType(type);

	   if (m_histogram != NULL)
	   {
	      m_colorTransferFunctionEditorWidget->updateHistogram(
	         m_histogram->getCounts());
	   }
	}

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

void LiveViewer::updateColorTransferFunction(gstar::ColorTransferFunction ctf){
   if (m_processStage != NULL)
   {
	   m_processStage -> setColorTransferFunction(\
	      m_colorTransferFunctionEditorWidget->getColorTransferFunction());
   }
}
