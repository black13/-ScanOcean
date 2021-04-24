/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <AbstractView.h>
#include <AbstractObject.h>

using namespace dstar;
using boost::shared_ptr;
using boost::weak_ptr;
using std::list;

/*---------------------------------------------------------------------------*/

AbstractView::AbstractView()
{
}

/*---------------------------------------------------------------------------*/

AbstractView::~AbstractView()
{

   // Detach view from subjects and erase subject entries
   list<weak_ptr<AbstractObject> >::iterator i;
   for (i = m_subjects.begin() ; i != m_subjects.end() ; ++i) {
      if (((i -> lock()).get()) != NULL) {
         (i -> lock()) -> detachView(this);
      }
   }
   m_subjects.clear();

}

/*---------------------------------------------------------------------------*/

void AbstractView::addDataObject(shared_ptr<AbstractObject> obj)
{

   // Store data object
   weak_ptr<AbstractObject> o = weak_ptr<AbstractObject>(obj);
   m_subjects.push_back(o);

   // Attach view (this object) to data
   obj -> attachView(this);

   // Notify implementation subclass that data was added
   dataAdded(obj);

}

/*---------------------------------------------------------------------------*/

list<shared_ptr<AbstractObject> > AbstractView::getDataObjects()
{

   // List as a copy of the subject list
   list<shared_ptr<AbstractObject> > sptrs;

   // Copy the list
   list<weak_ptr<AbstractObject> >::iterator i;
   for (i = m_subjects.begin() ; i != m_subjects.end() ; ++i) {
      sptrs.push_back(i -> lock());
   }

   // Return a copy
   return sptrs;

}

/*---------------------------------------------------------------------------*/

void AbstractView::removeDataObject(shared_ptr<AbstractObject> obj)
{

   // Find data object in subject list
   list<weak_ptr<AbstractObject> >::iterator i;
   for (i = m_subjects.begin() ; i != m_subjects.end() ; ++i) {
      if ((i -> lock()) == obj) {
         dataRemoved(obj);         // Notify implementations of removal
         obj -> detachView(this);  // Detach this from object's view list
         m_subjects.erase(i);      // Erase the object from the subject list
         break;                    // Break out, iterator is now invalid
      }
   }

}

/*---------------------------------------------------------------------------*/
