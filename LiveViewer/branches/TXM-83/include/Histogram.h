/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/


#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QList>

class Histogram
{
public:

   Histogram(int bins);

   ~Histogram();

   void addIntensity(qreal val);

   void setBins(int bins);

   int getBins();

   QList<int> getCounts();

   void reset();

private:

   qreal m_binsize;

   int m_nbins;

   int* m_bins;

   qreal m_min;

   qreal m_max;

};


#endif
