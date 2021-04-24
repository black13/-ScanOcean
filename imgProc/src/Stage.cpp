
#include <Stage.h>
#include <Operation.h>

Stage::Stage()
: m_operation(NULL)
{

}

Stage::Stage(Operation* operation)
: m_operation(operation)
{

   m_operation->setParent(this);

}

Stage::~Stage()
{

}

void Stage::setOperation(Operation* operation)
{

   m_operation = operation;
   m_operation->setParent(this);

}

Operation* Stage::getOperation()
{

   return m_operation;

}

void Stage::connect(Stage* stage)
{

   std::list<Stage*>::iterator i =
      std::find(m_connectedStages.begin(),
                m_connectedStages.end(),
                stage);

   //Not found
   if(i == m_connectedStages.end())
   {
      m_connectedStages.push_back(stage);
   }
   else
   {
      //TODO throw some exception
   }


}

void Stage::disconnect(Stage* stage)
{

   std::list<Stage*>::iterator i =
      std::find(m_connectedStages.begin(),
                m_connectedStages.end(),
                stage);

   //Found
   if(i != m_connectedStages.end())
   {
      m_connectedStages.erase(i);
   }
   else
   {
      //TODO throw some exception
   }

}

void Stage::process()
{

   // 1) Execute the operation (if any)
   if(m_operation != NULL) m_operation->execute();

   // 2) Update all the connected stages
   std::list<Stage* >::iterator i;
   for(i = m_connectedStages.begin(); i != m_connectedStages.end(); ++i)
   {
      Stage* current = *i;
      current->update();
   }

}
