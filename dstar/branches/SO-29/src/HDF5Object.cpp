/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <AbstractAttribute.h>
#include <HDF5Object.h>
#include <HDF5Attribute.h>
#include <HDF5DataScalar.h>

using namespace dstar;

using boost::dynamic_pointer_cast;
using boost::enable_shared_from_this;
using boost::shared_ptr;
using boost::weak_ptr;
using std::string;
using std::vector;

#include <iostream>

/*---------------------------------------------------------------------------*/

HDF5Object::HDF5Object()
: AbstractObject()
{

   m_hdf5Id = -1;

}

/*---------------------------------------------------------------------------*/

HDF5Object::~HDF5Object()
{

}

/*---------------------------------------------------------------------------*/

void HDF5Object::addAttribute(shared_ptr<AbstractAttribute> attr)
{

   m_attributes.push_back(attr);
   attr -> setParent(shared_from_this());

}

/*---------------------------------------------------------------------------*/

shared_ptr<const AbstractAttribute> HDF5Object::getAttribute(int i) const
{

   boost::shared_ptr<const AbstractAttribute> attr;
   try {
      attr = m_attributes.at(i);
   }
   catch (std::out_of_range& e) {
      attr.reset();
      throw std::out_of_range("Invalid index.");
   }

   return attr;

}

/*---------------------------------------------------------------------------*/

int
HDF5Object::getAttributeIndex(shared_ptr<const AbstractAttribute> attr) const
{

   int i;
   for (i = 0 ; i < (int) m_attributes.size() ; i++) {
      if (m_attributes.at(i) == attr) {
         return i;
      }
   }

   throw std::out_of_range("Not found.");
   return -1;

}

/*---------------------------------------------------------------------------*/

vector<shared_ptr<const AbstractAttribute> > HDF5Object::getAttributes() const
{

   return vector<shared_ptr<const AbstractAttribute> >(m_attributes.begin(),
      m_attributes.end());

}

/*---------------------------------------------------------------------------*/

hid_t HDF5Object::getHDF5Id()
{

   return m_hdf5Id;

}

/*---------------------------------------------------------------------------*/

string HDF5Object::getName() const
{

   return m_name;

}

/*---------------------------------------------------------------------------*/

int HDF5Object::getNumberOfAttributes() const
{

   return m_attributes.size();

}

/*---------------------------------------------------------------------------*/

shared_ptr<const AbstractObject> HDF5Object::getParent() const
{

   return m_parent.lock();

}

/*---------------------------------------------------------------------------*/

shared_ptr<const AbstractObject> HDF5Object::getRoot() const
{

   shared_ptr<const AbstractObject> parent = getParent();
   shared_ptr<const AbstractObject> current =
      dynamic_pointer_cast<const AbstractObject>(shared_from_this());

   while(parent.get() != NULL) {
      current = parent;
      parent = parent -> getParent();
   }

   return current;

}

/*---------------------------------------------------------------------------*/

void HDF5Object::removeAttribute(shared_ptr<AbstractAttribute> attr)
{

}

/*---------------------------------------------------------------------------*/

void HDF5Object::setHDF5Id(hid_t id)
{

   m_hdf5Id = id;

}

/*---------------------------------------------------------------------------*/

void HDF5Object::setName(string name)
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void HDF5Object::setParent(shared_ptr<AbstractObject> parent)
{

   m_parent = weak_ptr<AbstractObject>(parent);

}

/*---------------------------------------------------------------------------*/
