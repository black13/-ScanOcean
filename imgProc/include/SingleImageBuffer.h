
#ifndef SINGLEIMAGEBUFFER_H_
#define SINGLEIMAGEBUFFER_H_

#include <AbstractImageBuffer.h>

#include <Image.h>

/**
 * Implementation of the AbstractImageBuffer with a single shared image
 */
class SingleImageBuffer
: public AbstractImageBuffer
{

public:
   /**
    * Constructor
    *
    * @param width Width of the image
    * @param heigth Height of the image
    * @param channels Number of channels for an image
    */
   SingleImageBuffer(int width, int heigth, int channels);

   /**
    * Destructor
    */
   virtual ~SingleImageBuffer();

   /**
    * Get image for write
    *
    * @return Returns just the pointer
    */
   Image<unsigned char> * getImageForWrite();

   /**
    * Dispose image for write (does nothing)
    */
   void disposeImageForWrite(Image<unsigned char> * image);

   /**
    * Get image for read
    *
    * @return Returns just the pointer
    */
   Image<unsigned char> * getImageForRead();

   /**
    * Dispose image for read (does nothing)
    */
   void disposeImageForRead(Image<unsigned char> * image);

private:

   /**
    * Image
    */
   Image<unsigned char>* m_image;

};


#endif
