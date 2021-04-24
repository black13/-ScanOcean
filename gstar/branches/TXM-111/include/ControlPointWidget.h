/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef GSTAR_CONTROL_POINT_WIDGET_H
#define GSTAR_CONTROL_POINT_WIDGET_H

/*---------------------------------------------------------------------------*/

#include <QHBoxLayout>
#include <QIntValidator>
#include <QLineEdit>
#include <QPolygonF>
#include <QVBoxLayout>
#include <QWidget>

#include <ControlPointPicker.h>
#include <ControlPointSlider.h>

/*---------------------------------------------------------------------------*/

namespace gstar
{

class HistogramPlot;

class ControlPointWidget
: public QWidget
{

   Q_OBJECT

public:

   ControlPointWidget(QWidget* widget);
   QPolygonF getPoints() const;
   void getTotalRange(double* min, double* max);

public slots:

   void setColor(int color);
   void setPoints(const QPolygonF& points);
   void setSubRange(double min, double max);
   void setTotalRange(double min, double max);
   void updateHistogram(QList<int> points);

signals:
   
   void controlPointsChanged(const QPolygonF& points);
   void subRangeChanged(double min, double max);

private slots:

   void pointsChanged(const QPolygonF& points);
   void subRangeUpdated(double min, double max);
   void textMaxSubRangeChanged();
   void textMinSubRangeChanged();

private:

   ControlPointPicker* m_ctrlPointPicker;
   ControlPointSlider* m_ctrlPointSlider;

   QLineEdit* m_editMin;
   QLineEdit* m_editMax;

   QIntValidator* m_validatorMin;
   QIntValidator* m_validatorMax;

   HistogramPlot* m_histogram;


};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
