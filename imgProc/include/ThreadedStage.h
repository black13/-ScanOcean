
#ifndef THREADEDOPERATION_H_
#define THREADEDOPERATION_H_

#include <Stage.h>
#include <Thread.h>

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

class Operation;

/**
 * Class implementing a threaded stage. The update function wakes up the
 * thread using a condition variable
 */
class ThreadedStage
: public Stage,
  public Thread
{

public:
   /**
    * Constructor (no operation)
    */
   ThreadedStage();

   /**
    * Constructor (with operation set)
    *
    * @param operation Operation
    */
   ThreadedStage(Operation* operation);

   /**
    * Destructor
    */
   virtual ~ThreadedStage();

   /**
    * Update implementation (calls the class' condition variable notify)
    */
   void update();

protected:

   /**
    * Abstract function executed by the running thread
    */
   virtual void run() = 0;

protected:

   /**
    * True when the state changed, false otherwise
    */
   bool m_changed;

   /**
    * Mutex
    */
   boost::mutex m_mutex;

   /**
    * Condition variable
    */
   boost::condition_variable m_canRead;

};

#endif
