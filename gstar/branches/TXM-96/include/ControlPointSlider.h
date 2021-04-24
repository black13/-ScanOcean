/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef GSTAR_CONTROL_POINT_SLIDER_H
#define GSTAR_CONTROL_POINT_SLIDER_H

/*---------------------------------------------------------------------------*/

#include <QWidget>
#include <QPainter>

#include <ControlPoints.h>

/*---------------------------------------------------------------------------*/

namespace gstar
{

class ControlPointSlider
: public QWidget
{

   Q_OBJECT

public:

   ControlPointSlider();

public slots:

   void setMax(double max);
   void setMin(double min);
   void setMinMax(double min, double max);
   void setRange(double min, double max);

signals:

   void maxChanged(double max);
   void minChanged(double min);
   void minMaxChanged(double min, double max);

private slots:

   void sliderMinMaxUpdated(const QPolygonF& points);

private:

   ControlPoints* m_controlPoints;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
