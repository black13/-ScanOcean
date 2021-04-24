
#include <GaussianFilterOperation.h>

#include <Image.h>
#include <AbstractImageBuffer.h>
#include <opencv2/opencv.hpp>


GaussianFilterOperation::GaussianFilterOperation(
      AbstractImageBuffer* inputBuffer,
      AbstractImageBuffer* outputBuffer)
: Process(inputBuffer,outputBuffer)
{

}

GaussianFilterOperation::~GaussianFilterOperation()
{

}

void GaussianFilterOperation::execute()
{

   Image<unsigned char> * srcImage = m_inputBuffer->getImageForRead();

   if(srcImage != NULL)
   {

      Image<unsigned char> * dstImage = m_outputBuffer->getImageForWrite();

      if(dstImage != NULL)
      {

         IplImage* in = cvCreateImageHeader(cvSize(srcImage->getWidth(),
                                                   srcImage->getHeight()),
                                             IPL_DEPTH_8U,
                                             srcImage->getChannels());

         IplImage* out = cvCreateImageHeader(cvSize(dstImage->getWidth(),
                                                    dstImage->getHeight()),
                                             IPL_DEPTH_8U,
                                             dstImage->getChannels());


         in->imageData = (char*) (*srcImage)();

         out->imageData = (char*) (*dstImage)();

         cvSmooth( in, out, CV_GAUSSIAN, 15, 15 );



         cvReleaseImageHeader(&in);
         cvReleaseImageHeader(&out);

         m_outputBuffer->disposeImageForWrite(dstImage);
      }

      m_inputBuffer->disposeImageForRead(srcImage);

   }

}
