
#ifndef SOURCEOPERATION_H_
#define SOURCEOPERATION_H_


#include <AbstractImageBuffer.h>

/**
 * Class that describes a source for the image pipeline
 */
class Source
{

public:
   /**
    * Constructor (no buffer)
    */
   Source();

   /**
    * Constructor (with buffer)
    *
    * @param outputBuffer Buffer where to write data
    */
	Source(AbstractImageBuffer* outputBuffer);

	/**
	 * Destructor
	 */
	virtual ~Source();

	/**
	 * Get the buffer where to write data
	 *
	 * @return Buffer where to write data or NULL
	 */
	AbstractImageBuffer* getOutputBuffer();

   /**
    * Set the buffer where to write data
    *
    * @param outputBuffer Buffer where to write data
    */
	void setOutputBuffer(AbstractImageBuffer* outputBuffer);

protected:
	/**
	 * Buffer where to write data
	 */
   AbstractImageBuffer* m_outputBuffer;

};


#endif
