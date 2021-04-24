
#ifndef STAGE_H_
#define STAGE_H_

#include <list>
#include <algorithm>

class Operation;

/**
 * Abstract stage class. Executes operation using composition and
 * notifies other stages when the operation is finished
 */
class Stage
{

public:

   /**
    * Constructor (no operation is set yet)
    */
   Stage();

   /**
    * Constructor (operation is set)
    *
    * @param operation Operation class
    */
   Stage(Operation* operation);

   /**
    * Destructor
    */
   virtual ~Stage();

   /**
    * Get the operation pointer
    *
    * @return Operation or NULL if no operation is set
    */
   Operation* getOperation();

   /**
    * Set the operation
    *
    * @param operation Operation to be set
    */
   void setOperation(Operation* operation);

   //TODO - Exception (see implementation)
   /**
    * Connect this stage to another
    *
    * @param stage Stage to be connected
    */
   void connect(Stage* stage);

   //TODO - Exception (see implementation)
   /**
    * Disconnect the stage passed as parameter
    *
    * @param stage Stage to be disconnected
    */
   void disconnect(Stage* stage);

   /**
    * Function called to process the stage. The function will
    * 1) execute the operation if any
    * 2) update all the connected stages
    */
   void process();

   /**
    * Abstract function that describes how to update the connected stages
    */
   virtual void update() = 0;

protected:

   /**
    * Operation
    */
   Operation* m_operation;

   /**
    * List of connected stages
    */
   std::list<Stage*> m_connectedStages;

};


#endif
