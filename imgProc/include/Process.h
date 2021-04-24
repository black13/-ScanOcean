
#ifndef PROCESSOPERATION_H_
#define PROCESSOPERATION_H_

#include <Source.h>
#include <Destination.h>


#include <AbstractImageBuffer.h>

/**
 * Class which is both a Source and a Destination. This implies an input and
 * output buffer
 */
class Process
: public Source,
  public Destination
{

public:

   /**
    * Constructor (no buffers are set)
    */
   Process();

   /**
    * Constructor
    *
    * @param inputBuffer Input buffer
    * @param outputBuffer Output buffer
    */
    Process(AbstractImageBuffer* inputBuffer, AbstractImageBuffer* outputBuffer);

   /**
    * Destructor
    */
   virtual ~Process();

};


#endif
