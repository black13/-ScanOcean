/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <HistogramPlot.h>

#include <QDebug>

using namespace gstar;

/*---------------------------------------------------------------------------*/

HistogramPlot::HistogramPlot(QWidget* parent)
{

   m_widget = parent;
   m_widget->installEventFilter(this);
   m_plotType = 0;

}

/*---------------------------------------------------------------------------*/

HistogramPlot::~HistogramPlot()
{


}

/*---------------------------------------------------------------------------*/

bool HistogramPlot::eventFilter(QObject* source, QEvent* event)
{

   if (source == m_widget)
   {
      if (!(m_widget->isEnabled()))
      {
         if ((event->type()) != QEvent::Paint)
         {
            return true;
         }
      }

      switch (event->type())
      {
         case QEvent::Paint:
         {
            QWidget* tmp = m_widget;
            m_widget = 0;
            QApplication::sendEvent(source, event);
            m_widget = tmp;
            if (m_plotType == 1)
            {
               drawHistogramCont();
            }
            else
            {
               drawHistogramDisc();
            }
            return true;
            break;
         }
      }
   }

   return false;

}

/*---------------------------------------------------------------------------*/

void HistogramPlot::drawHistogramDisc()
{

   QPainter painter(m_widget);
   painter.setPen( QPen(QColor(158, 157, 162, 30), 0.0));
   painter.setBrush(QBrush(QColor(158, 157, 162, 90)));
   painter.setRenderHint(QPainter::Antialiasing, true);
   painter.setRenderHint(QPainter::SmoothPixmapTransform, true);


   if (m_values.size() <= 0) return;

   double binSize = qCeil((double) m_widget->width() / (double) m_values.size());

   float x = 0.0;
   float y = 0.0;
   float w = 0.0;
   float h = 0.0;

   for (int i=0; i<m_values.size(); i++)
   {
      y = m_widget->height() - map(m_values.at(i)) + (.3 * m_widget->height());
      w = binSize;
      h = map(m_values.at(i));
      painter.drawRect(x, y, w, h);
      x = x + binSize;
   }

}

/*---------------------------------------------------------------------------*/

void HistogramPlot::drawHistogramCont()
{

   QPainter painter(m_widget);
   painter.setPen( QPen(QColor(158, 157, 162, 200), 1));
   painter.setBrush(QBrush(QColor(158, 157, 162, 90)));
   //painter.setBrush(QBrush(QColor(255, 255, 255, 175)));
   painter.setRenderHint(QPainter::Antialiasing, true);
   painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

   if (m_values.size() <= 0) return;

   double binSize = (double) m_widget->width() / (double) m_values.size();;

   float x = 5.0;
   float y = 0.0;

   QPolygonF polylinePoints;
   polylinePoints.insert(0, QPointF(0.0, m_widget->height()));
   int i = 0;
   for ( ; i < m_values.size() ; i++) {
      y = m_widget->height() - map(m_values.at(i)) + (.3 * m_widget->height());
      polylinePoints.insert(i+1, QPointF(x, y));
      x = x + binSize;
   }
   polylinePoints.insert(i+1, QPointF((x-binSize)+5, m_widget->height()));

   painter.drawPolygon(polylinePoints, Qt::WindingFill);

}

/*---------------------------------------------------------------------------*/

qreal HistogramPlot::map(const qreal& value)
{

   qreal newRange = m_widget->height();
   qreal res = (value / m_max ) * newRange;

   return res;

}

/*---------------------------------------------------------------------------*/

void HistogramPlot::updatePoints(QList<int> pts)
{

   QList<int> tmp = m_values;
   m_values = pts;

   m_max = 0;

   bool shouldUpdate = false;

   for (int i=0; i<m_values.size(); i++)
   {
      if (tmp.size() == m_values.size())
      {
         if (m_values.at(i) != tmp.at(i))
         {
            shouldUpdate = true;
         }
      }
      else
      {
         shouldUpdate = true;
      }

      if (m_values.at(i) > m_max) m_max = m_values.at(i);

   }

   if (shouldUpdate)
   {
      m_widget->update();
   }

}

/*---------------------------------------------------------------------------*/

void HistogramPlot::updatePlotType(int type)
{

   m_plotType = type;

}

/*---------------------------------------------------------------------------*/
