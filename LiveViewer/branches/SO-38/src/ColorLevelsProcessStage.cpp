/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ColorLevelsProcessStage.h>
#include <stdio.h>

/*---------------------------------------------------------------------------*/

ColorLevelsProcessStage::ColorLevelsProcessStage()
: ProcessStage()
{

}

/*---------------------------------------------------------------------------*/

ColorLevelsProcessStage::~ColorLevelsProcessStage()
{

}

/*---------------------------------------------------------------------------*/

void ColorLevelsProcessStage::process(Array& input, Array& output)
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

   // Set output buffer parameters
   output.setType(Array::BGRA32);
   output.setDimensions(dims, 2);

   // Convert here
   char* inBuffer = input.getBuffer();
   char* outBuffer = output.getBuffer();
   for (int r = 0 ; r < dims[0] ; r++) {
      for (int c = 0 ; c < dims[1] ; c++) {
         int val = inBuffer[r * dims[1] + c];
         outBuffer[(r * dims[1] * 4) + (c * 4) + 0] = val; // B
         outBuffer[(r * dims[1] * 4) + (c * 4) + 1] = val; // G
         outBuffer[(r * dims[1] * 4) + (c * 4) + 2] = val; // R
         outBuffer[(r * dims[1] * 4) + (c * 4) + 3] = 255; // A
      }
   }

}

/*---------------------------------------------------------------------------*/
