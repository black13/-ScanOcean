
#include <PeriodicThreadedStage.h>

#include <iostream>

PeriodicThreadedStage::PeriodicThreadedStage(int ms)
: ThreadedStage(NULL),
  m_ms(ms)
{

}

PeriodicThreadedStage::PeriodicThreadedStage(Operation* operation, int ms)
: ThreadedStage(operation),
  m_ms(ms)
{

}

PeriodicThreadedStage::~PeriodicThreadedStage()
{

}

int PeriodicThreadedStage::getPeriod()
{

   return m_ms;

}

void PeriodicThreadedStage::setPeriod(int ms)
{

   m_ms = ms;

}

void PeriodicThreadedStage::run()
{

   boost::unique_lock<boost::mutex> lock(m_mutex);
   while(isRunning())
   {

      try
      {
         boost::this_thread::disable_interruption di;
         {
            process();
         }
         boost::this_thread::sleep(boost::posix_time::milliseconds(m_ms));
      }
      catch(const boost::thread_interrupted& e)
      {
         break;
      }

   }

}

