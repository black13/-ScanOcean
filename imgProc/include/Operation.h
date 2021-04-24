
#ifndef OPERATION_H_
#define OPERATION_H_

class Stage;

/**
 * Abstract class for an operation
 */
class Operation
{

public:
   /**
    * Constructor (no parent is set)
    */
   Operation();

   /**
    * Constructor (parent is set)
    *
    * @param parent Parent stage
    */
   Operation(Stage* parent);

   /**
    * Destructor
    */
   virtual ~Operation();

   /**
    * Set the parent
    *
    * @param parent Parent to be set
    */
   void setParent(Stage* parent);

   /**
    * Get the parent
    *
    * @return Returns parent or NULL is no parent is set
    */
   Stage* getParent();

   /**
    * Execute abstract function
    */
	virtual void execute() = 0;

protected:

	/**
	 * Parent pointer
	 */
	Stage* m_parent;

};


#endif
