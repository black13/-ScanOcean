/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ImageViewWidget.h>
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QListView>

using namespace gstar;

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

   updateZoomPercentage();

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
      m_zoomPercent->setEnabled(false);
      m_scene -> setZoomModeToFit();
      resizeEvent(NULL);
   }
   else {
      m_zoomGroup -> setEnabled(true);
      m_zoomPercent->setEnabled(true);
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

void ImageViewWidget::clickZoomOriginal()
{

   // Zoom back to actual image size
   m_view -> resetMatrix();

   // Force update scroll bars
   m_view -> setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   m_view -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

   updateZoomPercentage();

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

void ImageViewWidget::lineButtonTriggered()
{

   // Set zoom out mode
   m_scene -> setDrawLineMode();

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

   // Draw lines on the image
   m_lineDrawAction = new QAction(QIcon(":/images/linepointer.png"),
                                      tr("Draw Lines"), this);
   m_lineDrawAction -> setCheckable(true);
   connect(m_lineDrawAction, SIGNAL(triggered()), this,
          SLOT(lineButtonTriggered()));

   // Zoom action group
   m_zoomGroup = new QActionGroup(this);
   m_zoomGroup -> addAction(m_cursorAction);
   m_zoomGroup -> addAction(m_zoomInAction);
   m_zoomGroup -> addAction(m_zoomOutAction);
   m_zoomGroup -> addAction(m_zoomOriginalAction);
   m_zoomGroup -> addAction(m_lineDrawAction);

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
   m_toolbar -> addSeparator();
   m_toolbar -> addAction(m_lineDrawAction);
   m_toolbar -> addSeparator();


   QLabel* m_lbl = new QLabel("Zoom (%) :");
   m_toolbar->addWidget(m_lbl);

   m_zoomPercent = new QComboBox();
   m_zoomPercent->setEditable(true);

   connect(m_zoomPercent,
           SIGNAL(currentIndexChanged(int)),
           this,
           SLOT(zoomValueChanged()));

   m_zoomSettings.push_front(12.5);
   m_zoomSettings.push_front(25);
   m_zoomSettings.push_front(50);
   m_zoomSettings.push_front(100);
   m_zoomSettings.push_front(200);
   m_zoomSettings.push_front(400);
   m_zoomSettings.push_front(800);

   for (int i=0; i<m_zoomSettings.size(); i++)
   {
      m_zoomPercent->addItem(QString::number(m_zoomSettings.at(i)));
   }

   m_zoomPercent->setCurrentIndex(3);
   m_zoomPercent->setMinimumSize(80, 10);

   m_toolbar->addWidget(m_zoomPercent);
   m_toolbar->addSeparator();


   // Add the range widget and set the status, rank number

   createRangewidget();
   setRangeWidgetEnable(false);
   setRangewidgetVisible(false);



}

/*---------------------------------------------------------------------------*/
void ImageViewWidget::setRangeWidgetEnable(bool m_rangeEnable)
{
   m_range -> setRangewidgetStatus(m_rangeEnable);
   m_comboWidth -> setEnabled(m_rangeEnable);
   m_comboHeight -> setEnabled(m_rangeEnable);
}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::setRangeWidgetStartIndex(int index)
{

   m_range->setValue(index);

}

/*---------------------------------------------------------------------------*/
void ImageViewWidget::setRangewidgetVisible(bool m_rangeVisible)
{
   m_range -> setRangeWidgetVisible(m_rangeVisible);
   m_acomboHeight -> setVisible(m_rangeVisible);
   m_acomboWidth -> setVisible(m_rangeVisible);
   m_ahiglbl -> setVisible(m_rangeVisible);
   m_awidlbl -> setVisible(m_rangeVisible);
   m_widsep -> setVisible(m_rangeVisible);
}

/*---------------------------------------------------------------------------*/
void ImageViewWidget::createRangewidget()
{

   m_range = new RangeWidget();
   //range -> setId(0);
   m_range -> setMaximum(0);
   m_range -> setMinimum(0);
   connect(m_range, SIGNAL(valueChanged(int, int)),
   this, SLOT(rangeChanged(int, int)));
   m_toolbar->addWidget(m_range);

   m_higlbl = new QLabel(" Height :");
   m_ahiglbl = m_toolbar->addWidget(m_higlbl);

   m_comboHeight = new QComboBox();
   m_comboHeight->setEditable(true);
   connect(m_comboHeight, SIGNAL(activated(int)),
           this, SLOT(comboHeightChanged(int)));
   m_acomboHeight = m_toolbar->addWidget(m_comboHeight);

   m_widlbl = new QLabel(" Width :");
   m_awidlbl = m_toolbar->addWidget(m_widlbl);
   m_comboWidth = new QComboBox();
   m_comboWidth->setEditable(true);
   connect(m_comboWidth, SIGNAL(activated(int)),
           this, SLOT(comboWidthChanged(int)));
   m_acomboWidth = m_toolbar->addWidget(m_comboWidth);
   m_widsep = m_toolbar->addSeparator();

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::setNumberOfImages(int images)
{

   m_range->setMinimum(1);
   m_range->setMaximum(images);

}


/*---------------------------------------------------------------------------*/

void ImageViewWidget::setRank(int m_rankDim)
{
   
   m_comboWidth->clear();
   m_comboHeight->clear();

   for (int i = 0 ; i < m_rankDim ; i++) 
   {
        m_comboWidth -> addItem(tr("dim %1").arg(i));
        m_comboHeight -> addItem(tr("dim %1").arg(i));
   }

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::setHeightDims(int h)
{

   if (h > (m_comboHeight->count() - 1)) return;

   disconnect(m_comboHeight, SIGNAL(activated(int)),
              this, SLOT(comboHeightChanged(int)));

   m_comboHeight->setCurrentIndex(h);

   connect(m_comboHeight, SIGNAL(activated(int)),
           this, SLOT(comboHeightChanged(int)));

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::setWidthDims(int w)
{

   if (w > (m_comboWidth->count() - 1)) return;


   disconnect(m_comboWidth, SIGNAL(activated(int)),
              this, SLOT(comboWidthChanged(int)));

   m_comboWidth->setCurrentIndex(w);


   connect(m_comboWidth, SIGNAL(activated(int)),
           this, SLOT(comboWidthChanged(int)));


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

   updateZoomPercentage();

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

void ImageViewWidget::updateZoomPercentage()
{

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

void ImageViewWidget::comboWidthChanged(int value)
{

   emit valueChangedWidth(value);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::comboHeightChanged(int value)
{

   emit valueChangedHeight(value);

}

/*---------------------------------------------------------------------------*/

void ImageViewWidget::rangeChanged(int value, int id)
{
   emit imageViewSignal(value, id);
}
