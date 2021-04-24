/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_ABSTRACT_OBJECT_H
#define DSTAR_ABSTRACT_OBJECT_H

/*---------------------------------------------------------------------------*/

#include <AbstractView.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
#include <string>
#include <utility>
#include <vector>

/*---------------------------------------------------------------------------*/

namespace dstar
{

// Forward declaration of AbstractAttribute
class AbstractAttribute;

/**
 * @brief The AbstractObject class is the abstract data model root.
 */
class AbstractObject
: virtual public boost::enable_shared_from_this<AbstractObject>
{

public:

   /**
    * Default constructor.
    */
   AbstractObject();

   /**
    * Destructor.
    */
   virtual ~AbstractObject();

   /**
    * Add an attribute to the object. The attribute object's parent is
    * reassigned to this object.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param attr The attribute object to add.
    */
   virtual void addAttribute(boost::shared_ptr<AbstractAttribute> attr) = 0;

   /**
    * Attach a view to this data object as an observer. This object does not
    * take ownership of the view.
    *
    * @param v The view to attach.
    */
   virtual void attachView(AbstractView* v);

   /**
    * Detach all views observing this object.
    *
    * This method clears the list of views on the object. It does not send
    * notification of the detachment to the observer.
    */
   virtual void detachAllViews();

   /**
    * Detach an observer view from this data object. This object does not
    * take ownership of the view.
    *
    * @param v The view to detach.
    */
   virtual void detachView(AbstractView* v);
   
   /**
    * Returns the common shared pointer to this object.
    *
    * @return The common shared pointer to this object.
    */
   virtual boost::shared_ptr<AbstractObject> getAsSharedPtr();

   /**
    * Get attribute object based on its index. Use getNumberOfAttributes() to
    * determine number of attributes for this object.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param i The index of the attribute object.
    * @return A shared pointer to the desired attribute object.
    * @throws
    */
   virtual
   boost::shared_ptr<const AbstractAttribute> getAttribute(int i) const = 0;

   /**
    * Get the index of the specified attribute object.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param attr The object whose index is desired.
    * @return The index of the attribute object.
    * @throws
    */
   virtual
   int getAttributeIndex(boost::shared_ptr<const AbstractAttribute> attr)
   const = 0;

   /**
    * Get the object's attributes.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @return Attributes as a list of shared pointers.
    */
   virtual
   std::vector<boost::shared_ptr<const AbstractAttribute> >
   getAttributes() const = 0;

   /**
    * Get object name.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @return The name of the object as a string.
    */
   virtual std::string getName() const = 0;

   /**
    * Get the number of attributes attached to this object.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @return Number of attributes.
    */
   virtual int getNumberOfAttributes() const = 0;

   virtual std::list<AbstractView*> getObservers() const;

   /**
    * Get a pointer to this object's parent object in the data model.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @return A shared pointer to the parent object.
    */
   virtual boost::shared_ptr<const AbstractObject> getParent() const = 0;

   /**
    * Get a list of object property descriptions. Properties
    * are stored as pairs of strings where the first element in the pair is
    * the name of the property and the second element in the pair is the value.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @return List of object property descriptions.
    */
   virtual
   std::vector<std::pair<std::string, std::string> > getProperties() const = 0;

   /**
    * Get a pointer to this object's root object in the data model.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @return A shared pointer to the root object for this object.
    */
   virtual boost::shared_ptr<const AbstractObject> getRoot() const = 0;

   /**
    * Remove an attribute from the object.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param attr The attribute object to remove.
    * @throws
    */
   virtual void removeAttribute(boost::shared_ptr<AbstractAttribute> attr) = 0;

   /**
    * Set object name.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param name The object name as a string.
    */
   virtual void setName(std::string name) = 0;

   /**
    * Set this object's parent object in the data model.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param parent A shared pointer to the parent object.
    */
   virtual void setParent(boost::shared_ptr<AbstractObject> parent) = 0;

protected:   
   
   /**
    * List of observers
    */
   std::list<AbstractView*> m_observers;
   
};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
