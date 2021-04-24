/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <AbstractObject.h>

using namespace dstar;
using boost::shared_ptr;
using std::list;

/*---------------------------------------------------------------------------*/

AbstractObject::AbstractObject()
{

}

/*---------------------------------------------------------------------------*/

AbstractObject::~AbstractObject()
{

   // TODO - This needs to change to pass shared_ptr or to use a manager

   // Remove self from each observer
//   list<AbstractView*>::iterator i;
//   for(i = m_observers.begin() ; i != m_observers.end() ; ++i) {
//      (*i) -> removeDataObject(this);
//   }

}

/*---------------------------------------------------------------------------*/

void AbstractObject::attachView(AbstractView* v)
{

   m_observers.push_back(v);

}

/*---------------------------------------------------------------------------*/

void AbstractObject::detachAllViews()
{

   // Clear the observer list
   m_observers.clear();

}

/*---------------------------------------------------------------------------*/

void AbstractObject::detachView(AbstractView* v)
{

   // Find view and erase it from the observer list
   list<AbstractView*>::iterator i;
   for (i = m_observers.begin() ; i != m_observers.end() ; ++i) {
      if (*i == v) {
         m_observers.erase(i);
         break;
      }
   }

}

/*---------------------------------------------------------------------------*/

shared_ptr<AbstractObject> AbstractObject::getAsSharedPtr()
{

   return shared_from_this();

}

/*---------------------------------------------------------------------------*/

list<AbstractView*> AbstractObject::getObservers() const
{

   return m_observers;

}

/*---------------------------------------------------------------------------*/
