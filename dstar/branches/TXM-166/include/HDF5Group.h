/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_HDF5_GROUP_H
#define DSTAR_HDF5_GROUP_H

/*---------------------------------------------------------------------------*/

#include <AbstractGroup.h>
#include <HDF5Object.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <hdf5.h>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

/*---------------------------------------------------------------------------*/

namespace dstar
{

/**
 * HDF5Group class
 */
class HDF5Group
: virtual public AbstractGroup, virtual public HDF5Object
{

public:

   /**
    * Default constructor.
    */
   HDF5Group();

   /**
    * Pure virtual destructor.
    */
   virtual ~HDF5Group();

   /**
    * Add a child object to the group. The child object's parent is reassigned
    * to this group.
    *
    * @param child The child object to add.
    */
   virtual void addChild(boost::shared_ptr<AbstractObject> child);

   /**
    * Get child object based on its index. Use getNumberOfChildren() to
    * determine the total number of children.
    *
    * @param i The index of the child object.
    * @return A shared pointer to the desired child object.
    * @throws std::out_of_range
    */
   virtual boost::shared_ptr<const AbstractObject> getChild(int i) const;

   /**
    * Get the index of the specified child object.
    *
    * @param obj The object whose index is desired.
    * @return The index of the child object.
    * @throws std::out_of_range
    */
   virtual
   int getChildIndex(boost::shared_ptr<const AbstractObject> obj) const;

   /**
    * Get the group's children.
    *
    * @return Children as a list of shared pointers.
    */
   virtual
   std::vector<boost::shared_ptr<const AbstractObject> > getChildren() const;

   /**
    * Get the number of children in the group.
    *
    * @return Number of children.
    */
   virtual int getNumberOfChildren() const;

   /**
    * Get a list of object property descriptions. Properties
    * are stored as pairs of strings where the first element in the pair is
    * the name of the property and the second element in the pair is the value.
    *
    * @return List of object property descriptions.
    */
   virtual
   std::vector<std::pair<std::string, std::string> > getProperties() const;

   /**
    * Load this object from a specified HDF5 object id.
    *
    * The HDF5 object id must be opened by the caller, and the caller is
    * responsible for the HDF5 resource. Currently, DStar keeps all HDF5
    * resources open, and closes them when the HDF5 file is closed.
    *
    * @param id HDF5 object id to load.
    */
   virtual void loadFromHDF5Id(hid_t id);

   /**
    * Remove a child from the group.
    *
    * @param child The child object to remove.
    * @throws std::out_of_range
    */
   virtual void removeChild(boost::shared_ptr<AbstractObject> child);

protected:

   /**
    *
    */
   static herr_t iterator(hid_t id, const char* name,
                          const H5L_info_t* info, void* op_data);

   /**
    *
    */
   static herr_t iteratorAttr(hid_t id, const char* name,
                              const H5A_info_t* ainfo, void* op_data);

protected:

   /**
    * Child objects
    */
   std::vector<boost::shared_ptr<AbstractObject> > m_children;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
