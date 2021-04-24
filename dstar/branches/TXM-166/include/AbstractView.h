/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_ABSTRACT_VIEW_H
#define DSTAR_ABSTRACT_VIEW_H

/*---------------------------------------------------------------------------*/

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <list>

/*---------------------------------------------------------------------------*/

namespace dstar {   
   
// Forward declaration of AbstractObject
class AbstractObject;

/**
 * @brief The AbstractView class provides the abstract interface for view
 * classes.
 *
 * The AbstractView class defines the standard interface that views must use
 * to interoperate with DStar data objects. It can not be instantiated
 * directly. Instead, you should subclass it to create new views.
 */
class AbstractView
{
   
public:
   
   /**
    * Default constructor
    */
   AbstractView();
   
   /**
    * Destructor
    */
   virtual ~AbstractView() = 0;
   
   /**
    * Add a DStar data object to the view's list of observed subjects.
    *
    * This method first adds the object to its list of subjects. Then it
    * calls AbstractObserver::attachView() with the this pointer as the
    * argument. This sets the view as an observer of the data object. Finally,
    * it calls dataAdded() so that the derived implementation is informed
    * that a data object has been added.
    *
    * @param obj The data object to add.
    */
   virtual void addDataObject(boost::shared_ptr<dstar::AbstractObject> obj);

   /**
    * Adds a DStar data object to the list of subjects it is observing.
    *
    * This must be implemented by subclasses.
    *
    * @param obj The data object being added.
    */
   virtual void dataAdded(boost::shared_ptr<dstar::AbstractObject> obj) = 0;

   /**
    * Removes a DStar data object from the list of subjects it is observing.
    *
    * This must be implemented by subclasses.
    *
    * @param obj The data object being removed.
    */
   virtual void dataRemoved(boost::shared_ptr<dstar::AbstractObject> obj) = 0;

   /**
    * Get a list of data objects the view is observing.
    *
    * @return List of view's subjects.
    */
   virtual
   std::list<boost::shared_ptr<dstar::AbstractObject> > getDataObjects();

   /**
    * Remove a DStar data object to the view's list of observed subjects.
    *
    * This method first calls dataRemoved() so that the derived implementation
    * is informed that the data object is being removed. It then removes the
    * object from its list of subjects.
    *
    * @param obj The data object to remove.
    */
   virtual void removeDataObject(boost::shared_ptr<dstar::AbstractObject> obj);

protected:
   
   /**
    * List of subjects.
    */
   std::list<boost::weak_ptr<dstar::AbstractObject> > m_subjects;
   
};
   
}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
