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
#include <ROI.h>

/*---------------------------------------------------------------------------*/

class PVFinalStage
: public QObject, public FinalStage
{

   Q_OBJECT

public:

   /**
    * Initialize a PV writing stage with a mapping between ROI values and PVs.
    *
    * @param roiList - List of ROIs defined by the user along with their PVs.
    */
   PVFinalStage(QList<ROI>& roiList);

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
    * Data model providing ROI and PV information.
    */
   QList<ROI> m_roiList;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
