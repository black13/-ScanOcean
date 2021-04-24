/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_ABSTRACT_ATTRIBUTE_H
#define DSTAR_ABSTRACT_ATTRIBUTE_H

/*---------------------------------------------------------------------------*/

#include <AbstractObject.h>
#include <DStarTypes.h>

#include <boost/shared_array.hpp>
#include <string>
#include <utility>
#include <vector>

/*---------------------------------------------------------------------------*/

namespace dstar
{

/**
 * AbstractAttribute class
 */
class AbstractAttribute
: virtual public AbstractObject
{

public:

   /**
    * Default constructor.
    */
   AbstractAttribute();

   /**
    * Virtual destructor.
    */
   virtual ~AbstractAttribute();

   /**
    * Get data in current selection.
    *
    * Use getType() to determine the data type and cast it appropriately.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @return Data in current selection as a shared_array of char.
    */
   virtual boost::shared_array<char> getData() const = 0;

   /**
    * Get the extents of each dimension in the data object. Use getRank() to
    * determine the number of dimensions.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param dims Pointer to an array long enough to hold the extent of each
    *             dimension.
    * @param sz Length of (number of elements in) dims.
    */
   virtual void getDims(unsigned long* dims, unsigned int sz) const = 0;

   /**
    * Get the number of bytes in a single element.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    *@return The number of bytes in a single element.
    */
   virtual unsigned long getNumberOfBytesPerElement() const = 0;

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
    * Get the rank of (number of dimensions in) the data.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @return The rank of the data.
    */
   virtual unsigned long getRank() const = 0;

   /**
    * Get DataType of data set.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @return DataType of the data set.
    */
   virtual DataType getType() const = 0;

   /**
    * Set the extents of each dimension in the data object. Use setRank()
    * first to set the number of dimensions.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param dims Pointer to an array holding the extents of each dimension.
    * @param sz Length of (number of elements in) dims.
    */
   virtual void setDims(unsigned long* dims, unsigned int sz) const = 0;

   /**
    * Set the rank of (number of dimensions in) the data.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param rank The rank of the data.
    */
   virtual void setRank(unsigned long rank) = 0;

   /**
    * Set DataType of data set.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param type DataType of the data set.
    */
   virtual void setType(DataType type) = 0;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
