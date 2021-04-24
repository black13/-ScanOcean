/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <AverageIntensityProcessStage.h>
#include <stdio.h>
/*---------------------------------------------------------------------------*/

AverageIntensityProcessStage::AverageIntensityProcessStage()
: ProcessStage()
{

}

/*---------------------------------------------------------------------------*/

AverageIntensityProcessStage::~AverageIntensityProcessStage()
{

}

/*---------------------------------------------------------------------------*/

int AverageIntensityProcessStage::getBufferIntegerValue(char* buffer,
                                                        long offset,
                                                        Array::DataType type)
{

   int value = 0;

   switch (type) {
   case Array::UINT8:
      value = ((unsigned char*)buffer)[offset];
      break;
   case Array::UINT16:
      value = ((unsigned short*)buffer)[offset];
      break;
   }

   return value;

}

/*---------------------------------------------------------------------------*/

void AverageIntensityProcessStage::process(Array& input, Array& output)
{

   // Get rank
   unsigned long rank = input.getRank();

   // Get type
   Array::DataType type = input.getType();

   // Get dimensions
   unsigned long long dims[2];
   input.getDims(dims, 2);

   // Check image properties; only process UINT8 and UINT16 images
   if (rank != 2) {
      return;
   }
   if (dims[0] <= 0 || dims[1] <= 0) {
      return;
   }
   if (type != Array::UINT8 && type != Array::UINT16) {
      return;
   }

   // Number of ROIs
   unsigned long long numberOfROIs = m_roiMasks.size();

   // Check mask properties against input array properties
   for (unsigned int i = 0 ; i < numberOfROIs ; i++) {

      // Get type
      Array::DataType roiType = m_roiMasks[i] -> getType();

      // Get rank
      unsigned long roiRank = m_roiMasks[i] -> getRank();

      // Get dimensions
      unsigned long long roiDims[2];
      m_roiMasks[i] -> getDims(roiDims, 2);

      // Check image properties; only process UINT8 and UINT16 images
      if (roiRank != 2) {
         return;
      }
      if (roiDims[0] <= 0 || roiDims[1] <= 0) {
         return;
      }
      if (roiType != Array::UINT8 && roiType != Array::UINT16) {
         return;
      }
      if (roiDims[0] != dims[0] || roiDims[1] != dims[1]) {
         return;
      }

   }


   // Set output buffer parameters
   output.setType(Array::FLOAT64);
   output.setDimensions(&numberOfROIs, 1);

   // Get input buffer
   char* inBuffer = input.getBuffer();

   // Get output buffer
   double* outBuffer = (double*) output.getBuffer();

   // Loop through each mask
   // TODO: This may be made more efficient by moving the this outer loop
   // in the pixel loops below and updates each ROIs average as it goes.
   for (unsigned int roi = 0 ; roi < numberOfROIs ; roi++) {

      // Get mask
      char* maskBuffer = m_roiMasks[roi] -> getBuffer();

      // Initialize average value
      double sum = 0.0;
      unsigned long long count = 0;
      int val = 0;

      // Loop over each pixel in image
      for (unsigned int r = 0 ; r < dims[0] ; r++) {
         for (unsigned int c = 0 ; c < dims[1] ; c++) {

            // If the mask indicates this location should be used, get value
            // and update the average
            if (maskBuffer[r * dims[1] + c] != 0) {
               val = getBufferIntegerValue(inBuffer, r * dims[1] + c, type);
               sum += (double) val;
               count++;
            }

         }
      }

      // Calculate average
      outBuffer[roi] = sum / (double) count;

   }

}

/*---------------------------------------------------------------------------*/

void AverageIntensityProcessStage::setMasks(std::vector<Array*> roiMasks)
{

   m_roiMasks = roiMasks;

}

/*---------------------------------------------------------------------------*/
