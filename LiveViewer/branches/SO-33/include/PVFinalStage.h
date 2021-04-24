/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef PV_FINAL_STAGE_H
#define PV_FINAL_STAGE_H

/*---------------------------------------------------------------------------*/

#include <QObject>
#include <QList>
#include <QVariant>

#include <FinalStage.h>
#include <CA.h>

/*---------------------------------------------------------------------------*/

class PVFinalStage
: public QObject, public FinalStage
{

   Q_OBJECT

public:

   /**
    * Initialize a PV writing stage with a mapping between ROI values and PVs.
    *
    * @param roiPVs - list of mapping between ROI regions and PVs.
    */
   PVFinalStage(QList<QVariant> roiPVs);

   /**
    * Destructor.
    */
   ~PVFinalStage();

protected:

   /**
    * Write ROI intensity values to PVs.
    *
    * @param input - the intensity values corresponding to individual ROIs.
    */
   void process(Array& input);

private:

   /**
    * Channel access object.
    */
   CA* m_cha;

   /**
    * Mapping from ROI to PVs
    */
   QList<QVariant> m_roiPVs;

};

/*---------------------------------------------------------------------------*/

#endif

