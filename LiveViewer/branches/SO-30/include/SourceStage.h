/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SOURCE_STAGE_H
#define SOURCE_STAGE_H

/*---------------------------------------------------------------------------*/

#include <Stage.h>

/*---------------------------------------------------------------------------*/

class SourceStage
: public Stage
{

public:

   /**
    * Constructor.
    */
   SourceStage();

   /**
    * Destructor.
    */
   ~SourceStage();

protected:

   /**
    * The overridden run method from Thread. This is the thread's main loop
    * which gets an input buffer, calls process, and writes to the output
    * buffer.
    */
   void run() = 0;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
