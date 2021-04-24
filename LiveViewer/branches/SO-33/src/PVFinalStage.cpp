/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <PVFinalStage.h>
#include <QDebug>

#include <stdio.h>

/*---------------------------------------------------------------------------*/

PVFinalStage::PVFinalStage(QList<QVariant> l)
: QObject(0), FinalStage()
{
   m_cha = NULL;
   m_roiPVs = l;
}

/*---------------------------------------------------------------------------*/

PVFinalStage::~PVFinalStage()
{

}

/*---------------------------------------------------------------------------*/

void PVFinalStage::process(Array& input)
{
   // Initialize Channel Access if it is not.
   if (m_cha == NULL) {
      m_cha = new CA();

      m_cha -> attach();
   }

   // Each dimension correspond to the intensity value for
   // a single regions. If the mapping between PVs and ROI is
   // not one-to-one, then ignore further processing.
   int rank = input.getRank();
   if (rank != 1) {
      fprintf(stderr, "Couldn't write out PVs, region mis-match\n");
      return;
   }

   unsigned long long dims[1];
   input.getDims(dims, 1);
   if (m_roiPVs.size() != dims[0]) {
      fprintf(stderr, "Couldn't write out PVs, region mis-match\n");
      return;
   }

   //write out pvs
   double* buff = (double*)input.getBuffer();
   for (int i=0; i<m_roiPVs.size(); i++) {
      QString pv_name = m_roiPVs.at(i).toString();
      //make sure we have the connection to the PV.
      m_cha -> create(pv_name, true);
      if (pv_name.isEmpty())
         continue;

      m_cha -> put(pv_name, buff[i], true);
   }

}

/*---------------------------------------------------------------------------*/
