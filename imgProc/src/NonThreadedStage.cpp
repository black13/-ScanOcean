
#include <NonThreadedStage.h>

NonThreadedStage::NonThreadedStage()
: Stage(NULL)
{

}

NonThreadedStage::NonThreadedStage(Operation* operation)
: Stage(operation)
{

}

NonThreadedStage::~NonThreadedStage()
{

}

void NonThreadedStage::update()
{

   this->process();

}
