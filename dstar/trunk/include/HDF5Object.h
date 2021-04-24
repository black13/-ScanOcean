/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_HDF5_OBJECT_H
#define DSTAR_HDF5_OBJECT_H

/*---------------------------------------------------------------------------*/

#include <AbstractObject.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <hdf5.h>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

/*---------------------------------------------------------------------------*/

namespace dstar
{

// Forward declaration of AbstractAttribute
class AbstractAttribute;

/**
 * HDF5 data object
 */
class HDF5Object
: virtual public AbstractObject
{

public:

   /**
    * Default constructor.
    */
   HDF5Object();

   /**
    * Constructor. Loads object data from HDF5 file.
    *
    * @param id The HDF5 Id from which this object loads itself.
    */
   HDF5Object(hid_t id);

   /**
    * Pure virtual destructor.
    */
   virtual ~HDF5Object();

   /**
    * Add an attribute to the object. The attribute object's parent is
    * reassigned to this object.
    *
    * @param attr The attribute object to add.
    */
   virtual void addAttribute(boost::shared_ptr<AbstractAttribute> attr);

   /**
    * Get attribute object based on its index. Use getNumberOfAttributes() to
    * determine number of attributes for this object.
    *
    * @param i The index of the attribute object.
    * @return A shared pointer to the desired attribute object.
    * @throws std::out_of_range
    */
   virtual boost::shared_ptr<const AbstractAttribute> getAttribute(int i)
   const;

   /**
    * Get the index of the specified attribute object.
    *
    * @param attr The object whose index is desired.
    * @return The index of the attribute object.
    * @throws std::out_of_range
    */
   virtual
   int getAttributeIndex(boost::shared_ptr<const AbstractAttribute> attr)
   const;

   /**
    * Get the object's attributes.
    *
    * @return Attributes as a list of shared pointers.
    */
   virtual
   std::vector<boost::shared_ptr<const AbstractAttribute> > getAttributes()
   const;

   /**
    * Get object name.
    *
    * @return The name of the object as a string.
    */
   virtual std::string getName() const;

   /**
    * Get the number of attributes attached to this object.
    *
    * @return Number of attributes.
    */
   virtual int getNumberOfAttributes() const;

   /**
    * Get a pointer to this object's parent object in the data model.
    *
    * @return A shared pointer to the parent object.
    */
   virtual boost::shared_ptr<const AbstractObject> getParent() const;

   /**
    * Get a list of object property descriptions. Properties
    * are stored as pairs of strings where the first element in the pair is
    * the name of the property and the second element in the pair is the value.
    *
    * @return List of object property descriptions.
    */
   virtual
   std::vector<std::pair<std::string, std::string> > getProperties() const = 0;

   /**
    * Get a pointer to this object's root object in the data model.
    *
    * @return A shared pointer to the root object for this object.
    */
   virtual boost::shared_ptr<const AbstractObject> getRoot() const;

   /**
    * Load this object from a specified HDF5 object id.
    *
    * The HDF5 object id must be opened by the caller, and the caller is
    * responsible for the HDF5 resource. Currently, DStar keeps all HDF5
    * resources open, and closes them when the HDF5 file is closed.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param id HDF5 object id to load.
    */
   virtual void loadFromHDF5Id(hid_t id) = 0;

   /**
    * Remove an attribute from the object.
    *
    * @param attr The attribute object to remove.
    * @throws std::out_of_range
    */
   virtual void removeAttribute(boost::shared_ptr<AbstractAttribute> attr);

   /**
    * Set object name.
    *
    * @param name The object name as a string.
    */
   virtual void setName(std::string name);

   /**
    * Set this object's parent object in the data model.
    *
    * @param parent A shared pointer to the parent object.
    */
   virtual void setParent(boost::shared_ptr<AbstractObject> parent);

protected:

   /**
    * Get HDF5 object identifier corresponding to this object, if one exists.
    *
    * This is a potentially dangerous method. The caller should not close the
    * returned HDF5 object identifier or otherwise modify the data it
    * represents unless it really knows what it's doing.
    *
    * @return HDF5 object identifier for this object.
    */
   virtual hid_t getHDF5Id();

   /**
    * Set HDF5 object identifier corresponding to this object.
    *
    * @param id HDF5 object identifier for this object.
    */
   virtual void setHDF5Id(hid_t id);

protected:

   /**
    * Object attributes
    */
   std::vector<boost::shared_ptr<AbstractAttribute> > m_attributes;

   /**
    * HDF5 object identifier
    */
   hid_t m_hdf5Id;

   /**
    * Text name
    */
   std::string m_name;

   /**
    * weak_ptr to parent object
    */
   boost::weak_ptr<AbstractObject> m_parent;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
