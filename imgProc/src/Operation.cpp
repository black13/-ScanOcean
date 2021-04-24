
#include <Operation.h>
#include <Stage.h>
#include <iostream>

Operation::Operation()
: m_parent(NULL)
{

}

Operation::~Operation()
{

}

Operation::Operation(Stage* parent)
: m_parent(parent)
{

}

void Operation::setParent(Stage* parent)
{

   m_parent = parent;

}

Stage* Operation::getParent()
{

   return m_parent;

}
