/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <DisplayStage.h>

#include <stdio.h>

/*---------------------------------------------------------------------------*/

DisplayStage::DisplayStage()
: QObject(0), FinalStage()
{

}

/*---------------------------------------------------------------------------*/

DisplayStage::~DisplayStage()
{

}

/*---------------------------------------------------------------------------*/

QImage& DisplayStage::getImage()
{

   return m_img;

}

/*---------------------------------------------------------------------------*/

void DisplayStage::process(Array& input)
{

   // Get rank
   unsigned long rank = input.getRank();

   // Get type
   Array::DataType type = input.getType();

   // Get dimensions
   unsigned long long dims[2];
   input.getDims(dims, 2);

   // Check image properties; only process BGRA32 images
   if (rank != 2) {
      return;
   }
   if (dims[0] <= 0 || dims[1] <= 0) {
      return;
   }
   if (type != Array::BGRA32) {
      return;
   }

   // Create image
   m_img = QImage((uchar*) input.getBuffer(),
                  dims[1], dims[0],
                  QImage::Format_ARGB32);

   // Emit new frame available
   emit newFrame();

}

/*---------------------------------------------------------------------------*/
