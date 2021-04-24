
#include <ImagePoolBuffer.h>
#include <iostream>
#include <string>

void ImagePoolBuffer::print(std::string s)
{

	std::cout << s << std::endl;

	std::cout << "Availability List: ";
	for(std::list<int>::iterator i = m_availabilityList.begin();
		i != m_availabilityList.end();
		++i)
	{
		std::cout << *i << "->";
	}
	std::cout << std::endl;

	std::cout << "Reference Count: ";
	for(int i = 0; i < m_size; i++)
	{
		std::cout << m_readersRefCount[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Last Written: ";
	std::cout << m_lastWritten;
	std::cout << std::endl;
	std::cout << "-----------" << std::endl;
}

ImagePoolBuffer::ImagePoolBuffer(int size, int width, int heigth, int channels)
: AbstractImageBuffer(width,heigth,channels),
  m_size(size)
{

	m_resources = new Image<unsigned char>*[m_size];
	m_readersRefCount = new int[m_size];
	for(int i = 0; i < m_size; i++) {
		m_resources[i] = new Image<unsigned char>(width,heigth,channels);
		m_readersRefCount[i] = 0;
		m_availabilityList.push_back(i);
		m_ptrIndexTable.insert(std::pair<Image<unsigned char>*,int>(m_resources[i],i));
	}
	
	m_lastWritten = -1;

}

ImagePoolBuffer::~ImagePoolBuffer()
{

	for(int i = 0; i < m_size; i++)
		delete m_resources[i];
	delete[] m_resources;
	delete[] m_readersRefCount;

}

int ImagePoolBuffer::findIndex(Image<unsigned char> * image)
{

	std::map<Image<unsigned char>*,int>::iterator iter;
	iter = m_ptrIndexTable.find(image);

	if(iter != m_ptrIndexTable.end())
		return iter->second;
	else
		return -1;

}

Image<unsigned char> * ImagePoolBuffer::getImageForWrite()
{

   boost::unique_lock<boost::mutex> lock(m_mutex);

	// No Image is available for writing, fail
	if(m_availabilityList.empty())
	{

		return NULL;
	}
	else
	{
		// Take the next available image
		int nextAvailable = m_availabilityList.front();
		m_availabilityList.pop_front();

		return m_resources[nextAvailable];
	}

}

void ImagePoolBuffer::disposeImageForWrite(Image<unsigned char> * image)
{

   boost::unique_lock<boost::mutex> lock(m_mutex);

	//Find the index
	int writtenResource = findIndex(image);

	if(writtenResource != -1)
	{

		//Make available for writing the old last written if:
		//1) is valid
		//2) no one is reading (otherwise the reader will make it
		//   available for writing)
		if(m_lastWritten != -1 && m_readersRefCount[m_lastWritten] == 0)
			m_availabilityList.push_back(m_lastWritten);

		//Set the last written index
		m_lastWritten = writtenResource;

	}
	else
	{
	   //TODO Exception
	}


}

Image<unsigned char> * ImagePoolBuffer::getImageForRead()
{
	
   boost::unique_lock<boost::mutex> lock(m_mutex);

	//Never wrote on the buffer
	if(m_lastWritten == -1)
		return NULL;
	
	//Take ptr to the last written image
	Image<unsigned char>* image = m_resources[m_lastWritten];

	//Increment the reference count
	m_readersRefCount[m_lastWritten]++;
	

	return image;

}

void ImagePoolBuffer::disposeImageForRead(Image<unsigned char> * image)
{

   boost::unique_lock<boost::mutex> lock(m_mutex);

	//Find the index
	int resource = findIndex(image);

	if(resource != -1)
	{
	   //Decrement reference count
	   m_readersRefCount[resource]--;

	   //No more readers
	   if(m_readersRefCount[resource] <= 0 &&
	      resource != m_lastWritten)
	   {
	      m_readersRefCount[resource] = 0;

	      //Insert it available for writing
	      m_availabilityList.push_back(resource);

	   }
	}
	else
	{
	   //TODO Exception
	}

}
