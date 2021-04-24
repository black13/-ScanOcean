/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DEMO_FINAL_STAGE_H
#define DEMO_FINAL_STAGE_H

/*---------------------------------------------------------------------------*/

#include <FinalStage.h>
#include <Array.h>

/*---------------------------------------------------------------------------*/

class DemoFinalStage
: public FinalStage
{

public:

   DemoFinalStage();

   ~DemoFinalStage();

protected:

   void process(gstar::Array& input);

private:

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
