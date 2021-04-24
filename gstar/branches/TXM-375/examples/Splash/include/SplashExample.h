/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SPLASH_EXAMPLE_H
#define SPLASH_EXAMPLE_H

/*---------------------------------------------------------------------------*/

#include <QAction>
#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>

/*---------------------------------------------------------------------------*/

/**
 * @brief Demonstrate Splash class.
 *
 * Simple demonstration of the Splash class.
 */
class SplashExample
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
   SplashExample(QWidget* parent = 0, Qt::WFlags flags = 0);

private slots:

   /**
    * Show the splash screen as an about dialog
    */
   void showAbout();

private:

   /**
    * Create and setup the menu bar and connections for actions.
    */
   void createMenu();

private:

   /**
    * Main menu
    */
   QMenuBar* m_menu;

   /**
    * File menu
    */
   QMenu* m_menuFile;

   /**
    * Help menu
    */
   QMenu* m_menuHelp;

   /**
    * Exit action
    */
   QAction* m_exitAction;

   /**
    * About action
    */
   QAction* m_aboutAction;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
