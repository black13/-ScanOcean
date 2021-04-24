/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef AREA_DETECTOR_SOURCE_STAGE_H
#define AREA_DETECTOR_SOURCE_STAGE_H

/*---------------------------------------------------------------------------*/

#include <CA.h>
#include <SourceStage.h>
#include <Array.h>

#include <QObject>
#include <string>

/*---------------------------------------------------------------------------*/

class AreaDetectorSourceStage
: public QObject, public SourceStage
{

   Q_OBJECT

public:

   /**
    * Constructor.
    */
   AreaDetectorSourceStage(std::string pvPrefix);

   /**
    * Destructor.
    */
   ~AreaDetectorSourceStage();

protected:

   /**
    * The overridden run method from Thread. This is the thread's main loop
    * which gets an input buffer, calls process, and writes to the output
    * buffer.
    */
   void run();

private slots:

   /**
    * Slot called by the CA class when a monitor callback is called.
    *
    * @param name - PV name (PV that was updated)
    * @param val - value of updated PV
    */
   void channelAccessUpdated(QString name, int val);

private:

   /**
    * Process a callback/monitor on UniqueId_RBV for a new frame. This method
    * copies the data from the buffer provided for EPICS into the processing
    * pipeline.
    */
   void process();

private:

   /**
    * Channel access
    */
   CA* m_cha;

   /**
    * Area Detector Image PV prefix
    */
   std::string m_pvPrefix;

   /**
    * Raw buffer for image from Area Detector
    */
   char* m_buffer;

   /**
    * Raw buffer width
    */
   int m_width;

   /**
    * Raw buffer height
    */
   int m_height;

   /**
    * Data type
    */
   gstar::Array::DataType m_type;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
