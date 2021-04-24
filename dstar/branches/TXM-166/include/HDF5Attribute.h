/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_HDF5_ATTRIBUTE_H
#define DSTAR_HDF5_ATTRIBUTE_H

/*---------------------------------------------------------------------------*/

#include <AbstractAttribute.h>
#include <HDF5Object.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_array.hpp>
#include <boost/weak_ptr.hpp>
#include <hdf5.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

/*---------------------------------------------------------------------------*/

namespace dstar
{

/**
 * HDF5Attribute class
 */
class HDF5Attribute
: public AbstractAttribute, public HDF5Object
{

public:

   /**
    * Default constructor.
    */
   HDF5Attribute();

   /**
    * Virtual destructor.
    */
   virtual ~HDF5Attribute();

   /**
    * Get data in current selection.
    *
    * Use getType() to determine the data type and cast it appropriately.
    *
    * @return Data in current selection as a shared_array of char.
    */
   virtual boost::shared_array<char> getData() const;

   /**
    * Get the extents of each dimension in the data object. Use getRank() to
    * determine the number of dimensions.
    *
    * @param dims Pointer to an array long enough to hold the extent of each
    *             dimension.
    * @param sz Length of (number of elements in) dims.
    */
   virtual void getDims(unsigned long* dims, unsigned int sz) const;

   /**
    * Get the number of bytes in a single element.
    *
    *@return The number of bytes in a single element.
    */
   virtual unsigned long getNumberOfBytesPerElement() const;

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
    * Get the rank of (number of dimensions in) the data.
    *
    * @return The rank of the data.
    */
   virtual unsigned long getRank() const;

   /**
    * Get DataType of data set.
    *
    * @return DataType of the data set.
    */
   virtual DataType getType() const;

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
    * Set the extents of each dimension in the data object. Use setRank()
    * first to set the number of dimensions.
    *
    * @param dims Pointer to an array holding the extents of each dimension.
    * @param sz Length of (number of elements in) dims.
    */
   virtual void setDims(unsigned long* dims, unsigned int sz) const;

   /**
    * Set the rank of (number of dimensions in) the data.
    *
    * @param rank The rank of the data.
    */
   virtual void setRank(unsigned long rank);

   /**
    * Set DataType of data set.
    *
    * @param type DataType of the data set.
    */
   virtual void setType(DataType type);

protected:

   /**
    * Dimension extents
    */
   hsize_t* m_dims;

   /**
    * Dataset rank in AbstractData terms, not HDF5 terms.
    */
   unsigned long m_rank;

   /**
    * Data type
    */
   DataType m_type;

   /**
    * HDF5 data space (file space) id
    */
   hid_t m_dataSpaceId;

   /**
    * The number of bytes in a single element.
    */
   unsigned long m_bytesPerElement;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
