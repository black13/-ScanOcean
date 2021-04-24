/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef STAGE_H
#define STAGE_H

/*---------------------------------------------------------------------------*/

#include <Buffer.h>
#include <Thread.h>

/*---------------------------------------------------------------------------*/

/**
 * @brief A stage in the processing pipeline...
 */
class Stage
: public Thread
{

public:

   /**
    * Constructor.
    */
   Stage();

   /**
    * Destructor.
    */
   ~Stage();

   /**
    * Set input buffer
    *
    * @param buffer - input buffer
    */
   void setInputBuffer(Buffer* buffer);

   /**
    * Set output buffer
    *
    * @param buffer - output buffer
    */
   void setOutputBuffer(Buffer* buffer);

protected:

   /**
    * Input buffer
    */
   Buffer* m_inputBuffer;

   /**
    * Output buffer
    */
   Buffer* m_outputBuffer;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
