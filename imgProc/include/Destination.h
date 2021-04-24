
#ifndef ENDOPERATION_H_
#define ENDOPERATION_H_


#include <Image.h>

#include <AbstractImageBuffer.h>

/**
 * Class that describes a destination for the image pipeline
 */
class Destination
{

public:
   /**
    * Constructor (no buffer)
    */
   Destination();

   /**
    * Constructor (with input Buffer set)
    *
    * @param inputBuffer buffer to write data
    */
   Destination(AbstractImageBuffer* inputBuffer);

   /**
    * Destructor
    */
   virtual ~Destination();

   /**
    * Get the destination buffer
    *
    * @return Destination buffer or NULL
    */
   AbstractImageBuffer* getInputBuffer();

   /**
    * Set the destination buffer
    *
    * @param inputBuffer Destination buffer
    */
   void setInputBuffer(AbstractImageBuffer* inputBuffer);

protected:

   /**
    * Destination buffer
    */
   AbstractImageBuffer* m_inputBuffer;

};



#endif /* ENDOPERATION_H_ */
