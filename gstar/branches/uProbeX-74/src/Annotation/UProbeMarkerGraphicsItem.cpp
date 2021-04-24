/*-----------------------------------------------------------------------------
 * Copyright (c) 2013, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include "UProbeMarkerGraphicsItem.h"

#include "AnnotationProperty.h"
#include "CoordinateModel.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QDebug>

using namespace gstar;

/*---------------------------------------------------------------------------*/

UProbeMarkerGraphicsItem::UProbeMarkerGraphicsItem(AbstractGraphicsItem* parent)
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

   m_measuredXProp = new AnnotationProperty(UPROBE_MICRO_POS_X, 0.0);
   m_measuredYProp = new AnnotationProperty(UPROBE_MICRO_POS_Y, 0.0);

   m_sizeProp = new AnnotationProperty("Size", 20.0);


   m_data.push_back(m_outlineColorProp);
   m_data.push_back(m_positionXProp);
   m_data.push_back(m_positionYProp);
   m_data.push_back(m_positionZProp);

   m_data.push_back(m_predictXProp);
   m_data.push_back(m_predictYProp);

   m_data.push_back(m_measuredXProp);
   m_data.push_back(m_measuredYProp);

   //m_data.push_back(m_sizeProp);

   setSize(m_sizeProp->getValue().toDouble());

   connectAllProperties();

}

/*---------------------------------------------------------------------------*/

QRectF UProbeMarkerGraphicsItem::boundingRect() const
{

   return m_polygon.boundingRect();

}

/*---------------------------------------------------------------------------*/

void UProbeMarkerGraphicsItem::calculate()
{

   //nothing to calculate

}

/*---------------------------------------------------------------------------*/

const QString UProbeMarkerGraphicsItem::displayName() const
{

   const QString name = QString("Calibration Point");
   return name;

}

/*---------------------------------------------------------------------------*/

AbstractGraphicsItem* UProbeMarkerGraphicsItem::duplicate()
{

   UProbeMarkerGraphicsItem* item = new UProbeMarkerGraphicsItem();

   QColor color(m_outlineColorProp->getValue().toString());
   item->setColor(color);
   item->setSize(m_sizeProp->getValue().toDouble());
   item->setPos(pos());
   return item;

}

/*---------------------------------------------------------------------------*/

void UProbeMarkerGraphicsItem::paint(QPainter* painter,
           const QStyleOptionGraphicsItem* option,
           QWidget* widget)
{

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
   painter->setBrush(m_outlineColor);
   painter->drawPolygon(m_polygon);

}

/*---------------------------------------------------------------------------*/

void UProbeMarkerGraphicsItem::setMouseOverPixelCoordModel(CoordinateModel* model)
{

   if(m_mouseOverPixelCoordModel != NULL)
   {
      disconnect(m_mouseOverPixelCoordModel,
                 SIGNAL(modelUpdated()),
                 this,
                 SLOT(updateModel()));
   }

   m_mouseOverPixelCoordModel = model;

   connect(m_mouseOverPixelCoordModel,
           SIGNAL(modelUpdated()),
           this,
           SLOT(updateModel()));
}

/*---------------------------------------------------------------------------*/

void UProbeMarkerGraphicsItem::setLightToMicroCoordModel(CoordinateModel* model)
{

   if(m_lightToMicroCoordModel != NULL)
   {
      disconnect(m_lightToMicroCoordModel,
                 SIGNAL(modelUpdated()),
                 this,
                 SLOT(updateModel()));
   }

   m_lightToMicroCoordModel = model;

   connect(m_lightToMicroCoordModel,
           SIGNAL(modelUpdated()),
           this,
           SLOT(updateModel()));

}

/*---------------------------------------------------------------------------*/

void UProbeMarkerGraphicsItem::setColor(QColor color)
{

   m_outlineColor = color;

}

/*---------------------------------------------------------------------------*/

void UProbeMarkerGraphicsItem::setSize(double size)
{

   m_size = size;
   double halfSize = size * 0.5;
   m_polygon.clear();

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
   m_polygon.push_back(QPoint(lineWidth, halfSize+lineWidth));

   update();

}

/*---------------------------------------------------------------------------*/

QPainterPath UProbeMarkerGraphicsItem::shape() const
{

   QPainterPath path;
   path.addPolygon(m_polygon);
   return path;

}

/*---------------------------------------------------------------------------*/

void UProbeMarkerGraphicsItem::updateModel()
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

void UProbeMarkerGraphicsItem::updateView()
{

   //double x = m_positionXProp->getValue().toDouble();
   //double y = m_positionYProp->getValue().toDouble();

   setSize(m_sizeProp->getValue().toDouble());
   //setX(x);
   //setY(y);

   m_outlineColor = QColor(m_outlineColorProp->getValue().toString());

}

/*---------------------------------------------------------------------------*/
