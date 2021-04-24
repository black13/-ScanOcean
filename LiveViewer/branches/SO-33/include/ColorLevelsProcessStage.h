/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef COLOR_LEVELS_PROCESS_STAGE_H
#define COLOR_LEVELS_PROCESS_STAGE_H

/*---------------------------------------------------------------------------*/

#include <ProcessStage.h>
#include <ColorTransferFunction.h>
using gstar::ColorTransferFunction;

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

   /**
    * Get the minimum value in the latest image array
    */
   double getImageMin();

   /**
    * Get the maximum value in the latest image array
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
    * Process each Array from the input buffer and write results to the
    * output buffer.
    *
    * @param input - the input Array to process
    * @param output - the output Array in to which results should be written
    */
   void process(Array& input, Array& output);

private:
   /**
    * Set overall data range based on the data type
    */
   void setRangeMinMax(Array::DataType type);

   /**
    * Set the min and max value found in the data
    */
   void setDataMinMax(Array &input);

   int getBufferIntegerValue(char * buffer, long offset, Array::DataType type);


   ColorTransferFunction m_ctf;
   double m_rangeMin;
   double m_rangeMax;
   double m_imageMin;
   double m_imageMax;
   Array m_lastImage;
};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
