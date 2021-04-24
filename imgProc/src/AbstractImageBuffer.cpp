
#include <AbstractImageBuffer.h>

AbstractImageBuffer::AbstractImageBuffer(int width, int height, int channels)
: m_width(width),
  m_height(height),
  m_channels(channels)
{

}

int AbstractImageBuffer::getWitdh()
{
   return m_width;
}

int AbstractImageBuffer::getHeight()
{
   return m_height;
}

int AbstractImageBuffer::getChannels()
{
   return m_channels;
}

