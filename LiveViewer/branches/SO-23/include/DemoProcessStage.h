/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DEMO_PROCESS_STAGE_H
#define DEMO_PROCESS_STAGE_H

/*---------------------------------------------------------------------------*/

#include <ProcessStage.h>

/*---------------------------------------------------------------------------*/

class DemoProcessStage
: public ProcessStage
{

public:

   DemoProcessStage();

   ~DemoProcessStage();

protected:

   void process(Array& input, Array& output);

private:

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
