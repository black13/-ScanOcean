/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_HDF5_DATA_H
#define DSTAR_HDF5_DATA_H

/*---------------------------------------------------------------------------*/

#include <AbstractData.h>
#include <HDF5Object.h>
#include <Selection.h>

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

/**
 * HDF5Data class
 */
class HDF5Data
: virtual public HDF5Object, virtual public AbstractData
{

public:

   /**
    * Default constructor.
    */
   HDF5Data();

   /**
    * Virtual destructor.
    */
   virtual ~HDF5Data();

   /**
    * Attach a scale to a dimension of this data object.
    *
    * @param dim The dimension to attach the scale.
    * @param obj Data object representing the scale.
    */
   virtual void attachScale(unsigned long dim,
                            boost::shared_ptr<AbstractData> obj);

   /**
    * Get data in current selection.
    *
    * Use getType() to determine the data type and cast it appropriately.
    *
    * @return Data in current selection as a shared_array of char.
    */
   virtual boost::shared_array<char> getData() const = 0;

   /**
    * Get the extents of each dimension in the data object. Use getRank() to
    * determine the number of dimensions.
    *
    * @param dims Pointer to an array long enough to hold the extent of each
    *             dimension.
    * @param sz Length of (number of elements in) dims.
    */
   virtual void getDims(unsigned long long* dims, unsigned long sz) const;

   /**
    * Get the number of bytes in current selection.
    *
    *@return The number of bytes in the current selection.
    */
   virtual unsigned long long getNumberOfBytesInSelection() const;

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
   std::vector<std::pair<std::string, std::string> > getProperties() const = 0;

   /**
    * Get the rank of (number of dimensions in) the data.
    *
    * @return The rank of the data.
    */
   virtual unsigned long getRank() const;

   /**
    * Get all scales associated with this data object. This method returns a
    * list of lists. The outer list has one list for each dimension in the
    * data. The list for each dimension contains string / data object pairs.
    * An unlimited number of scales may be associated with each dimension.
    *
    * @return All scales associated with this data object.
    */
   virtual
   std::list<std::list<std::pair<std::string,
                       boost::shared_ptr<const AbstractData> > > >
   getScaleList() const;

   /**
    * Get the current selection in the data.
    *
    * @return Current selection in the data given by an instance of Selection.
    */
   virtual Selection getSelection() const;

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
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param id HDF5 object id to load.
    */
   virtual void loadFromHDF5Id(hid_t id) = 0;

   /**
    * Remove a scale from a dimension of this data object. This method does
    * nothing if either the dimension is invalid or the data object is not
    * found.
    *
    *
    * @param dim The dimension from which the data object is removed.
    * @param obj The data object to remove from the dimension given by dim.
    */
   virtual void removeScale(unsigned long dim,
                            boost::shared_ptr<AbstractData> obj);

   /**
    * Set the extents of each dimension in the data object. Use setRank()
    * first to set the number of dimensions.
    *
    * @param dims Pointer to an array holding the extents of each dimension.
    * @param sz Length of (number of elements in) dims.
    */
   virtual void setDims(unsigned long long* dims, unsigned long sz) const;

   /**
    * Set the rank of (number of dimensions in) the data.
    *
    * @param rank The rank of the data.
    */
   virtual void setRank(unsigned long rank);

   /**
    * Set the desired selection range in the data.
    *
    * Make certain that the rank and dimensions in the selection object match
    * those for the data object. The rank and dimensions may be obtained with
    * Selection::GetRank() and Selection::GetDims(). It is recommended to
    * first use GetSelection() to obtain an instance of the current selection
    * including the correct rank and dimensions, modify the selection for that
    * instance, and then pass it to this method.
    *
    * @param Desired selection range in the data given by an instance of
    *        Selection.
    * @throws std::out_of_range when selection is invalid.
    */
   virtual void setSelection(Selection selection);

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
   boost::shared_array<hsize_t> m_dataDims;

   /**
    * Count selection in data space
    */
   boost::shared_array<hsize_t> m_dataCount;

   /**
    * Start positions in data space
    */
   boost::shared_array<hsize_t> m_dataStart;

   /**
    * Data stride in memory space
    */
   boost::shared_array<hsize_t> m_dataStride;

   /**
    * Start positions in memory space
    */
   boost::shared_array<hsize_t> m_memStartDims;

   /**
    * Dataset rank in AbstractData terms, not HDF5 terms.
    */
   unsigned long m_rank;

   /**
    * Dimension scales
    *
    * The subclass that instantiates this must allocate the correct size list.
    */
   std::list<std::list<std::pair<std::string,
                                 boost::weak_ptr< AbstractData> > > > m_scales;

   /**
    * Selection within data
    */
   Selection m_selection;

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
