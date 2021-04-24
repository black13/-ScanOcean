/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ImageViewScene.h>
#include <QDebug>

/*---------------------------------------------------------------------------*/

ImageViewScene::ImageViewScene(QWidget* parent)
{

   Q_UNUSED(parent)

   // Initialize pointers to NULL
   m_pixItem = NULL;
   m_zoomSelection = NULL;

   // Initialize mode
   m_mode = None;

   // Set initial pixmap
   QPixmap p(1024, 1024);
   p.fill(Qt::gray);
   m_pixItem = addPixmap(p);

}

/*---------------------------------------------------------------------------*/

ImageViewScene::~ImageViewScene()
{

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

   if ((m_mode == ZoomIn) && (m_zoomSelection != NULL)) {

      QGraphicsView* view = qobject_cast<QGraphicsView*> (
         m_zoomSelection -> parent() -> parent());
      Q_ASSERT(view);

      // Resize rubber band based on initial mouse press and current mouse drag.
      QRectF rect(m_zoomOrigin, view -> mapFromScene(event -> scenePos()));
      m_zoomSelection -> setGeometry(rect.toRect().normalized());

      // Rubber band should only becomes visible, if the mouse is dragged.
      if (!m_zoomSelection -> isVisible())
         m_zoomSelection -> show();
      m_zoomRect = rect;

   }

   else {

      QGraphicsScene::mouseMoveEvent(event);

   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

   // Left click and mode is ZoomIn
   if ((event -> button() == Qt::LeftButton) && (m_mode == ZoomIn)) {

      QGraphicsView* view = qobject_cast<QGraphicsView*>(
         event -> widget() -> parent());
      Q_ASSERT(view);
      // Construct a rubber band object for the view.
      m_zoomSelection = new QRubberBand(QRubberBand::Rectangle,
                                        view -> viewport());
      m_zoomOrigin = view -> mapFromScene(event -> scenePos());
      // Store the size of rubber band rectangle in a QRectF object.
      m_zoomRect = QRectF(m_zoomOrigin, m_zoomOrigin);

   }

   // Left click and mode is ZoomOut
   else if ((event -> button() == Qt::LeftButton) && (m_mode == ZoomOut)) {

      // Emit zoomOut signal
      emit zoomOut();

   }

   // Propagate event
   if ((event -> button() == Qt::LeftButton ||
        event -> button() == Qt::RightButton) &&
       (m_mode == None || m_mode == Fit)) {
      QGraphicsScene::mousePressEvent(event);
   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

   if ((m_mode == ZoomIn) && m_zoomSelection != NULL) {

      delete m_zoomSelection;
      m_zoomSelection = NULL;

      emit zoomIn(m_zoomRect);

   }

   else {

      QGraphicsScene::mouseReleaseEvent(event);

   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setMode(Mode mode)
{

   // Set mode for mouse clicks
   m_mode = mode;

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setPixmap(QPixmap p)
{

   // Set pixmap
   if (m_pixItem != NULL) {

      // Check against old image size and reset scene if necessary
      if ((m_pixItem -> boundingRect()).width() != p.width() ||
          (m_pixItem -> boundingRect()).height() != p.height()) {
         m_pixItem -> setPixmap(p);
         setSceneRect(m_pixItem -> boundingRect());
      }

      // New and old images have matching dimensions
      else {
         m_pixItem -> setPixmap(p);
      }

   }

   // Set first pixmap
   else {
      m_pixItem = addPixmap(p);
   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setZoomModeToFit()
{

   m_mode = Fit;

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setZoomModeToNone()
{

   m_mode = None;

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setZoomModeToZoomIn()
{

   m_mode = ZoomIn;

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setZoomModeToZoomOut()
{

   m_mode = ZoomOut;

}

/*---------------------------------------------------------------------------*/
