/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DATA_EXPLORER_H
#define DATA_EXPLORER_H

/*---------------------------------------------------------------------------*/

#include <DStar.h>
#include <ImageView.h>
#include <PropertiesView.h>
#include <TableView.h>
#include <TreeView.h>
#include <RangeWidget.h>
#include <SubWindow.h>

#include <QAction>
#include <QCoreApplication>
#include <QDockWidget>
#include <QFileDialog>
#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenu>
#include <QMenuBar>

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>
#include <utility>

/*---------------------------------------------------------------------------*/

/**
 * @brief The main DataExplorer window.
 */
class DataExplorer
: public QMainWindow
{
	
   Q_OBJECT
	
public:
	
   /**
    * Constructor
    *
    * @param parent Qt's parent widget
    * @flags Qt flags for window borders
    */
   DataExplorer(QWidget *parent = 0, Qt::WFlags flags = 0);
	
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
    * Cascade MDI area subwindows.
    */
   void cascadeSubWindows();

   /**
    * Close data set.
    *
    * @param item
    */
   void closeData(boost::shared_ptr<dstar::AbstractObject> obj);

   /**
    * Slot that exits the application.
    */
   void exitApplication();

   /**
    * Create a new ImageView for the data object
    *
    * @param obj
    */
   void makeImageView(boost::shared_ptr<dstar::AbstractObject> obj);

   /**
    * Create a new TableView for the data object
    *
    * @param obj
    */
   void makeTableView(boost::shared_ptr<dstar::AbstractObject> obj);
   
   /**
    * Show the open file dialog.
    */
   void showOpen();

   /**
    * Handle a user closing a subwindow
    *
    * @param subwin
    */
   void subWindowClosed(SubWindow* subwin);

   /**
    * Tile MDI area subwindows.
    */
   void tileSubWindows();

   /**
    * Update the properties view when a selection in TreeView changes
    *
    * @param obj
    */
   void updateProperties(boost::shared_ptr<dstar::AbstractObject> obj);

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

   /**
    * Update the 'Window' menu to enable/disable cascade/tile actions, and
    * add/remove windows.
    */
   void updateWindowMenu();
   
private:
	
   // Menu actions
   QAction* m_openAction;
   QAction* m_preferencesAction;
   QAction* m_exitAction;
   QAction* m_cascadeAction;
   QAction* m_tabAction;
   QAction* m_tileAction;
   QAction* m_aboutAction;
	
   // Menu
   QMenuBar* m_menu;
   QMenu* m_menuFile;
   QMenu* m_menuView;
   QMenu* m_menuWindow;
   QMenu* m_menuHelp;
   
   // Dock widgets
   QDockWidget* m_dataTreeDock;
   QDockWidget* m_dataPropertiesDock;
   
   /**
    * Data tree
    */
   TreeView* m_dataTree;

   /**
    * Properties view
    */
   PropertiesView* m_propertiesView;

   /**
    * MDI area that serves as the central widget
    */
   QMdiArea* m_mdiArea;
	
   /**
    * Application path
    */
   QString m_appPath;
   
   /**
    * Master list of datasets
    */
   std::list<boost::shared_ptr<dstar::AbstractGroup> > m_data;

   /**
    * View, window map
    */
   std::map<dstar::AbstractView*, SubWindow*> m_mapViewWindow;

   /**
    * Root data, child data map
    */
   std::multimap<boost::shared_ptr<const dstar::AbstractObject>,
                 boost::shared_ptr<const dstar::AbstractObject> >
      m_dataParentChild;
	
};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
