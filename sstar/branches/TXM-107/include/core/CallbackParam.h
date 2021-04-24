/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CALLBACK_PARAM_H
#define SSTAR_CALLBACK_PARAM_H

/*---------------------------------------------------------------------------*/

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition_variable.hpp>

/*---------------------------------------------------------------------------*/

class CAEventHandler;
class PVSharedResources;
class PVSpecificResources;

/**
 * Class used to pass information to put and get callbacks
 */
class CallbackParam
{

public:

   /**
    * Different enums identifying the type of message
    */
   enum MessageType
   {
      ASYN_PUT_WITH_HANDLER,
      SYN_PUT,
      ASYN_GET,
      SYN_GET
   };

public:

   /**
    * Constructor
    *
    * @param type Type Enum
    * @param threadID ID of the requesting thread
    * @param pSpecificResources Smart-Pointer to the specific resources
    * @param pSharedResources Smart-Pointer to the shared resources
    * @param pHandler Pointer to the user-defined handler
    */
   CallbackParam(
      MessageType type,
      const boost::thread::id& threadID,
      const boost::shared_ptr<PVSpecificResources>& pSpecificResources,
      const boost::shared_ptr<PVSharedResources>& pSharedResources,
      CAEventHandler* pHandler);

   /**
    * Get the param type
    *
    * @return Param type
    */
   MessageType getType();

   /**
    * Get the requesting thread ID
    *
    * @return Thread ID
    */
   const boost::thread::id& getThreadID();

   /**
    * Get thread specific resources
    *
    * @return Smart-pointer to the thread specific resources
    */
   const boost::shared_ptr<PVSpecificResources>& getSpecificResources();

   /**
    * Get shared resources
    *
    * @return Smart-pointer to the shared resources
    */
   const boost::shared_ptr<PVSharedResources>& getSharedResources();

   /**
    * Get user define handler
    *
    * @return User-defined handler
    */
   CAEventHandler* getHandler();

   /**
    * Create a message for an asynchronous put with handler
    *
    * @param threadID ID of the requesting thread
    * @param pSpecificResources Smart-Pointer to the specific resources
    * @param pSharedResources Smart-Pointer to the shared resources
    * @param pHandler Pointer to the user-defined handler
    */
   static const CallbackParam createAsynPutWithHandlerParam(
      boost::thread::id threadID,
      boost::shared_ptr<PVSpecificResources> pSpecificResources,
      boost::shared_ptr<PVSharedResources> pSharedResources,
      CAEventHandler* pHandler);

   /**
    * Create a message for an synchronous put
    *
    * @param threadID ID of the requesting thread
    * @param pSpecificResources Smart-Pointer to the specific resources
    * @param pSharedResources Smart-Pointer to the shared resources
    */
   static const CallbackParam createSynPutParam(
      boost::thread::id threadID,
      boost::shared_ptr<PVSpecificResources> pSpecificResources,
      boost::shared_ptr<PVSharedResources> pSharedResources);

   /**
    * Create a message for an asynchronous get
    *
    * @param threadID ID of the requesting thread
    * @param pSpecificResources Smart-Pointer to the specific resources
    * @param pSharedResources Smart-Pointer to the shared resources
    * @param pHandler Pointer to the user-defined handler
    */
   static const CallbackParam createAsynGetParam(
      boost::thread::id threadID,
      boost::shared_ptr<PVSpecificResources> pSpecificResources,
      boost::shared_ptr<PVSharedResources> pSharedResources,
      CAEventHandler* pHandler);

   /**
    * Create a message for an synchronous get
    *
    * @param threadID ID of the requesting thread
    * @param pSpecificResources Smart-Pointer to the specific resources
    * @param pSharedResources Smart-Pointer to the shared resources
    * @param pHandler Pointer to the user-defined handler
    */
   static const CallbackParam createSynGetParam(
      boost::thread::id threadID,
      boost::shared_ptr<PVSpecificResources> pSpecificResources,
      boost::shared_ptr<PVSharedResources> pSharedResources,
      CAEventHandler* pHandler);

private:

   /**
    * Message type
    */
   MessageType m_type;

   /**
    * Thread ID
    */
   boost::thread::id m_threadID;

   /**
    * Specific PV Resources
    */
   boost::shared_ptr<PVSpecificResources> m_pSpecificResources;

   /**
    * Shared PV Resources
    */
   boost::shared_ptr<PVSharedResources> m_pSharedResources;

   /**
    * Used defined handler
    */
   CAEventHandler* m_pHandler;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
