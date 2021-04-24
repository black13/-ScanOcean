
#include <ColorMapOperation.h>
#include <ColorTransferMapping.h>
#include <iostream>

ColorMapOperation::ColorMapOperation(AbstractImageBuffer* input,
                                     AbstractImageBuffer* output,
                                     ColorTransferMapping* mapping)
: Process(input,output),
  m_mapping(mapping)
{


}

void ColorMapOperation::execute()
{

   Image<unsigned char> * srcImage = m_inputBuffer->getImageForRead();

   if(srcImage != NULL)
   {

      Image<unsigned char> * dstImage = m_outputBuffer->getImageForWrite();

      if(dstImage != NULL)
      {
         for(int x = 0; x < srcImage->getWidth(); x++)
         {
            for(int y = 0; y < srcImage->getHeight(); y++)
            {
               unsigned char value = srcImage->getValue(x,y,0);

               dstImage->setValue(x,y,0,m_mapping->getRed(value));
               dstImage->setValue(x,y,1,m_mapping->getGreen(value));
               dstImage->setValue(x,y,2,m_mapping->getBlue(value));

            }
         }

         m_outputBuffer->disposeImageForWrite(dstImage);
      }

      m_inputBuffer->disposeImageForRead(srcImage);

   }

}
