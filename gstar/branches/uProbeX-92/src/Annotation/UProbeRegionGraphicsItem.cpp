/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include "UProbeRegionGraphicsItem.h""
#include <ImageViewScene.h>
#include <QSize>

using namespace gstar;

/*---------------------------------------------------------------------------*/

UProbeRegionGraphicsItem::UProbeRegionGraphicsItem(AbstractGraphicsItem* parent)
   : AbstractGraphicsItem(parent)
{

   m_mouseOverPixelCoordModel = NULL;
   m_lightToMicroCoordModel = NULL;

   m_outlineColor = QColor(106, 200, 106);
   //m_innerColorProp = new AnnotationProperty("Fill Color", m_innerColor);

   m_outlineColorProp = new AnnotationProperty("Color", m_outlineColor);
   m_positionXProp = new AnnotationProperty(UPROBE_LIGHT_POS_X, 0.0);
   m_positionYProp = new AnnotationProperty(UPROBE_LIGHT_POS_Y, 0.0);
   m_positionZProp = new AnnotationProperty(UPROBE_LIGHT_POS_Z, 0.0);

   m_predictXProp = new AnnotationProperty(UPROBE_PRED_POS_X, 0.0);
   m_predictYProp = new AnnotationProperty(UPROBE_PRED_POS_Y, 0.0);

   m_widthProp = new AnnotationProperty("Width", 60.0);
   m_heightProp = new AnnotationProperty("Height", 60.0);

   m_measuredXProp = new AnnotationProperty(UPROBE_MICRO_POS_X, "0.0");
   m_measuredYProp = new AnnotationProperty(UPROBE_MICRO_POS_Y, "0.0");

   m_sizeProp = new AnnotationProperty("Size", 20.0);


   m_data.push_back(m_outlineColorProp);
   //m_data.push_back(m_positionXProp);
   //m_data.push_back(m_positionYProp);
   //m_data.push_back(m_positionZProp);

   m_data.push_back(m_predictXProp);
   m_data.push_back(m_predictYProp);

   m_data.push_back(m_widthProp);
   m_data.push_back(m_heightProp);

   //m_data.push_back(m_measuredXProp);
   //m_data.push_back(m_measuredYProp);

   //m_data.push_back(m_sizeProp);
   m_rect = QRectF(-30, -30, 60, 60);

   setSize(m_sizeProp->getValue().toDouble());

   connectAllProperties();

   // Initialize rectangle size

   setFlag(QGraphicsItem::ItemSendsGeometryChanges);

   // Accept hover events
   setAcceptHoverEvents(true);

}

/*---------------------------------------------------------------------------*/

UProbeRegionGraphicsItem::UProbeRegionGraphicsItem(QMap<QString, QString>& marker,
                                                   AbstractGraphicsItem* parent)
                                                   : AbstractGraphicsItem(parent)
{

   m_mouseOverPixelCoordModel = NULL;
   m_lightToMicroCoordModel = NULL;

   m_outlineColor = QColor(marker["color"]);

   m_outlineColorProp = new AnnotationProperty("Color", m_outlineColor);
   //m_positionXProp = new AnnotationProperty(UPROBE_LIGHT_POS_X, marker["LX"]);
   //m_positionYProp = new AnnotationProperty(UPROBE_LIGHT_POS_Y, marker["LY"]);
   //m_positionZProp = new AnnotationProperty(UPROBE_LIGHT_POS_Z, marker["LZ"]);

   m_predictXProp = new AnnotationProperty(UPROBE_PRED_POS_X, marker["PX"]);
   m_predictYProp = new AnnotationProperty(UPROBE_PRED_POS_Y, marker["PY"]);

   m_widthProp = new AnnotationProperty("Width", marker["Width"]);
   m_heightProp = new AnnotationProperty("Height", marker["Height"]);

   //m_measuredXProp = new AnnotationProperty(UPROBE_MICRO_POS_X, marker["MX"]);
   //m_measuredYProp = new AnnotationProperty(UPROBE_MICRO_POS_Y, marker["MY"]);

   m_sizeProp = new AnnotationProperty("Size", 20.0);


   m_data.push_back(m_outlineColorProp);
   //m_data.push_back(m_positionXProp);
   //m_data.push_back(m_positionYProp);
   //m_data.push_back(m_positionZProp);

   m_data.push_back(m_predictXProp);
   m_data.push_back(m_predictYProp);

   m_data.push_back(m_widthProp);
   m_data.push_back(m_heightProp);

   //m_data.push_back(m_measuredXProp);
   //m_data.push_back(m_measuredYProp);

   //m_data.push_back(m_sizeProp);

   setSize(m_sizeProp->getValue().toDouble());

   connectAllProperties();

}

/*---------------------------------------------------------------------------*/

QRectF UProbeRegionGraphicsItem::boundingRect() const
{

   // Return bounding rectangle
   return m_rect;

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::calculate()
{

   //nothing to calculate

}

/*---------------------------------------------------------------------------*/

const QString UProbeRegionGraphicsItem::displayName() const
{

   const QString name = QString("Micro Probe Region");
   return name;

}

/*---------------------------------------------------------------------------*/

AbstractGraphicsItem* UProbeRegionGraphicsItem::duplicate()
{

   UProbeRegionGraphicsItem* item = new UProbeRegionGraphicsItem();

   QColor color(m_outlineColorProp->getValue().toString());
   item->setColor(color);
   item->setSize(m_sizeProp->getValue().toDouble());
   item->setPos(pos());
   item->setMouseOverPixelCoordModel(m_mouseOverPixelCoordModel);
   item->setLightToMicroCoordModel(m_lightToMicroCoordModel);
   return item;

}

/*---------------------------------------------------------------------------*/

/*char* UProbeRegionGraphicsItem::getMask()
{

   // Get bounding rectangle
   QRectF boundRect = ((ImageViewScene*) scene()) -> pixRect();

   // Get image dimensions
   int w = boundRect.width();
   int h = boundRect.height();

   // Check image dimensions
   if (w <= 0 || h <= 0) {
      return NULL;
   }

   // Create new image mask
   char* mask = new char[w * h];

   // Loop through each pixel in image
   for (int r = 0 ; r < h ; r++) {
      for (int c = 0 ; c < w ; c++) {

         // Test if pixel is within ROI
         if (contains(mapFromScene(QPointF((float) c, (float) r)))) {
            mask[r * w + c] = 255;
         }
         else {
            mask[r * w + c] = 0;
         }

      }
   }

   // Return mask
   return mask;

}*/

/*---------------------------------------------------------------------------*/

/*void UProbeRegionGraphicsItem::getMask(Array& mask) const
{

   // Get bounding rectangle
   QRectF boundRect = ((ImageViewScene*) scene()) -> pixRect();

   // Get image dimensions
   int w = boundRect.width();
   int h = boundRect.height();

   // Check image dimensions
   if (w <= 0 || h <= 0) {
      return;
   }

   // Memory allocated to mask array is too small
   if (mask.getBytes() < (w * h)) {
      return;
   }

   // Get buffer from array
   uchar* buffer = mask.getBuffer();
   if (buffer == NULL) {
      return;
   }

   // Set array properties
   unsigned long long dims[2];
   dims[0] = h;
   dims[1] = w;
   mask.setRank(2);
   mask.setType(Array::UINT8);
   mask.setDimensions(dims, 2);

   // Loop through each pixel in image
   for (int r = 0 ; r < h ; r++) {
      for (int c = 0 ; c < w ; c++) {

         // Test if pixel is within ROI. If it is, set value to 255,
         // 0 otherwise.
         if (contains(mapFromScene(QPointF((float) c, (float) r)))) {
            buffer[r * w + c] = 255;
         }
         else {
            buffer[r * w + c] = 0;
         }

      }
   }

}*/

/*---------------------------------------------------------------------------*/

double UProbeRegionGraphicsItem::getSceneScale()
{

   // The view's scale
   double scale = 1.0;

   // Get list of views on this scene
   QList<QGraphicsView *> l = scene() -> views();

   // There are no views, so return 1.0
   if (l.isEmpty()) {
      return scale;
   }

   // Get the first view
   QGraphicsView* v = l[0];

   // Get the scale portion of its transform
   QTransform t = v -> transform();
   scale = t.m11();

   // Return the scale
   return scale;

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{

   // Mark unused
   Q_UNUSED(event);

   // Return if item is not selected
   if (!isSelected()) {
      return;
   }

   // Set cursor
   setCursor(Qt::SizeAllCursor);

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{

   // Mark unused
   Q_UNUSED(event);

   // Reset cursor
   unsetCursor();

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{

   // Return if item is not selected
   if (!isSelected()) {
      return;
   }

   // Get scale factor from QGraphicsView
   double scale = getSceneScale();

   // Mouse click position (in item coordinates)
   QPointF pt = event -> pos();
   //qDebug()<<"hoverMoveEvent pt position is"<<pt.x()<<pt.y()<<endl;
   // Check for bottom right grip
   if (pt.x() <= m_rect.right() &&
       pt.y() <= m_rect.bottom() &&
       pt.x() >= m_rect.right() - 6 &&
       pt.y() >= m_rect.bottom() - 6)
   {
      setCursor(Qt::SizeFDiagCursor);
   }
   else if (pt.x() >= m_rect.left() &&
       pt.y() > m_rect.bottom() - 6 &&
       pt.x() < m_rect.left() + 6 &&
       pt.y() <= m_rect.bottom())
   {
      setCursor(Qt::SizeBDiagCursor);
   }
   // Reset cursor
   else {
      setCursor(Qt::OpenHandCursor);
   }

}

/*---------------------------------------------------------------------------*/

/*QVariant UProbeRegionGraphicsItem::itemChange(GraphicsItemChange change,
                              const QVariant& value)
{

   // Check for change in position
   // Only check for one of QGraphicsItem::ItemPositionChange or
   // QGraphicsItem::ItemPositionHasChanged to avoid infinite recursion
   if (change == QGraphicsItem::ItemPositionHasChanged) {

      // Get boundary item rectangle
      QRectF boundRect = ((ImageViewScene*) scene()) -> pixRect();

      // Check bounds
      setPos(qBound(boundRect.left(), pos().x(),
                    boundRect.right() - m_rect.width()),
             qBound(boundRect.top(), pos().y(),
                    boundRect.bottom() - m_rect.height()));

   }

   // Get ItemSelectedHasChanged change
   if (change == QGraphicsItem::ItemSelectedHasChanged) {

      // If this item is the newest one selected then
      // emit itemSelected signal, which should be connected
      // to ROIView, which in turn should deselect all other
      // selected items.
      if (isSelected() == true) {
         emit itemSelected(this);
      }

   }

   return QGraphicsItem::itemChange(change, value);

}*/

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

   // Current mouse position
   QPointF pt = event -> pos();
   //qDebug()<<"pt position is in mouse move"<<pt.x()<<pt.y()<<endl;
   // Last mouse position
   QPointF lpt = event -> lastPos();

   // Get scale factor from QGraphicsView
   double scale = getSceneScale();
   //qDebug()<<"the scale is"<<scale;
   // Get boundary item rectangle
   QRectF boundRect = ((ImageViewScene*) scene()) -> pixRect();
   //qDebug()<<m_rect.top()<<"m rect top and pt.y() is";

   // Check for bottom right grip
   if (m_grip == BottomRight)
   {
      // Indicate geometry change about to occur
      prepareGeometryChange();

      // Check against top edge
      if (pt.y()-m_rect.top() < 12)
      {
         m_rect.setHeight(12);
         m_heightProp -> setValue(12);
      }
      else if (mapToScene(pt).y() >= boundRect.bottom())
      {
         m_rect.setBottom(mapFromScene(boundRect.bottomRight()).y());
         m_heightProp->setValue(mapFromScene(boundRect.bottomRight()).y() - m_rect.top());
      }
      else
      {
         m_rect.setHeight(pt.y()-m_rect.top());
         m_heightProp->setValue(pt.y()-m_rect.top());
      }
      // Check against left edge
      if (pt.x() - m_rect.left() < 12)
      {
         m_rect.setWidth(12);
         m_widthProp->setValue(12);
      }
      else if (mapToScene(pt).x() >= boundRect.right())
      {
         m_rect.setRight(mapFromScene(boundRect.bottomRight()).x());
         m_widthProp->setValue(mapFromScene(boundRect.bottomRight()).x() - m_rect.left());
      }
      else
      {
         m_rect.setWidth(pt.x() - m_rect.left());
         m_widthProp->setValue(pt.x() - m_rect.left());
      }
      // Emit change
      //emit itemChanged(this);
      //qDebug()<<m_rect.bottom()<<" the bottom from scen is"<<endl;
      //this->setPropertyValue("Width", 160.0);
      setPos(pos().x()+1,pos().y());
   }
   else if(m_grip == BottomLeft)
   {
      // Indicate geometry change about to occur
      prepareGeometryChange();

      // Check against top edge
      if (pt.y() -m_rect.top() < 12)
      {
         m_rect.setHeight(12);
      }
      else if (mapToScene(pt).y() >= boundRect.bottom())
      {
         m_rect.setBottom(mapFromScene(boundRect.bottomRight()).y());
      }
      else
      {
         m_rect.setHeight(pt.y()-m_rect.top());
      }

      // Check against right edge
      if( m_rect.right() - pt.x() < 12)
      {
         //m_rect.setX(pt.x());
         m_rect.setWidth(12);
      }
      else if (mapToScene(pt).x() <= boundRect.left())
      {
         m_rect.setLeft(mapFromScene(boundRect.bottomLeft()).x());
      }
      else
      {
         m_rect.setX(pt.x());
         //qDebug()<<"the left x is "<<m_rect.left();
      }
   }
   // No grip selected (this is a move)
   else {
      // Queue an update
      update();

      // Pass mouse position
      QGraphicsItem::mouseMoveEvent(event);
      setPos(pos().x(),pos().y());

      // Check bounds
/*      setPos(qBound(boundRect.left(), pos().x(),
                    boundRect.right() - m_rect.width()),
             qBound(boundRect.top(), pos().y(),
                    boundRect.bottom() - m_rect.height()));*/
      // Emit change
      //emit itemChanged(this);

   }

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

   // Get scale factor from QGraphicsView
   double scale = getSceneScale();

   // Mouse click position (in item coordinates)
   QPointF pt = event -> pos();

   // Check for bottom right grip
   if (pt.x() <= m_rect.right() &&
       pt.y() <= m_rect.bottom() &&
       pt.x() >= m_rect.right() - 6 &&
       pt.y() >= m_rect.bottom() - 6)
   {
      m_grip = BottomRight;
   }
   else if(pt.x() >= m_rect.left() &&
       pt.y() > m_rect.bottom() - 6 &&
       pt.x() < m_rect.left() + 6 &&
       pt.y() <= m_rect.bottom())
   {
      m_grip = BottomLeft;
   }
   // No grip selected
   else
   {
      m_grip = None;
   }

   // Queue an update
   update();

   // Pass mouse event
   QGraphicsItem::mousePressEvent(event);

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

   // No grip selected
   m_grip = None;

   // Queue an update
   update();

   // Pass mouse event
   QGraphicsItem::mouseReleaseEvent(event);

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::paint(QPainter* painter,
                     const QStyleOptionGraphicsItem* option,
                     QWidget* widget)
{
/*
   // Mark unused
   Q_UNUSED(widget);

   // Get scale factor from QGraphicsView
   double scale = getSceneScale();

   // Save initial pen
   QPen oldPen = painter -> pen();

   // New pen for drawing ROI item
   QPen pen;

   // Make pen cosmetic
   pen.setCosmetic(true);

   // Set width and color
   pen.setWidthF(2.0);
   pen.setColor(m_outlineColor);
   painter -> setPen(pen);

   // Draw ROI as rect
   painter -> drawRect(m_rect);*/

   // Draw text string on top of ROI
   //painter -> drawText(QPointF(x1, y2), m_text);

   // Draw outline and grips if item is selected
/*   if (option -> state & QStyle::State_Selected) {

      // Set style, width and color
      pen.setStyle(Qt::DashLine);
      pen.setWidthF(1.0);
      pen.setColor(Qt::cyan);
      painter -> setPen(pen);

      // Draw outline as rectangle
      painter -> drawRect(m_rect);

      // Solid line for grips
      pen.setStyle(Qt::SolidLine);
      painter -> setPen(pen);

      // Draw grip
      QRectF grip(m_rect.right() - 8 / scale,
                  m_rect.bottom() - 8 / scale,
                  8 / scale,
                  8 / scale);
      painter -> drawRect(grip);

   }*/

   // Restore old pen: not sure if this is needed
   //painter -> setPen(oldPen);


   Q_UNUSED(widget);

   QTransform trans = getFirstViewTransform();
   if (trans.isScaling())
   {
      bool isInvertable = false;
      QTransform invTrans = trans.inverted(&isInvertable);
      if (isInvertable)
      {
         double xScale = invTrans.m11();
         //double yScale = invTrans.m22();
         double s = scale();
         if (s != xScale)
         {
            setScale(xScale);
         }
         //scale(xScale, yScale);
      }
   }
   else
   {
      double s = scale();
      //rescale to 1 if otherwise
      if (s != 1.0)
      {
         setScale(1.0);
      }
   }

   QPen pen(m_outlineColor);
   if (option->state & QStyle::State_Selected)
   {
      pen.setStyle(Qt::DotLine);
      pen.setWidth(2);
   }
   painter->setPen(pen);
   //painter->setBrush(m_outlineColor);
   painter->drawRect(m_rect);


/*
   if (option->state & QStyle::State_Selected)
   {
      double scale = getSceneScale();

      pen.setStyle(Qt::SolidLine);
      painter -> setPen(pen);

      QRectF grip(m_rect.right() - 8 / scale,
                  m_rect.bottom() - 8 / scale,
                  8 / scale,
                  8 / scale);
      painter -> drawRect(grip);

   }*/



}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::setColor(const QColor& color)
{

   // Set color
   m_outlineColor = color;

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::setHeight(double height)
{

   // Prepare for change
   prepareGeometryChange();

   // Set width
   m_rect.setHeight(height);

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::setMouseOverPixelCoordModel(CoordinateModel* model)
{

   if(m_mouseOverPixelCoordModel != NULL)
   {
      disconnect(m_mouseOverPixelCoordModel,
                 SIGNAL(modelUpdated()),
                 this,
                 SLOT(updateModel()));
   }

   m_mouseOverPixelCoordModel = model;

   if(m_mouseOverPixelCoordModel != NULL)
   {
      connect(m_mouseOverPixelCoordModel,
              SIGNAL(modelUpdated()),
              this,
              SLOT(updateModel()));
   }

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::setLightToMicroCoordModel(CoordinateModel* model)
{

   if(m_lightToMicroCoordModel != NULL)
   {
      disconnect(m_lightToMicroCoordModel,
                 SIGNAL(modelUpdated()),
                 this,
                 SLOT(updateModel()));
   }

   m_lightToMicroCoordModel = model;

   if(m_lightToMicroCoordModel != NULL)
   {
      connect(m_lightToMicroCoordModel,
              SIGNAL(modelUpdated()),
              this,
              SLOT(updateModel()));
   }

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::setSize(double size)
{

   m_size = size;

   double halfSize = size * 0.5;
   //m_polygon.clear();


   //setPos(x, y);
/*



   double lineWidth =2;
   m_polygon.push_back(QPoint(-lineWidth, halfSize+lineWidth));
   m_polygon.push_back(QPoint(-lineWidth, lineWidth));
   m_polygon.push_back(QPoint(-(halfSize+lineWidth), lineWidth));
   m_polygon.push_back(QPoint(-(halfSize+lineWidth), -lineWidth));
   m_polygon.push_back(QPoint(-lineWidth, -lineWidth));
   m_polygon.push_back(QPoint(-lineWidth, -(halfSize+lineWidth)));

   m_polygon.push_back(QPoint(lineWidth, -(halfSize+lineWidth)));
   m_polygon.push_back(QPoint(lineWidth, -lineWidth));
   m_polygon.push_back(QPoint((halfSize+lineWidth), -lineWidth));
   m_polygon.push_back(QPoint((halfSize+lineWidth), lineWidth));
   m_polygon.push_back(QPoint(lineWidth, lineWidth));
   m_polygon.push_back(QPoint(lineWidth, halfSize+lineWidth));*/

   update();

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::setWidth(double width)
{

   // Prepare for change
   prepareGeometryChange();

   // Set width
   m_rect.setWidth(width);

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::setX(double x)
{

   // Prepare for change
   prepareGeometryChange();

   // Set x
   setPos(x, pos().y());

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::setY(double y)
{

   // Prepare for change
   prepareGeometryChange();

   // Set y
   setPos(pos().x(), y);

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::updateModel()
{

   QPointF position = pos();
   m_sizeProp->setValue(m_size);

   if(m_mouseOverPixelCoordModel != NULL)
   {
      double x,y,z;
      m_mouseOverPixelCoordModel->runTransformer((double)position.x(),
                                                 (double)position.y(),
                                                 0.0,
                                                 &x,
                                                 &y,
                                                 &z);
      m_positionXProp->setValue(x);
      m_positionYProp->setValue(y);


      if(m_lightToMicroCoordModel != NULL)
      {
         double x1,y1,z1;
         m_lightToMicroCoordModel->runTransformer(x,
                                                  y,
                                                  0.0,
                                                  &x1,
                                                  &y1,
                                                  &z1);
         m_predictXProp->setValue(x1);
         m_predictYProp->setValue(y1);
      }

   }
   else
   {
      m_positionXProp->setValue(position.x());
      m_positionYProp->setValue(position.y());

      m_predictXProp->setValue(0.0);
      m_predictYProp->setValue(0.0);
   }

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::updateView()
{
   //double x = m_positionXProp->getValue().toDouble();
   //double y = m_positionYProp->getValue().toDouble();

   setSize(m_sizeProp->getValue().toDouble());
   //setX(x);
   //setY(y);

   m_outlineColor = QColor(m_outlineColorProp->getValue().toString());

}

/*---------------------------------------------------------------------------*/

