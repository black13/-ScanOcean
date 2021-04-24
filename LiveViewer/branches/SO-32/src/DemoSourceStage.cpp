/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <DemoSourceStage.h>

#include <stdio.h>

/*---------------------------------------------------------------------------*/

DemoSourceStage::DemoSourceStage()
: SourceStage()
{
	m_imageWidth = 1024;
	m_imageHeight = 768;
	m_imageScale = 128;
	m_imageOffset = 64;
}

/*---------------------------------------------------------------------------*/

DemoSourceStage::~DemoSourceStage()
{

}

/*---------------------------------------------------------------------------*/

void DemoSourceStage::run()
{

   int startVal = 0;

   // Loop, producing demo images
   while(true) {

      // Sleep a bit
      usleep(100*1000);

      // Check for interruption point
      try {
         interuptionPoint();
      }
      catch(const boost::thread_interrupted& e) {
         break;
      }

      // Get output buffer
      Array* aptr = NULL;
      aptr = m_outputBuffer -> getMemory();

      // Check for interruption point
      try {
         interuptionPoint();
      }
      catch(const boost::thread_interrupted& e) {
         break;
      }

      // Set image properties
      unsigned long long dims[2];
      dims[0] = m_imageHeight;
      dims[1] = m_imageWidth;
      aptr -> setDimensions(dims, 2);
      aptr -> setType(Array::UINT8);

      // Check for interruption point
      try {
         interuptionPoint();
      }
      catch(const boost::thread_interrupted& e) {
         break;
      }

      // Get output buffer
      char* outBuffer = aptr -> getBuffer();


      // Fill demo image
      for (int r = 0 ; r < m_imageHeight ; r++) {

         // Check for interruption point
         try {
            interuptionPoint();
         }
         catch(const boost::thread_interrupted& e) {
            return;
         }

         // Fill row in buffer
         for (int c = 0 ; c < m_imageWidth ; c++) {
            float val = ((float) r / (float)m_imageHeight) * (float)m_imageScale;
            val += startVal;
            outBuffer[r * m_imageWidth + c] = ((int) val % m_imageScale) + m_imageOffset;
         }

      }
      startVal++;

      // Check for interruption point
      try {
         m_outputBuffer -> insertNext(aptr);
      }
      catch(const boost::thread_interrupted& e) {
         break;
      }

   }

}

/*---------------------------------------------------------------------------*/
