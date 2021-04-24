/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <AreaDetectorSourceStage.h>
#include <stdio.h>

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

   // Create channel access and channels
   m_cha = new CA();

}

/*---------------------------------------------------------------------------*/

AreaDetectorSourceStage::~AreaDetectorSourceStage()
{

   // Clean up frame buffer
   if (m_buffer != NULL) {
      delete [] m_buffer;
   }

   // Destroy CA context
   if (m_cha != NULL) {
      delete m_cha;
   }

}

/*---------------------------------------------------------------------------*/

void AreaDetectorSourceStage::channelAccessUpdated(QString name, int val)
{

   QString pvPrefix = m_pvPrefix.c_str();
   if (name == QString(pvPrefix + "UniqueId_RBV")) {
      process();
   }

}

/*---------------------------------------------------------------------------*/

void AreaDetectorSourceStage::process()
{

   // Get width, height and color mode
   int width = 0;
   int height = 0;
   int depth = 0;
   int colorMode = 0;
   m_cha -> get((m_pvPrefix + "ArraySize0_RBV").c_str(), &width, true);
   m_cha -> get((m_pvPrefix + "ArraySize1_RBV").c_str(), &height, true);
   m_cha -> get((m_pvPrefix + "ArraySize2_RBV").c_str(), &depth, true);
   m_cha -> get((m_pvPrefix + "ColorMode_RBV").c_str(), &colorMode, true);

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
   chtype dataType =
      m_cha -> getFieldType(QString((m_pvPrefix + "ArrayData").c_str()));

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

   // Get array from EPICS
   m_cha -> getArray((m_pvPrefix + "ArrayData").c_str(),
                     m_buffer,
                     width * height,
                     true);

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

   // Attach context in thread
   m_cha -> attach();

   m_cha -> create((m_pvPrefix + "ArraySize0_RBV").c_str(), false);
   m_cha -> create((m_pvPrefix + "ArraySize1_RBV").c_str(), false);
   m_cha -> create((m_pvPrefix + "ArraySize2_RBV").c_str(), false);
   m_cha -> create((m_pvPrefix + "ColorMode_RBV").c_str(), false);
   m_cha -> create((m_pvPrefix + "ArrayData").c_str(), false);
   m_cha -> create((m_pvPrefix + "UniqueId_RBV").c_str(), true);
   m_cha -> subscribe((m_pvPrefix + "UniqueId_RBV").c_str(), true);

   // Connect channel access callback
   connect(m_cha, SIGNAL(update(QString, int)),
           this, SLOT(channelAccessUpdated(QString, int)));

   // Loop forever, checking for interruption point
   while(true) {

      // Check for interruption point
      try {
         interuptionPoint();
      }
      catch(const boost::thread_interrupted& e) {
         break;
      }

      try {
         boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
      }
      catch(const boost::thread_interrupted& e) {
         break;
      }

   }

}

/*---------------------------------------------------------------------------*/
