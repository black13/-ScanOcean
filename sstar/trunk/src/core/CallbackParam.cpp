/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <core/CallbackParam.h>
#include <core/PVSpecificResources.h>
#include <handlers/base/CAEventHandler.h>

using std::thread;
using std::shared_ptr;

/*---------------------------------------------------------------------------*/

CallbackParam::CallbackParam(
   MessageType type,
   const thread::id& requestingThread,
   const shared_ptr<PVSpecificResources>& pSpecificResources,
   const shared_ptr<PVSharedResources>& pSharedResources,
   CAEventHandler* pHandler)
: m_type(type),
  m_threadID(requestingThread),
  m_pSpecificResources(pSpecificResources),
  m_pSharedResources(pSharedResources),
  m_pHandler(pHandler)
{

}

/*---------------------------------------------------------------------------*/

CallbackParam::MessageType CallbackParam::getType()
{

   return m_type;

}

/*---------------------------------------------------------------------------*/

const thread::id& CallbackParam::getThreadID()
{

   return m_threadID;

}

/*---------------------------------------------------------------------------*/

const shared_ptr<PVSpecificResources>& CallbackParam::getSpecificResources()
{

   return m_pSpecificResources;

}

/*---------------------------------------------------------------------------*/

const shared_ptr<PVSharedResources>& CallbackParam::getSharedResources()
{

   return m_pSharedResources;

}

/*---------------------------------------------------------------------------*/

CAEventHandler* CallbackParam::getHandler()
{

   return m_pHandler;

}

/*---------------------------------------------------------------------------*/

const CallbackParam CallbackParam::createAsynPutWithHandlerParam(
   thread::id requestingThread,
   shared_ptr<PVSpecificResources> pSpecificResources,
   shared_ptr<PVSharedResources> pSharedResources,
   CAEventHandler* pHandler)
{

   return CallbackParam(CallbackParam::ASYN_PUT_WITH_HANDLER,
                        requestingThread,
                        pSpecificResources,
                        pSharedResources,
                        pHandler);

}

/*---------------------------------------------------------------------------*/

const CallbackParam CallbackParam::createSynPutParam(
   thread::id requestingThread,
   shared_ptr<PVSpecificResources> pSpecificResources,
   shared_ptr<PVSharedResources> pSharedResources)
{

   return CallbackParam(CallbackParam::SYN_PUT,
                        requestingThread,
                        pSpecificResources,
                        pSharedResources,
                        NULL);

}

/*---------------------------------------------------------------------------*/

const CallbackParam CallbackParam::createAsynGetParam(
   thread::id requestingThread,
   shared_ptr<PVSpecificResources> pSpecificResources,
   shared_ptr<PVSharedResources> pSharedResources,
   CAEventHandler* pHandler)
{

   return CallbackParam(CallbackParam::ASYN_GET,
                        requestingThread,
                        pSpecificResources,
                        pSharedResources,
                        pHandler);

}

/*---------------------------------------------------------------------------*/

const CallbackParam CallbackParam::createSynGetParam(
   thread::id requestingThread,
   shared_ptr<PVSpecificResources> pSpecificResources,
   shared_ptr<PVSharedResources> pSharedResources,
   CAEventHandler* pHandler)
{

   return CallbackParam(CallbackParam::SYN_GET,
                        requestingThread,
                        pSpecificResources,
                        pSharedResources,
                        pHandler);

}

/*---------------------------------------------------------------------------*/
