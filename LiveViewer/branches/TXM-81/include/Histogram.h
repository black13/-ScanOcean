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

   /**
    * Compute image histogram with give number of bins.
    */
   Histogram(int bins);

   ~Histogram();

   /**
    * Compute bin number for each pixel intensity value.
    */
   void addIntensity(qreal val);


   void setBins(int bins);

   int getBins();

   /**
    * Get the histogram, the index is the bin number and the value is the count.
    */
   QList<int> getCounts();

   /**
    * Re-initialize the count, set all of them to zero.
    */
   void reset();

private:

   /**
    * Size (range) of each bin
    */
   qreal m_binsize;

   /**
    * Total number of bins.
    */
   int m_nbins;

   /**
    * Hold count for each bin
    */
   int* m_bins;

   /**
    * Minimum pixel intensity value
    */
   qreal m_min;

   /**
    * Maximum pixel intensity value.
    */
   qreal m_max;

};


#endif
