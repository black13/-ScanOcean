/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_TIFF_OBJECT_H
#define DSTAR_TIFF_OBJECT_H

/*---------------------------------------------------------------------------*/

#include <AbstractObject.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

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
 * TIFF data object
 */
class TIFFObject
: virtual public AbstractObject
{

public:

   /**
    * Default constructor.
    */
   TIFFObject();

/*   *
    * Constructor. Loads object data from HDF5 file.
    *
    * @param id The HDF5 Id from which this object loads itself.

   TIFFObject(hid_t id);*/

   /**
    * Pure virtual destructor.
    */
   virtual ~TIFFObject();

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

   /*
    * Get a list of object property descriptions. Properties
    * are stored as pairs of strings where the first element in the pair is
    * the name of the property and the second element in the pair is the value.
    *
    * @return List of object property descriptions.*/

   virtual
   std::vector<std::pair<std::string, std::string> > getProperties() const = 0;

   /**
    * Get a pointer to this object's root object in the data model.
    *
    * @return A shared pointer to the root object for this object.
    */
   virtual boost::shared_ptr<const AbstractObject> getRoot() const;

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
    * Object attributes
    */
   std::vector<boost::shared_ptr<AbstractAttribute> > m_attributes;



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
