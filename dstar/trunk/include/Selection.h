/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_SELECTION_H
#define DSTAR_SELECTION_H

/*---------------------------------------------------------------------------*/

#include <iostream>
#include <stdexcept>
#include <vector>

/*---------------------------------------------------------------------------*/

namespace dstar {

/**
 * The Selection class provides a representation of a selection of data within
 * a class derived from AbstractData.
 */
class Selection
{

public:

   /**
    * Default constructor.
    */
   Selection();

   /**
    * Constructor specifying selection rank.
    */
   Selection(unsigned long rank);

   /**
    * Pure virtual destructor.
    */
   ~Selection();

   /**
    * Get count.
    *
    * @param dims Pointer to array in which to store selection counts.
    * @param sz Length of array in which to store selection counts.
    */
   void getCount(unsigned long long* count, unsigned long sz) const;

   /**
    * Get selection count.
    *
    * @param d0 Pointer to store the selection count for dimension 0.
    * @throws std::out_of_range when rank is not 1.
    */
   void getCount(unsigned long long* d0) const;

   /**
    * Get selection count.
    *
    * @param d0 Pointer to store the selection count for dimension 0.
    * @param d1 Pointer to store the selection count for dimension 1.
    * @throws std::out_of_range when rank is not 2.
    */
   void getCount(unsigned long long* d0, unsigned long long* d1) const;

   /**
    * Get selection count.
    *
    * @param d0 Pointer to store the selection count for dimension 0.
    * @param d1 Pointer to store the selection count for dimension 1.
    * @param d2 Pointer to store the selection count for dimension 2.
    * @throws std::out_of_range when rank is not 3.
    */
   void getCount(unsigned long long* d0, unsigned long long* d1,
                 unsigned long long* d2) const;

   /**
    * Get selection count.
    *
    * @param d0 Pointer to store the selection count for dimension 0.
    * @param d1 Pointer to store the selection count for dimension 1.
    * @param d2 Pointer to store the selection count for dimension 2.
    * @param d3 Pointer to store the selection count for dimension 3.
    * @throws std::out_of_range when rank is not 4.
    */
   void getCount(unsigned long long* d0, unsigned long long* d1,
                 unsigned long long* d2, unsigned long long* d3) const;

   /**
    * Get data dimensions.
    *
    * @param dims Pointer to array in which to store dimensions.
    * @param sz Length of array in which to store dimensions.
    */
   void getDims(unsigned long long* dims, unsigned long sz) const;

   /**
    * Get data dimensions.
    *
    * @param d0 Pointer to store the extent of dimension 0.
    * @throws std::out_of_range when rank is not 1.
    */
   void getDims(unsigned long long* d0) const;

   /**
    * Get data dimensions.
    *
    * @param d0 Pointer to store the extent of dimension 0.
    * @param d1 Pointer to store the extent of dimension 1.
    * @throws std::out_of_range when rank is not 2.
    */
   void getDims(unsigned long long* d0, unsigned long long* d1) const;

   /**
    * Get data dimensions.
    *
    * @param d0 Pointer to store the extent of dimension 0.
    * @param d1 Pointer to store the extent of dimension 1.
    * @param d2 Pointer to store the extent of dimension 2.
    * @throws std::out_of_range when rank is not 3.
    */
   void getDims(unsigned long long* d0, unsigned long long* d1,
                unsigned long long* d2) const;

   /**
    * Get data dimensions.
    *
    * @param d0 Pointer to store the extent of dimension 0.
    * @param d1 Pointer to store the extent of dimension 1.
    * @param d2 Pointer to store the extent of dimension 2.
    * @param d3 Pointer to store the extent of dimension 3.
    * @throws std::out_of_range when rank is not 4.
    */
   void getDims(unsigned long long* d0, unsigned long long* d1,
                unsigned long long* d2, unsigned long long* d3) const;

   /**
    * Get the rank of (number of dimensions in) the data.
    *
    * @return The rank of the data.
    */
   unsigned long getRank() const;

   /**
    * Get number of elements in the selection.
    *
    * @return The number of elements in the selection.
    */
   unsigned long long getNumberOfElements() const;

   /**
    * Get start position.
    *
    * @param dims Pointer to array in which to store start positions.
    * @param sz Length of array in which to store start positions.
    */
   void getStart(unsigned long long* start, unsigned long sz) const;

   /**
    * Get start position.
    *
    * @param d0 Pointer to store the start position along dimension 0.
    * @throws std::out_of_range when rank is not 1.
    */
   void getStart(unsigned long long* d0) const;

   /**
    * Get start position.
    *
    * @param d0 Pointer to store the start position along dimension 0.
    * @param d1 Pointer to store the start position along dimension 1.
    * @throws std::out_of_range when rank is not 2.
    */
   void getStart(unsigned long long* d0, unsigned long long* d1) const;

   /**
    * Get start position.
    *
    * @param d0 Pointer to store the start position along dimension 0.
    * @param d1 Pointer to store the start position along dimension 1.
    * @param d2 Pointer to store the start position along dimension 2.
    * @throws std::out_of_range when rank is not 3.
    */
   void getStart(unsigned long long* d0, unsigned long long* d1,
                 unsigned long long* d2) const;

   /**
    * Get start position.
    *
    * @param d0 Pointer to store the start position along dimension 0.
    * @param d1 Pointer to store the start position along dimension 1.
    * @param d2 Pointer to store the start position along dimension 2.
    * @param d3 Pointer to store the start position along dimension 3.
    * @throws std::out_of_range when rank is not 4.
    */
   void getStart(unsigned long long* d0, unsigned long long* d1,
                 unsigned long long* d2, unsigned long long* d3) const;

   /**
    * Get data stride. The stride along a dimension is initially set to 1.
    *
    * @param dims Pointer to array in which to store strides.
    * @param sz Length of array in which to store strides.
    */
   void getStride(unsigned long long* stride, unsigned long sz) const;

   /**
    * Get data stride. The stride along a dimension is initially set to 1.
    *
    * @param d0 Pointer to store the stride along dimension 0.
    * @throws std::out_of_range when rank is not 1.
    */
   void getStride(unsigned long long* d0) const;

   /**
    * Get data stride. The stride along a dimension is initially set to 1.
    *
    * @param d0 Pointer to store the stride along dimension 0.
    * @param d1 Pointer to store the stride along dimension 1.
    * @throws std::out_of_range when rank is not 2.
    */
   void getStride(unsigned long long* d0, unsigned long long* d1) const;

   /**
    * Get data stride. The stride along a dimension is initially set to 1.
    *
    * @param d0 Pointer to store the stride along dimension 0.
    * @param d1 Pointer to store the stride along dimension 1.
    * @param d2 Pointer to store the stride along dimension 2.
    * @throws std::out_of_range when rank is not 3.
    */
   void getStride(unsigned long long* d0, unsigned long long* d1,
                  unsigned long long* d2) const;

   /**
    * Get data stride. The stride along a dimension is initially set to 1.
    *
    * @param d0 Pointer to store the stride along dimension 0.
    * @param d1 Pointer to store the stride along dimension 1.
    * @param d2 Pointer to store the stride along dimension 2.
    * @param d3 Pointer to store the stride along dimension 3.
    * @throws std::out_of_range when rank is not 4.
    */
   void getStride(unsigned long long* d0, unsigned long long* d1,
                  unsigned long long* d2, unsigned long long* d3) const;

   /**
    * Print the current selection to std::cerr.
    */
   void printSelf();

   /**
    * Set selection count for specified dimension.
    *
    * @param count Selection count array.
    * @param dim The dimension to set.
    * @throws std::out_of_range when count is invalid.
    */
   void setCount(unsigned long long count, unsigned long dim);

   /**
    * Set selection count.
    *
    * @param count Selection count.
    * @param sz Length of selection count array.
    * @throws std::out_of_range when count is invalid.
    */
   void setCount(unsigned long long* count, unsigned long sz);

   /**
    * Set selection count.
    *
    * @param d0 Selection count for dimension 0.
    * @throws std::out_of_range when rank is not 1 or when count is invalid.
    */
   void setCount(unsigned long long d0);

   /**
    * Set selection count.
    *
    * @param d0 Selection count for dimension 0.
    * @param d1 Selection count for dimension 1.
    * @throws std::out_of_range when rank is not 2 or when count is invalid.
    */
   void setCount(unsigned long long d0, unsigned long long d1);

   /**
    * Set selection count.
    *
    * @param d0 Selection count for dimension 0.
    * @param d1 Selection count for dimension 1.
    * @param d2 Selection count for dimension 2.
    * @throws std::out_of_range when rank is not 3 or when count is invalid.
    */
   void setCount(unsigned long long d0, unsigned long long d1,
                 unsigned long long d2);

   /**
    * Set selection count.
    *
    * @param d0 Selection count for dimension 0.
    * @param d1 Selection count for dimension 1.
    * @param d2 Selection count for dimension 2.
    * @param d3 Selection count for dimension 3.
    * @throws std::out_of_range when rank is not 4 or when count is invalid.
    */
   void setCount(unsigned long long d0, unsigned long long d1,
                 unsigned long long d2, unsigned long long d3);

   /**
    * Set data dimensions.
    *
    * @param dims Data dimension array.
    * @param sz Length of data dimension array.
    */
   void setDims(unsigned long long* dims, unsigned long sz);

   /**
    * Set data dimensions.
    *
    * @param d0 Extent of dimension 0.
    * @throws std::out_of_range when rank is not 1.
    */
   void setDims(unsigned long long d0);

   /**
    * Set data dimensions.
    *
    * @param d0 Extent of dimension 0.
    * @param d1 Extent of dimension 1.
    * @throws std::out_of_range when rank is not 2.
    */
   void setDims(unsigned long long d0, unsigned long long d1);

   /**
    * Set data dimensions.
    *
    * @param d0 Extent of dimension 0.
    * @param d1 Extent of dimension 1.
    * @param d2 Extent of dimension 2.
    * @throws std::out_of_range when rank is not 3.
    */
   void setDims(unsigned long long d0, unsigned long long d1,
                unsigned long long d2);

   /**
    * Set data dimensions.
    *
    * @param d0 Extent of dimension 0.
    * @param d1 Extent of dimension 1.
    * @param d2 Extent of dimension 2.
    * @param d3 Extent of dimension 3.
    * @throws std::out_of_range when rank is not 4.
    */
   void setDims(unsigned long long d0, unsigned long long d1,
                unsigned long long d2, unsigned long long d3);

   /**
    * Set the rank of (number of dimensions in) the data.
    *
    * @param rank The rank of the data.
    */
   void setRank(unsigned long rank);

   /**
    * Set start position for a specified dimension.
    *
    * @param start Start position.
    * @param dim The dimension to set.
    * @throws std::out_of_range when start is invalid.
    */
   void setStart(unsigned long long start, unsigned long dim);

   /**
    * Set start position.
    *
    * @param start Start position array.
    * @param sz Length of start position array.
    * @throws std::out_of_range when start is invalid.
    */
   void setStart(unsigned long long* start, unsigned long sz);

   /**
    * Set start position.
    *
    * @param d0 Start position along dimension 0.
    * @throws std::out_of_range when rank is not 1 or when start position is
    * invalid.
    */
   void setStart(unsigned long long d0);

   /**
    * Set start position.
    *
    * @param d0 Start position along dimension 0.
    * @param d1 Start position along dimension 1.
    * @throws std::out_of_range when rank is not 2 or when start position is
    * invalid.
    */
   void setStart(unsigned long long d0, unsigned long long d1);

   /**
    * Set start position.
    *
    * @param d0 Start position along dimension 0.
    * @param d1 Start position along dimension 1.
    * @param d2 Start position along dimension 2.
    * @throws std::out_of_range when rank is not 3 or when start position is
    * invalid.
    */
   void setStart(unsigned long long d0, unsigned long long d1,
                 unsigned long long d2);

   /**
    * Set start position.
    *
    * @param d0 Start position along dimension 0.
    * @param d1 Start position along dimension 1.
    * @param d2 Start position along dimension 2.
    * @param d3 Start position along dimension 3.
    * @throws std::out_of_range when rank is not 4 or when start position is
    * invalid.
    */
   void setStart(unsigned long long d0, unsigned long long d1,
                 unsigned long long d2, unsigned long long d3);

   /**
    * Set data stride.
    *
    * @param stride Data stride array.
    * @param sz Length of data stride array.
    * @throws std::out_of_range when stride is invalid.
    */
   void setStride(unsigned long long* stride, unsigned long sz);

   /**
    * Set data stride. The stride along a dimension is initially set to 1.
    *
    * @param d0 Stride along dimension 0.
    * @throws std::out_of_range when rank is not 1 or when stride is invalid.
    */
   void setStride(unsigned long long d0);

   /**
    * Set data stride. The stride along a dimension is initially set to 1.
    *
    * @param d0 Stride along dimension 0.
    * @param d1 Stride along dimension 1.
    * @throws std::out_of_range when rank is not 2 or when stride is invalid.
    */
   void setStride(unsigned long long d0, unsigned long long d1);

   /**
    * Set data stride. The stride along a dimension is initially set to 1.
    *
    * @param d0 Stride along dimension 0.
    * @param d1 Stride along dimension 1.
    * @param d2 Stride along dimension 2.
    * @throws std::out_of_range when rank is not 3 or when stride is invalid.
    */
   void setStride(unsigned long long d0, unsigned long long d1,
                  unsigned long long d2);

   /**
    * Set data stride. The stride along a dimension is initially set to 1.
    *
    * @param d0 Stride along dimension 0.
    * @param d1 Stride along dimension 1.
    * @param d2 Stride along dimension 2.
    * @param d3 Stride along dimension 3.
    * @throws std::out_of_range when rank is not 4 or when stride is invalid.
    */
   void setStride(unsigned long long d0, unsigned long long d1,
                  unsigned long long d2, unsigned long long d3);

private:

   /**
    * Performs a basic check to determine if the selection is valid by checking
    * the count, start and stride against the dimension extents.
    *
    * @return true if selection is valid; false otherwise.
    */
   bool isValid();

   // Number of elements selected for each dimension
   std::vector<unsigned long long> m_count;

   // Extent of each dimension in the data
   std::vector<unsigned long long> m_dims;

   // Rank of the data, i.e. number of dimensions
   unsigned long m_rank;

   // Index of element to start at along each dimension
   std::vector<unsigned long long> m_start;

   // Data stride, i.e. number of elements to skip along each dimension
   std::vector<unsigned long long> m_stride;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
