/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <PVFinalStage.h>
#include <QDebug>

#include <stdio.h>

using gstar::ROI;
using gstar::Array;

/*---------------------------------------------------------------------------*/

PVFinalStage::PVFinalStage(QList<ROI>& roiList)
: QObject(0), FinalStage()
{

   m_cha = NULL;
   m_roiList = roiList;

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
   unsigned int pvsize = m_roiList.size();

   if (pvsize > dims[0])
      pvsize = dims[0];

   // Write out pvs
   double* buff = (double*)input.getBuffer();
   if (buff == NULL) {
      fprintf(stderr, "Invalid memory buffer for reading ROI values.");
      return;
   }

   for (unsigned int i = 0 ; i < pvsize ; i++) {
      ROI roi = m_roiList.at(i);

      // Make sure we have the connection to the PV.
      if (roi.getText().isEmpty()) {
         continue;
      }

      m_cha -> create(roi.getText(), true);
      m_cha -> put(roi.getText(), buff[i], true);
   }

}

/*---------------------------------------------------------------------------*/
