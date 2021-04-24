
#ifndef ABSTRACTIMGBUFFER_H_
#define ABSTRACTIMGBUFFER_H_

#include <Image.h>

/**
 * Abstract interface for a buffer used to make operations communicate
 */
class AbstractImageBuffer
{

public:
   /**
    * Constructor (defines the image/images properties)
    *
    * @param width Width of the image
    * @param height Heigth of the image
    * @param channels Channels of the image
    */
   AbstractImageBuffer(int width, int height, int channels);

   /**
    * Get width of the image
    *
    * @return Width of the image
    */
   int getWitdh();

   /**
    * Get the height of the image
    *
    * @return Height of the image
    */
   int getHeight();

   /**
    * Get the channels of the image
    *
    * @return Channels of the image
    */
   int getChannels();

   /**
    * Abstract function to get an image for write
    */
   virtual Image<unsigned char> * getImageForWrite() = 0;

   //TODO It would be better to encapsulate the retrieved image into another
   //     class. Using the RAII principle, this class would have the purpose of
   //     automatically disposing the image when it is destroyed.
   /**
    * Abstract function to dispose an image for write
    */
   virtual void disposeImageForWrite(Image<unsigned char> * image) = 0;

   /**
    * Abstract function to get an image for read
    */
   virtual Image<unsigned char> * getImageForRead() = 0;

   //TODO It would be better to encapsulate the retrieved image into another
   //     class. Using the RAII principle, this class would have the purpose of
   //     automatically disposing the image when it is destroyed.
   /**
    * Abstract function to dispose an image for read
    */
   virtual void disposeImageForRead(Image<unsigned char> * image) = 0;

protected:

   /**
    * Width of the image
    */
   int m_width;

   /**
    * Height of the image
    */
   int m_height;

   /**
    * Channels of the image
    */
   int m_channels;

};

#endif
