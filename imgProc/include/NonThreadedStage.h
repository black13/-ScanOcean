
#ifndef NONTHREADEDSTAGE_H_
#define NONTHREADEDSTAGE_H_

#include <Stage.h>

class Operation;

/**
 * Stage implementation that is not threaded. The update simply calls
 * the process function
 */
class NonThreadedStage
: public Stage
{

public:
   /**
    * Constructor (no operation set)
    */
   NonThreadedStage();

   /**
    * Constructor (operation is set)
    *
    * @param operation Operation
    */
   NonThreadedStage(Operation* operation);

   /**
    * Destructor
    */
   virtual ~NonThreadedStage();

   /**
    * Update implementation
    */
   void update();

};


#endif
