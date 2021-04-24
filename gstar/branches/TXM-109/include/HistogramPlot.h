/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef GSTAR_HISTOGRAM_PLOT_H
#define GSTAR_HISTOGRAM_PLOT_H

/*---------------------------------------------------------------------------*/

#include <QtGui>

/*---------------------------------------------------------------------------*/

namespace gstar
{

class HistogramPlot
: public QObject
{

   Q_OBJECT

public:

   HistogramPlot(QWidget* parent);

   ~HistogramPlot();

   bool eventFilter(QObject* object, QEvent* event);

public slots:

   void updatePoints(QList<int> pts);

private:

   void drawHistogram();

   qreal ymap(const qreal& value);

private:

   QWidget* m_widget;

   QList<int> m_values;

   int m_max;

};

}

#endif
