
#include <Destination.h>
#include <iostream>

Destination::Destination()
: m_inputBuffer(NULL)
{

}

Destination::Destination(AbstractImageBuffer* inputBuffer)
: m_inputBuffer(inputBuffer)
{

}

Destination::~Destination()
{

}

AbstractImageBuffer* Destination::getInputBuffer()
{

   return m_inputBuffer;

}

void Destination::setInputBuffer(AbstractImageBuffer* inputBuffer)
{

   m_inputBuffer = inputBuffer;

}
