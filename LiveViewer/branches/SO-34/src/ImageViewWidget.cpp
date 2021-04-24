/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ImageViewWidget.h>

/*---------------------------------------------------------------------------*/

ImageViewWidget::ImageViewWidget(QWidget* parent)
: QWidget(parent)
{

   // Initialize scene
   m_scene = new ImageViewScene();

   // Initialize view
   m_view = new QGraphicsView();
   m_view -> setScene(m_scene);

   // Create actions
   createActions();

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

   // Make toolbar button look checked
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

   // Zoom action group
   m_zoomGroup = new QActionGroup(this);
   m_zoomGroup -> addAction(m_cursorAction);
   m_zoomGroup -> addAction(m_zoomInAction);
   m_zoomGroup -> addAction(m_zoomOutAction);

   // Toolbar fill action
   m_fillAction = new QAction(QIcon(":/images/fill.png"),
                              tr("Fill"), this);
   m_fillAction -> setCheckable(true);
   connect(m_fillAction, SIGNAL(triggered()), this, SLOT(clickFill()));

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::createLayout()
{

   // Layout for two combo boxes
   QVBoxLayout* layout = new QVBoxLayout();
   layout -> setContentsMargins(0, 0, 0, 0);
   layout -> setAlignment(Qt::AlignLeft | Qt::AlignTop);
   layout -> addWidget(m_toolbar);
   layout -> addWidget(m_view);

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

void ImageViewWidget::setScene(ImageViewScene* scene)
{

   // Keep a pointer
   m_scene = scene;

   // Update the view
   m_view -> setScene(scene);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::zoomIn()
{

   // Zoom in
   m_view -> scale(1.25, 1.25);

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
