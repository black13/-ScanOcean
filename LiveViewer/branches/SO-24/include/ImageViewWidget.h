/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef IMAGE_VIEW_WIDGET_H
#define IMAGE_VIEW_WIDGET_H

/*---------------------------------------------------------------------------*/

#include <ImageViewScene.h>

#include <QAction>
#include <QCursor>
#include <QGraphicsView>
#include <QIcon>
#include <QPixmap>
#include <QStandardItemModel>
#include <QTableView>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

/*---------------------------------------------------------------------------*/

/**
 * @brief The ImageViewWidget class ...
 */
class ImageViewWidget
: public QWidget
{

   Q_OBJECT

public:

   /**
    * Constructor
    *
    * @param parent the Qt parent widget.
    */
   ImageViewWidget(QWidget* parent = 0);

   /**
    * Destructor
    */
   ~ImageViewWidget();

   /**
    * Returns a pointer to the scene that is currently visualized in the view.
    * If no scene is currently visualized, 0 is returned.
    *
    * @return the current scene.
    */
   ImageViewScene* scene();

   /**
    * Sets the current scene to scene. If scene is already being viewed,
    * this function does nothing.
    *
    * @param scene - The scene to set.
    */
   void setScene(ImageViewScene* scene);

protected:

   /**
    * Overridden resize handler
    *
    * See Qt documentation
    */
   void resizeEvent(QResizeEvent* event);

private slots:

   /**
    * Handle click on cursor tool bar icon
    */
   void clickCursor();

   /**
    * Handle click on fill tool bar icon. Switch to fill mode.
    */
   void clickFill();

   /**
    * Handle click on zoom in tool bar icon. Switch to zoom in mode.
    */
   void clickZoomIn();

   /**
    * Handle click on zoom out tool bar icon. Switch to zoom out mode.
    */
   void clickZoomOut();

   /**
    * Zoom in
    */
   void zoomIn();

   /**
    * Zoom out
    */
   void zoomOut();

private:

   /**
    * Create standard actions used on the menu bar.
    */
   void createActions();

   /**
    * Create layout for widget
    */
   void createLayout();

   /**
    * Create graphics scene and graphics view
    */
   void createSceneAndView();

   /**
    * Create and setup the tool bar and connections for standard actions.
    */
   void createToolBar();

private:

   /**
    * Tool bar for zoom tools
    */
   QToolBar* m_toolbar;

   /**
    * Group for zoom in, out and fill tools
    */
   QActionGroup* m_zoomGroup;

   /**
    * Cursor
    */
   QAction* m_cursorAction;

   /**
    * Zoom in
    */
   QAction* m_zoomInAction;

   /**
    * Zoom out
    */
   QAction* m_zoomOutAction;

   /**
    * Fill
    */
   QAction* m_fillAction;

   /**
    * The QGraphicsScene subclass for the QGraphicsView
    */
   ImageViewScene* m_scene;

   /**
    * QGraphicsView for displaying the scene graph
    */
   QGraphicsView* m_view;

   /**
    * Zoom in cursor
    */
   QCursor m_zoomInCursor;

   /**
    * Zoom out cursor
    */
   QCursor m_zoomOutCursor;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
