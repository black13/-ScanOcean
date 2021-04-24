/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DEMO_SOURCE_STAGE_H
#define DEMO_SOURCE_STAGE_H

/*---------------------------------------------------------------------------*/

#include <SourceStage.h>

/*---------------------------------------------------------------------------*/

class DemoSourceStage
: public SourceStage
{

public:

   /**
    * Constructor.
    */
   DemoSourceStage();

   /**
    * Destructor.
    */
   ~DemoSourceStage();

protected:

   /**
    * The overridden run method from Thread. This is the thread's main loop
    * which gets an input buffer, calls process, and writes to the output
    * buffer.
    */
   void run();

protected:
   int imageWidth;
   int imageHeight;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
