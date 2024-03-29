/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef ARRAY_H
#define ARRAY_H

/*---------------------------------------------------------------------------*/

#include <boost/shared_array.hpp>
#include <stdlib.h>

/*---------------------------------------------------------------------------*/

class Array
{

public:

   /**
    * Type enumerations.
    */
   enum DataType {
      INVALID = 0,
      UINT8 = 1,
      UINT16 = 2,
      BGRA32 = 3,
      FLOAT64 = 4
   };

   /**
    * Constructor.
    *
    * @param bytes - number of bytes to allocate
    */
   Array(unsigned long long bytes = 1000000);

   /**
    * Destructor.
    */
   ~Array();

   /**
    * Get the raw memory buffer.
    *
    * @return memory buffer
    */
   char* getBuffer() const;

   /**
    * Get the maximum number of bytes allocated.
    *
    * @return number of bytes allocated
    */
   unsigned long long getBytes() const;

   /**
    * Get the extents of each dimension in the data object. Use getRank() to
    * determine the number of dimensions.
    *
    * @param dims Pointer to an array long enough to hold the extent of each
    *             dimension.
    * @param sz Length of (number of elements in) dims.
    */
   void getDims(unsigned long long* dims, unsigned long sz) const;

   /**
    * Get the rank of (number of dimensions in) the data.
    *
    * @return The rank of the data.
    */
   unsigned long getRank() const;

   /**
    * Get data type.
    *
    * @return data type
    */
   Array::DataType getType() const;

   /**
    * Set the extents of each dimension in the data object. Use setRank()
    * first to set the number of dimensions.
    *
    * @param dims Pointer to an array holding the extents of each dimension.
    * @param sz Length of (number of elements in) dims.
    */
   void setDimensions(unsigned long long* dims, unsigned long sz);

   /**
    * Set the rank of (number of dimensions in) the data. Calling this
    * method resets the extents in each dimension. Call setDimensions() after
    * calling this method.
    *
    * @param rank - The rank of the data.
    */
   void setRank(unsigned long rank);

   /**
    * Set data type.
    *
    * @param type - data type
    */
   void setType(Array::DataType type);

private:

   /**
    * Raw memory buffer
    */
   char* m_buffer;

   /**
    * Number of bytes allocated
    */
   unsigned long long m_bytes;

   /**
    * Dimension extents
    */
   boost::shared_array<unsigned long long> m_dataDims;

   /**
    * Array rank
    */
   unsigned long m_rank;

   /**
    * Data type
    */
   DataType m_type;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
