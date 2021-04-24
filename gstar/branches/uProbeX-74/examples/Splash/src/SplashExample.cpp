/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <SplashExample.h>
#include <Splash.h>

using gstar::Splash;

/*---------------------------------------------------------------------------*/

SplashExample::SplashExample(QWidget* parent, Qt::WFlags flags)
: QMainWindow(parent, flags)
{

   // Set wait cursor
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

   // Set window title and icon
   setWindowTitle(tr("GStar - Splash Example"));

   // Make window a decent size
   resize(320, 200);

   // Show window and force update the view
   show();

   // Splash screen
   Splash splash(this, Qt::Popup, tr("Splash Example"), true);
   splash.show();
   splash.appendMessageAndProcess(tr("Initializing..."));
   splash.appendMessageAndProcess(tr("Creating GUI..."));

   // Create menu
   createMenu();

   // Update message
   splash.appendMessageAndProcess(tr("Ready..."));

   // Hide splash screen and restore cursor
   splash.hide();
   QApplication::restoreOverrideCursor();

}

/*---------------------------------------------------------------------------*/

void SplashExample::createMenu()
{

   // Exit action
   m_exitAction = new QAction(tr("Exit"), this);
   connect(m_exitAction, SIGNAL(triggered()),
           this, SLOT(close()));

   // Help menu actions
   m_aboutAction = new QAction(tr("About..."), this);
   connect(m_aboutAction, SIGNAL(triggered()),
           this, SLOT(showAbout()));

   // Menu bar
   m_menu = new QMenuBar(this);

   // File menu
   m_menuFile = new QMenu(tr("File"));
   m_menuFile -> addAction(m_exitAction);

   // Help menu
   m_menuHelp = new QMenu(tr("Help"));
   m_menuHelp -> addAction(m_aboutAction);

   // Add menus
   m_menu -> addMenu(m_menuFile);
   m_menu -> addMenu(m_menuHelp);

   // Set menu bar
   setMenuBar(m_menu);

}

/*---------------------------------------------------------------------------*/

void SplashExample::showAbout()
{

   // About screen
   Splash splashAbout(this, Qt::Popup, tr("Splash Example"), true);

   // Show and add message
   splashAbout.setWindowModality(Qt::ApplicationModal);
   splashAbout.clear();
   splashAbout.appendMessage(tr("Created by"));
   splashAbout.appendMessage(tr("Software Services Group"));
   splashAbout.appendMessage(tr("Advanced Photon Source"));
   splashAbout.appendMessage(tr("Argonne National Laboratory"));
   splashAbout.appendMessage(tr(""));
   splashAbout.appendMessage(tr("Copyright (c) 2012"));
   splashAbout.appendMessageAndProcess(tr("UChicago Argonne, LLC"));

   // Show it
   splashAbout.exec();

}

/*---------------------------------------------------------------------------*/
