/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <HDF5DataSimple.h>

using namespace dstar;

using boost::shared_array;
using std::string;
using std::vector;

/*---------------------------------------------------------------------------*/

HDF5DataSimple::HDF5DataSimple()
: HDF5Data()
{

}

/*---------------------------------------------------------------------------*/

HDF5DataSimple::~HDF5DataSimple()
{

}

/*---------------------------------------------------------------------------*/

shared_array<char> HDF5DataSimple::getData() const
{

   // Allocate memory
   shared_array<char> buffer;
   buffer = shared_array<char>(new char[getNumberOfBytesInSelection()]);

   // Create datatype
   hid_t dt = H5Dget_type(m_hdf5Id);

   // Get native datatype
   hid_t ndt = H5Tget_native_type(dt, H5T_DIR_ASCEND);

   // If it's a string
   if (m_type == dstar::String) {

      // Set data type size
      hid_t dtype = H5Tcopy(ndt);
      H5Tset_size(dtype, m_selection.getNumberOfElements());

      // Read dataset
      H5Dread(m_hdf5Id, dtype, H5S_ALL, H5S_ALL, H5P_DEFAULT,
              (void*) buffer.get());

      // Clean up HDF5
      H5Tclose(dtype);

   }

   // If it's not a string
   else {

      // Get selection
      m_selection.getCount(m_dataCount.get(), m_rank);
      m_selection.getStart(m_dataStart.get(), m_rank);
      m_selection.getStride(m_dataStride.get(), m_rank);

      // Setup extents to read from file
      H5Sselect_hyperslab(m_dataSpaceId, H5S_SELECT_SET,
                          m_dataStart.get(), NULL,
                          m_dataCount.get(), NULL);

      // Create memory space to match data to be read from file
      hid_t memSpaceId = H5Screate_simple(m_rank, m_dataCount.get(), NULL);

      // Setup extents to place data in memory
      H5Sselect_hyperslab(memSpaceId, H5S_SELECT_SET,
                          m_memStartDims.get(), NULL,
                          m_dataCount.get(), NULL);

      // Perform the read
      H5Dread(m_hdf5Id, ndt, memSpaceId, m_dataSpaceId,
              H5P_DEFAULT, (void*) buffer.get());

      // Close mem space
      H5Sclose(memSpaceId);

   }

   // Clean up data space
   H5Tclose(ndt);
   H5Tclose(dt);

   // Return buffer as smart pointer
   return buffer;

}

/*---------------------------------------------------------------------------*/

vector<std::pair<string, string> > HDF5DataSimple::getProperties() const
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
   second = "Data";
   tmp = make_pair(first, second);
   props.push_back(tmp);

   first = "Data Type";
   second = dstar::getDataTypeAsString(m_type);
   tmp = make_pair(first, second);
   props.push_back(tmp);

   first = "Rank";
   ss << m_rank;
   second = ss.str();
   tmp = make_pair(first, second);
   props.push_back(tmp);

   first = "Dimensions";
   ss.str(std::string());
   ss.clear();
   for (unsigned long d = 0 ; d < m_rank ; d++) {
      ss << m_dataDims[d];
      if ((d + 1) < m_rank) ss << " x ";
   }
   second = ss.str();
   tmp = make_pair(first, second);
   props.push_back(tmp);

   first = "HDF5 Class";
   second = "H5S_SIMPLE";
   tmp = make_pair(first, second);
   props.push_back(tmp);

   first = "Attributes";
   ss.str(std::string());
   ss.clear();
   ss << getNumberOfAttributes();
   second = ss.str();
   tmp = make_pair(first, second);
   props.push_back(tmp);

   return props;

}

/*---------------------------------------------------------------------------*/

void HDF5DataSimple::loadFromHDF5Id(hid_t id)
{

   // Save HDF5 object id
   m_hdf5Id = id;

   // Get file (data) space for the file
   m_dataSpaceId = H5Dget_space(m_hdf5Id);

   // Get number of dimensions in data space, i.e. rank
   m_rank = H5Sget_simple_extent_ndims(m_dataSpaceId);

   // Allocate array for dimension sizes
   m_dataDims = shared_array<hsize_t>(new hsize_t[m_rank]);

   // Get sizes for each dimension in file
   H5Sget_simple_extent_dims(m_dataSpaceId, m_dataDims.get(), NULL);

   // Allocate array for file space start dimensions
   m_dataStart = shared_array<hsize_t>(new hsize_t[m_rank]);
   for (unsigned long i = 0 ; i < m_rank ; i++) {
      m_dataStart[i] = 0;
   }

   // Allocate array for memory space start dimensions
   // They should always be zero
   m_memStartDims = shared_array<hsize_t>(new hsize_t[m_rank]);
   for (unsigned long i = 0 ; i < m_rank ; i++) {
      m_memStartDims[i] = 0;
   }

   // Allocate array for file space selection
   m_dataCount = shared_array<hsize_t>(new hsize_t[m_rank]);
   for (unsigned long i = 0 ; i < m_rank ; i++) {
      m_dataCount[i] = m_dataDims[i];
   }

   // Allocate array for file space stride
   m_dataStride = shared_array<hsize_t>(new hsize_t[m_rank]);
   for (unsigned long i = 0 ; i < m_rank ; i++) {
      if (m_dataDims[i] >= 1) {
         m_dataStride[i] = 1;
      }
      else {
         m_dataStride[i] = 0;
      }
   }

   // Determine and set native type and size
   hid_t type = H5Tget_native_type(H5Dget_type(m_hdf5Id), H5T_DIR_ASCEND);
   H5T_class_t tcls = H5Tget_class(type);

   // If it's a string
   if (tcls == H5T_STRING) {

      // Set type
      m_type = dstar::String;

      // Set number of bytes per element to 1 for a char
      m_bytesPerElement = 1;

      // Set string size
      hssize_t spts = H5Tget_size(type);
      m_dataDims[0] = spts;
      m_dataCount[0] = m_dataDims[0];

   }

   // If it's not a string
   else {

      // Determine and set native type and size
      hid_t ntype = H5Tget_native_type(type, H5T_DIR_ASCEND);
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
      m_bytesPerElement = H5Tget_size(ntype);
      H5Tclose(ntype);

   }

   // Clean up HDF5
   H5Tclose(type);

   // Setup initial selection
   m_selection.setRank(m_rank);
   m_selection.setDims(m_dataDims.get(), m_rank);
   m_selection.setStride(m_dataStride.get(), m_rank);
   m_selection.setCount(m_dataCount.get(), m_rank);
   m_selection.setStart(m_dataStart.get(), m_rank);

   // Iterate over attributes
   //H5Aiterate(m_hdf5Id, H5_INDEX_NAME, H5_ITER_NATIVE,
   //           NULL, HDF5DataSimple::iteratorAttr, this);

}

/*---------------------------------------------------------------------------*/
