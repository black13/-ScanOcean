/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef COLOR_LEVELS_PROCESS_STAGE_H
#define COLOR_LEVELS_PROCESS_STAGE_H

/*---------------------------------------------------------------------------*/

#include <ProcessStage.h>

/*---------------------------------------------------------------------------*/

class ColorLevelsProcessStage
: public ProcessStage
{

public:

   /**
    * Constructor.
    */
   ColorLevelsProcessStage();

   /**
    * Destructor.
    */
   ~ColorLevelsProcessStage();

protected:

   /**
    * Process each Array from the input buffer and write results to the
    * output buffer.
    *
    * @param input - the input Array to process
    * @param output - the output Array in to which results should be written
    */
   void process(Array& input, Array& output);

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
