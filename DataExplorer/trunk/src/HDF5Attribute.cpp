/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <HDF5Attribute.h>

using namespace dstar;

using boost::shared_array;
using std::string;
using std::vector;

#include <iostream>

/*---------------------------------------------------------------------------*/

HDF5Attribute::HDF5Attribute()
: AbstractAttribute(), HDF5Object()
{

   m_rank = 0;
   m_type = dstar::Char;
   m_dataSpaceId = -1;
   m_bytesPerElement = 0;
   m_dims = NULL;

}

/*---------------------------------------------------------------------------*/

HDF5Attribute::~HDF5Attribute()
{

   if (m_dims != NULL) {
      free(m_dims);
      m_dims = NULL;
   }

}

/*---------------------------------------------------------------------------*/

shared_array<char> HDF5Attribute::getData() const
{

   // Allocate memory
   boost::shared_array<char> buffer;
   buffer = boost::shared_array<char>(new char[m_bytesPerElement * m_dims[0]]);

   // Create datatype
   hid_t dt = H5Aget_type(m_hdf5Id);

   // Get native datatype
   hid_t ndt = H5Tget_native_type(dt, H5T_DIR_ASCEND);

   hid_t dtype = H5Tcopy(ndt);
   H5Tset_size(dtype, m_dims[0]);

   H5Aread(m_hdf5Id, dtype, (void*) buffer.get());

   H5Tclose(ndt);
   H5Tclose(dt);
   H5Tclose(dtype);

   return buffer;

}

/*---------------------------------------------------------------------------*/

void HDF5Attribute::getDims(unsigned long* dims, unsigned int sz) const
{

   for (unsigned int d = 0 ; (d < m_rank) && (d < sz) ; d++) {
      dims[d] = m_dims[d];
   }

}

/*---------------------------------------------------------------------------*/

unsigned long HDF5Attribute::getNumberOfBytesPerElement() const
{

   return m_bytesPerElement;

}

/*---------------------------------------------------------------------------*/

vector<std::pair<string, string> > HDF5Attribute::getProperties() const
{

   vector<std::pair<string, string> > props;
   std::stringstream ss;
   string first;
   string second;
   std::pair<string, string> tmp;

   first = "Name";
   second = getName();
   tmp = make_pair(first, second);
   props.push_back(tmp);

   first = "Type";
   second = "Attribute";
   tmp = make_pair(first, second);
   props.push_back(tmp);

   first = "Data Type";
   second = dstar::getDataTypeAsString(m_type);
   tmp = make_pair(first, second);
   props.push_back(tmp);

   return props;

}

/*---------------------------------------------------------------------------*/

unsigned long HDF5Attribute::getRank() const
{

   return m_rank;

}

/*---------------------------------------------------------------------------*/

DataType HDF5Attribute::getType() const
{

   return m_type;

}

/*---------------------------------------------------------------------------*/

void HDF5Attribute::loadFromHDF5Id(hid_t id)
{

   // Save HDF5 object id
   m_hdf5Id = id;

   // Data space
   hid_t m_dataSpaceId = H5Aget_space(id);

   // Get space class
   H5S_class_t cls = H5Sget_simple_extent_type(m_dataSpaceId);

   // Scalar data
   if (cls == H5S_SCALAR) {

      // Set rank
      m_rank = 1;

      // Get type
      hid_t tid = H5Aget_type(m_hdf5Id);

      // Get type class
      H5T_class_t tcls = H5Tget_class(tid);

      if (tcls == H5T_INTEGER || tcls == H5T_FLOAT) {

         // Determine and set native type and size
         hid_t type = H5Tget_native_type(H5Aget_type(m_hdf5Id), H5T_DIR_ASCEND);
         if (H5Tequal(type, H5T_NATIVE_CHAR)) {
            m_type = dstar::Char;
         }
         else if (H5Tequal(type, H5T_NATIVE_SCHAR)) {
            m_type = dstar::ShortChar;
         }
         else if (H5Tequal(type, H5T_NATIVE_UCHAR)) {
            m_type = dstar::UnsignedChar;
         }
         else if (H5Tequal(type, H5T_NATIVE_SHORT)) {
            m_type = dstar::Short;
         }
         else if (H5Tequal(type, H5T_NATIVE_USHORT)) {
            m_type = dstar::UnsignedShort;
         }
         else if (H5Tequal(type, H5T_NATIVE_INT)) {
            m_type = dstar::Int;
         }
         else if (H5Tequal(type, H5T_NATIVE_UINT)) {
            m_type = dstar::UnsignedInt;
         }
         else if (H5Tequal(type, H5T_NATIVE_LONG)) {
            m_type = dstar::Long;
         }
         else if (H5Tequal(type, H5T_NATIVE_ULONG)) {
            m_type = dstar::UnsignedLong;
         }
         else if (H5Tequal(type, H5T_NATIVE_LLONG)) {
            m_type = dstar::LongLong;
         }
         else if (H5Tequal(type, H5T_NATIVE_ULLONG)) {
            m_type = dstar::UnsignedLongLong;
         }
         else if (H5Tequal(type, H5T_NATIVE_FLOAT)) {
            m_type = dstar::Float;
         }
         else if (H5Tequal(type, H5T_NATIVE_DOUBLE)) {
            m_type = dstar::Double;
         }
         else if (H5Tequal(type, H5T_NATIVE_LDOUBLE)) {
            m_type = dstar::LongDouble;
         }
         m_bytesPerElement = H5Tget_size(type);
         H5Tclose(type);

         // Allocate array for dimension sizes
         m_dims = (hsize_t*) malloc(sizeof(hsize_t) * 1);
         m_dims[0] = 1;

      }

      else if (tcls == H5T_STRING) {

         // Allocate array for dimension sizes
         m_dims = (hsize_t*) malloc(sizeof(hsize_t) * 1);
         m_dims[0] = (unsigned long) H5Tget_size(tid);
         m_type = dstar::String;
         m_bytesPerElement = 1;

      }

      // Close data type
      H5Tclose(tid);

   }

}

/*---------------------------------------------------------------------------*/

void HDF5Attribute::setDims(unsigned long* dims, unsigned int sz) const
{

   for (unsigned int d = 0 ; (d < m_rank) && (d < sz) ; d++) {
      m_dims[d] = dims[d];
   }

}

/*---------------------------------------------------------------------------*/

void HDF5Attribute::setRank(unsigned long rank)
{

   m_rank = rank;

}

/*---------------------------------------------------------------------------*/

void HDF5Attribute::setType(DataType type)
{

   m_type = type;

}

/*---------------------------------------------------------------------------*/
