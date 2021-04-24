/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <HDF5Attribute.h>
#include <HDF5DataScalar.h>

using namespace dstar;

using boost::dynamic_pointer_cast;
using boost::shared_array;
using boost::shared_ptr;
using std::string;
using std::vector;

/*---------------------------------------------------------------------------*/

HDF5DataScalar::HDF5DataScalar()
: HDF5Data()
{

}

/*---------------------------------------------------------------------------*/

HDF5DataScalar::~HDF5DataScalar()
{

}

/*---------------------------------------------------------------------------*/

shared_array<char> HDF5DataScalar::getData() const
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

//      // Get padding
//      H5T_str_t strpd = H5Tget_strpad(ndt);
//      if (strpd == H5T_STR_NULLTERM) {
//         std::cerr << "   H5T_STR_NULLTERM" << std::endl;
//      }
//      else if (strpd == H5T_STR_NULLPAD) {
//         std::cerr << "   H5T_STR_NULLPAD" << std::endl;
//      }
//      else if (strpd == H5T_STR_SPACEPAD) {
//         std::cerr << "   H5T_STR_SPACEPAD" << std::endl;
//      }

      // Set data type size
      hid_t dtype = H5Tcopy(ndt);
      H5Tset_size(dtype, m_selection.getNumberOfElements());

      // Read dataset
      H5Dread(m_hdf5Id, dtype, H5S_ALL, H5S_ALL, H5P_DEFAULT,
              (void*) buffer.get());

      // Clean up HDF5
      H5Tclose(dtype);

   }

   else {

      // Read dataset
      H5Dread(m_hdf5Id, ndt, H5S_ALL, H5S_ALL, H5P_DEFAULT,
              (void*) buffer.get());

   }

   // Clean up HDF5
   H5Tclose(ndt);
   H5Tclose(dt);

   // Return buffer as smart pointer
   return buffer;

}

/*---------------------------------------------------------------------------*/

vector<std::pair<string, string> > HDF5DataScalar::getProperties() const
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
   second = "H5S_SCALAR";
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

herr_t HDF5DataScalar::iteratorAttr(hid_t id, const char* name,
                                    const H5A_info_t* ainfo, void* op_data)
{

   // Cast caller to HDF5DataScalar
   HDF5DataScalar* data = static_cast<HDF5DataScalar*>(op_data);

   // Check if dataset exists
   if (H5Aexists(id, name)) {

      // Open HDF5 dataset
      hid_t cid = H5Aopen(id, name, H5P_DEFAULT);

      // Get data space
      hid_t ds = H5Aget_space(cid);

      // Get data class
      H5S_class_t hdf5Class = H5Sget_simple_extent_type(ds);

      // Close data space
      H5Sclose(ds);

      // Create appropriate data set object
      shared_ptr<AbstractAttribute> attr =
         shared_ptr<HDF5Attribute>(new HDF5Attribute());

      // Set child name
      attr -> setName(name);

      // Add child group to list of children
      data -> addAttribute(attr);

      // Cast child group appropriately
      shared_ptr<HDF5Attribute> tmp;
      tmp = boost::dynamic_pointer_cast<HDF5Attribute>(attr);

      // Load attribute
      tmp -> loadFromHDF5Id(cid);

   }

   // Continue iterating
   return 0;

}

/*---------------------------------------------------------------------------*/

void HDF5DataScalar::loadFromHDF5Id(hid_t id)
{

   // Save HDF5 object id
   m_hdf5Id = id;

   // Get file (data) space for the file
   m_dataSpaceId = H5Dget_space(m_hdf5Id);

   // Get number of dimensions in data space, i.e. rank
   m_rank = H5Sget_simple_extent_ndims(m_dataSpaceId);

   // Set rank to 1
   if (m_rank == 0) {
      m_rank = 1;
   }

   // Get data type and class
   hid_t type = H5Dget_type(m_hdf5Id);
   H5T_class_t tcls = H5Tget_class(type);

   // Get sizes
   hssize_t npts = H5Sget_simple_extent_npoints(m_dataSpaceId);
   hssize_t spts = H5Tget_size(type);

//   switch(tcls) {
//   case H5T_INTEGER:
//      std::cerr << "H5T_INTEGER" << std::endl;
//      break;
//   case H5T_FLOAT:
//      std::cerr << "H5T_FLOAT" << std::endl;
//      break;
//   case H5T_TIME:
//      std::cerr << "H5T_TIME" << std::endl;
//      break;
//   case H5T_STRING:
//      std::cerr << "H5T_STRING" << std::endl;
//      break;
//   case H5T_BITFIELD:
//      std::cerr << "H5T_BITFIELD" << std::endl;
//      break;
//   case H5T_OPAQUE:
//      std::cerr << "H5T_OPAQUE" << std::endl;
//      break;
//   case H5T_COMPOUND:
//      std::cerr << "H5T_COMPOUND" << std::endl;
//      break;
//   case H5T_REFERENCE:
//      std::cerr << "H5T_REFERENCE" << std::endl;
//      break;
//   case H5T_ENUM:
//      std::cerr << "H5T_ENUM" << std::endl;
//      break;
//   case H5T_VLEN:
//      std::cerr << "H5T_VLEN" << std::endl;
//      break;
//   case H5T_ARRAY:
//      std::cerr << "H5T_ARRAY" << std::endl;
//      break;
//   default:
//      break;
//   }

   // If it's a string
   if (tcls == H5T_STRING) {

      // Set type
      m_type = dstar::String;

      // Set number of bytes per element to 1 for a char
      m_bytesPerElement = 1;

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

   // Allocate array for dimension sizes
   m_dataDims = shared_array<hsize_t>(new hsize_t[m_rank]);
   for (unsigned long i = 0 ; i < m_rank ; i++) {
      if (m_type == dstar::String) {
         m_dataDims[i] = spts;
      }
      else {
         m_dataDims[i] = npts;
      }
   }

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


   // Setup initial selection
   m_selection.setRank(m_rank);
   m_selection.setDims(m_dataDims.get(), m_rank);
   m_selection.setStride(m_dataStride.get(), m_rank);
   m_selection.setCount(m_dataCount.get(), m_rank);
   m_selection.setStart(m_dataStart.get(), m_rank);

   // Iterate over attributes
   H5Aiterate(m_hdf5Id, H5_INDEX_NAME, H5_ITER_NATIVE,
              NULL, HDF5DataScalar::iteratorAttr, this);

}

/*---------------------------------------------------------------------------*/
