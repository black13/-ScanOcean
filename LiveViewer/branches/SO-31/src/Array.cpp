/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <Array.h>

using boost::shared_array;

/*---------------------------------------------------------------------------*/

Array::Array(unsigned long long bytes)
: m_bytes(bytes)
{

   m_buffer = new char[m_bytes];
   m_rank = 0;
   m_type = UINT8;

}

/*---------------------------------------------------------------------------*/

Array::~Array()
{

   if (m_buffer != NULL) {
      delete [] m_buffer;
   }

}

/*---------------------------------------------------------------------------*/

char* Array::getBuffer() const
{

   return m_buffer;

}

/*---------------------------------------------------------------------------*/

void Array::getDims(unsigned long long* dims, unsigned long sz) const
{

   for (unsigned int d = 0 ; (d < m_rank) && (d < sz) ; d++) {
      dims[d] = (unsigned long long) m_dataDims[d];
   }

}

/*---------------------------------------------------------------------------*/

unsigned long Array::getRank() const
{

   return m_rank;

}

/*---------------------------------------------------------------------------*/

Array::DataType Array::getType() const
{

   return m_type;

}

/*---------------------------------------------------------------------------*/

void Array::setDimensions(unsigned long long* dims, unsigned long sz)
{

   for (unsigned long d = 0 ; (d < m_rank) && (d < sz) ; d++) {
      m_dataDims[d] = dims[d];
   }

}

/*---------------------------------------------------------------------------*/

void Array::setRank(unsigned long rank)
{

   m_rank = rank;
   m_dataDims = shared_array<unsigned long long>(
      new unsigned long long[m_rank]);

}

/*---------------------------------------------------------------------------*/

void Array::setType(Array::DataType type)
{

   m_type = type;

}

/*---------------------------------------------------------------------------*/
