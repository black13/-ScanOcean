/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ProcessStage.h>
#include <Queue.h>

using gstar::Array;

/*---------------------------------------------------------------------------*/

ProcessStage::ProcessStage()
: Stage()
{

}

/*---------------------------------------------------------------------------*/

ProcessStage::~ProcessStage()
{

}

/*---------------------------------------------------------------------------*/

void ProcessStage::run()
{

   // Make certain there are input and output buffers
   if (m_inputBuffer == NULL || m_outputBuffer == NULL) {
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
         inBuf = m_inputBuffer -> getNext(m_stageId);
      }
      catch (const boost::thread_interrupted& e) {
         break;
      }


      // Get next available output buffer
      Array* outBuf = NULL;
      try {
         outBuf = m_outputBuffer -> getMemory();
      }
      catch (const boost::thread_interrupted& e) {
         break;
      }

      // Process input buffer
      // Implemented by subclass
      process(*inBuf, *outBuf);

      // Place output buffer on output queue
      try {
         m_outputBuffer -> insertNext(outBuf);
      }
      catch (const boost::thread_interrupted& e) {
         break;
      }

   }

}

/*---------------------------------------------------------------------------*/
