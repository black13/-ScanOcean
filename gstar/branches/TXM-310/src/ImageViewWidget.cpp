/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ImageViewWidget.h>
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QListView>
#include <QGraphicsView>
#include <QResizeEvent>

using namespace gstar;

/*---------------------------------------------------------------------------*/

ImageViewWidget::ImageViewWidget(QWidget* parent)
: QWidget(parent), m_fillState(false)
{

   // Create scene and view
   createSceneAndView();

   // Create main layout and add widgets
   createLayout();

   // Zoom in/out cursors
   m_zoomInCursor = QCursor(QPixmap(":/images/zoomin.png"));
   m_zoomOutCursor = QCursor(QPixmap(":/images/zoomout.png"));

   m_zoomPercent = NULL;

/*   m_widget = parent;
   m_widget->installEventFilter(this);*/

}

/*---------------------------------------------------------------------------*/

ImageViewWidget::~ImageViewWidget()
{


}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::clickCursor()
{

   // Set scene mode
   m_scene->setZoomModeToNone();

   // Set regular cursor
   m_view->viewport()->setCursor(Qt::ArrowCursor);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::clickFill(bool checked)
{

   // State is used by the resizeEvent raised below.
   //  Make sure state is set before calling resizeEvent method.
   m_fillState = checked;
   
   // Get out of zoom mode
   clickCursor();

   // Set scene mode
   if (checked == true) {
      m_scene->setZoomModeToFit();
      resizeEvent(NULL);
      m_zoomPercent->setCurrentIndex(-1);
   }
   
   // Set regular cursor
   m_view->viewport()->setCursor(Qt::ArrowCursor);


}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::clickZoomIn()
{

   // Set zoom in mode
   m_scene->setZoomModeToZoomIn();

   // Change cursor
   m_view->viewport()->setCursor(m_zoomInCursor);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::clickZoomOriginal()
{

   // Zoom back to actual image size
   m_view->resetMatrix();

   // Force update scroll bars
   m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

   updateZoomPercentage();

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::clickZoomOut()
{

   // Set zoom out mode
   m_scene->setZoomModeToZoomOut();

   // Change cursor
   m_view->viewport()->setCursor(m_zoomOutCursor);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::createLayout()
{

   // Layout
   QVBoxLayout* layout = new QVBoxLayout();
   layout -> setContentsMargins(0, 0, 0, 0);
   layout -> addWidget(m_view);

   // Set widget's layout
   setLayout(layout);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::createSceneAndView()
{

   // Initialize scene
   m_scene = new ImageViewScene();
   m_scene->setSceneRect(m_scene->itemsBoundingRect());


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

qreal ImageViewWidget::getCurrentZoomPercent()
{

   QTransform t = m_view->transform();
   QRectF tImage = t.mapRect(m_scene->pixRect());

   qreal wp = tImage.width() / m_scene->pixRect().width() * 100.0;

   return wp;

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::resizeEvent(QResizeEvent* event)
{

   Q_UNUSED(event)

   if (m_fillState == false) return;
   
   // Get image size
   QRectF r(0, 0,
            (m_scene->sceneRect()).width(),
            (m_scene->sceneRect()).height());

   m_view -> fitInView(r,Qt::KeepAspectRatio);

   updateZoomPercentage();
   update();

   m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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

   updateZoomPercentage();

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::setZoomPercentWidget(QComboBox* zoomPercent)
{

   m_zoomPercent  = zoomPercent;

   connect(m_zoomPercent,
           SIGNAL(currentIndexChanged(int)),
           this,
           SLOT(zoomValueChanged()));

   updateZoomPercentage();

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::updateZoomPercentage()
{

   if (m_zoomPercent == NULL) return;

   qreal wp = getCurrentZoomPercent();


   disconnect(m_zoomPercent,
              SIGNAL(currentIndexChanged(int)),
              this,
              SLOT(zoomValueChanged()));

   m_zoomPercent->setEditText(QString("%1").arg(wp, 0, 'f',  0));

   connect(m_zoomPercent,
           SIGNAL(currentIndexChanged(int)),
           this,
           SLOT(zoomValueChanged()));

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
      if (xscale > yscale) {
         scalev = yscale;
      }

      qreal wp = getCurrentZoomPercent();

      if (wp >= 800) return;

      m_view -> scale(scalev, scalev);

      // Center the zoomed-in image at the center of zoom selection
      QPointF imageonScene = m_view -> mapToScene(zoomRect.topLeft().toPoint());
      m_view -> centerOn(imageonScene);

   }

   else {
      // Without zoom rectangle, scale using fixed value
      qreal wp = getCurrentZoomPercent();

      if (wp >= 800) return;

      m_view -> scale(1.50, 1.50);

   }

   // Force update scroll bars
   m_view -> setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   m_view -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

   updateZoomPercentage();

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::zoomOut()
{

   qreal wp = getCurrentZoomPercent();

   if (wp <= 12.5) return;

   m_view -> scale(.66, .66);

   // Force update scroll bars
   m_view -> setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   m_view -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

   updateZoomPercentage();

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::zoomValueChanged()
{

   bool isOK = false;
   float value = m_zoomPercent->currentText().toFloat(&isOK);
   if (!isOK || value < 12.5 || value > 800) {
      m_zoomPercent->removeItem(m_zoomPercent->currentIndex());
      updateZoomPercentage();
      return;
   }

   QTransform t = m_view->transform();
   QRectF image = m_scene->pixRect();
   QRectF tImage = t.mapRect(image);

   qreal sx = (value/100 * image.width()) / tImage.width();
   qreal sy = (value/100 * image.height()) / tImage.height();

   qreal s = sx;
   if (sy < sx) s = sy;

   m_view->scale(s, s);

}

/*---------------------------------------------------------------------------*/
