/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <DataExplorer.h>

using namespace dstar;

using boost::const_pointer_cast;
using boost::dynamic_pointer_cast;
using boost::shared_ptr;
using std::list;
using std::map;
using std::multimap;
using std::pair;

#include <iostream>

/*---------------------------------------------------------------------------*/

DataExplorer::DataExplorer(QWidget* parent, Qt::WFlags flags)
: QMainWindow(parent, flags)
{
	
   // Initialize all pointers to NULL
   initializeToNULL();
	
   // Initialize GUI
   initializeGUI();
	
}

/*---------------------------------------------------------------------------*/

void DataExplorer::cascadeSubWindows()
{

   // Cascade subwindows
   m_mdiArea -> cascadeSubWindows();

}

/*---------------------------------------------------------------------------*/

void DataExplorer::closeData(shared_ptr<AbstractObject> obj)
{

   // Add const for main maps
   shared_ptr<const AbstractObject> tmp =
      dynamic_pointer_cast<const AbstractObject>(obj);


   // Iterator for parent, child map
   pair<multimap<shared_ptr<const AbstractObject>,
                 shared_ptr<const AbstractObject> >::iterator,
        multimap<shared_ptr<const AbstractObject>,
                 shared_ptr<const AbstractObject> >::iterator> pciter;

   // Get all pairs with object to close as the key
   pciter = m_dataParentChild.equal_range(tmp);


   // Iterate over each pair with object to close as key
   multimap<shared_ptr<const AbstractObject>,
            shared_ptr<const AbstractObject> >::iterator oiter;
   for (oiter = pciter.first ; oiter != pciter.second; ++oiter) {

      // Get object's observers (views)
      list<AbstractView*> vlist = (*oiter).second -> getObservers();

      // Remove subject pairs in parent, child map from observers (views)
      std::list<AbstractView*>::iterator viter;
      for (viter = vlist.begin() ; viter != vlist.end() ; ++viter) {

         // Remove data object (subject) from view
         (*viter) -> removeDataObject(
               const_pointer_cast<AbstractObject>((*oiter).second));

         // If the view is a subwindow (it's in the view, window map), close it
         std::map<AbstractView*, SubWindow*>::iterator vwiter;
         vwiter = m_mapViewWindow.find(*viter);
         if (vwiter != m_mapViewWindow.end()) {

            // Cast to QMdiSubWindow and close it
            SubWindow* sub = (*vwiter).second;
            sub -> close();

            // Remove the view from the view, window map
            m_mapViewWindow.erase(*viter);

         }

      }

   }


   // make certain everything is removed from both maps
   m_dataParentChild.erase(tmp);


   // Clear properties view
   std::list<shared_ptr<AbstractObject> > lst =
      m_propertiesView -> getDataObjects();
   std::list<shared_ptr<AbstractObject> >::iterator ii;
   for (ii = lst.begin() ; ii != lst.end() ; ++ii) {
      std::cerr << "Remove last thing." << std::endl;
      m_propertiesView -> removeDataObject(*ii);
   }


   // Remove from tree view
   m_dataTree -> removeDataObject(obj);


   // Find item in m_data and remove it
   std::list<shared_ptr<AbstractGroup> >::iterator i;
   for (i = m_data.begin() ; i != m_data.end() ; ++i) {
      if ((*i) == obj) {
         m_data.erase(i);
         std::cerr << "Closing item: " << i -> use_count() << std::endl;
         break;
      }
   }


   // Update window menu state
   updateWindowMenu();

}

/*---------------------------------------------------------------------------*/

void DataExplorer::closeEvent(QCloseEvent* event)
{
	
   Q_UNUSED(event)
	
   // Quit
   QCoreApplication::quit();
	
}

/*---------------------------------------------------------------------------*/

void DataExplorer::createActions()
{
	
   // Open action
   m_openAction = new QAction(tr("Open..."), this);
   connect(m_openAction, SIGNAL(triggered()),
           this, SLOT(showOpen()));
	
   // Preferences action
   m_preferencesAction = new QAction(tr("Preferences..."), this);
   connect(m_preferencesAction, SIGNAL(triggered()),
           this, SLOT(ShowPreferences()));
	
   // Exit action
   m_exitAction = new QAction(tr("Exit"), this);
   connect(m_exitAction, SIGNAL(triggered()),
           this, SLOT(exitApplication()));

   // Cascade action
   m_cascadeAction = new QAction(tr("Cascade"), this);
   connect(m_cascadeAction, SIGNAL(triggered()),
           this, SLOT(cascadeSubWindows()));

   // Tile action
   m_tileAction = new QAction(tr("Tile"), this);
   connect(m_tileAction, SIGNAL(triggered()),
           this, SLOT(tileSubWindows()));
	
   // Help menu actions
   m_aboutAction = new QAction(tr("About..."), this);
   connect(m_aboutAction, SIGNAL(triggered()),
           this, SLOT(ShowAbout()));
	
}

/*---------------------------------------------------------------------------*/

void DataExplorer::createDockWidgets()
{
	
   // Data tree dock
   m_dataTreeDock = new QDockWidget(tr("Data Tree"), this);
   m_dataTreeDock -> setEnabled(true);
   m_dataTreeDock -> setAllowedAreas(Qt::AllDockWidgetAreas);
   m_dataTreeDock -> setWidget(m_dataTree);
   m_menuView -> addAction(m_dataTreeDock -> toggleViewAction());
   addDockWidget(Qt::LeftDockWidgetArea, m_dataTreeDock);
   
   // Data properties dock
   m_dataPropertiesDock = new QDockWidget(tr("Data Properties"), this);
   m_dataPropertiesDock -> setEnabled(true);
   m_dataPropertiesDock -> setAllowedAreas(Qt::AllDockWidgetAreas);
   m_dataPropertiesDock -> setWidget(m_propertiesView);
   m_menuView -> addAction(m_dataPropertiesDock -> toggleViewAction());
   addDockWidget(Qt::LeftDockWidgetArea, m_dataPropertiesDock);
	
}

/*---------------------------------------------------------------------------*/

void DataExplorer::createMenuBar()
{
	
   // Menu bar
   m_menu = new QMenuBar(this);
	
   // File menu
   m_menuFile = new QMenu(tr("File"));
   m_menuFile -> addAction(m_openAction);
   m_menuFile -> addSeparator();
   m_menuFile -> addAction(m_preferencesAction);
   m_menuFile -> addSeparator();
   m_menuFile -> addAction(m_exitAction);
	
   // View menu
   m_menuView = new QMenu(tr("View"));
	
   // Help menu
   m_menuHelp = new QMenu(tr("Help"));
   m_menuHelp -> addAction(m_aboutAction);

   // Window menu
   m_menuWindow = new QMenu(tr("Window"));
   m_menuWindow -> addAction(m_cascadeAction);
   m_menuWindow -> addAction(m_tileAction);
	
   // Add menus
   m_menu -> addMenu(m_menuFile);
   m_menu -> addMenu(m_menuView);
   m_menu -> addMenu(m_menuWindow);
   m_menu -> addMenu(m_menuHelp);
	
   // Set menu bar
   setMenuBar(m_menu);

   // Disable actions
   m_cascadeAction -> setEnabled(false);
   m_tileAction -> setEnabled(false);
	
}

/*---------------------------------------------------------------------------*/

void DataExplorer::exitApplication()
{
	
   // Quit
   close();
	
}

/*---------------------------------------------------------------------------*/

void DataExplorer::initializeGUI()
{
	
   // Get application path
   m_appPath = QCoreApplication::applicationDirPath();
	
	
   // Create actions
   createActions();
	
   // Create menu bar
   createMenuBar();
   
   // Create data tree
   m_dataTree = new TreeView();

   // User selects close in tree view
   connect(m_dataTree,
           SIGNAL(dataClosed(boost::shared_ptr<dstar::AbstractObject>)),
           this,
           SLOT(closeData(boost::shared_ptr<dstar::AbstractObject>)));

   // User selects open table view in tree view
   connect(m_dataTree,
           SIGNAL(tableViewRequested(boost::shared_ptr<dstar::AbstractObject>)),
           this,
           SLOT(makeTableView(boost::shared_ptr<dstar::AbstractObject>)));

   // User selects open image view in tree view
   connect(m_dataTree,
           SIGNAL(imageViewRequested(boost::shared_ptr<dstar::AbstractObject>)),
           this,
           SLOT(makeImageView(boost::shared_ptr<dstar::AbstractObject>)));

   // Create properties view
   m_propertiesView = new PropertiesView();

   // User changes selection
   connect(m_dataTree,
           SIGNAL(selectionChanged(boost::shared_ptr<dstar::AbstractObject>)),
           this,
           SLOT(updateProperties(boost::shared_ptr<dstar::AbstractObject>)));

   // Create dock widgets
   createDockWidgets();
   

   // Set window title and icon
   setWindowTitle(tr("ScanOcean - Data Explorer Prototype"));
	
   // Setup central widget
   m_mdiArea = new QMdiArea();
   m_mdiArea -> setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   m_mdiArea -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   setCentralWidget(m_mdiArea);
	
   // Make window a decent size
   resize(800, 600);
	
   // Show window and force update the view
   show();
	
}

/*---------------------------------------------------------------------------*/

void DataExplorer::initializeToNULL()
{

   m_openAction = NULL;
   m_preferencesAction = NULL;
   m_exitAction = NULL;
   m_cascadeAction = NULL;
   m_tileAction = NULL;
   m_aboutAction = NULL;
	
   m_menu = NULL;
   m_menuFile = NULL;
   m_menuView = NULL;
   m_menuWindow = NULL;
   m_menuHelp = NULL;
   
   m_dataTreeDock = NULL;
   m_dataPropertiesDock = NULL;
   
   m_dataTree = NULL;
   m_propertiesView = NULL;

   m_mdiArea = NULL;
	
}

/*---------------------------------------------------------------------------*/

void DataExplorer::makeImageView(shared_ptr<AbstractObject> obj)
{

   // Create a new subwindow for the view
   SubWindow* subWin = new SubWindow(m_mdiArea);
   subWin -> setWindowTitle(tr("Data - %1").arg((obj -> getName()).c_str()));
   connect(subWin, SIGNAL(windowClosing(SubWindow*)),
           this, SLOT(subWindowClosed(SubWindow*)));

   // Create a new table view widget and add data to it
   ImageView* view = new ImageView(subWin);
   view -> addDataObject(obj);
   subWin -> setWidget(view);
   subWin -> show();

   // Add root, child pair to map
   shared_ptr<const AbstractObject> root = obj -> getRoot();
   m_dataParentChild.insert(std::make_pair(root, obj));

   // Add view, window pair to map
   m_mapViewWindow[view] = subWin;

   // Update window menu state
   updateWindowMenu();

}

/*---------------------------------------------------------------------------*/

void DataExplorer::makeTableView(shared_ptr<AbstractObject> obj)
{

   // Create a new table view widget and add data to it
   TableView* view = new TableView();
   view -> addDataObject(obj);

   // Create a new subwindow for the view
   SubWindow* subWin = new SubWindow(m_mdiArea);
   subWin -> setWidget(view);
   subWin -> setWindowTitle(tr("Data - %1").arg((obj -> getName()).c_str()));
   subWin -> show();
   connect(subWin, SIGNAL(windowClosing(SubWindow*)),
           this, SLOT(subWindowClosed(SubWindow*)));

   // Add root, child pair to map
   shared_ptr<const AbstractObject> root = obj -> getRoot();
   m_dataParentChild.insert(std::make_pair(root, obj));

   // Add view, window pair to map
   m_mapViewWindow[view] = subWin;

   // Update window menu state
   updateWindowMenu();

}

/*---------------------------------------------------------------------------*/

void DataExplorer::resizeEvent(QResizeEvent* event)
{
	
   Q_UNUSED(event)

}

/*---------------------------------------------------------------------------*/

void DataExplorer::showOpen()
{
   
   // Open string path
   QString openPath;
   
   // Show open file dialog box
   QString fileName =
   QFileDialog::getOpenFileName(this,
                                tr("Open HDF5 File"),
                                ".",
                                tr("HDF5 Files (*.hdf5 *.h5)"));
   
   // User cancels operation
   if (fileName.isEmpty()) {
      return;
   }
   
   // Create new HDF5File
   shared_ptr<HDF5File> file = shared_ptr<HDF5File>(new HDF5File());

   // Read the file
   file -> Read(fileName.toAscii().constData());
   
   // Convert to a group
   shared_ptr<AbstractGroup> data = dynamic_pointer_cast<AbstractGroup>(file);
   

   // Add to list of open datasets
   m_data.push_back(data);

   // Add data to view/observer
   m_dataTree -> addDataObject(data);

}

/*---------------------------------------------------------------------------*/

void DataExplorer::subWindowClosed(SubWindow* subwin)
{

   // View that's in the subwindow
   AbstractView* view = NULL;

   // Find view for subwindow
   map<AbstractView*, SubWindow*>::iterator vwiter;
   for (vwiter = m_mapViewWindow.begin() ;
        vwiter != m_mapViewWindow.end() ;
        ++vwiter) {
      if ((*vwiter).second == subwin) {
         view = (*vwiter).first;
         break;
      }
   }

   // Get view's subjects (data objects)
   list<shared_ptr<AbstractObject> > olist = view -> getDataObjects();

   // Remove subjects from view
   list<shared_ptr<AbstractObject> >::iterator oiter;
   for (oiter = olist.begin() ; oiter != olist.end() ; ++oiter) {
      view -> removeDataObject(*oiter);
   }

   // Remove parent, child from multimap

   // Remove view, subwindow from map
   m_mapViewWindow.erase(view);

   // Update window menu state
   updateWindowMenu();

}

/*---------------------------------------------------------------------------*/

void DataExplorer::tileSubWindows()
{

   // Tile subwindows
   m_mdiArea -> tileSubWindows();

}

/*---------------------------------------------------------------------------*/

void
DataExplorer::updateProperties(boost::shared_ptr<dstar::AbstractObject> obj)
{

   std::list<shared_ptr<AbstractObject> > lst =
      m_propertiesView -> getDataObjects();

   std::list<shared_ptr<AbstractObject> >::iterator i;
   for (i = lst.begin() ; i != lst.end() ; ++i) {
      m_propertiesView -> removeDataObject(*i);
   }

   // Update properties
   m_propertiesView -> addDataObject(obj);

}

/*---------------------------------------------------------------------------*/

void DataExplorer::updateWindowMenu()
{

   // Enable/disable window actions
   if (m_mapViewWindow.size() <= 0) {
      m_cascadeAction -> setEnabled(false);
      m_tileAction -> setEnabled(false);
   }
   else {
      m_cascadeAction -> setEnabled(true);
      m_tileAction -> setEnabled(true);
   }

}

/*---------------------------------------------------------------------------*/
