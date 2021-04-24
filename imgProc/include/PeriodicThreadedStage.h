/*
 * PeriodicThreadedStage.h
 *
 *  Created on: Oct 9, 2012
 *      Author: afaraldo
 */

#ifndef PERIODICTHREADEDSTAGE_H_
#define PERIODICTHREADEDSTAGE_H_

#include <ThreadedStage.h>

class Operation;

/**
 * Implementation of a threaded stage. The operation is executed periodically
 * by the thread (e.g. fetching periodically an image)
 */
class PeriodicThreadedStage
: public ThreadedStage
{

public:
   /**
    * Constructor (operation is not set)
    *
    * @param ms Operation period
    */
   PeriodicThreadedStage(int ms);

   /**
    * Constructor (operation is set)
    *
    * @param operation Operation
    * @param ms Operation period
    */
   PeriodicThreadedStage(Operation* operation, int ms);

   /**
    * Get the operation period
    *
    * @return Operation period
    */
   int getPeriod();

   /**
    * Set the operation period
    *
    * @ms Operation period
    */
   void setPeriod(int ms);

   /**
    * Destructor
    */
   virtual ~PeriodicThreadedStage();

protected:

   /**
    * Implementation of the thread's run function
    */
   void run();

private:
   /**
    * Operation period
    */
   int m_ms;

};


#endif /* PERIODICTHREADEDSTAGE_H_ */
