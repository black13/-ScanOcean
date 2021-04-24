

#include <PassiveThreadedStage.h>

#include <Operation.h>

#include <iostream>

PassiveThreadedStage::PassiveThreadedStage()
: ThreadedStage(NULL)
{

}

PassiveThreadedStage::PassiveThreadedStage(Operation* operation)
: ThreadedStage(operation)
{

}

PassiveThreadedStage::~PassiveThreadedStage()
{

}

void PassiveThreadedStage::run()
{

   boost::unique_lock<boost::mutex> lock(m_mutex);
   while(isRunning())
   {

      try
      {
         while(!m_changed)
            m_canRead.wait(lock);

         boost::this_thread::disable_interruption di;
         {
            process();
            m_changed = false;
         }

      }
      catch(const boost::thread_interrupted& e)
      {
         break;
      }

   }

}



