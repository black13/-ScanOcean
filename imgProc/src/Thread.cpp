/*---------------------------------------------------------------------------*/

#include <Thread.h>

using boost::bind;
using boost::shared_ptr;
using boost::thread;

/*---------------------------------------------------------------------------*/

Thread::Thread()
{

   m_isRunning = false;

}

/*---------------------------------------------------------------------------*/

Thread::~Thread()
{
}

/*---------------------------------------------------------------------------*/

bool Thread::isRunning()
{

   return m_isRunning;

}

/*---------------------------------------------------------------------------*/

void Thread::interuptionPoint()
{

   // Check for interruption
   boost::this_thread::interruption_point();

}

/*---------------------------------------------------------------------------*/

void Thread::start()
{

   // Create thread and start it
   m_thread = shared_ptr<thread>(new thread(bind(&Thread::run, this)));

   // Set to running
   m_isRunning = true;

}

/*---------------------------------------------------------------------------*/

void Thread::stop()
{

   // Don't do anything if it's not running
   if (m_isRunning == false) {
      return;
   }

   // Interrupt thread
   m_thread -> interrupt();

   // Set to not running
   m_isRunning = false;

   // Wait for thread to finish
   m_thread -> join();

}

/*---------------------------------------------------------------------------*/
