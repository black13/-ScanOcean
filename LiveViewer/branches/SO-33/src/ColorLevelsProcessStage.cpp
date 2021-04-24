/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ColorLevelsProcessStage.h>
#include <stdio.h>

/*---------------------------------------------------------------------------*/

ColorLevelsProcessStage::ColorLevelsProcessStage()
: ProcessStage(), m_imageMin(0), m_imageMax(132), m_rangeMin(0), m_rangeMax(200)
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

   setRangeMinMax(type);
   setDataMinMax(input);

   // Set output buffer parameters
   output.setType(Array::BGRA32);
   output.setDimensions(dims, 2);

   // Convert here
   char* inBuffer = input.getBuffer();
   char* outBuffer = output.getBuffer();
   double redVal = 0, greenVal = 0, blueVal=0;
   for (unsigned int r = 0 ; r < dims[0] ; r++) {
      for (unsigned int c = 0 ; c < dims[1] ; c++) {
         int val = getBufferIntegerValue(inBuffer,r * dims[1] + c, type);
         m_ctf.getColorAt((double)val, &redVal, &greenVal, &blueVal);
         outBuffer[(r * dims[1] * 4) + (c * 4) + 0] = blueVal; // B
         outBuffer[(r * dims[1] * 4) + (c * 4) + 1] = greenVal; // G
         outBuffer[(r * dims[1] * 4) + (c * 4) + 2] = redVal; // R
         outBuffer[(r * dims[1] * 4) + (c * 4) + 3] = 255; // A
      }
   }

}

/*---------------------------------------------------------------------------*/

void ColorLevelsProcessStage::setColorTransferFunction(ColorTransferFunction ctf){
	this->m_ctf = ctf;
}

/*---------------------------------------------------------------------------*/

double ColorLevelsProcessStage::getImageMin()
{
	return m_imageMin;
}

/*---------------------------------------------------------------------------*/

double ColorLevelsProcessStage::getImageMax()
{
	return m_imageMax;
}

/*---------------------------------------------------------------------------*/

double ColorLevelsProcessStage::getRangeMin()
{
	return m_rangeMin;
}
/*---------------------------------------------------------------------------*/

double ColorLevelsProcessStage::getRangeMax()
{
	return m_rangeMax;
}

/*---------------------------------------------------------------------------*/

void ColorLevelsProcessStage::setRangeMinMax(Array::DataType type){
	if (type == Array::UINT8){
		m_rangeMin = 0.0;
		m_rangeMax = 255.0;
	}
	else if (type == Array::UINT16){
		m_rangeMin = 0.0;
		m_rangeMax = 65535.0;
	}
}

void ColorLevelsProcessStage::setDataMinMax(Array &input){
   m_imageMax = m_rangeMin;
   m_imageMin = m_rangeMax;

   unsigned long rank = input.getRank();
   unsigned long long dims[2];
   input.getDims(dims, rank);

   char* inBuffer = input.getBuffer();
   for (unsigned int ii = 0; ii < dims[0]*dims[1]; ii++)
   {
      int val = getBufferIntegerValue(inBuffer, ii, input.getType());
      m_imageMin = (val < m_imageMin) ? val : m_imageMin;
      m_imageMax = (val > m_imageMax) ? val : m_imageMax;
   }
}

int ColorLevelsProcessStage::getBufferIntegerValue(char * buffer, long offset, Array::DataType type){
   int value = 0;
   switch(type){
   case Array::UINT8:
      value = ((unsigned char *)buffer)[offset];
      break;
   case Array::UINT16:
      value = ((unsigned short *)buffer)[offset];
      break;
   }

   return value;
}
