
#include <Source.h>
#include <iostream>
#include <Image.h>

Source::Source()
: m_outputBuffer(NULL)
{

}

Source::Source(AbstractImageBuffer* outputBuffer)
: m_outputBuffer(outputBuffer)
{

}

Source::~Source()
{

}

AbstractImageBuffer* Source::getOutputBuffer()
{

   return m_outputBuffer;

}

void Source::setOutputBuffer(AbstractImageBuffer* outputBuffer)
{

   m_outputBuffer = outputBuffer;

}

