/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef GSTAR_CONTROL_POINT_PICKER_H
#define GSTAR_CONTROL_POINT_PICKER_H

/*---------------------------------------------------------------------------*/

#include <QWidget>
#include <QPainter>
#include <QPolygonF>

#include <ControlPoints.h>

/*---------------------------------------------------------------------------*/

namespace gstar
{

class ControlPointPicker
: public QWidget
{

   Q_OBJECT

public:

   enum Type {
      Red,
      Green,
      Blue,
      White
   };

   ControlPointPicker();
   int getColor();
   QPolygonF getPoints() const;
   void getTotalRange(double* min, double* max);
   void paintEvent(QPaintEvent* event);
   void setColor(int type);

public slots:

   void setPoints(const QPolygonF& points);
   void setSubRange(double min, double max);
   void setTotalRange(double min, double max);

signals:
   
   void controlPointsChanged(const QPolygonF& points);

private slots:

   void pointsChanged(const QPolygonF& points);

private:

   int m_type;

   ControlPoints* m_controlPoints;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
