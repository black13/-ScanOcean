/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <HDF5Data.h>

using namespace dstar;
using boost::shared_array;
using boost::shared_ptr;
using boost::weak_ptr;
using std::list;
using std::pair;
using std::string;
using std::vector;

/*---------------------------------------------------------------------------*/

HDF5Data::HDF5Data()
: HDF5Object(), AbstractData()
{

   m_rank = 0;
   m_type = dstar::Char;
   m_dataSpaceId = -1;
   m_bytesPerElement = 0;

}

/*---------------------------------------------------------------------------*/

HDF5Data::~HDF5Data()
{

}

/*---------------------------------------------------------------------------*/

void HDF5Data::attachScale(unsigned long dim, shared_ptr<AbstractData> obj)
{

}

/*---------------------------------------------------------------------------*/

void HDF5Data::getDims(unsigned long long* dims, unsigned long sz) const
{

   for (unsigned int d = 0 ; (d < m_rank) && (d < sz) ; d++) {
      dims[d] = (unsigned long long) m_dataDims[d];
   }

}

/*---------------------------------------------------------------------------*/

unsigned long long HDF5Data::getNumberOfBytesInSelection() const
{

   return m_bytesPerElement * m_selection.getNumberOfElements();

}

/*---------------------------------------------------------------------------*/

unsigned long HDF5Data::getNumberOfBytesPerElement() const
{

   return m_bytesPerElement;

}

/*---------------------------------------------------------------------------*/

unsigned long HDF5Data::getRank() const
{

   return m_rank;

}

/*---------------------------------------------------------------------------*/

list<list<pair<string, shared_ptr<const AbstractData> > > >
HDF5Data::getScaleList() const
{

   const list<list<pair<string, shared_ptr<const AbstractData> > > > ret;
   return ret;

   //return list<list<pair<string, shared_ptr<const AbstractData> > > >(m_scales.begin(), m_scales.end());

   //return vector<shared_ptr<const AbstractAttribute> >(m_attributes.begin(),
//      m_attributes.end());

   // Fix this
   //return m_scales;

}

/*---------------------------------------------------------------------------*/

Selection HDF5Data::getSelection() const
{

   return m_selection;

}

/*---------------------------------------------------------------------------*/

DataType HDF5Data::getType() const
{

   return m_type;

}

/*---------------------------------------------------------------------------*/

void HDF5Data::removeScale(unsigned long dim, shared_ptr<AbstractData> obj)
{

   // Dimension is not valid
   if (dim >= m_scales.size()) {
      return;
   }

   // Get list for specified dimension
   list<list<pair<string, weak_ptr<AbstractData> > > >::iterator i;
   i = m_scales.begin();
   std::advance(i, dim);

   // Search through dimension for item and erase it
   list<pair<string, weak_ptr<AbstractData> > >::iterator j;
   for (j = i -> begin() ; j != i -> end() ; j++) {
      if ((j -> second).lock() == obj) {
         i -> erase(j);
         return;
      }
   }

}

/*---------------------------------------------------------------------------*/

void HDF5Data::setDims(unsigned long long* dims, unsigned long sz) const
{

   for (unsigned int d = 0 ; (d < m_rank) && (d < sz) ; d++) {
      m_dataDims[d] = (hsize_t) dims[d];
   }

}

/*---------------------------------------------------------------------------*/

void HDF5Data::setRank(unsigned long rank)
{

   m_rank = rank;
   m_selection.setRank(m_rank);

}

/*---------------------------------------------------------------------------*/

void HDF5Data::setSelection(Selection selection)
{

   // Validate rank
   if (selection.getRank() != m_rank) {
      throw std::out_of_range("Rank does not match. " + m_name);
      return;
   }

   // Update selection
   m_selection = selection;

}

/*---------------------------------------------------------------------------*/

void HDF5Data::setType(DataType type)
{

   m_type = type;

}

/*---------------------------------------------------------------------------*/
