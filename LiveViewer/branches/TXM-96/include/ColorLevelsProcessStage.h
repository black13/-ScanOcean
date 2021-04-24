/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef COLOR_LEVELS_PROCESS_STAGE_H
#define COLOR_LEVELS_PROCESS_STAGE_H

/*---------------------------------------------------------------------------*/

#include <ProcessStage.h>
#include <ColorTransferFunction.h>
#include <Array.h>

#include <QList>

using gstar::ColorTransferFunction;

class Histogram;
/*---------------------------------------------------------------------------*/

class ColorLevelsProcessStage
: public ProcessStage
{

public:

   /**
    * Constructor.
    */
   ColorLevelsProcessStage();

   /**
    * Destructor.
    */
   ~ColorLevelsProcessStage();

   /**
    * Set the transfer function to use while displaying color
    */
   void setColorTransferFunction(ColorTransferFunction ctf);

   void setHistogram(Histogram* hist);

   /**
    * Get the minimum value in the latest image gstar::Array
    */
   double getImageMin();

   /**
    * Get the maximum value in the latest image gstar::Array
    */
   double getImageMax();

   /**
    * Get the minimum value associated with the data type
    * of the most recent image
    */
   double getRangeMin();

   /**
    * Get the maximum value associated with the data type
    * of the most recent image
    */
   double getRangeMax();

protected:

   /**
    * Process each gstar::Array from the input buffer and write results to the
    * output buffer.
    *
    * @param input - the input gstar::Array to process
    * @param output - the output gstar::Array in to which results should be written
    */
   void process(gstar::Array& input, gstar::Array& output);

private:
   /**
    * Set overall data range based on the data type
    */
   void setRangeMinMax(gstar::Array::DataType type);

   /**
    * Set the min and max value found in the data
    */
   void setDataMinMax(gstar::Array &input);

   int getBufferIntegerValue(char * buffer, long offset, gstar::Array::DataType type);

private:

   ColorTransferFunction m_ctf;
   double m_rangeMin;
   double m_rangeMax;
   double m_imageMin;
   double m_imageMax;
   gstar::Array m_lastImage;
   Histogram* m_histogram;
   int m_count;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
