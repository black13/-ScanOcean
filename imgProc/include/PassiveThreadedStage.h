
#ifndef PASSIVETHREADEDSTAGE_H_
#define PASSIVETHREADEDSTAGE_H_

#include <ThreadedStage.h>

class Operation;

/**
 * Implementation of a Passive threaded stage. This thread sleeps until
 * someone else (e.g. connected stages) calls the update function. The update
 * function wakes up the thread that executes one-time the operation and
 * notifies the other connected stages
 */
class PassiveThreadedStage
: public ThreadedStage
{

public:
   /**
    * Constructor (no operation)
    */
   PassiveThreadedStage();

   /**
    * Constructor (operation is set)
    *
    * @param operation Operation
    */
   PassiveThreadedStage(Operation* operation);

   /**
    * Destructor
    */
   virtual ~PassiveThreadedStage();

protected:

   /**
    * Implementation of the thread's run function
    */
   void run();


};


#endif /* PASSIVETHREADEDSTAGE_H_ */
