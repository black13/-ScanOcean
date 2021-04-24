/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <LiveViewer.h>

#include <iostream>
#include <PreferencesDialog.h>

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

}

/*---------------------------------------------------------------------------*/

void LiveViewer::createDockWidgets()
{

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
   // TO DO

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

   // Set wait cursor
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

   // Set window title and icon
   setWindowTitle(tr("LiveViewer"));

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
   QWidget* central = new QWidget();
   setCentralWidget(central);

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
	
   m_menu = NULL;
   m_menuFile = NULL;
   m_menuView = NULL;
   m_menuWindow = NULL;
   m_menuHelp = NULL;

   m_toolbar = NULL;
   m_statusBar = NULL;

   m_splashAbout = NULL;

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

}

/*---------------------------------------------------------------------------*/

void LiveViewer::showPreferences()
{

//   // Show preferences dialog with current settings
     PreferencesDialog* dialog = new PreferencesDialog(this, Qt::Dialog);
     dialog -> setPreferences(&m_preferences);
     dialog -> exec();
//
//   // Update with current settings
//   if (dialog -> exec() == QDialog::Accepted) {
//
//      // Update things if user clicks OK
//      QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
//      QApplication::restoreOverrideCursor();
//
//   }
//
//   // Delete dialog
     delete dialog;

}

/*---------------------------------------------------------------------------*/
