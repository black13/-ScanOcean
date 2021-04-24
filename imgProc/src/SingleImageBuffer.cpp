
#include <SingleImageBuffer.h>

SingleImageBuffer::SingleImageBuffer(int width, int heigth, int channels)
: AbstractImageBuffer(width,heigth,channels)
{

   m_image = new Image<unsigned char>(width,heigth,channels);

}

SingleImageBuffer::~SingleImageBuffer()
{

   delete m_image;

}

Image<unsigned char> * SingleImageBuffer::getImageForWrite()
{

   return m_image;

}

void SingleImageBuffer::disposeImageForWrite(Image<unsigned char> * image)
{

}

Image<unsigned char> * SingleImageBuffer::getImageForRead()
{
   return m_image;
}

void SingleImageBuffer::disposeImageForRead(Image<unsigned char> * image)
{

}



