/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef GSTAR_CONTROL_POINTS_H
#define GSTAR_CONTROL_POINTS_H

/*---------------------------------------------------------------------------*/

#include <QtGui>

/*---------------------------------------------------------------------------*/

namespace gstar
{

class ControlPoints
: public QObject
{

   Q_OBJECT

public:

   enum Mode {
      Points,
      MinMaxSlider
   };

   ControlPoints(QWidget* widget);

   bool eventFilter(QObject* object, QEvent* event);

   QPolygonF getPoints() const;

   void getTotalRange(double* min, double* max);

   void paintPoints();

   void setMax(double max);

   void setMaxMin(double max, double min);

   void setMin(double min);

   void setMode(int mode);

   void setPoints(const QPolygonF& points, bool emitSignal = true);

   void setRange(int min, int max);

signals:
   
   void pointsChanged(const QPolygonF& points);

private:

   QPointF boundPoint(int index, const QPointF& value) const;

   QRectF pointBoundingRect(int i) const;

   QPointF pixelToNormalValue(const QPointF& pixel) const;

   QPointF normalValueToPixel(const QPointF& value) const;

   void movePoint(int i, const QPointF &newPos, bool emitChange = true);

   void restretchPoints();

   // Parent widget
   QWidget* m_widget;

   // Control points
   QPolygonF m_points;

   QSizeF m_pointSize;
   QPen m_pointPen;
   QBrush m_pointBrush;
   QPen m_connectionPen;

   QPen m_sliderPen;
   QBrush m_sliderBrush;

   int m_min;
   int m_max;
   int m_minOld;
   int m_maxOld;

   int m_mode;

   int m_currentIndex;

   double m_range[2];

   // Flag to know if a point is being moved using mouse.
   bool m_pointInMove;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
