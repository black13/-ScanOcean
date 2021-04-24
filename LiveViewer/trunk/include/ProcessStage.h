/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef PROCESS_STAGE_H
#define PROCESS_STAGE_H

/*---------------------------------------------------------------------------*/

#include <Stage.h>
#include <Array.h>

/*---------------------------------------------------------------------------*/

class ProcessStage
: public Stage
{

public:

   /**
    * Constructor.
    */
   ProcessStage();

   /**
    * Destructor.
    */
   ~ProcessStage();

protected:

   /**
    * Process each Array from the input buffer and write results to the
    * output buffer. This must be implemented by a subclass.
    *
    * @param input - the input Array to process
    * @param output - the output Array in to which results should be written
    */
   virtual void process(gstar::Array& input, gstar::Array& output) = 0;

   /**
    * The overridden run method from Thread. This is the thread's main loop
    * which gets an input buffer, calls process, and writes to the output
    * buffer.
    */
   void run();

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
