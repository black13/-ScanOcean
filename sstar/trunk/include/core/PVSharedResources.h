/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_PV_SHARED_RESOURCES_H
#define SSTAR_PV_SHARED_RESOURCES_H

/*---------------------------------------------------------------------------*/

#include <queue>
#include <list>

#include <cadef.h>

#include <mutex>
#include <condition_variable>
#include <unordered_set>

#include <core/CallbackParam.h>

/*---------------------------------------------------------------------------*/

class GlobalRegister;
class CAEventHandler;
class CAConnectionHandler;

/**
 * Resources shared by all threads using the same PV
 */
class PVSharedResources
{

public:

   /**
    * Connection State Enum
    */
   enum ConnectionState {
      NOT_BOUND,
      CONNECTED,
      DISCONNECTED,
   };

public:

   /**
    * Constructor
    *
    * @param name PV Name
    * @param pGlobalRegister Pointer to the global register data structure
    */
   PVSharedResources(const std::string& name, GlobalRegister* pGlobalRegister);

   /**
    * Get pointer to the global register
    *
    * @return Pointer to the global register
    */
   GlobalRegister* getGlobalRegister();

   /**
    * Get PV Local Mutex
    *
    * @return Pointer to the local mutex
    */
   std::mutex& getLocalMutex();

   /**
    * Get Chid
    *
    * @return chid
    */
   chid getChid();

   /**
    * Get pointer to the Chid
    *
    * @return Pointer to chid
    */
   chid* getPChid();

   /**
    * Get pointer to the data change subscription ID
    *
    * @return Subscription ID Pointer
    */
   evid* getPDataChangeSubId();

   /**
    * Get pointer to the alarm subscription ID
    *
    * @return Subscription ID Pointer
    */
   evid* getPAlarmsSubId();

   /**
    * Get PV Name
    *
    * @return PV Name
    */
   const std::string& getName();

   /**
    * Get Condition Variable used to notify when the put queue is empty
    *
    * @return Condition Variable
    */
   std::condition_variable& getPutQueueEmptyCV();

   /**
    * Get queue of put callback parameters
    *
    * @return List of callback parameters
    */
   std::queue<CallbackParam, std::list<CallbackParam> >& getPutQueue();

   /**
    * Get queue of get callback parameters
    *
    * @return List of callback parameters
    */
   std::queue<CallbackParam, std::list<CallbackParam> >& getGetQueue();

   /**
    * Get list of connection handlers
    *
    * @return List of connection handlers
    */
   std::list<CAConnectionHandler*>& getConnectionHandlers();

   /**
    * Get list of data change handlers
    *
    * @return List of data change handlers
    */
   std::list<CAEventHandler*>& getDataChangeHandlers();

   /**
    * Get list of alarms handlers
    *
    * @return list of alarms handlers
    */
   std::list<CAEventHandler*>& getAlarmsHandlers();

   //TODO To be refactored
   bool isDataChangeToBeBound();
   bool isDataChangeToBeUnbound();
   void requestDataChangeToBeBound();
   void requestDataChangeToBeUnbound();
   void dataChangeBindingCompleted();
   void dataChangeUnbindingCompleted();

   //TODO To be refactore
   bool isAlarmToBeBound();
   bool isAlarmToBeUnbound();
   void requestAlarmToBeBound();
   void requestAlarmToBeUnbound();
   void alarmBindingCompleted();
   void alarmUnbindingCompleted();

   /**
    * Get Condition Variable used to notify when there is a change in the
    * PV connection state
    *
    * @return Condition variable
    */
   std::condition_variable& getConnectionCV();

   /**
    * Get connection state
    *
    * @return Connection State Enum
    */
   ConnectionState getConnectionState();

   /**
    * Set connection state
    *
    * @param connectionState Connection state to be set
    */
   void setConnectionState(ConnectionState connectionState);

private:

   /**
    * Global register pointer
    */
   GlobalRegister* m_pGlobalRegister;

   /**
    * Local mutex
    */
   std::mutex m_localMutex;

   /**
    * Connection condition variable
    */
   std::condition_variable m_connectionCV;

   /**
    * Put queue empty condition variable
    */
   std::condition_variable m_putQueueEmptyCV;

   /**
    * PV Name
    */
   std::string m_name;

   /**
    * Chid
    */
   chid m_pChid;

   /**
    * Connection state
    */
   ConnectionState m_connectionState;

   /**
    * Put Callback Parameters Queue
    */
   std::queue<CallbackParam, std::list<CallbackParam> > m_putQueue;

   /**
    * Get Callback Parameters Queue
    */
   std::queue<CallbackParam, std::list<CallbackParam> > m_getQueue;

   /**
    * Connection handlers list
    */
   std::list<CAConnectionHandler*> m_connectionHandlers;

   /**
    * Alarm handlers list
    */
   std::list<CAEventHandler*> m_alarmHandlers;

   /**
    * Data change handlers list
    */
   std::list<CAEventHandler*> m_dataChangedHandlers;

   /**
    * Alarm Channel Access Subscription ID
    */
   evid m_alarmsSubID;

   /**
    * Data Change Channel Access Subscription ID
    */
   evid m_dataChangeSubID;

   //TODO to be refactored
   bool m_dataChangeToBeBound;
   bool m_dataChangeToBeUnbound;
   bool m_alarmToBeBound;
   bool m_alarmToBeUnbound;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
