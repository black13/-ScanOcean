/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <core/PVResources.h>

#include <core/PVSharedResources.h>
#include <core/PVSpecificResources.h>


using std::shared_ptr;

/*---------------------------------------------------------------------------*/

PVResources::PVResources(const shared_ptr<PVSharedResources>& pSharedResources)
: m_pSharedResources(pSharedResources),
  m_pSpecificResources(new PVSpecificResources)
{

}

/*---------------------------------------------------------------------------*/

PVResources::~PVResources()
{

}

/*---------------------------------------------------------------------------*/

const shared_ptr<PVSharedResources>& PVResources::getSharedResources()
{
   return m_pSharedResources;
}

/*---------------------------------------------------------------------------*/

const shared_ptr<PVSpecificResources>& PVResources::getSpecificResources()
{
   return m_pSpecificResources;
}

/*---------------------------------------------------------------------------*/
