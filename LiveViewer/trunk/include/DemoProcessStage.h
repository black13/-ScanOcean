/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DEMO_PROCESS_STAGE_H
#define DEMO_PROCESS_STAGE_H

/*---------------------------------------------------------------------------*/

#include <ProcessStage.h>
#include <Array.h>

/*---------------------------------------------------------------------------*/

class DemoProcessStage
: public ProcessStage
{

public:

   DemoProcessStage();

   ~DemoProcessStage();

protected:

   void process(gstar::Array& input, gstar::Array& output);

private:

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
