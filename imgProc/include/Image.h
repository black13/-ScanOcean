
#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstring>

/**
 * Image Data Structure
 */
template <class T>
class Image
{

public:

   /**
    * Constructor
    *
    * @param width Width of the image
    * @param height Height of the image
    * @param channels Number of channels
    */
	Image(int width, int height, int channels);

	/**
	 * Destructor
	 */
	~Image();

	/**
	 * Expose the internal data
	 *
	 * @return Pointer to the data
	 */
	T* operator() ();

	/**
	 * Set one pixel value (Inefficient for many pixels)
	 *
	 * @param x X-coordinate
	 * @param y Y-coordinate
	 * @param value Value
	 */
	void setValue(int x, int y, int c, T value);

	/**
	 * Get a copy of the written value (Inefficient for many pixels)
	 *
    * @param x X-coordinate
    * @param y Y-coordinate
    * @param c Channels value
	 */
	T getValue(int x, int y, int c);

	//TODO - Provide image iterators (rows, cols iterators etc) for efficient
	//       operations

	/**
	 * Get image width
	 */
	int getWidth();

	/**
	 * Get image height
	 */
	int getHeight();

	/**
	 * Get number of channels
	 */
   int getChannels();

private:
   /**
    * Width
    */
	int m_width;

	/**
	 * Height
	 */
	int m_height;

	/**
	 * Channels
	 */
	int m_channels;

	/**
	 * Data
	 */
	T* m_data;

};

template <class T>
Image<T>::Image(int width, int height, int channels)
: m_width(width),
  m_height(height),
  m_channels(channels)
{

   m_data = new T[m_width * m_height * m_channels];
   memset(m_data, 0 ,m_width * m_height * m_channels * sizeof(T));

}

template <class T>
T* Image<T>::operator() ()
{

   return m_data;

}

template <class T>
void Image<T>::setValue(int x, int y, int c, T value)
{

   m_data[m_channels * (y * m_width + x) + c] = value;

}

template <class T>
T Image<T>::getValue(int x, int y, int c)
{

   return (T) m_data[m_channels * (y * m_width + x) + c];

}

template <class T>
Image<T>::~Image()
{

   delete[] m_data;

}

template <class T>
int Image<T>::getWidth()
{

   return m_width;

}

template <class T>
int Image<T>::getHeight()
{

   return m_height;

}

template <class T>
int Image<T>::getChannels()
{

   return m_channels;

}

#endif
