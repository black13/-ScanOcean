
#include <ColorTransferMapping.h>

ColorTransferMapping::ColorTransferMapping()
{

   for(int i = 0; i < 256; i++)
   {
      m_redMapping[i] = i;
      m_blueMapping[i] = i;
      m_greenMapping[i] = i;
   }

}

ColorTransferMapping::~ColorTransferMapping()
{

}

unsigned char ColorTransferMapping::getRed(int index)
{

   if(!isValidValue(index)) {
      //TODO throw exception
   }

   return m_redMapping[index];

}

unsigned char ColorTransferMapping::getBlue(int index)
{

   if(!isValidValue(index)) {
	  //TODO throw exception
   }

   return m_blueMapping[index];

}

unsigned char ColorTransferMapping::getGreen(int index)
{

   if(!isValidValue(index)) {
      //TODO throw exception
   }

   return m_greenMapping[index];

}

void ColorTransferMapping::setRed(int index, unsigned char value)
{

   if(!isValidValue(index)) {
	  //TODO throw exception
   }

   m_redMapping[index] = value;

}

void ColorTransferMapping::setBlue(int index, unsigned char value)
{

   if(!isValidValue(index)) {
	  //TODO throw exception
   }

   m_blueMapping[index] = value;

}

void ColorTransferMapping::setGreen(int index, unsigned char value)
{

   if(!isValidValue(index)) {
	  //TODO throw exception
   }

   m_greenMapping[index] = value;

}

void ColorTransferMapping::setAllRed(unsigned char value)
{

   for(int i = 0; i < 255; i++)
      m_redMapping[i] = value;

}

void ColorTransferMapping::setAllBlue(unsigned char value)
{

   for(int i = 0; i < 255; i++)
      m_blueMapping[i] = value;

}

void ColorTransferMapping::setAllGreen(unsigned char value)
{

   for(int i = 0; i < 255; i++)
      m_greenMapping[i] = value;

}

bool ColorTransferMapping::isValidValue(int index)
{

   return index >=0 && index <= 255;

}
