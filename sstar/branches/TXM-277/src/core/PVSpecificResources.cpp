/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <core/PVSpecificResources.h>

using boost::condition_variable;

/*---------------------------------------------------------------------------*/

PVSpecificResources::PVSpecificResources()
: m_bSuccessfulPut(false),
  m_bSuccessfulGet(false),
  m_totalPendingRequests(0),
  m_referenceCount(0)
{

}

/*---------------------------------------------------------------------------*/

condition_variable& PVSpecificResources::getGetCV()
{

   return m_synGetCV;

}

/*---------------------------------------------------------------------------*/

condition_variable& PVSpecificResources::getPutCV()
{

   return m_synPutCV;

}

/*---------------------------------------------------------------------------*/

condition_variable& PVSpecificResources::getPendingRequestsCV()
{

   return m_pendingRequestsCompletionCV;

}

/*---------------------------------------------------------------------------*/

bool PVSpecificResources::getLastPutOutcome()
{

   return m_bSuccessfulPut;

}

/*---------------------------------------------------------------------------*/

bool PVSpecificResources::getLastGetOutcome()
{

   return m_bSuccessfulGet;

}

/*---------------------------------------------------------------------------*/

int PVSpecificResources::getPendingRequests()
{

   return m_totalPendingRequests;

}

/*---------------------------------------------------------------------------*/

bool PVSpecificResources::arePendingRequests()
{

   return m_totalPendingRequests > 0;

}

/*---------------------------------------------------------------------------*/

void PVSpecificResources::incrementPendingRequests()
{

   m_totalPendingRequests++;

}

/*---------------------------------------------------------------------------*/

void PVSpecificResources::decrementPendingRequests()
{

   if(m_totalPendingRequests > 0)
      m_totalPendingRequests--;

}

/*---------------------------------------------------------------------------*/

void PVSpecificResources::setLastPutOutcome(bool value)
{

   m_bSuccessfulPut = value;

}

/*---------------------------------------------------------------------------*/

void PVSpecificResources::setLastGetOutcome(bool value)
{

   m_bSuccessfulGet = value;

}

/*---------------------------------------------------------------------------*/

int PVSpecificResources::interfacesCount()
{

   return m_referenceCount;

}

/*---------------------------------------------------------------------------*/

void PVSpecificResources::incrementInterfacesCount()
{

   m_referenceCount++;

}

/*---------------------------------------------------------------------------*/

void PVSpecificResources::decrementInterfacesCount()
{

   if(m_referenceCount > 0)
      m_referenceCount--;

}

/*---------------------------------------------------------------------------*/
