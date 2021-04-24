#ifndef ImagePoolBuffer_h__
#define ImagePoolBuffer_h__

#include <AbstractImageBuffer.h>

#include <list>
#include <map>
#include <utility>
#include <string>

#include <boost/thread/mutex.hpp>

/**
 * Implementation of an AbstractImageBuffer using a pool of resources (images).
 * Readers will always get the most updated image available for reading.
 * Writers will always use available image-buffers for writing.
 */
class ImagePoolBuffer
: public AbstractImageBuffer
{

public:
   /**
    * Constructor
    *
    * @param size Size of the pool (Number of images)
    * @param width Width of the image
    * @param heigth Height of the image
    * @param channels Number of channels for an image
    */
	ImagePoolBuffer(int size, int width, int heigth, int channels);

	/**
	 * Destructor
	 */
	virtual ~ImagePoolBuffer();

	/**
	 * Get the size of the pool
	 *
	 * @return Size of the pool
	 */
	int getSize();

	/**
	 * Get an image that can be safely used for writing. When retrieved, this
	 * image cannot be used by any other writers for writing operations.
	 *
	 * @return Image or NULL if it is impossible to get an image for writing
	 */
	Image<unsigned char> * getImageForWrite();

	/**
	 * At the end of the operation the image has to be disposed. This operation
	 * sets the disposed image as the most recent available data.
	 *
	 * @param image Image to be diposed
	 */
	void disposeImageForWrite(Image<unsigned char> * image);

	/**
	 * Get the most recently written image for reading. Multiple readers can read
	 * safely from the same image.
	 *
    * @return Image or NULL if it is impossible to get an image for writing
	 */
	Image<unsigned char> * getImageForRead();

	/**
	 * When a reader has finished the reader operation, it has to release the
	 * resource. This will decrement the readers' reference count by one. Once
	 * this count reaches 0 and the data is not the most recent anymore,
	 * the image becomes again available for writing again
	 *
	 * @param image Image to be disposed
	 */
	void disposeImageForRead(Image<unsigned char> * image);

private:
	/**
	 * Mutex
	 */
	boost::mutex m_mutex;

	/**
	 * Debugging utility
	 */
	void print(std::string s);

	/**
	 * Accessory to find the array index associated to the image
	 */
	int findIndex(Image<unsigned char> * image);

	/**
	 * Buffer size
	 */
	int m_size;

	/**
	 * Resources
	 */
	Image<unsigned char>** m_resources;

	/**
	 * Availability list (list of images available for writing)
	 */
	std::list<int> m_availabilityList;

	/**
	 * Index of the last written image
	 */
	int m_lastWritten;

	/**
	 * Readers reference count array (image index -> count)
	 */
	int* m_readersRefCount;

	//TODO change to an hash table, the interface is the same (unordered_map)
	/**
	 * Associated table image ptr -> array-index
	 */
	std::map<Image<unsigned char>*,int> m_ptrIndexTable;

};


#endif // ImagePoolBuffer_h__
