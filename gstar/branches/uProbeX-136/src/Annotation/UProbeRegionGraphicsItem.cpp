/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include "UProbeRegionGraphicsItem.h"
#include "GStarResource.h"
#include <ImageViewScene.h>
#include <QSize>

using namespace gstar;

/*---------------------------------------------------------------------------*/

UProbeRegionGraphicsItem::UProbeRegionGraphicsItem(AbstractGraphicsItem* parent)
   : AbstractGraphicsItem(parent)
{

   m_mouseOverPixelCoordModel = NULL;
   m_lightToMicroCoordModel = NULL;

   m_outlineColor = QColor(255, 0, 127);
   m_rect = QRectF(-300, -300, 600, 600);
   // The grip size of the grip rect
   setGripSize();

   m_outlineColorProp = new AnnotationProperty(UPROBE_COLOR, m_outlineColor);

   m_predictXProp = new AnnotationProperty(UPROBE_PRED_POS_X, 0.0);
   m_predictYProp = new AnnotationProperty(UPROBE_PRED_POS_Y, 0.0);

   m_widthProp = new AnnotationProperty(UPROBE_WIDTH, 0.0);
   m_heightProp = new AnnotationProperty(UPROBE_HEIGHT, 0.0);

   m_measuredXProp = new AnnotationProperty(UPROBE_MICRO_POS_X, "0.0");
   m_measuredYProp = new AnnotationProperty(UPROBE_MICRO_POS_Y, "0.0");

   m_sizeProp = new AnnotationProperty(UPROBE_SIZE, 20.0);

   m_data.push_back(m_outlineColorProp);

   m_data.push_back(m_predictXProp);
   m_data.push_back(m_predictYProp);

   m_data.push_back(m_widthProp);
   m_data.push_back(m_heightProp);

   setSize(m_sizeProp->getValue().toDouble());

   connectAllProperties();

   // Initialize rectangle size
   setFlag(QGraphicsItem::ItemSendsGeometryChanges);
   // Accept hover events
   setAcceptHoverEvents(true);

   initialScale();

}

/*---------------------------------------------------------------------------*/

UProbeRegionGraphicsItem::UProbeRegionGraphicsItem(QMap<QString, QString>& marker,
                                                   AbstractGraphicsItem* parent)
                                                   : AbstractGraphicsItem(parent)
{

   m_mouseOverPixelCoordModel = NULL;
   m_lightToMicroCoordModel = NULL;


   m_outlineColor = QColor(marker[UPROBE_COLOR]);
   m_rect = QRectF(marker["TopLeftX"].toDouble(),
                   marker["TopLeftY"].toDouble(),
                   marker["RectWidth"].toDouble(),
                   marker["RectHeight"].toDouble());
   setGripSize();

   m_outlineColorProp = new AnnotationProperty(UPROBE_COLOR, m_outlineColor);
   m_predictXProp = new AnnotationProperty(UPROBE_PRED_POS_X, marker[UPROBE_PRED_POS_X]);
   m_predictYProp = new AnnotationProperty(UPROBE_PRED_POS_Y, marker[UPROBE_PRED_POS_Y]);
   m_widthProp = new AnnotationProperty(UPROBE_WIDTH, 0.0);
   m_heightProp = new AnnotationProperty(UPROBE_HEIGHT, 0.0);
   m_sizeProp = new AnnotationProperty(UPROBE_SIZE, 20.0);


   m_data.push_back(m_outlineColorProp);
   m_data.push_back(m_predictXProp);
   m_data.push_back(m_predictYProp);
   m_data.push_back(m_widthProp);
   m_data.push_back(m_heightProp);


   setSize(m_sizeProp->getValue().toDouble());

   connectAllProperties();

   setFlag(QGraphicsItem::ItemSendsGeometryChanges);
   // Accept hover events
   setAcceptHoverEvents(true);

   initialScale();

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
   item->setPos(pos());
   item->setSameRect(m_rect);

   item->setMouseOverPixelCoordModel(m_mouseOverPixelCoordModel);
   item->setLightToMicroCoordModel(m_lightToMicroCoordModel);
   return item;

}

/*---------------------------------------------------------------------------*/

double UProbeRegionGraphicsItem::getFactorX()
{

   //TODO: add annotation property
   return 1.0;

}

/*---------------------------------------------------------------------------*/

double UProbeRegionGraphicsItem::getFactorY()
{

   //TODO: add annotation property
   return 1.0;

}

/*---------------------------------------------------------------------------*/

double UProbeRegionGraphicsItem::getHeight()
{

   return m_heightProp->getValue().toDouble();

}

/*---------------------------------------------------------------------------*/

double UProbeRegionGraphicsItem::getWidth()
{

   return m_widthProp->getValue().toDouble();

}

/*---------------------------------------------------------------------------*/

double UProbeRegionGraphicsItem::getX()
{

   return m_predictXProp->getValue().toDouble();

}

/*---------------------------------------------------------------------------*/

double UProbeRegionGraphicsItem::getY()
{

   return m_predictYProp->getValue().toDouble();

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

   // Mouse click position (in item coordinates)
   QPointF pt = event -> pos();

   // Check for bottom right grip
   if (pt.x() <= m_rect.right() &&
       pt.y() <= m_rect.bottom() &&
       pt.x() >= m_rect.right() - m_gripSize &&
       pt.y() >= m_rect.bottom() - m_gripSize)
   {
      setCursor(Qt::SizeFDiagCursor);
   }// bottom left
   else if (pt.x() >= m_rect.left() &&
       pt.y() >= m_rect.bottom() - m_gripSize &&
       pt.x() <= m_rect.left() + m_gripSize &&
       pt.y() <= m_rect.bottom())
   {
      setCursor(Qt::SizeBDiagCursor);
   }//top left
   else if (pt.x() <= m_rect.left() + m_gripSize &&
       pt.y() <= m_rect.top() + m_gripSize &&
       pt.x() >= m_rect.left() &&
       pt.y() >= m_rect.top())
   {
      setCursor(Qt::SizeFDiagCursor);
   }//top right
   else if (pt.x() >= m_rect.right() - m_gripSize &&
       pt.y() >= m_rect.top()&&
       pt.x() <= m_rect.right() &&
       pt.y() <= m_rect.top() + m_gripSize )
   {
      setCursor(Qt::SizeBDiagCursor);
   }
   // Reset cursor
   else {
      setCursor(Qt::OpenHandCursor);
   }

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::initialScale()
{

   QTransform trans = getFirstViewTransform();
      if (trans.isScaling())
      {
         bool isInvertable = false;
         QTransform invTrans = trans.inverted(&isInvertable);
         if (isInvertable)
         {
            double xScale = invTrans.m11();
            double s = scale();
            if (s != xScale)
            {
               setScale(100*xScale);
            }
         }
      }

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

   // Current mouse position
   QPointF pt = event -> pos();

   // Last mouse position
   QPointF lpt = event -> lastPos();

   // Get boundary item rectangle
   QRectF boundRect = ((ImageViewScene*) scene()) -> pixRect();

   // Check for bottom right grip
   if (m_grip == BottomRight)
   {
      // Indicate geometry change about to occur
      prepareGeometryChange();

      // Check against top edge
      if (pt.y()-m_rect.top() < m_gripSize*2)
      {
         m_rect.setHeight(m_gripSize*2);
      }
      else if (mapToScene(pt).y() >= boundRect.bottom())
      {
         m_rect.setBottom(mapFromScene(boundRect.bottomRight()).y());
      }
      else
      {
         m_rect.setHeight(pt.y()-m_rect.top());
      }
      // Check against left edge
      if (pt.x() - m_rect.left() < m_gripSize*2)
      {
         m_rect.setWidth(m_gripSize*2);
      }
      else if (mapToScene(pt).x() >= boundRect.right())
      {
         m_rect.setRight(mapFromScene(boundRect.bottomRight()).x());
      }
      else
      {
         m_rect.setWidth(pt.x() - m_rect.left());
      }

   }
   else if(m_grip == BottomLeft)
   {
      // Indicate geometry change about to occur
      prepareGeometryChange();

      // Check against top edge
      if (pt.y() -m_rect.top() < m_gripSize*2)
      {
         m_rect.setHeight(m_gripSize*2);
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
      if( m_rect.right() - pt.x() < m_gripSize*2)
      {
         //m_rect.setX(pt.x());
         m_rect.setWidth(m_gripSize*2);
      }
      else if (mapToScene(pt).x() <= boundRect.left())
      {
         m_rect.setLeft(mapFromScene(boundRect.bottomLeft()).x());
      }
      else
      {
         m_rect.setX(pt.x());
      }
   }
   else if(m_grip == TopLeft)
   {
      prepareGeometryChange();
      // Check against top edge
      if (m_rect.bottom() - pt.y() < m_gripSize*2)
      {
         m_rect.setHeight(m_gripSize*2);
      }
      else if (mapToScene(pt).y() <= boundRect.top())
      {
         m_rect.setTop(mapFromScene(boundRect.topLeft()).y());
      }
      else
      {
         m_rect.setY(pt.y());
         //m_rect.setHeight(m_rect.bottom() - pt.y());
      }
      // Check against left edge
      if(m_rect.right() - pt.x() < m_gripSize*2)
      {
         m_rect.setWidth(m_gripSize*2);
      }
      else if (mapToScene(pt).x() <= boundRect.left())
      {
         m_rect.setLeft(mapFromScene(boundRect.bottomLeft()).x());
      }
      else
      {
         m_rect.setX(pt.x());
      }

   }
   else if(m_grip == TopRight)
   {
      prepareGeometryChange();
      // Check against top edge
      if (m_rect.bottom() - pt.y() < m_gripSize*2)
      {
         m_rect.setHeight(m_gripSize*2);
      }
      else if (mapToScene(pt).y() <= boundRect.top())
      {
         m_rect.setTop(mapFromScene(boundRect.topLeft()).y());
      }
      else
      {
         m_rect.setY(pt.y());
      }
      // Check against left edge
      if (pt.x() - m_rect.left() < m_gripSize*2)
      {
         m_rect.setWidth(m_gripSize*2);
      }
      else if (mapToScene(pt).x() >= boundRect.right())
      {
         m_rect.setRight(mapFromScene(boundRect.bottomRight()).x());
      }
      else
      {
         m_rect.setWidth(pt.x() - m_rect.left());
      }
   }
   // No grip selected (this is a move)
   else {
      // Queue an update
      update();

      // Pass mouse position
      QGraphicsItem::mouseMoveEvent(event);
      setPos(pos().x(), pos().y());

      // Check bounds
/*      setPos(qBound(boundRect.left(), pos().x(),
                    boundRect.right() - m_rect.width()),
             qBound(boundRect.top(), pos().y(),
                    boundRect.bottom() - m_rect.height()));*/
      // Emit change
      //emit itemChanged(this);

   }

   setPos(pos().x()+1,pos().y());
   setPos(pos().x()-1,pos().y());

   setGripSize();

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

   // Mouse click position (in item coordinates)
   QPointF pt = event -> pos();

   // Check for bottom right grip
   if (pt.x() <= m_rect.right() &&
       pt.y() <= m_rect.bottom() &&
       pt.x() >= m_rect.right() - m_gripSize &&
       pt.y() >= m_rect.bottom() - m_gripSize)
   {
      m_grip = BottomRight;
   }// bottom left
   else if (pt.x() >= m_rect.left() &&
       pt.y() >= m_rect.bottom() - m_gripSize &&
       pt.x() <= m_rect.left() + m_gripSize &&
       pt.y() <= m_rect.bottom())
   {
      m_grip = BottomLeft;
   }//top left
   else if (pt.x() <= m_rect.left() + m_gripSize &&
       pt.y() <= m_rect.top() + m_gripSize &&
       pt.x() >= m_rect.left() &&
       pt.y() >= m_rect.top())
   {
      m_grip = TopLeft;
   }//top right
   else if (pt.x() >= m_rect.right() - m_gripSize &&
       pt.y() >= m_rect.top()&&
       pt.x() <= m_rect.right() &&
       pt.y() <= m_rect.top() + m_gripSize )
   {
      m_grip = TopRight;
   }
   // Reset cursor
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

   Q_UNUSED(widget);
   // Draw the center of the rect.

   // Draw grip box
   QRectF gripBottomLeft(m_rect.left(),
                   m_rect.bottom() - m_gripSize,
                   m_gripSize, m_gripSize);

   QRectF gripBottomRight(m_rect.right() - m_gripSize,
                    m_rect.bottom() - m_gripSize,
                    m_gripSize, m_gripSize);

   QRectF gripTopLeft(m_rect.left(),
                      m_rect.top(),
                      m_gripSize, m_gripSize);

   QRectF gripTopRight(m_rect.right() - m_gripSize,
                       m_rect.top(),
                       m_gripSize, m_gripSize);


   QPen pen(m_outlineColor);
   if (option->state & QStyle::State_Selected)
   {
      pen.setStyle(Qt::DotLine);
      pen.setWidth(2);

   }
   pen.setCosmetic(true);

   painter->setPen(pen);
   painter->drawRect(m_rect);

   /*   QVector<QLineF> crossLines;
      qreal x = m_rect.center().x();
      qreal y = m_rect.center().y();
      crossLines<<QLineF(QPointF(m_rect.left(), y), QPointF(m_rect.right(), y))
                <<QLineF(QPointF(x, m_rect.top()), QPointF(x, m_rect.bottom()));*/
   //painter->drawLines(crossLines);

   if(m_rect.width()<10&&m_rect.height()<10)
   {
      painter->drawPoint(m_rect.center());
   }
   else
   {
      // Draw the crosshair in the center of the region box.
      double midX = m_rect.left() + ( ( m_rect.right() - m_rect.left() ) * 0.5);
      double midY = m_rect.bottom() + ( ( m_rect.top() - m_rect.bottom() ) * 0.5);
      double thirdX = ( m_rect.right() - m_rect.left() ) * 0.1;
      double thirdY = ( m_rect.top() - m_rect.bottom() ) * 0.1;
      double cX = m_rect.center().x();
      double cY = m_rect.center().y();
      painter->drawLine(midX, cY - thirdY, midX, cY + thirdY);
      painter->drawLine(cX - thirdX, midY, cX + thirdX, midY);
   }
   
   painter->drawRect(gripBottomLeft);
   painter->drawRect(gripBottomRight);
   painter->drawRect(gripTopLeft);
   painter->drawRect(gripTopRight);

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::setColor(const QColor& color)
{

   // Set color
   m_outlineColor = color;

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::setGripSize()
{

   if (m_rect.width() < m_rect.height())
   {
      m_gripSize = 0.1 * m_rect.width();
   }
   else
   {
      m_gripSize = 0.1 * m_rect.height();
   }

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

void UProbeRegionGraphicsItem::setSameRect(QRectF& rect)
{

   // Prepare for change
   prepareGeometryChange();

   // Set y
   m_rect = rect;

}

/*---------------------------------------------------------------------------*/

void UProbeRegionGraphicsItem::setSize(double size)
{

   m_size = size;

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

   // Center needs to be calculated uProbe position
   QPointF position = mapToScene(m_rect.center());

   QPointF topLeft = mapToScene(m_rect.topLeft());
   QPointF topRight = mapToScene(m_rect.topRight());
   QPointF bottomRight = mapToScene(m_rect.bottomRight());

   if(m_mouseOverPixelCoordModel != NULL)
   {
      double x,y,z;
      m_mouseOverPixelCoordModel->runTransformer((double)position.x(),
                                                 (double)position.y(),
                                                 0.0,
                                                 &x,
                                                 &y,
                                                 &z);

      double topLeftX, topLeftY, topLeftZ;
      double topRightX, topRightY, topRightZ;
      double bottomRightX, bottomRightY, bottomRightZ;
      m_mouseOverPixelCoordModel->runTransformer((double)topLeft.x(),
                                                 (double)topLeft.y(),
                                                 0.0,
                                                 &topLeftX,
                                                 &topLeftY,
                                                 &topLeftZ);
      m_mouseOverPixelCoordModel->runTransformer((double)topRight.x(),
                                                 (double)topRight.y(),
                                                 0.0,
                                                 &topRightX,
                                                 &topRightY,
                                                 &topRightZ);
      m_mouseOverPixelCoordModel->runTransformer((double)bottomRight.x(),
                                                 (double)bottomRight.y(),
                                                 0.0,
                                                 &bottomRightX,
                                                 &bottomRightY,
                                                 &bottomRightZ);

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
//         m_predictXProp->setValue(QString::number(x1, 'f', m_decimalPreci));
//         m_predictYProp->setValue(QString::number(y1, 'f', m_decimalPreci));

         double topLeftX1, topLeftY1, topLeftZ1;
         double topRightX1, topRightY1, topRightZ1;
         double bottomRightX1, bottomRightY1, bottomRightZ1;
         m_lightToMicroCoordModel->runTransformer(topLeftX,
                                                  topLeftY,
                                                  0.0,
                                                  &topLeftX1,
                                                  &topLeftY1,
                                                  &topLeftZ1);
         m_lightToMicroCoordModel->runTransformer(topRightX,
                                                  topRightY,
                                                  0.0,
                                                  &topRightX1,
                                                  &topRightY1,
                                                  &topRightZ1);
         m_lightToMicroCoordModel->runTransformer(bottomRightX,
                                                  bottomRightY,
                                                  0.0,
                                                  &bottomRightX1,
                                                  &bottomRightY1,
                                                  &bottomRightZ1);

         m_widthProp->setValue(topLeftX1-topRightX1);
         m_heightProp->setValue(topRightY1-bottomRightY1);

//         m_widthProp->setValue(QString::number((topLeftX1-topRightX1), 'f', m_decimalPreci));
//         m_heightProp->setValue(QString::number((topRightY1-bottomRightY1), 'f', m_decimalPreci));

      }

   }
   else
   {
      m_predictXProp->setValue(0.0);
      m_predictYProp->setValue(0.0);
      m_widthProp->setValue(topRight.x()-topLeft.x());
      m_heightProp->setValue(bottomRight.y()-topRight.y());
//      m_widthProp->setValue(QString::number((topRight.x()-topLeft.x()), 'f', m_decimalPreci));
//      m_heightProp->setValue(QString::number((bottomRight.y()-topRight.y()), 'f', m_decimalPreci));
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

