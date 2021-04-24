/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <Histogram.h>
#include <QDebug>
#include <QtCore/qmath.h>

/*---------------------------------------------------------------------------*/

Histogram::Histogram(int bins)
{

   m_nbins = bins;
   m_min = 0.0;
   m_max = 255.0;
   m_binsize = m_max / (qreal) m_nbins;
   m_bins = new int[m_nbins];

   reset();

}

/*---------------------------------------------------------------------------*/

Histogram::~Histogram()
{

   if (m_bins != NULL)
      delete m_bins;

}

/*---------------------------------------------------------------------------*/

void Histogram::addIntensity(qreal val)
{

   int bin = qCeil(val / m_binsize) - 1;
   if (bin < 0) bin = 0;

   if (bin >= 0 && bin < m_nbins)
   {
      m_bins[bin]++;
   }
}

/*---------------------------------------------------------------------------*/

void Histogram::setBins(int bins)
{

   m_nbins = bins;
   if (m_bins != NULL)
   {
      delete m_bins;
      m_bins = new int[m_nbins];
   }

}

/*---------------------------------------------------------------------------*/

int Histogram::getBins()
{

   return m_nbins;

}

/*---------------------------------------------------------------------------*/


QList<int> Histogram::getCounts()
{

   QList<int> counts;

   for (int i=0; i<m_nbins; i++)
   {
      counts.push_back(m_bins[i]);
   }

   return counts;

}

/*---------------------------------------------------------------------------*/


void Histogram::reset()
{

   for (int i=0; i<m_nbins; i++) m_bins[i] = 0;

}

/*---------------------------------------------------------------------------*/

