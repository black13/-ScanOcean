/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <AreaDetectorSourceStage.h>
#include <stdio.h>


#include <CAEmitDataChangeHandler.h>

#include <qdebug.h>

/*---------------------------------------------------------------------------*/

AreaDetectorSourceStage::AreaDetectorSourceStage(std::string pvPrefix)
: QObject(NULL), SourceStage()
{

   // Store PV prefix
   m_pvPrefix = pvPrefix;

   // Initialize image buffer
   m_buffer = NULL;
   m_width = -1;
   m_height = -1;
   m_type = Array::INVALID;

}

/*---------------------------------------------------------------------------*/

AreaDetectorSourceStage::~AreaDetectorSourceStage()
{

   // Clean up frame buffer
   if (m_buffer != NULL) {
      delete [] m_buffer;
   }

}

/*---------------------------------------------------------------------------*/

//void AreaDetectorSourceStage::channelAccessUpdated(QString name, int val)
//{
//
//   Q_UNUSED(val)
//
//   QString pvPrefix = m_pvPrefix.c_str();
//   if (name == QString(pvPrefix + "UniqueId_RBV")) {
//      process();
//   }
//
//}

void AreaDetectorSourceStage::channelAccessUpdated(int val)
{

      //process();

}

/*---------------------------------------------------------------------------*/

void AreaDetectorSourceStage::process()
{

   // Get width, height and color mode
   int width = 0;
   int height = 0;
   int depth = 0;
   int colorMode = 0;

   ChannelAccess* ca = ChannelAccess::getInstance();

   m_ArraySize0_RBV = ca->getPV(m_pvPrefix + "ArraySize0_RBV",1,5);
   m_ArraySize1_RBV = ca->getPV(m_pvPrefix + "ArraySize1_RBV",1,5);
   m_ArraySize2_RBV = ca->getPV(m_pvPrefix + "ArraySize2_RBV",1,5);
   m_ColorMode_RBV = ca->getPV(m_pvPrefix + "ColorMode_RBV",1,5);
   m_ArrayData = ca->getPV(m_pvPrefix + "ArrayData",1,5);
   m_UniqueId_RBV = ca->getPV(m_pvPrefix + "UniqueId_RBV",1,5);

   CAGetTotalCopy<int> widthReader(&width);
   CAGetTotalCopy<int> heightReader(&height);
   CAGetTotalCopy<int> depthReader(&depth);
   CAGetTotalCopy<int> colorModeReader(&colorMode);

   m_ArraySize0_RBV->synGet(1,&widthReader);
   m_ArraySize1_RBV->synGet(1,&heightReader);
   m_ArraySize2_RBV->synGet(1,&depthReader);
   m_ColorMode_RBV->synGet(1,&colorModeReader);

   // Image size check
   if (width <= 0 || height <= 0) {
      return;
   }

   // Image depth check
   if (depth < 0 || depth > 1) {
      return;
   }

   // Color mode check
   if (colorMode != 0) {
      return;
   }

   // Get the EPICS data type
   chtype dataType = m_ArrayData->getType();

   // Convert EPICS data type to Array data type
   Array::DataType type = Array::INVALID;
   switch (dataType) {
   case DBF_CHAR:
      type = Array::UINT8;
      break;
   case DBF_SHORT:
      type = Array::UINT16;
      break;
   }

   // Resize buffer (if image size or depth changes)
   if (width != m_width || height != m_height || type != m_type) {

      // Delete old buffer
      if (m_buffer != NULL) {
         delete [] m_buffer;
      }

      // Set new width, height and type
      m_width = width;
      m_height = height;
      m_type = type;

      // Allocate memory
      switch (type) {
      case Array::INVALID:
         fprintf(stderr, "Can't handle INVALID\n");
         return;
         break;
      case Array::UINT8:
         m_buffer = new char[m_width * m_height];
         break;
      case Array::UINT16:
         m_buffer = new char[m_width * m_height * 2];
         break;
      case Array::BGRA32:
         fprintf(stderr, "Can't handle BGRA32\n");
         return;
         break;
      default:
         return;
         break;
      }

   }

   CAGetTotalCopy<char> arrayDataReader(m_buffer);
   m_ArrayData->synGet(width * height,&arrayDataReader);

   // Get output buffer
   Array* aptr = NULL;
   try {
      aptr = m_outputBuffer -> getMemory();
   }
   catch(const boost::thread_interrupted& e) {
      return;
   }

   // Set image properties
   unsigned long long dims[2];
   dims[0] = height;
   dims[1] = width;
   aptr -> setDimensions(dims, 2);
   aptr -> setType(m_type);

   // Check for interruption point
   try {
      interuptionPoint();
   }
   catch(const boost::thread_interrupted& e) {
      return;
   }

   // Get output buffer from Array
   char* outBuffer = aptr -> getBuffer();

   // Fill output buffer
   switch (type) {
   case Array::INVALID:
      fprintf(stderr, "Can't handle INVALID\n");
      return;
      break;
   case Array::UINT8:
      memcpy(outBuffer, m_buffer, m_height * m_width);
      break;
   case Array::UINT16:
      memcpy(outBuffer, m_buffer, m_height * m_width * 2);
      break;
   case Array::BGRA32:
      fprintf(stderr, "Can't handle BGRA32\n");
      return;
      break;
   default:
      return;
      break;
   }

   // Check for interruption point
   try {
      m_outputBuffer -> insertNext(aptr);
   }
   catch(const boost::thread_interrupted& e) {
      return;
   }

}

/*---------------------------------------------------------------------------*/

void AreaDetectorSourceStage::run()
{

   // Loop forever, checking for interruption point
   while(true) {

      // Check for interruption point
      try {
         interuptionPoint();
      }
      catch(const boost::thread_interrupted& e) {
         break;
      }

      process();

      try {
         boost::this_thread::sleep(boost::posix_time::milliseconds(33));
      }
      catch(const boost::thread_interrupted& e) {
         break;
      }

   }

   // When the thread is stopped, clean CA
   m_ArraySize0_RBV.reset();
   m_ArraySize1_RBV.reset();
   m_ArraySize2_RBV.reset();
   m_ColorMode_RBV.reset();
   m_ArrayData.reset();
   m_UniqueId_RBV.reset();

}

/*---------------------------------------------------------------------------*/
