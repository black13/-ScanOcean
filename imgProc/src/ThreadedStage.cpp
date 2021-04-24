
#include <ThreadedStage.h>
#include <Operation.h>

#include <iostream>


ThreadedStage::ThreadedStage()
: Stage(NULL),
  Thread(),
  m_changed(true)
{

}

ThreadedStage::ThreadedStage(Operation* operation)
: Stage(operation),
  Thread(),
  m_changed(true)
{

}

ThreadedStage::~ThreadedStage()
{

}

void ThreadedStage::update()
{
   m_changed = true;
   m_canRead.notify_one();
}


