
#include <Process.h>

Process::Process()
: Source(NULL),
  Destination(NULL)
{

}

Process::Process(AbstractImageBuffer* inputBuffer,
                 AbstractImageBuffer* outputBuffer)
: Source(outputBuffer),
  Destination(inputBuffer)
{

}

Process::~Process()
{

}

