/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <Selection.h>

using namespace dstar;
using std::cerr;
using std::vector;

/*---------------------------------------------------------------------------*/

Selection::Selection()
{

}

/*---------------------------------------------------------------------------*/

Selection::Selection(unsigned long rank)
{

   setRank(rank);

}

/*---------------------------------------------------------------------------*/

Selection::~Selection()
{

}

/*---------------------------------------------------------------------------*/

void Selection::getCount(unsigned long long* count, unsigned long sz) const
{

   for (unsigned long d = 0 ; (d < m_count.size()) && (d < sz) ; d++) {
      count[d] = m_count[d];
   }

}

/*---------------------------------------------------------------------------*/

void Selection::getCount(unsigned long long* d0) const
{

   if (m_count.size() != 1) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_count[0];

}

/*---------------------------------------------------------------------------*/

void Selection::getCount(unsigned long long* d0, unsigned long long* d1) const
{

   if (m_count.size() != 2) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_count[0];
   *d1 = m_count[1];

}

/*---------------------------------------------------------------------------*/

void Selection::getCount(unsigned long long* d0, unsigned long long* d1,
                         unsigned long long* d2) const
{

   if (m_count.size() != 3) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_count[0];
   *d1 = m_count[1];
   *d2 = m_count[2];

}

/*---------------------------------------------------------------------------*/

void Selection::getCount(unsigned long long* d0, unsigned long long* d1,
                         unsigned long long* d2, unsigned long long* d3) const
{

   if (m_count.size() != 4) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_count[0];
   *d1 = m_count[1];
   *d2 = m_count[2];
   *d3 = m_count[3];

}

/*---------------------------------------------------------------------------*/

void Selection::getDims(unsigned long long* dims, unsigned long sz) const
{

   for (unsigned long d = 0 ; (d < m_dims.size()) && (d < sz) ; d++) {
      dims[d] = m_dims[d];
   }

}

/*---------------------------------------------------------------------------*/

void Selection::getDims(unsigned long long* d0) const
{

   if (m_dims.size() != 1) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_dims[0];

}

/*---------------------------------------------------------------------------*/

void Selection::getDims(unsigned long long* d0, unsigned long long* d1) const
{

   if (m_dims.size() != 2) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_dims[0];
   *d1 = m_dims[1];

}

/*---------------------------------------------------------------------------*/

void Selection::getDims(unsigned long long* d0, unsigned long long* d1,
                        unsigned long long* d2) const
{

   if (m_dims.size() != 3) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_dims[0];
   *d1 = m_dims[1];
   *d2 = m_dims[2];

}

/*---------------------------------------------------------------------------*/

void Selection::getDims(unsigned long long* d0, unsigned long long* d1,
                        unsigned long long* d2, unsigned long long* d3) const
{

   if (m_dims.size() != 4) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_dims[0];
   *d1 = m_dims[1];
   *d2 = m_dims[2];
   *d3 = m_dims[3];

}

/*---------------------------------------------------------------------------*/

unsigned long long Selection::getNumberOfElements() const
{

   if (m_rank <= 0) {
      return 0;
   }

   unsigned long long num = 1;
   for (unsigned long d = 0 ; d < m_rank ; d++) {
      num *= m_count[d];
   }

   return num;

}

/*---------------------------------------------------------------------------*/

unsigned long Selection::getRank() const
{

   return m_rank;

}

/*---------------------------------------------------------------------------*/

void Selection::getStart(unsigned long long* start, unsigned long sz) const
{

   for (unsigned long d = 0 ; (d < m_start.size()) && (d < sz) ; d++) {
      start[d] = m_start[d];
   }

}

/*---------------------------------------------------------------------------*/

void Selection::getStart(unsigned long long* d0) const
{

   if (m_start.size() != 1) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_start[0];

}

/*---------------------------------------------------------------------------*/

void Selection::getStart(unsigned long long* d0, unsigned long long* d1) const
{

   if (m_start.size() != 2) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_start[0];
   *d1 = m_start[1];

}

/*---------------------------------------------------------------------------*/

void Selection::getStart(unsigned long long* d0, unsigned long long* d1,
                         unsigned long long* d2) const
{

   if (m_start.size() != 3) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_start[0];
   *d1 = m_start[1];
   *d2 = m_start[2];

}

/*---------------------------------------------------------------------------*/

void Selection::getStart(unsigned long long* d0, unsigned long long* d1,
                         unsigned long long* d2, unsigned long long* d3) const
{

   if (m_start.size() != 4) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_start[0];
   *d1 = m_start[1];
   *d2 = m_start[2];
   *d3 = m_start[3];

}

/*---------------------------------------------------------------------------*/

void Selection::getStride(unsigned long long* stride, unsigned long sz) const
{

   for (unsigned long d = 0 ; (d < m_stride.size()) && (d < sz) ; d++) {
      stride[d] = m_stride[d];
   }

}

/*---------------------------------------------------------------------------*/

void Selection::getStride(unsigned long long* d0) const
{

   if (m_stride.size() != 1) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_stride[0];

}

/*---------------------------------------------------------------------------*/

void Selection::getStride(unsigned long long* d0, unsigned long long* d1) const
{

   if (m_stride.size() != 2) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_stride[0];
   *d1 = m_stride[1];

}

/*---------------------------------------------------------------------------*/

void Selection::getStride(unsigned long long* d0, unsigned long long* d1,
                          unsigned long long* d2) const
{

   if (m_stride.size() != 3) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_stride[0];
   *d1 = m_stride[1];
   *d2 = m_stride[2];

}

/*---------------------------------------------------------------------------*/

void Selection::getStride(unsigned long long* d0, unsigned long long* d1,
                          unsigned long long* d2, unsigned long long* d3) const
{

   if (m_stride.size() != 4) {
      throw std::out_of_range("Selection - Incorrect getter for rank.");
      return;
   }

   *d0 = m_stride[0];
   *d1 = m_stride[1];
   *d2 = m_stride[2];
   *d3 = m_stride[3];

}

/*---------------------------------------------------------------------------*/

bool Selection::isValid()
{

   for (unsigned long d = 0 ; d < m_count.size() ; d++) {
      if (m_count[d] > m_dims[d]) {
         return false;
      }
   }

   for (unsigned long d = 0 ; d < m_start.size() ; d++) {
      if (m_start[d] > (m_dims[d] - 1)) {
         return false;
      }
   }

   for (unsigned long d = 0 ; d < m_stride.size() ; d++) {
      if (m_stride[d] > m_dims[d]) {
         return false;
      }
   }

   return true;

}

/*---------------------------------------------------------------------------*/

void Selection::printSelf()
{

   cerr << "Printing Selection" << std::endl;
   cerr << "  Rank: " << m_rank << std::endl;
   cerr << "  Dims\tStart\tCount\tStride" << std::endl;

   for (unsigned int i = 0 ; i < m_dims.size() ; i++) {
      cerr << "  "
           << m_dims[i] << "\t"
           << m_start[i] << "\t"
           << m_count[i] << "\t"
           << m_stride[i] << std::endl;
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setCount(unsigned long long count, unsigned long dim)
{

   m_count[dim] = count;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid selection count.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setCount(unsigned long long* count, unsigned long sz)
{

   for (unsigned long d = 0 ; (d < m_count.size()) && (d < sz) ; d++) {
      m_count[d] = count[d];
   }

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid selection count.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setCount(unsigned long long d0)
{

   if (m_count.size() != 1) {
      throw std::out_of_range("Selection - Incorrect setter for rank.");
      return;
   }

   m_count[0] = d0;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid selection count.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setCount(unsigned long long d0, unsigned long long d1)
{

   if (m_count.size() != 2) {
      throw std::out_of_range("Selection - Incorrect setter for rank.");
      return;
   }

   m_count[0] = d0;
   m_count[1] = d1;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid selection count.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setCount(unsigned long long d0, unsigned long long d1,
                         unsigned long long d2)
{

   if (m_count.size() != 3) {
      throw std::out_of_range("Selection - Incorrect setter for rank.");
      return;
   }

   m_count[0] = d0;
   m_count[1] = d1;
   m_count[2] = d2;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid selection count.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setCount(unsigned long long d0, unsigned long long d1,
                         unsigned long long d2, unsigned long long d3)
{

   if (m_count.size() != 4) {
      throw std::out_of_range("Selection - Incorrect setter for rank.");
      return;
   }

   m_count[0] = d0;
   m_count[1] = d1;
   m_count[2] = d2;
   m_count[3] = d3;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid selection count.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setDims(unsigned long long* dims, unsigned long sz)
{

   for (unsigned long d = 0 ; (d < m_dims.size()) && (d < sz) ; d++) {
      m_dims[d] = dims[d];
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setDims(unsigned long long d0)
{

   if (m_dims.size() != 1) {
      throw std::out_of_range("Selection - Incorrect setter for rank.");
      return;
   }

   m_dims[0] = d0;

}

/*---------------------------------------------------------------------------*/

void Selection::setDims(unsigned long long d0, unsigned long long d1)
{

   if (m_dims.size() != 2) {
      throw std::out_of_range("Selection - Incorrect setter for rank.");
      return;
   }

   m_dims[0] = d0;
   m_dims[1] = d1;

}

/*---------------------------------------------------------------------------*/

void Selection::setDims(unsigned long long d0, unsigned long long d1,
                        unsigned long long d2)
{

   if (m_dims.size() != 3) {
      throw std::out_of_range("Selection - Incorrect setter for rank.");
      return;
   }

   m_dims[0] = d0;
   m_dims[1] = d1;
   m_dims[2] = d2;

}

/*---------------------------------------------------------------------------*/

void Selection::setDims(unsigned long long d0, unsigned long long d1,
                        unsigned long long d2, unsigned long long d3)
{

   if (m_dims.size() != 4) {
      throw std::out_of_range("Selection - Incorrect setter for rank.");
      return;
   }

   m_dims[0] = d0;
   m_dims[1] = d1;
   m_dims[2] = d2;
   m_dims[3] = d3;

}

/*---------------------------------------------------------------------------*/

void Selection::setRank(unsigned long rank)
{

   m_rank = rank;

   m_count.resize(m_rank, 0);
   m_dims.resize(m_rank, 0);
   m_start.resize(m_rank, 0);
   m_stride.resize(m_rank, 1);

}

/*---------------------------------------------------------------------------*/

void Selection::setStart(unsigned long long start, unsigned long dim)
{

   m_start[dim] = start;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid start.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setStart(unsigned long long* start, unsigned long sz)
{

   for (unsigned long d = 0 ; (d < m_start.size()) && (d < sz) ; d++) {
      m_start[d] = start[d];
   }

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid start.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setStart(unsigned long long d0)
{

   if (m_start.size() != 1) {
      throw std::out_of_range("Incorrect setter for rank.");
      return;
   }

   m_start[0] = d0;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid start.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setStart(unsigned long long d0, unsigned long long d1)
{

   if (m_start.size() != 2) {
      throw std::out_of_range("Incorrect setter for rank.");
      return;
   }

   m_start[0] = d0;
   m_start[1] = d1;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid start.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setStart(unsigned long long d0, unsigned long long d1,
                         unsigned long long d2)
{

   if (m_start.size() != 3) {
      throw std::out_of_range("Incorrect setter for rank.");
      return;
   }

   m_start[0] = d0;
   m_start[1] = d1;
   m_start[2] = d2;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid start.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setStart(unsigned long long d0, unsigned long long d1,
                         unsigned long long d2, unsigned long long d3)
{

   if (m_start.size() != 4) {
      throw std::out_of_range("Incorrect setter for rank.");
      return;
   }

   m_start[0] = d0;
   m_start[1] = d1;
   m_start[2] = d2;
   m_start[3] = d3;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid start.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setStride(unsigned long long* stride, unsigned long sz)
{

   for (unsigned long d = 0 ; (d < m_stride.size()) && (d < sz) ; d++) {
      m_stride[d] = stride[d];
   }

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid stride.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setStride(unsigned long long d0)
{

   if (m_stride.size() != 1) {
      throw std::out_of_range("Incorrect setter for rank.");
      return;
   }

   m_stride[0] = d0;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid stride.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setStride(unsigned long long d0, unsigned long long d1)
{

   if (m_stride.size() != 2) {
      throw std::out_of_range("Selection - Incorrect setter for rank.");
      return;
   }

   m_stride[0] = d0;
   m_stride[1] = d1;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid stride.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setStride(unsigned long long d0, unsigned long long d1,
                          unsigned long long d2)
{

   if (m_stride.size() != 3) {
      throw std::out_of_range("Selection - Incorrect setter for rank.");
      return;
   }

   m_stride[0] = d0;
   m_stride[1] = d1;
   m_stride[2] = d2;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid stride.");
   }

}

/*---------------------------------------------------------------------------*/

void Selection::setStride(unsigned long long d0, unsigned long long d1,
                          unsigned long long d2, unsigned long long d3)
{

   if (m_stride.size() != 4) {
      throw std::out_of_range("Selection - Incorrect setter for rank.");
      return;
   }

   m_stride[0] = d0;
   m_stride[1] = d1;
   m_stride[2] = d2;
   m_stride[3] = d3;

   if (isValid() == false) {
      throw std::out_of_range("Selection - Invalid stride.");
   }

}

/*---------------------------------------------------------------------------*/
