/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <FinalStage.h>
#include <Queue.h>

/*---------------------------------------------------------------------------*/

FinalStage::FinalStage()
: Stage()
{

}

/*---------------------------------------------------------------------------*/

FinalStage::~FinalStage()
{

}

/*---------------------------------------------------------------------------*/

void FinalStage::run()
{

   // Make certain there is an input buffer
   if (m_inputBuffer == NULL) {
      return;
   }

   // Loop and process
   while (true) {

      // Check for interruption point
      try {
         interuptionPoint();
      }
      catch(const boost::thread_interrupted& e) {
         break;
      }

      // Get input buffer
      Array* inBuf = NULL;
      try {
         inBuf = m_inputBuffer -> getNext();
      }
      catch(const boost::thread_interrupted& e) {
         break;
      }

      // Process input buffer
      // Implemented by subclass
      process(*inBuf);

   }

}

/*---------------------------------------------------------------------------*/
