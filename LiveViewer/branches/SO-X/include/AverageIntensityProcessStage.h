/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef AVERAGE_INTENSITY_PROCESS_STAGE_H
#define AVERAGE_INTENSITY_PROCESS_STAGE_H

/*---------------------------------------------------------------------------*/

#include <ProcessStage.h>

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
    * @param roiMasks - vector of pointer to Arrays with ROI masks
    */
   void setMasks(std::vector<Array*> roiMasks);

protected:

   /**
    * Get buffer value as an integer. Handles type casting pointer to buffer.
    *
    * @param buffer - pointer to the raw data buffer
    * @param offset - index offset from beginning of buffer
    * @param type - Array::DataType to treat buffer as
    * @return the value in the buffer as an integer
    */
   int getBufferIntegerValue(char* buffer, long offset, Array::DataType type);

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
    * Masks used for computing ROIs
    */
   std::vector<Array*> m_roiMasks;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
