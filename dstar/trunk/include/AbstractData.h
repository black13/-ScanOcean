/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_ABSTRACT_DATA_H
#define DSTAR_ABSTRACT_DATA_H

/*---------------------------------------------------------------------------*/

#include <AbstractObject.h>
#include <DStarTypes.h>
#include <Selection.h>

#include <list>
#include <utility>
#include <boost/smart_ptr/shared_array.hpp>

/*---------------------------------------------------------------------------*/

namespace dstar {

/**
 * Abstract data model data object
 */
class AbstractData
: virtual public AbstractObject
{

public:

   /**
    * Default constructor.
    */
   AbstractData();

   /**
    * Pure virtual destructor.
    */
   virtual ~AbstractData() = 0;

   /**
    * Attach a scale to a dimension of this data object.
    *
    * @param dim The dimension to attach the scale.
    * @param obj Data object representing the scale.
    */
   virtual void attachScale(unsigned long dim,
                            boost::shared_ptr<AbstractData> obj) = 0;

   /**
    * Get all scales associated with this data object. This method returns a
    * list of lists. The outer list has one list for each dimension in the
    * data. The list for each dimension contains string / data object pairs.
    * An unlimited number of scales may be associated with each dimension.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @return All scales associated with this data object.
    */
   virtual
   std::list<std::list<std::pair<std::string,
                       boost::shared_ptr<const AbstractData> > > >
   getScaleList() const = 0;

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
   virtual void getDims(unsigned long long* dims, unsigned long sz) const = 0;

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
    * Get the current selection in the data.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @return Current selection in the data given by an instance of Selection.
    */
   virtual Selection getSelection() const = 0;

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
    * Remove a scale from a dimension of this data object. This method does
    * nothing if either the dimension is invalid or the data object is not
    * found.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
    *
    * @param dim The dimension from which the data object is removed.
    * @param obj The data object to remove from the dimension given by dim.
    */
   virtual void removeScale(unsigned long dim,
                            boost::shared_ptr<AbstractData> obj) = 0;

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
   virtual void setDims(unsigned long long* dims, unsigned long sz) const = 0;

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
    * Set the desired selection range in the data.
    *
    * This is a pure virtual function provided as an interface. Must be
    * implemented in a subclass.
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
    */
   virtual void setSelection(Selection selection) = 0;

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
