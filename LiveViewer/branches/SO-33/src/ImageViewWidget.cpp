/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ImageViewWidget.h>
#include <QDebug>

/*---------------------------------------------------------------------------*/

ImageViewWidget::ImageViewWidget(QWidget* parent)
: QWidget(parent)
{

   // Create actions
   createActions();

   // Create scene and view
   createSceneAndView();

   // Create tool bar
   createToolBar();

   // Create layout and add widgets
   createLayout();

   // Zoom in/out cursors
   m_zoomInCursor = QCursor(QPixmap(":/images/zoomin.png"));
   m_zoomOutCursor = QCursor(QPixmap(":/images/zoomout.png"));

}

/*---------------------------------------------------------------------------*/

ImageViewWidget::~ImageViewWidget()
{

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::clickCursor()
{

   // Set scene mode
   m_scene -> setZoomModeToNone();

   // Set regular cursor
   m_view -> viewport() -> setCursor(Qt::ArrowCursor);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::clickFill()
{

   // Make tool bar button look checked
   m_cursorAction -> setChecked(true);

   // Get out of zoom mode
   clickCursor();

   // Set scene mode
   if (m_fillAction -> isChecked()) {
      m_zoomGroup -> setEnabled(false);
      m_scene -> setZoomModeToFit();
      resizeEvent(NULL);
   }
   else {
      m_zoomGroup -> setEnabled(true);
   }

   // Set regular cursor
   m_view -> viewport() -> setCursor(Qt::ArrowCursor);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::clickZoomIn()
{

   // Set zoom in mode
   m_scene -> setZoomModeToZoomIn();

   // Change cursor
   m_view -> viewport() -> setCursor(m_zoomInCursor);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::clickZoomOut()
{

   // Set zoom out mode
   m_scene -> setZoomModeToZoomOut();

   // Change cursor
   m_view -> viewport() -> setCursor(m_zoomOutCursor);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::clickZoomOriginal()
{

   // Zoom back to actual image size
   m_view -> resetMatrix();

   // Force update scroll bars
   m_view -> setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   m_view -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::createActions()
{

   // Toolbar cursor action
   m_cursorAction = new QAction(QIcon(":images/cursor.png"),
                                tr("Cursor"), this);
   m_cursorAction -> setCheckable(true);
   m_cursorAction -> setChecked(true);
   connect(m_cursorAction, SIGNAL(triggered()), this, SLOT(clickCursor()));

   // Toolbar zoom in action
   m_zoomInAction = new QAction(QIcon(":/images/zoomin.png"),
                                tr("Zoom In"), this);
   m_zoomInAction -> setCheckable(true);
   connect(m_zoomInAction, SIGNAL(triggered()), this, SLOT(clickZoomIn()));

   // Toolbar zoom out action
   m_zoomOutAction = new QAction(QIcon(":/images/zoomout.png"),
                                 tr("Zoom Out"), this);
   m_zoomOutAction -> setCheckable(true);
   connect(m_zoomOutAction, SIGNAL(triggered()), this, SLOT(clickZoomOut()));

   // Toolbar zoom to original image.
   m_zoomOriginalAction = new QAction(QIcon(":/images/zoomoriginal.png"),
                                       tr("Actual Size"), this);
   connect(m_zoomOriginalAction, SIGNAL(triggered()), this,
          SLOT(clickZoomOriginal()));


   // Zoom action group
   m_zoomGroup = new QActionGroup(this);
   m_zoomGroup -> addAction(m_cursorAction);
   m_zoomGroup -> addAction(m_zoomInAction);
   m_zoomGroup -> addAction(m_zoomOutAction);
   m_zoomGroup -> addAction(m_zoomOriginalAction);

   // Toolbar fill action
   m_fillAction = new QAction(QIcon(":/images/fill.png"),
                              tr("Fill"), this);
   m_fillAction -> setCheckable(true);
   connect(m_fillAction, SIGNAL(triggered()), this, SLOT(clickFill()));

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::createLayout()
{

   // Layout
   QVBoxLayout* layout = new QVBoxLayout();
   layout -> setContentsMargins(0, 0, 0, 0);
   //layout -> setAlignment(Qt::AlignLeft | Qt::AlignTop);
   layout -> addWidget(m_toolbar);
   layout -> addWidget(m_view);

   // Set widget's layout
   setLayout(layout);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::createSceneAndView()
{

   // Initialize scene
   m_scene = new ImageViewScene();
   connect(m_scene, SIGNAL(zoomIn(QRectF)), this, SLOT(zoomIn(QRectF)));
   connect(m_scene, SIGNAL(zoomOut()), this, SLOT(zoomOut()));
   connect(m_scene, SIGNAL(sceneRectChanged(const QRectF&)),
           this, SLOT(sceneRectUpdated(const QRectF&)));

   // Initialize view
   m_view = new QGraphicsView();
   m_view -> setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
   m_view -> setScene(m_scene);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::createToolBar()
{

   // Create toolbar
   m_toolbar = new QToolBar(this);
   m_toolbar -> setFloatable(false);
   m_toolbar -> setMovable(false);

   // Add toolbar actions
   m_toolbar -> addAction(m_cursorAction);
   m_toolbar -> addAction(m_zoomInAction);
   m_toolbar -> addAction(m_zoomOutAction);
   m_toolbar -> addAction(m_zoomOriginalAction);
   m_toolbar -> addAction(m_fillAction);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::resizeEvent(QResizeEvent* event)
{

   Q_UNUSED(event)

   // Check if fill is not enabled
   if (!m_fillAction -> isChecked()) {
      return;
   }

   // Get image size
   QRectF r(0, 0,
            (m_scene -> sceneRect()).width(),
            (m_scene -> sceneRect()).height());

   // Make image fit window
   m_view -> fitInView(r, Qt::KeepAspectRatio);

}

/*---------------------------------------------------------------------------*/

ImageViewScene* ImageViewWidget::scene()
{

   // Return current scene
   return m_scene;

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::sceneRectUpdated(const QRectF& rect)
{

   Q_UNUSED(rect)

   // Force a resize
   resizeEvent(NULL);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::setScene(ImageViewScene* scene)
{

   // Pointer check
   if (scene == NULL) return;

   // Disconnect current scene
   if (m_scene != NULL) {
      disconnect(m_scene, SIGNAL(zoomIn()), this, SLOT(zoomIn()));
      disconnect(m_scene, SIGNAL(zoomOut()), this, SLOT(zoomOut()));
      disconnect(m_scene, SIGNAL(sceneRectChanged(const QRectF&)),
                 this, SLOT(sceneRectUpdated(const QRectF&)));
   }

   // Keep a pointer and connect new scene
   m_scene = scene;
   connect(m_scene, SIGNAL(zoomIn()), this, SLOT(zoomIn()));
   connect(m_scene, SIGNAL(zoomOut()), this, SLOT(zoomOut()));
   connect(m_scene, SIGNAL(sceneRectChanged(const QRectF&)),
           this, SLOT(sceneRectUpdated(const QRectF&)));

   // Update the view
   m_view -> setScene(m_scene);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::zoomIn(QRectF zoomRect)
{

   // Zoom in
   if (!zoomRect.isEmpty() || !zoomRect.normalized().isEmpty()) {

      QRect viewport = m_view -> rect();

      float xscale = viewport.width()  / zoomRect.width();
      float yscale = viewport.height() / zoomRect.height();

      // To preserve aspect ratio in the scaled image,
      // pick the smallest of two dimensions as scaling factor.

      float scalev = xscale;
      if (xscale > yscale)
         scalev = yscale;

      m_view -> scale(scalev, scalev);

      // Center the zoomed-in image at the center of zoom selection
      QPointF imageonScene = m_view -> mapToScene(zoomRect.topLeft().toPoint());
      m_view -> centerOn(imageonScene);
   }

   else {
      // Without zoom rectangle, scale using fixed value
      //TODO:: Put this value in preferences.
      m_view -> scale(1.25, 1.25);
   }

   // Force update scroll bars
   m_view -> setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   m_view -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::zoomOut()
{

   // Zoom out
   m_view -> scale(0.75, 0.75);

   // Force update scroll bars
   m_view -> setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   m_view -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

}

/*---------------------------------------------------------------------------*/
