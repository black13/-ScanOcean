/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef FINAL_STAGE_H
#define FINAL_STAGE_H

/*---------------------------------------------------------------------------*/

#include <Stage.h>
#include <Array.h>

/*---------------------------------------------------------------------------*/

class FinalStage
: public Stage
{

public:

   /**
    * Constructor.
    */
   FinalStage();

   /**
    * Destructor.
    */
   ~FinalStage();

protected:

   /**
    * Process each Array from the input buffer. This must be implemented by
    * a subclass.
    *
    * @param input - the input Array to process
    */
   virtual void process(gstar::Array& input) = 0;

   /**
    * The overridden run method from Thread. This is the thread's main loop
    * which gets an input buffer and calls process.
    */
   void run();

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
