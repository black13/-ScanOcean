/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <AbstractAttribute.h>
#include <AbstractObject.h>
#include <HDF5Attribute.h>
#include <HDF5Group.h>
#include <HDF5DataScalar.h>
#include <HDF5DataSimple.h>

using namespace dstar;

using boost::enable_shared_from_this;
using boost::dynamic_pointer_cast;
using boost::shared_ptr;
using boost::weak_ptr;
using std::string;
using std::vector;

/*---------------------------------------------------------------------------*/

HDF5Group::HDF5Group()
: AbstractGroup(), HDF5Object()
{

}

/*---------------------------------------------------------------------------*/

HDF5Group::~HDF5Group()
{

}

/*---------------------------------------------------------------------------*/

void HDF5Group::addChild(shared_ptr<AbstractObject> child)
{

   m_children.push_back(child);
   child -> setParent(shared_from_this());

}

/*---------------------------------------------------------------------------*/

shared_ptr<const AbstractObject> HDF5Group::getChild(int i) const
{

   boost::shared_ptr<const AbstractObject> attr;
   try {
      attr = m_children.at(i);
   }
   catch (std::out_of_range& e) {
      attr.reset();
      throw std::out_of_range("Invalid index.");
   }

   return attr;

}

/*---------------------------------------------------------------------------*/

int HDF5Group::getChildIndex(shared_ptr<const AbstractObject> obj) const
{

   int i;
   for (i = 0 ; i < (int) m_children.size() ; i++) {
      if (m_children.at(i) == obj) {
         return i;
      }
   }

   throw std::out_of_range("Not found.");
   return -1;

}

/*---------------------------------------------------------------------------*/

vector<shared_ptr<const AbstractObject> > HDF5Group::getChildren() const
{

   return vector<shared_ptr<const AbstractObject> >(m_children.begin() ,
      m_children.end());

}

/*---------------------------------------------------------------------------*/

int HDF5Group::getNumberOfChildren() const
{

   return m_children.size();

}

/*---------------------------------------------------------------------------*/

vector<std::pair<string, string> > HDF5Group::getProperties() const
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
   second = "Group";
   tmp = make_pair(first, second);
   props.push_back(tmp);

   first = "Children";
   ss.str(std::string());
   ss.clear();
   ss << getNumberOfChildren();
   second = ss.str();
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

/*--------------------------------------------------------------------------*/

herr_t HDF5Group::iterator(hid_t id, const char* name,
                           const H5L_info_t* info, void* op_data)
{

   // Cast caller to HDF5Group
   HDF5Group* group = static_cast<HDF5Group*>(op_data);

   // Get information about subgroups, i.e. their type
   H5O_info_t i;
   H5Oget_info_by_name(id, name, &i, H5P_DEFAULT);
   H5O_type_t type = i.type;

   // Handle HDF5 objects appropriately
   switch(type) {

   // Handle a group
   case H5O_TYPE_GROUP:
   {

      // Open HDF5 group if it exists
      if (H5Lexists(id, name, H5P_DEFAULT)) {

         // Open HDF5 group
         hid_t cid = H5Gopen(id, name, H5P_DEFAULT);

         // Create a new child group
         shared_ptr<AbstractObject> child =
            shared_ptr<HDF5Group>(new HDF5Group());

         // Set child name
         child -> setName(name);

         // Add child group to list of children
         group -> addChild(child);

         // Cast child group appropriately
         shared_ptr<HDF5Object> tmp;
         tmp = dynamic_pointer_cast<HDF5Object>(child);

         // Load child recursively
         tmp -> loadFromHDF5Id(cid);

      }

   }
   break;

   // Handle a dataset
   case H5O_TYPE_DATASET:
   {

      // Check if dataset exists
      if (H5Lexists(id, name, H5P_DEFAULT)) {

         // Open HDF5 dataset
         hid_t cid = H5Dopen(id, name, H5P_DEFAULT);

         // Get data space
         hid_t ds = H5Dget_space(cid);

         // Get data class
         H5S_class_t hdf5Class = H5Sget_simple_extent_type(ds);

         // Close data space
         H5Sclose(ds);

         // Create appropriate data set object
         shared_ptr<AbstractObject> child;
         if (hdf5Class == H5S_SCALAR) {
            child = shared_ptr<HDF5DataScalar>(new HDF5DataScalar());
         }
         else if (hdf5Class == H5S_SIMPLE) {
            child = shared_ptr<HDF5DataSimple>(new HDF5DataSimple());
         }

         // Set child name
         child -> setName(name);

         // Add child group to list of children
         group -> addChild(child);

         // Cast child group appropriately
         shared_ptr<HDF5Object> tmp;
         tmp = boost::dynamic_pointer_cast<HDF5Object>(child);

         // Load child
         tmp -> loadFromHDF5Id(cid);

      }

   }
   break;

   default:
      break;
   }

   // Continue iterating
   return 0;

}

/*---------------------------------------------------------------------------*/

herr_t HDF5Group::iteratorAttr(hid_t id, const char* name,
                               const H5A_info_t* ainfo, void* op_data)
{

   // Cast caller to HDF5Group
   HDF5Group* group = static_cast<HDF5Group*>(op_data);

   // Check if dataset exists
   if (H5Aexists(id, name)) {

      // Open HDF5 dataset
      hid_t cid = H5Aopen(id, name, H5P_DEFAULT);

      // Get data space
      hid_t ds = H5Aget_space(cid);

      // Get data class
      //H5S_class_t hdf5Class = H5Sget_simple_extent_type(ds);

      // Close data space
      H5Sclose(ds);

      // Create appropriate data set object
      shared_ptr<AbstractAttribute> attr =
         shared_ptr<HDF5Attribute>(new HDF5Attribute());

      // Set child name
      attr -> setName(name);

      // Add child group to list of children
      group -> addAttribute(attr);

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

void HDF5Group::loadFromHDF5Id(hid_t id)
{

   // Save HDF5 object id
   m_hdf5Id = id;

   // Iterate over name in group
   H5Literate(m_hdf5Id, H5_INDEX_NAME, H5_ITER_NATIVE,
              NULL, HDF5Group::iterator, this);

   // Iterate over name in group
   H5Aiterate(m_hdf5Id, H5_INDEX_NAME, H5_ITER_NATIVE,
              NULL, HDF5Group::iteratorAttr, this);

}

/*---------------------------------------------------------------------------*/

void HDF5Group::removeChild(boost::shared_ptr<AbstractObject> child)
{

}

/*---------------------------------------------------------------------------*/
