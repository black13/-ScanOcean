/*-----------------------------------------------------------------------------
 * Copyright (c) 2013, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include "UProbeMarkerGraphicsItem.h"

#include "AnnotationProperty.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QDebug>

using namespace gstar;

/*---------------------------------------------------------------------------*/

UProbeMarkerGraphicsItem::UProbeMarkerGraphicsItem(AbstractGraphicsItem* parent)
   : AbstractGraphicsItem(parent)
{

   m_outlineColor = QColor(106, 200, 106);
   //m_innerColorProp = new AnnotationProperty("Fill Color", m_innerColor);

   m_outlineColorProp = new AnnotationProperty("Color", m_outlineColor);
   m_positionXProp = new AnnotationProperty("LX", QPoint(0, 0));
   m_positionYProp = new AnnotationProperty("LY", QPoint(0, 0));
   m_positionZProp = new AnnotationProperty("LZ", QPoint(0, 0));

   m_measuredXProp = new AnnotationProperty("MX", QPoint(0, 0));
   m_measuredYProp = new AnnotationProperty("MY", QPoint(0, 0));

   m_predictXProp = new AnnotationProperty("PX", QPoint(0, 0));
   m_predictYProp = new AnnotationProperty("PY", QPoint(0, 0));
   m_sizeProp = new AnnotationProperty("Size", 20.0);


   m_data.push_back(m_outlineColorProp);
   m_data.push_back(m_positionXProp);
   m_data.push_back(m_positionYProp);
   m_data.push_back(m_positionZProp);

   m_data.push_back(m_measuredXProp);
   m_data.push_back(m_measuredYProp);

   m_data.push_back(m_predictXProp);
   m_data.push_back(m_predictYProp);
   m_data.push_back(m_sizeProp);


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

   const QString name = QString("UProbeMarker");
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

   m_polygon.push_back(QPoint(-halfSize, -halfSize));
   m_polygon.push_back(QPoint(halfSize, -halfSize));
   m_polygon.push_back(QPoint(0, 0));

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
   m_positionXProp->setValue(position.x());
   m_positionYProp->setValue(position.y());

}

/*---------------------------------------------------------------------------*/

void UProbeMarkerGraphicsItem::updateView()
{

   double x = m_positionXProp->getValue().toDouble();
   double y = m_positionYProp->getValue().toDouble();

   setSize(m_sizeProp->getValue().toDouble());
   setX(x);
   setY(y);

   m_outlineColor = QColor(m_outlineColorProp->getValue().toString());

}

/*---------------------------------------------------------------------------*/
