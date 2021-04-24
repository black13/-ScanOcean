/*-----------------------------------------------------------------------------
 * Copyright (c) 2013, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include "LineGraphicsItem.h"

#include "AnnotationProperty.h"
//#include "Node.h"

#include <algorithm>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QDebug>

using namespace gstar;

/*---------------------------------------------------------------------------*/

LineGraphicsItem::LineGraphicsItem(AbstractGraphicsItem* parent)
   : AbstractGraphicsItem(parent)
{

   m_isMovable = false;
   m_isSelected = false;
   m_text = "";
   m_lineColor = QColor(206, 106, 106);
   m_moveType = LINE;
   m_nodeSize = 4;

   m_line = new QGraphicsLineItem(this);

   //setup model properties
   m_lineColorProp = new AnnotationProperty("Color", m_lineColor);
   m_startXProp = new AnnotationProperty("Point1 X", -20.0);
   m_startYProp = new AnnotationProperty("Point1 Y", 0.0);
   m_endXProp = new AnnotationProperty("Point2 X", 20.0);
   m_endYProp = new AnnotationProperty("Point2 Y", 0.0);

   m_data.push_back(m_lineColorProp);
   m_data.push_back(m_startXProp);
   m_data.push_back(m_startYProp);
   m_data.push_back(m_endXProp);
   m_data.push_back(m_endYProp);

   QLineF line(-20, 0, 20, 0);
   m_line->setLine(line);

   connectAll();

}

/*---------------------------------------------------------------------------*/

LineGraphicsItem::~LineGraphicsItem()
{

   delete m_line;

}

/*---------------------------------------------------------------------------*/

QRectF LineGraphicsItem::boundingRect() const
{

   QRectF r = m_line->boundingRect();
   r.adjust(-14, -14, 14, 14);
   return r;

}

/*---------------------------------------------------------------------------*/

bool LineGraphicsItem::checkBoundPos(QPointF newPos, QPointF offset)
{

   newPos += offset;

   QRectF bRect;
   bRect.adjust(-m_nodeSize, -m_nodeSize, m_nodeSize, m_nodeSize);
   double halfW = bRect.width() * 0.5;
   double halfH = bRect.height() * 0.5;
   QPointF halfP(halfW, halfH);
   QRectF rect = scene()->sceneRect();

   if (!rect.contains(newPos + halfP) ||
       !rect.contains(newPos - halfP))
   {

      double xp = newPos.x();
      if ((xp + halfW) > rect.right())
      {
         return true;
      }
      else if ((xp - halfW) < rect.left())
      {
         return true;
      }

      double yp = newPos.y();
      if ((yp + halfH) > rect.bottom())
      {
         yp = rect.bottom() - halfH;
         return true;
      }
      else if ((yp - halfH) < rect.top())
      {
         yp = rect.top() + halfH;
         return true;
      }

   }

   return false;

}

/*---------------------------------------------------------------------------*/

void LineGraphicsItem::connectAll()
{

   connectAllViewItems();
   connectAllProperties();

}

/*---------------------------------------------------------------------------*/

const QString LineGraphicsItem::displayName() const
{

   const QString name = QString("Line");
   return name;

}

/*---------------------------------------------------------------------------*/

void LineGraphicsItem::disconnectAll()
{

   disconnectAllViewItems();
   disconnectAllProperties();

}

/*---------------------------------------------------------------------------*/

QPointF LineGraphicsItem::endNodePos()
{

   return m_line->line().p2();

}

/*---------------------------------------------------------------------------*/

QVariant LineGraphicsItem::itemChange(GraphicsItemChange change,
                                          const QVariant& value)
{

   if (change == ItemPositionChange && scene())
   {
      QPointF newPos = value.toPointF();

      QLineF line = m_line->line();
      if (checkBoundPos(line.p1(), newPos))
      {
         return pos();
      }
      if (checkBoundPos(line.p2(), newPos))
      {
         return pos();
      }
   }
   else if (change == QGraphicsItem::ItemSelectedHasChanged)
   {
     bool selected = value.toBool();
     if (selected)
     {
        setZValue( 999 );
     }
     else
     {
        setZValue( 0 );
     }
   }
   return QGraphicsItem::itemChange(change, value);

}

/*---------------------------------------------------------------------------*/

void LineGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

   QPointF delta = event->pos() - event->lastPos();
   if (m_moveType == LINE)
   {
      setPos(pos() + delta);
      QGraphicsItem::mouseMoveEvent(event);
   }
   else if (m_moveType == P1)
   {
      QLineF line = m_line->line();
      QPointF p1 = line.p1();
      QPointF nP1 = p1 + delta;

      if (checkBoundPos(nP1, pos()) == false)
      {
         line.setP1(p1 + delta);
         m_line->setLine(line);
         //fix for paint issue but messes up bounds check
         QPointF myPos = pos();
         setPos(pos() + delta);
         setPos(myPos);
      }

      updateModel();

   }
   else if (m_moveType == P2)
   {
      QLineF line = m_line->line();
      QPointF p2 = line.p2();
      QPointF nP2 = p2 + delta;

      if (checkBoundPos(nP2, pos()) == false)
      {
         line.setP2(p2 + delta);
         m_line->setLine(line);
         //fix for paint issue
         QPointF myPos = pos();
         setPos(pos() + delta);
         setPos(myPos);
      }

      updateModel();

   }

}

/*---------------------------------------------------------------------------*/

void LineGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

   //
   QRectF p1Rect, p2Rect;
   p1Rect.adjust(-m_nodeSize, -m_nodeSize, m_nodeSize, m_nodeSize);
   p2Rect.adjust(-m_nodeSize, -m_nodeSize, m_nodeSize, m_nodeSize);
   p1Rect.translate(m_line->line().p1());
   p2Rect.translate(m_line->line().p2());
   if ( p1Rect.contains( event->pos() ) )
   {
       m_moveType = P1;
   }
   else if ( p2Rect.contains( event->pos() ) )
   {
       m_moveType = P2;
   }
   else
   {
       m_moveType = LINE;
   }
   QGraphicsItem::mousePressEvent(event);

}

/*---------------------------------------------------------------------------*/

void LineGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

   m_moveType = LINE;
   QGraphicsItem::mouseReleaseEvent(event);

}

/*---------------------------------------------------------------------------*/

void LineGraphicsItem::paint(QPainter* painter,
                             const QStyleOptionGraphicsItem* option,
                             QWidget*  widget)
{

   Q_UNUSED(widget);

   QLineF line = m_line->line();

   QPen pen(m_lineColor);
   if (option->state & QStyle::State_Selected)
   {
      pen.setStyle(Qt::DotLine);
      pen.setWidthF(2.1);
   }
   painter->setPen(pen);
   m_line->setPen(pen);
   m_line->setLine(line);


   QRectF rect;
   rect.adjust(-m_nodeSize, -m_nodeSize, m_nodeSize, m_nodeSize);

   const int diameter = 12;
   int nSize = 100 * diameter / int(m_nodeSize);

   //draw node 1
   QPointF tranP = line.p1();
   rect.translate(tranP);
   painter->drawRoundRect(rect, nSize, nSize);

   //draw node 2
   rect.translate(-tranP);
   tranP = line.p2();
   rect.translate(tranP);
   painter->drawRoundRect(rect, nSize, nSize);


   //draw box in middle of line
/*
   QPointF p = m_nodeStart->pos();

   QPolygonF poly;
   QTransform trans;
   trans.translate(p.x(), p.y());
   trans.rotate(-line.angle());

   double len = line.length();
   double halfLen = len * 0.5;

   poly.append(trans.map(QPointF(halfLen - 10, -5)));
   poly.append(trans.map(QPointF(halfLen - 10, 5)));
   poly.append(trans.map(QPointF(halfLen + 10, 5)));
   poly.append(trans.map(QPointF(halfLen + 10, -5)));

   painter->drawPolygon(poly);
*/

   //uncomment to see bounding rect. this will cause paint issues
   //painter->drawRect(boundingRect());

   QRectF textBRect = textBoundingRect();
   double angle = line.angle();
   double len = line.length();

   if (textBRect.width() < len)
   {
      QPointF cVec = line.p2() - line.p1();
      cVec /= len;

      //calculate a scale position along the line
      //for the text
      double diffLen = len - textBRect.width();
      double scalePos = (diffLen / 20);
      scalePos = std::min(scalePos, 1.0);
      scalePos *= 0.4;
      scalePos = std::max(scalePos, 0.1);

      if (angle < 90 || angle > 270)
      {
         cVec = line.p1() + (cVec * (len * scalePos));
         painter->translate(cVec.x(), cVec.y());
         painter->rotate(-angle);
      }
      else
      {
         scalePos = 1.0 - scalePos;
         cVec = line.p1() + (cVec * (len * scalePos));
         painter->translate(cVec.x(), cVec.y());
         painter->rotate(180 - angle);
      }
      painter->drawText(0, 0, m_text);
   }

}

/*---------------------------------------------------------------------------*/

void LineGraphicsItem::setEndPos(QPointF pos)
{

   m_line->line().setP2(pos);

}

/*---------------------------------------------------------------------------*/

void LineGraphicsItem::setLinkColor(QColor color)
{

   m_lineColor = color;
   m_lineColorProp->setValue(color);

}

/*---------------------------------------------------------------------------*/

void LineGraphicsItem::setStartPos(QPointF pos)
{

   m_line->line().setP1(pos);

}

/*---------------------------------------------------------------------------*/

QPointF LineGraphicsItem::startNodePos()
{

   return m_line->line().p1();

}


/*---------------------------------------------------------------------------*/

QPainterPath LineGraphicsItem::shape() const
{

   QPolygonF poly;

   QPointF p = m_line->line().p1();
   QLineF line = m_line->line();

   QTransform trans;
   trans.translate(p.x(), p.y());
   trans.rotate(-line.angle());

   double len = line.length() + 7;
   double height = 10;

   poly.append(trans.map(QPointF(-7, -height)));
   poly.append(trans.map(QPointF(-7, height)));
   poly.append(trans.map(QPointF(len, height)));
   poly.append(trans.map(QPointF(len, -height)));

   QPainterPath path;
   path.addPolygon(poly);
   return path;

}

/*---------------------------------------------------------------------------*/

QRectF LineGraphicsItem::textBoundingRect() const
{

   const int Padding = 7;
   QFontMetricsF metrics = qApp->font();
   QRectF rect = metrics.boundingRect(m_text);
   rect.adjust(-Padding, -Padding, +Padding, +Padding);
   rect.translate(-rect.center());
   return rect;

}

/*---------------------------------------------------------------------------*/

void LineGraphicsItem::updateModel()
{

   disconnectAll();

   QPointF sPos = m_line->line().p1();
   sPos += pos();
   QPointF ePos = m_line->line().p2();
   ePos += pos();

   m_startXProp->setValue(sPos.x());
   m_startYProp->setValue(sPos.y());
   m_endXProp->setValue(ePos.x());
   m_endYProp->setValue(ePos.y());
   calculate();

   update();

   connectAll();

   emit viewUpdated(this);

}

/*---------------------------------------------------------------------------*/

void LineGraphicsItem::updateView()
{

   disconnectAll();


   QPointF start = QPointF(m_startXProp->getValue().toDouble(),
                          m_startYProp->getValue().toDouble());
   QPointF end = QPointF(m_endXProp->getValue().toDouble(),
                          m_endYProp->getValue().toDouble());
   start -= pos();
   end -= pos();

   QLineF line(start, end);
   m_line->setLine(line);

   m_lineColor = QColor(m_lineColorProp->getValue().toString());


   calculate();
   update();

   connectAll();

}

/*---------------------------------------------------------------------------*/
