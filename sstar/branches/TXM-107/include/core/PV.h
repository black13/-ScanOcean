/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_PV_H
#define SSTAR_PV_H

/*---------------------------------------------------------------------------*/

#include <boost/shared_ptr.hpp>
#include <boost/thread/condition_variable.hpp>

#include <core/PVSharedResources.h>

/*---------------------------------------------------------------------------*/

class PVResources;
class PVSharedResources;
class PVSpecificResources;
class CAEventHandler;
class CAConnectionHandler;

/**
 * PV is used to easily perform put and get operations
 *
 * Uses:
 * - Asynchronous (2 forms) and Synchronous PUT
 * - Asynchronous and Synchronous GET
 * - Subscribe to connection events
 * - Subscribe to alarm events
 * - Subscribe to data changes
 * - Obtain PV connection state
 *
 * Features:
 * - ThreadSafe
 */
class PV
{

public:

   /**
    * Constructor
    *
    * @param pResources Resources used by this PV
    */
   PV(const boost::shared_ptr<PVResources>& pResources);

   /**
    * Destructor
    */
   ~PV();

   /**
    * Get PV name
    *
    * @return PV Name
    */
   const std::string& getName();

   /**
    * Get count
    *
    * @return count
    */
   unsigned getCount();

   /**
    * Get PV type
    *
    * @return PV type
    */
   chtype getType();

   /**
    * Get PV current connection state
    *
    * @return Connection State
    */
   PVSharedResources::ConnectionState getConnectionState();

   /**
    * Connection function
    *
    * @param attempts If 'attempts' is > 0 an 'attempts' number of attemps
    *                 is performed, each of duration 'timeoutSeconds' before
    *                 throwing an Exception.
    *                 If 'attempts' is 0, no exception is thrown. If the
    *                 connection cannot be established, the function does
    *                 nothing, just bind the channel
    *
    * @param timeoutSeconds Number of seconds before a time
    */
   void connect(int attempts = 0,
                long timeoutSeconds = 5);
   /**
    * Asynchronous Put returns immediately after a request has been
    * sent. If a handler is provided, it will be called asynchronously
    * at the end of the operation.
    *
    * When the channel is disconnected, the asynchronous put fails
    * and no handler is registered for execution.
    *
    * When an asynchronous put is successfully registered, the handler
    * will always be called. If the channel becomes disconnected, the
    * onFailure function of the handler is called
    *
    * "AsynPut with no handler" override other AsynPut with no handler,
    * but block if put operation with "callback" have still to be
    * processed.
    *
    * "AsynPut with handler" wait for the other put operations with
    * callback to be finished before calling theirs. Moreover they can
    * override other AsynPut with no handler
    *
    * Examples
    *
    *   asynPut(val,1)
    *
    *   asynPut(val,1)    - OVERRIDE
    *
    *   asynPut(val,1)    - OVERRIDE
    *
    *   asynPut(val,1,&h) - OVERRIDE
    *
    *   asynPut(val,1,&h) - BUFFERED
    *
    *   asynPut(val,1,&h) - BUFFERED
    *
    *   asynPut(val,1)    - BUFFERED
    *
    *   synPut(val,1)     - OVERRIDE (blocking)
    *
    * @param pData Void pointer to the data to be written
    * @param n Number of elements to write
    * @param pHandler Executed at the end of the operation
    * @param flush True if the network channel has to be flushed
    *
    * @throw ChannelAccessException Something failed performing the PUT
    */
   void asynPut(void* pData,
                int n,
                CAEventHandler* pHandler = NULL,
                bool flush = true);

   /**
    * Synchronous Put block until the requested operation is completed
    *
    * If there is a disconnection during the wait of a synchronous put
    * , the call is unblocked and a ChannelDisconnected exception is
    * thrown
    *
    * SynPut will not be allowed to continue the execution until all the
    * other put with "callback" have been processed
    *
    * @param pData Void pointer to the data to be written
    * @param n Number of elements to write
    *
    * @throw ChannelAccessException Something failed performing the PUT
    */
   void synPut(void* pData, int n);

   /**
    * Asynchronous Get return immediately after the request has been
    * sent. A handler to describe how to "read" the data must always be
    * provided
    *
    * When the channel is disconnected, the asynchronous get fails
    * and no handler is registered for execution.
    *
    * When an asynchronous get is successfully registered, the handler
    * will always be called. If the channel becomes disconnected, the
    * onFailure function of the handler is called
    *
    * AsynGet wait for the handler of other get operations with
    * callback to finish before calling theirs
    *
    * @param n Number of elements to read
    * @param pHandler Handler executed at the end of the operation and
    *                 used to describe how to read the data
    * @param flush True if the network channel has to be flushe if
    */
   void asynGet(int n, CAEventHandler* pHandler, bool flush = true);

   /**
    * Synchronous Get block until the requested operation is completed
    *
    * If there is a disconnection during the wait of a synchronous get
    * , the call is unblocked and a ChannelDisconnected exception is
    * thrown
    *
    * SynGet won't be allowed to continue the execution until all the
    * other get with "callback" have been processed
    *
    * @param n Number of elements to read
    * @param pHandler Handler executed at the end of the operation and
    *                 used to describe how to read the data
    */
   void synGet(int n, CAEventHandler* pHandler);

   /**
    * Wait for the completion of all the put/get which use a handler
    */
   void waitCompletion();

   /**
    * Add a connection handler to be executed whenever a connection
    * event for this PV occurs. Execute-on-bind mode will execute the
    * handler right away during the subscription
    *
    * @param pHandler Pointer to a CAConnectionHandler object
    * @param executedOnBind The connection handler is executed once
    *                       during the subscription without needing
    *                       a change in the connection state. According
    *                       to the current state either onConnection
    *                       or onDisconnection is called
    */
   void subscribeConnectionEvent(CAConnectionHandler* pHandler,
                                 bool executedOnBind = false);

   /**
    * Unregister a connection event handler
    *
    * @param pHandler Pointer to a CAConnectionHandler object
    */
   void unsubscribeConnectionEvent(CAConnectionHandler* pHandler);

   /**
    * Add an data change handler to be called whenever data change
    * event for this PV occurs
    *
    * @param pHandler Pointer to a CAEventHandler object
    * @param wait True if the call has to block until successful, False
    *             otherwise
    */
   void subscribeDataChangeEvent(CAEventHandler* pHandler, bool wait = false);

   /**
    * Unregister a data change event handler
    *
    * @param pHandler Pointer to a CAEventHandler object
    * @param wait True if the call has to block until successful, False
    *             otherwise
    */
   void unsubscribeDataChangeEvent(CAEventHandler* pHandler, bool wait = false);

   /**
    * Add an alarm handler to be called whenever an alarm
    * event for this PV occurs
    *
    * @param pHandler Pointer to a CAEventHandler object
    * @param wait True if the call has to block until successful, False
    *             otherwise
    */
   void subscribeAlarmEvent(CAEventHandler* pHandler, bool wait = false);

   /**
    * Unregister an alarm event handler
    *
    * @param pHandler Pointer to a CAEventHandler object
    * @param wait True if the call has to block until successful, False
    *             otherwise
    */
   void unsubscribeAlarmEvent(CAEventHandler* pHandler, bool wait = false);

private:

   /**
    * PV Shared Resources
    */
   boost::shared_ptr<PVSharedResources> m_pSharedResources;

   /**
    * PV Specific Resources
    */
   boost::shared_ptr<PVSpecificResources> m_pSpecificResources;

private:

   /**
    * Connection Attempt accessory
    *
    * @param localLock Local lock
    * @param timeoutSecond Second before a timeout event
    */
   void connectionAttempt(boost::unique_lock<boost::mutex>& localLock,
                          long timeoutSeconds = 5);

   /**
    * Utility that check the error code and throws the proper exception
    *
    * @param errorCode Channel Access Error Code
    */
   void handleErrorCode(int errorCode);

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
