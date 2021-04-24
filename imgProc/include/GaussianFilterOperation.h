/*
 * GaussianFilterOperation.h
 *
 *  Created on: Oct 12, 2012
 *      Author: afaraldo
 */

#ifndef GAUSSIANFILTEROPERATION_H_
#define GAUSSIANFILTEROPERATION_H_

#include <Process.h>
#include <Operation.h>

class AbstractImageBuffer;

//TODO the class is not very general. It doesn't allow to specify the kernel
//     (since it is hard-coded).
/**
 * Operation that applies a gaussian filter to the image (using OpenCV)
 */
class GaussianFilterOperation
: public Process,
  public Operation
{

public:
   /**
    * Constructor
    *
    * @param inputBuffer Buffer used to read images
    * @param outputBuffer Buffer used to write the output
    */
   GaussianFilterOperation(AbstractImageBuffer* inputBuffer,
                           AbstractImageBuffer* outputBuffer);

   /**
    * Destructor
    */
   virtual ~GaussianFilterOperation();

   /**
    * Execute operation
    */
   void execute();


};


#endif /* GAUSSIANFILTEROPERATION_H_ */
