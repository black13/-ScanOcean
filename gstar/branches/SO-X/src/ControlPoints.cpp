/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ControlPoints.h>

using namespace gstar;

/*---------------------------------------------------------------------------*/

ControlPoints::ControlPoints(QWidget* widget)
: QObject(widget)
{

   m_mode = Points;

   m_widget = widget;
   m_widget -> installEventFilter(this);

   m_pointPen = QPen(QColor(255, 255, 255, 191), 1);
   m_connectionPen = QPen(QColor(255, 255, 255, 127), 2);
   m_pointBrush = QBrush(QColor(191, 191, 191, 127));
   m_pointSize = QSize(11, 11);

   m_sliderPen = QPen(QColor(0, 0, 0, 191), 1);
   m_sliderBrush = QBrush(QColor(59, 59, 59, 127));

   m_points.insert(0, QPointF(0, 0));
   m_points.insert(1, QPointF(255, 255));

   m_range[0] = 0.0;
   m_range[1] = 255.0;

   m_min = 0;
   m_max = 255;
   m_minOld = 0;
   m_maxOld = 255;

   m_currentIndex = -1;

   connect(this, SIGNAL(pointsChanged(QPolygonF)),
           m_widget, SLOT(update()));

}

/*---------------------------------------------------------------------------*/

QPointF ControlPoints::boundPoint(int index, const QPointF& value) const
{

   QPointF newPoint(value);

   if (m_mode == Points) {

      if (index == 0) {
         newPoint.setX(m_min);
      }

      else if (index == m_points.size() - 1) {
         newPoint.setX(m_max);
      }

      else {
         QPointF prev = m_points[index - 1];
         if (value.x() < prev.x()) {
            newPoint.setX(prev.x());
         }

         QPointF next = m_points[index + 1];
         if (value.x() > next.x()) {
            newPoint.setX(next.x());
         }
      }

      if (value.y() < 0.0) {
         newPoint.setY(0.0);
      }

      if (value.y() > 255.0) {
         newPoint.setY(255.0);
      }

   }

   else {

      if (index == 0) {
         if (value.x() < m_min) {
            newPoint.setX(m_min);
         }
         if (value.x() > m_points[m_points.size() - 1].x()) {
            newPoint.setX(m_points[m_points.size() - 1].x());
         }
      }

      else {
         if (value.x() > m_max) {
            newPoint.setX(m_max);
         }
         if (value.x() < m_points[0].x()) {
            newPoint.setX(m_points[0].x());
         }
      }

      newPoint.setY(7);

   }

   return newPoint;

}

/*---------------------------------------------------------------------------*/

bool ControlPoints::eventFilter(QObject* object, QEvent* event)
{

   if (object == m_widget) {
      if (!(m_widget -> isEnabled())) {
         if ((event -> type()) != QEvent::Paint) {
            return true;
         }
      }
   }

   if (object == m_widget) {
      switch (event -> type()) {

         case QEvent::MouseButtonPress:
            {

               QMouseEvent* me = (QMouseEvent*) event;
               QPointF clickPos = me -> pos();
               int index = -1;
               for (int i = 0 ; i < m_points.size() ; ++i) {

                  QPainterPath path;
                  path.addEllipse(pointBoundingRect(i));

                  if (path.contains(clickPos)) {
                     index = i;
                     break;
                  }
               }

               if (me -> button() == Qt::LeftButton) {
                  if (index == -1) {
                     if (m_mode == Points) {

                        QPointF normClickPos = pixelToNormalValue(clickPos);

                        if (normClickPos.x() >= m_min && 
                            normClickPos.x() <= m_max) {

                           int insertIndex = 0;

                           for (int i = 0 ; i < m_points.size() ; i++) {
                              if (m_points.at(i).x() > normClickPos.x()) {
                                 insertIndex = i;
                                 break;
                              }
                           }

                           m_points.insert(insertIndex, normClickPos);
                           m_currentIndex = insertIndex;
                           emit pointsChanged(m_points);

                        }

                     }

                  }
                  else {
                     m_currentIndex = index;
                  }
               }

               else if (me -> button() == Qt::RightButton) {
                  if (m_mode == Points) {
                     if (index > 0 && index < m_points.size() - 1) {
                        m_points.remove(index);
                        emit pointsChanged(m_points);
                     }
                  }
               }

               return true;
               break;
            }
        
         case QEvent::MouseButtonRelease:
            {
               m_currentIndex = -1;
               break;
            }

         case QEvent::MouseMove:
            {
               if (m_currentIndex >= 0) {
                  movePoint(m_currentIndex, ((QMouseEvent*)event) -> pos());
               }
               break;
            }

         case QEvent::Paint:
            {
               QWidget* tmp = m_widget;
               m_widget = 0;
               QApplication::sendEvent(object, event);
               m_widget = tmp;
               paintPoints();
               return true;
               break;
            }
      
      }
   }

   return false;

}

/*---------------------------------------------------------------------------*/

QPolygonF ControlPoints::getPoints() const
{

   return m_points;

}

/*---------------------------------------------------------------------------*/

void ControlPoints::getTotalRange(double* min, double* max)
{

   *min = m_range[0];
   *max = m_range[1];

}

/*---------------------------------------------------------------------------*/

void ControlPoints::movePoint(int index, const QPointF &point, 
                              bool emitUpdate)
{

   m_points[index] = boundPoint(index, pixelToNormalValue(point));
   
   if (emitUpdate)
      emit pointsChanged(m_points);

}

/*---------------------------------------------------------------------------*/

QPointF ControlPoints::normalValueToPixel(const QPointF& value) const
{

   qreal x = ((value.x() - m_range[0]) / (m_range[1] - m_range[0])) * 
      (m_widget -> width());
   qreal y = m_widget -> height() - 
      ((value.y() / 255.0) * m_widget -> height());

   QPointF pixel(x, y);

   return pixel;

}

/*---------------------------------------------------------------------------*/

void ControlPoints::paintPoints()
{

   QPainter p;
   p.begin(m_widget);

   if (m_mode == Points) {

      QPolygonF polylinePoints;
      for (int i = 0 ; i < m_points.size() ; i++) {
         polylinePoints.insert(i, normalValueToPixel(m_points[i]));
      }

      p.setPen(m_connectionPen);
      p.drawPolyline(polylinePoints);

   }

   if (m_mode == Points) {
      p.setPen(m_pointPen);
      p.setBrush(m_pointBrush);
   }
   else {
      p.setPen(m_sliderPen);
      p.setBrush(m_sliderBrush);
   }

   for (int i = 0 ; i < m_points.size() ; i++) {   
      QRectF bounds = pointBoundingRect(i);
      if (m_mode == Points) {
         p.drawEllipse(bounds);
      }
      else {
         if (i == 0) {
            QPointF points[3] = {
               QPointF((bounds.width()/2) + bounds.left(), bounds.bottom()),
               QPointF(bounds.bottomRight()),
               QPointF((bounds.width()/2) + bounds.left(), bounds.top())
            };
            p.drawPolygon(points, 3);
         }
         else {
            QPointF points[3] = {
               QPointF(bounds.bottomLeft()),
               QPointF((bounds.width()/2) + bounds.left(), bounds.bottom()),
               QPointF((bounds.width()/2) + bounds.left(), bounds.top())
            };
            p.drawPolygon(points, 3);
         }
      }
   }

   if (m_mode == Points) {
      QPointF tl = normalValueToPixel(QPointF(m_range[0], 255.0));
      QPointF br = normalValueToPixel(QPointF(m_min, 0.0));
      p.drawRect(QRectF(tl, br));

      tl = normalValueToPixel(QPointF(m_max, 255.0));
      br = normalValueToPixel(QPointF(m_range[1], 0.0));
      p.drawRect(QRectF(tl, br));
   }

}

/*---------------------------------------------------------------------------*/

QPointF ControlPoints::pixelToNormalValue(const QPointF& pixel) const
{

   qreal w = m_widget -> width();
   qreal h = m_widget -> height();

   qreal x = (pixel.x() / w) * (m_range[1] - m_range[0]) + m_range[0];
   qreal y = ((h - pixel.y()) / h) * 255.0;

   QPointF normalValue(x, y);

   return normalValue;   

}

/*---------------------------------------------------------------------------*/

QRectF ControlPoints::pointBoundingRect(int i) const
{

   QPointF p = m_points.at(i);
   qreal w = m_pointSize.width();
   qreal h = m_pointSize.height();

   QPointF pixel = normalValueToPixel(p);

   qreal x = pixel.x() - w / 2;
   qreal y = pixel.y() - h / 2;

   if (m_mode == MinMaxSlider) y = 0.0;

   return QRectF(x, y, w, h);

}

/*---------------------------------------------------------------------------*/

void ControlPoints::restretchPoints()
{

   for (int i = 0 ; i < m_points.size() ; i++) {

      if (i == 0) {
         m_points[i].setX(m_min);
      }

      else if (i == m_points.size() - 1) {
         m_points[i].setX(m_max);
      }

      else {
         double nor = 0.0;
         double val = 0.0;
         if (m_min != m_minOld || m_max != m_maxOld) {
            nor = (m_points[i].x() - m_minOld) / (m_maxOld - m_minOld);
            val = nor * (m_max - m_min) + m_min;
            m_points[i].setX(val);
         }
      }

   }

}

/*---------------------------------------------------------------------------*/

void ControlPoints::setMax(double max)
{

   m_maxOld = m_max;
   m_max = max;

   restretchPoints();

   emit pointsChanged(m_points);
   m_widget -> update();

}

/*---------------------------------------------------------------------------*/

void ControlPoints::setMaxMin(double max, double min)
{

   m_maxOld = m_max;
   m_max = max;

   m_minOld = m_min;
   m_min = min;

   restretchPoints();

   emit pointsChanged(m_points);
   m_widget -> update();

}

/*---------------------------------------------------------------------------*/

void ControlPoints::setMin(double min)
{

   m_minOld = m_min;
   m_min = min;

   restretchPoints();
   
   emit pointsChanged(m_points);
   m_widget -> update();

}

/*---------------------------------------------------------------------------*/

void ControlPoints::setMode(int mode)
{

   m_mode = mode;

}

/*---------------------------------------------------------------------------*/

void ControlPoints::setPoints(const QPolygonF& points, bool emitSignal)
{

   m_points.clear();

   for (int i = 0 ; i < points.size() ; i++) {
      m_points.push_back(points[i]);
   }
   
   if (m_mode == Points) {
      restretchPoints();
   }

   if (emitSignal) {
      emit pointsChanged(m_points);
   }

   m_widget -> update();

}

/*---------------------------------------------------------------------------*/

void ControlPoints::setRange(int min, int max)
{

   m_range[0] = min;
   m_range[1] = max;

}

/*---------------------------------------------------------------------------*/
