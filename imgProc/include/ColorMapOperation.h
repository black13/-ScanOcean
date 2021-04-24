
#ifndef COLORMAPOPERATION_H_
#define COLORMAPOPERATION_H_

#include <Process.h>
#include <Operation.h>
#include <AbstractImageBuffer.h>
#include <Image.h>

class ColorTransferMapping;

/**
 * Implementation of a color mapping operation
 */
class ColorMapOperation
: public Process,
  public Operation
{

public:
   //TODO this class is not the most general one. The implementation expectes
   //     a single channel image as input and a 3-channels image as output.
   //     Either the name should be changed accordingly or the class slightly
   //     modified to take in consideration the more general case
   /**
    * Constructor
    *
    * @param inputBuffer Buffer used to read the input
    * @param outputBuffer Buffer used to write the output
    * @param mapping Mapping of colors
    */
   ColorMapOperation(AbstractImageBuffer* inputBuffer,
                     AbstractImageBuffer* outputBuffer,
                     ColorTransferMapping* mapping);


   /**
    * Execute operation
    */
   void execute();

private:

   /**
    * Color mapping
    */
   ColorTransferMapping* m_mapping;

};


#endif
