
#include <iostream>


#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <Image.h>
#include <SingleImageBuffer.h>
#include <ImagePoolBuffer.h>

#include <NonThreadedStage.h>

#include <PeriodicThreadedStage.h>
#include <PassiveThreadedStage.h>

#include <FetchAreaDetectorOperation.h>
#include <ColorMapOperation.h>
#include <ColorTransferMapping.h>
#include <LIColorTransferFunction.h>
#include <GaussianFilterOperation.h>

#include <SStar.h>


int main(int argc, char** argv)
{

   Logger::setActive(false);

   ChannelAccess* ca = ChannelAccess::getInstance();
   std::string name = "walleye:image1:";
   boost::shared_ptr<PV> m_ArraySize0_RBV =
      ca->getPV(name + "ArraySize0_RBV",1,5);
   boost::shared_ptr<PV> m_ArraySize1_RBV =
      ca->getPV(name + "ArraySize1_RBV",1,5);
   boost::shared_ptr<PV> m_ArraySize2_RBV =
      ca->getPV(name + "ArraySize2_RBV",1,5);
   boost::shared_ptr<PV> m_ColorMode_RBV =
      ca->getPV(name + "ColorMode_RBV",1,5);
   boost::shared_ptr<PV> m_UniqueId_RBV =
      ca->getPV(name + "UniqueId_RBV",1,5);

   int width = 0;
   int height = 0;
   int depth = 0;
   int colorMode = 0;
   CAGetTotalCopy<int> widthReader(&width);
   CAGetTotalCopy<int> heightReader(&height);
   CAGetTotalCopy<int> depthReader(&depth);
   CAGetTotalCopy<int> colorModeReader(&colorMode);
   m_ArraySize0_RBV->synGet(1,&widthReader);
   m_ArraySize1_RBV->synGet(1,&heightReader);
   m_ArraySize2_RBV->synGet(1,&depthReader);
   m_ColorMode_RBV->synGet(1,&colorModeReader);

//   SingleImageBuffer rawInput(width,height,1);
//   SingleImageBuffer colorMappedImage1(width,height,3);
//   SingleImageBuffer colorMappedImage2(width,height,3);

   ImagePoolBuffer rawInput(20,width,height,1);
   ImagePoolBuffer colorMappedImage1(20,width,height,3);
   ImagePoolBuffer colorMappedImage2(20,width,height,3);
   ImagePoolBuffer gaussFiltered(20,width,height,1);

   FetchAreaDetectorOperation fas(name,&rawInput);

//   Manual modification of the mapping

//   ColorTransferMapping colorMapping1;
//   colorMapping1.setAllRed(255);
//   ColorMapOperation colorOperation1(&rawInput,
//                                     &colorMappedImage1,
//                                     &colorMapping1);
//   ColorTransferMapping colorMapping2;
//   colorMapping2.setAllGreen(255);
//   ColorMapOperation colorOperation2(&rawInput,
//                                     &colorMappedImage2,
//                                     &colorMapping2);

   //Linear color mapper

   LIColorTransferFunction colorTransferFunction1;
   ColorMapOperation colorOperation1(&rawInput,
                                     &colorMappedImage1,
                                     &colorTransferFunction1.getColorMap());

   colorTransferFunction1.addRedKnot(128,255);
   colorTransferFunction1.addRedKnot(255,0);
   //colorTransferFunction1.removeRedKnot(128);

   LIColorTransferFunction colorTransferFunction2;
   ColorMapOperation colorOperation2(&rawInput,
                                     &colorMappedImage2,
                                     &colorTransferFunction2.getColorMap());


   GaussianFilterOperation gaussFilter(&rawInput,&gaussFiltered);

//   NonThreadedStage s0(&fas);
//   NonThreadedStage s1(&colorOperation1);
//   NonThreadedStage s2(&colorOperation2);
//   s0.connect(&s1);
//   s0.connect(&s2);

// Threaded stages

   //PeriodicThreadedStage t0(&fas,17);
   PassiveThreadedStage t0(&fas);
   PassiveThreadedStage t1(&colorOperation1);
   PassiveThreadedStage t2(&colorOperation2);
   PassiveThreadedStage t3(&gaussFilter);

// Create connection

   t0.connect(&t1);
   t0.connect(&t2);
   t0.connect(&t3);
   t0.start();
   t1.start();
   t2.start();
   t3.start();

// Setup OpenCV just to show things

   IplImage* img1 = cvCreateImageHeader(cvSize(rawInput.getWitdh(),
                                               rawInput.getHeight()),
                                       IPL_DEPTH_8U,
                                       1);

   IplImage* img2 = cvCreateImageHeader(cvSize(rawInput.getWitdh(),
                                               rawInput.getHeight()),
                                       IPL_DEPTH_8U,
                                       3);

   IplImage* img3 = cvCreateImageHeader(cvSize(rawInput.getWitdh(),
                                               rawInput.getHeight()),
                                       IPL_DEPTH_8U,
                                       3);

   IplImage* img4 = cvCreateImageHeader(cvSize(rawInput.getWitdh(),
                                               rawInput.getHeight()),
                                       IPL_DEPTH_8U,
                                       1);


   cvNamedWindow( "Raw", CV_WINDOW_AUTOSIZE );
   cvNamedWindow( "ColorMapped1", CV_WINDOW_AUTOSIZE );
   cvNamedWindow( "ColorMapped2", CV_WINDOW_AUTOSIZE );
   cvNamedWindow( "GaussFilt", CV_WINDOW_AUTOSIZE );

   while(true) {
      //Call for non-threaded processing
      //s0.process();

      // Get the images from the proper pool
      Image<unsigned char> * image1 = rawInput.getImageForRead();
      Image<unsigned char> * image2 = colorMappedImage1.getImageForRead();
      Image<unsigned char> * image3 = colorMappedImage2.getImageForRead();
      Image<unsigned char> * image4 = gaussFiltered.getImageForRead();

      if(image1 != NULL &&
         image2 != NULL &&
         image3 != NULL &&
         image4 != NULL)
      {

         img1->imageData = (char*) (*image1)();
         img2->imageData = (char*) (*image2)();
         img3->imageData = (char*) (*image3)();
         img4->imageData = (char*) (*image4)();

         cvShowImage("Raw", img1);
         cvShowImage("ColorMapped1", img2);
         cvShowImage("ColorMapped2", img3);
         cvShowImage("GaussFilt", img4);
         char c = cvWaitKey(17);
         if( c == 27 ) break;

         // Dispose images from the pool
         rawInput.disposeImageForRead(image1);
         colorMappedImage1.disposeImageForRead(image2);
         colorMappedImage2.disposeImageForRead(image3);
         gaussFiltered.disposeImageForRead(image4);

      }

   }

   // Clean memory
   cvReleaseImageHeader(&img1);
   cvReleaseImageHeader(&img2);
   cvReleaseImageHeader(&img3);
   cvReleaseImageHeader(&img4);
   cvDestroyWindow( "Raw" );
   cvDestroyWindow( "ColorMapped1" );
   cvDestroyWindow( "ColorMapped2" );
   cvDestroyWindow( "GaussFilt" );

   return 0;
}
