/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_ABSTRACT_GROUP_H
#define DSTAR_ABSTRACT_GROUP_H

/*---------------------------------------------------------------------------*/

#include <AbstractObject.h>

#include <boost/shared_ptr.hpp>
#include <list>
#include <vector>

/*---------------------------------------------------------------------------*/

namespace dstar
{

/**
 * Abstract data model group object
 */
class AbstractGroup
: virtual public AbstractObject
{

public:

   /**
    * Default constructor.
    */
   AbstractGroup();

   /**
    * Pure virtual destructor.
    */
   virtual ~AbstractGroup() = 0;

   /**
    * Add a child object to the group. The child object's parent is reassigned
    * to this group.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param child The child object to add.
    */
   virtual void addChild(boost::shared_ptr<AbstractObject> child) = 0;

   /**
    * Get child object based on its index. Use GetNumberOfChildren() to
    * determine the total number of children.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param i The index of the child object.
    * @return A shared pointer to the desired child object.
    * @throws
    */
   virtual boost::shared_ptr<const AbstractObject> getChild(int i) const = 0;

   /**
    * Get the index of the specified child object.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param obj The object whose index is desired.
    * @return The index of the child object.
    * @throws
    */
   virtual
   int getChildIndex(boost::shared_ptr<const AbstractObject> obj) const = 0;

   /**
    * Get the group's children.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @return Children as a list of shared pointers.
    */
   virtual
   std::vector<boost::shared_ptr<const AbstractObject> > getChildren()
   const = 0;

   /**
    * Get the number of children in the group.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @return Number of children.
    */
   virtual int getNumberOfChildren() const = 0;

   /**
    * Remove a child from the group.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param child The child object to remove.
    * @throws
    */
   virtual void removeChild(boost::shared_ptr<AbstractObject> child) = 0;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
