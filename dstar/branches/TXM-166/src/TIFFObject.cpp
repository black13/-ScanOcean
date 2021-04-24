/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <AbstractAttribute.h>
#include <TIFFObject.h>


using namespace dstar;

using boost::dynamic_pointer_cast;
using boost::enable_shared_from_this;
using boost::shared_ptr;
using boost::weak_ptr;
using std::string;
using std::vector;

#include <iostream>

/*---------------------------------------------------------------------------*/

TIFFObject::TIFFObject()
: AbstractObject()
{



}

/*---------------------------------------------------------------------------*/

TIFFObject::~TIFFObject()
{

}

/*---------------------------------------------------------------------------*/

void TIFFObject::addAttribute(shared_ptr<AbstractAttribute> attr)
{

   m_attributes.push_back(attr);
   attr -> setParent(shared_from_this());

}

/*---------------------------------------------------------------------------*/

shared_ptr<const AbstractAttribute> TIFFObject::getAttribute(int i) const
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
TIFFObject::getAttributeIndex(shared_ptr<const AbstractAttribute> attr) const
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

vector<shared_ptr<const AbstractAttribute> > TIFFObject::getAttributes() const
{

   return vector<shared_ptr<const AbstractAttribute> >(m_attributes.begin(),
      m_attributes.end());

}

/*---------------------------------------------------------------------------*/

string TIFFObject::getName() const
{

   return m_name;

}

/*---------------------------------------------------------------------------*/

int TIFFObject::getNumberOfAttributes() const
{

   return m_attributes.size();

}

/*---------------------------------------------------------------------------*/

shared_ptr<const AbstractObject> TIFFObject::getParent() const
{

   return m_parent.lock();

}

/*---------------------------------------------------------------------------*/

shared_ptr<const AbstractObject> TIFFObject::getRoot() const
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

void TIFFObject::removeAttribute(shared_ptr<AbstractAttribute> attr)
{

}

/*---------------------------------------------------------------------------*/

void TIFFObject::setName(string name)
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void TIFFObject::setParent(shared_ptr<AbstractObject> parent)
{

   m_parent = weak_ptr<AbstractObject>(parent);

}

/*---------------------------------------------------------------------------*/
