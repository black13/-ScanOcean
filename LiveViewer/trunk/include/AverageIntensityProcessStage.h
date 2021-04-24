/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef AVERAGE_INTENSITY_PROCESS_STAGE_H
#define AVERAGE_INTENSITY_PROCESS_STAGE_H

/*---------------------------------------------------------------------------*/

#include <ProcessStage.h>
#include <Array.h>

#include <vector>

/*---------------------------------------------------------------------------*/

class AverageIntensityProcessStage
: public ProcessStage
{

public:

   /**
    * Constructor.
    */
   AverageIntensityProcessStage();

   /**
    * Destructor.
    */
   ~AverageIntensityProcessStage();

   /**
    * Set masks used for computing ROIs
    *
    * @param roiMasks - vector of pointer to gstar::Arrays with ROI masks
    */
   void setMasks(std::vector<gstar::Array*> roiMasks);

protected:

   /**
    * Get buffer value as an integer. Handles type casting pointer to buffer.
    *
    * @param buffer - pointer to the raw data buffer
    * @param offset - index offset from beginning of buffer
    * @param type - gstar::Array::DataType to treat buffer as
    * @return the value in the buffer as an integer
    */
   int getBufferIntegerValue(char* buffer, long offset, gstar::Array::DataType type);

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
    * Masks used for computing ROIs
    */
   std::vector<gstar::Array*> m_roiMasks;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
