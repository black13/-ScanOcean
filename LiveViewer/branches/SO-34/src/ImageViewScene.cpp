/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ImageViewScene.h>

/*---------------------------------------------------------------------------*/

ImageViewScene::ImageViewScene(QWidget* parent)
{

   Q_UNUSED(parent)

   // Initialize pointers to NULL
   m_pixItem = NULL;

   // Initialize mode
   m_mode = None;

}

/*---------------------------------------------------------------------------*/

ImageViewScene::~ImageViewScene()
{

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

   QGraphicsScene::mouseMoveEvent(event);

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

   // Left click and mode is ZoomIn
   if ((event -> button() == Qt::LeftButton) && (m_mode == ZoomIn)) {

      // Emit zoomIn signal
      emit zoomIn();

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
      m_pixItem -> setPixmap(p);
   }
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
