/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <core/PV.h>

#include <algorithm>

#include <cadef.h>

#include <core/PVResources.h>
#include <core/PVSpecificResources.h>
#include <core/GlobalRegister.h>
#include <core/CallbackParam.h>
#include <core/EpicsCallbacks.h>

#include <handlers/base/CAConnectionHandler.h>
#include <handlers/base/CAEventHandler.h>

#include <utils/ChannelAccessExceptions.h>
#include <utils/Logger.h>
#include <chrono>

/*---------------------------------------------------------------------------*/

using std::string;
using std::for_each;
using std::list;

using std::shared_ptr;
using std::mutex;
using std::unique_lock;
using std::thread;

/*---------------------------------------------------------------------------*/

PV::PV(const shared_ptr<PVResources>& pResources)
: m_pSharedResources(pResources->getSharedResources()),
  m_pSpecificResources(pResources->getSpecificResources())
{

   unique_lock<mutex> localLock(m_pSharedResources->getLocalMutex());

   IndentedWriter w = Logger::getIndentedWriter("PVInterface: Constructor");

   m_pSpecificResources->incrementInterfacesCount();

   w() << "Incrementing interfaces count ("
       << m_pSpecificResources->interfacesCount() << ")" << std::endl;

}

/*---------------------------------------------------------------------------*/

PV::~PV()
{

   //Disconnect
   unique_lock<mutex> localLock(m_pSharedResources->getLocalMutex());

   IndentedWriter w = Logger::getIndentedWriter("PVInterface: Destructor");

   w() << "Decrementing interfaces count ("
       << m_pSpecificResources->interfacesCount() << ")" << std::endl;
   m_pSpecificResources->decrementInterfacesCount();

   if(m_pSpecificResources->interfacesCount() == 0)
   {
      w() << "Last Smart Pointer to the PV, cleaning!" << std::endl;

      if(m_pSharedResources->getConnectionState() !=
         PVSharedResources::NOT_BOUND)
      {

         w() << "PV is in a BOUND state" << std::endl;

         while(m_pSpecificResources->arePendingRequests())
         {
            w() << "There are pending requests, waiting..." << std::endl;
            m_pSpecificResources->getPendingRequestsCV().wait(localLock);
            w() << "Notified, are there pending requests?" << std::endl;

         }

         w() << "No pending requests" << std::endl;

         if(m_pSharedResources->getGlobalRegister()->isLastThread(
            m_pSharedResources->getName()))
         {
            w() << "Last thread using PVSharedResources, ca_clear_channel()"
                << std::endl;

//            list<CAEventHandler*>::iterator iter;
//            for(iter = m_pSharedResources->getDataChangeHandlers().begin();
//                iter != m_pSharedResources->getDataChangeHandlers().end();
//                ++iter)
//            {
//               CAEventHandler* pHandler = (CAEventHandler*) * iter;
//
//               //TODO unsubscribe without lock
//            }
//            m_pSharedResources->getDataChangeHandlers().clear();
//            m_pSharedResources->getAlarmsHandlers().clear();
//            m_pSharedResources->getConnectionHandlers().clear();

            ca_clear_channel(m_pSharedResources->getChid());

            w() << "Set connection state to NOT_BOUND" << std::endl;
            m_pSharedResources->setConnectionState(
               PVSharedResources::NOT_BOUND);
         }
         else
         {
            w() << "This is not the last thread using"
                << m_pSharedResources->getName() <<", can't ca_clear_channel()"
                << std::endl;
         }
      }

      localLock.unlock();

      //Global cleaning
      m_pSharedResources->getGlobalRegister()->disposeResources(
         m_pSharedResources->getName());
      GlobalRegister* gRegister = m_pSharedResources->getGlobalRegister();
      w() << "Disposing PVSharedResources from GlobalRegister - "
          << m_pSharedResources->getName() << "("
   	      << gRegister->getSharedResourcesNum() + 1 << "->"
   	      << gRegister->getSharedResourcesNum() << ")"
   	   << std::endl;

   }
   else
   {
      w() << "Still other living Smart Pointers ("
          << m_pSpecificResources->interfacesCount() <<"), can't clean"
          << std::endl;
   }

}

/*---------------------------------------------------------------------------*/

const string& PV::getName()
{

   unique_lock<mutex> localLock(m_pSharedResources->getLocalMutex());

   return m_pSharedResources->getName();

}

/*---------------------------------------------------------------------------*/

unsigned PV::getCount()
{

   unique_lock<mutex> localLock(m_pSharedResources->getLocalMutex());

   return ca_element_count(m_pSharedResources->getChid());

}

/*---------------------------------------------------------------------------*/

chtype PV::getType()
{

   // The documentation says nothing about error codes...

   unique_lock<mutex> localLock(m_pSharedResources->getLocalMutex());

   int result = ca_field_type(m_pSharedResources->getChid());

   return result;

}

/*---------------------------------------------------------------------------*/

PVSharedResources::ConnectionState PV::getConnectionState()
{

   return m_pSharedResources->getConnectionState();

}

/*---------------------------------------------------------------------------*/

void PV::connect(int attempts, long timeoutSeconds)
{

   unique_lock<mutex> localLock(m_pSharedResources->getLocalMutex());

   IndentedWriter w = Logger::getIndentedWriter("PV: Connect()");

   if(attempts == 0)
   {
      w() << "Getting PVInterface even if disconnected" << std::endl;

      connectionAttempt(localLock, 0);
   }
   else
   {
      w() << "Getting PVInterface only if connected" << std::endl;

      int attemptsLeft = attempts;
      bool done = false;

      while(attemptsLeft >= 1 && done == false)
      {
         w() << "Attempt #" << attempts - attemptsLeft + 1 << std::endl;

         try
         {
            connectionAttempt(localLock, timeoutSeconds);

            w() << "Successful connection attempt!" << std::endl;

            done = true;
         }
         catch(ChannelAccessException& e)
         {
            w() << "Unsuccessful connection attempt!" << std::endl;
         }
         attemptsLeft--;
      }

      if(done == false)
      {
         w() << "Couldn't get a connected PVInterface in #" << attempts
             << " attempts" << std::endl;
         throw ChannelDisconnectedException();
      }

   }

}

/*---------------------------------------------------------------------------*/

void PV::connectionAttempt(unique_lock<mutex>& localLock,long timeoutSeconds)
{

   IndentedWriter w = Logger::getIndentedWriter("PV: Connection attempt");

   if(m_pSharedResources->getConnectionState() == PVSharedResources::NOT_BOUND)
   {
      w() << "Calling ca_create_channel()" << std::endl;



      int result = ca_create_channel(m_pSharedResources->getName().c_str(),
                                     EpicsCallbacks::connectionCallback,
                                     m_pSharedResources->getGlobalRegister(),
                                     CA_PRIORITY_DEFAULT,
                                     m_pSharedResources->getPChid());

      if(result != ECA_NORMAL)
      {
         w() << "Error in binding the channel, throwing an exception"
             << std::endl;
         throw ChannelNotBoundException();
      }

      ca_flush_io();

      w() << "Changing the channel state to DISCONNECTED" << std::endl;
      m_pSharedResources->setConnectionState(PVSharedResources::DISCONNECTED);
   }

   if(m_pSharedResources->getConnectionState()
      == PVSharedResources::DISCONNECTED)
   {

      w() << "Channel state is DISCONNECTED" << std::endl;
      if(timeoutSeconds > 0)
      {

         w() << "Waiting for a connection notification by EPICS..."
             << std::endl;

         m_pSharedResources->getConnectionCV().wait_for( localLock,  std::chrono::seconds( timeoutSeconds ));

         if(m_pSharedResources->getConnectionState()
            == PVSharedResources::DISCONNECTED)
         {
            w() << "Channel still disconnected, throwing an exception!"
               << std::endl;
            throw ChannelDisconnectedException();
         }

         w() << "Channel successfully connected" << std::endl;
      }

   }
   else
   {
      w() << "Channel already connected" << std::endl;
   }

}

/*---------------------------------------------------------------------------*/

void PV::asynPut(void* pData,
                 int n,
                 CAEventHandler* pHandler,
                 bool flush)
{

   unique_lock<mutex> lock(m_pSharedResources->getLocalMutex());

   IndentedWriter w = Logger::getIndentedWriter("PV: AsynPut");

   int result;
   if(pHandler == NULL)
   {
      w() << "AsynPut without handler" << std::endl;

      while(m_pSharedResources->getPutQueue().empty() != true)
      {
         w() << "There are put handlers to be executed, waiting" << std::endl;

         m_pSharedResources->getPutQueueEmptyCV().wait(lock);

         w() << "Are there put handlers to be executed?" << std::endl;
      }

      w() << "No more put handlers to be executed" << std::endl;

      result = ca_array_put(ca_field_type(m_pSharedResources->getChid()),
                            n,
                            m_pSharedResources->getChid(),
                            pData);
   }
   else
   {
      w() << "AsynPut with handler" << std::endl;

      result = ca_array_put_callback(
         ca_field_type(m_pSharedResources->getChid()),
         n,
         m_pSharedResources->getChid(),
         pData,
         EpicsCallbacks::putCallback,
         m_pSharedResources->getGlobalRegister());

      if(result == ECA_NORMAL)
      {
         std::thread::id tid = std::this_thread::get_id();

         w() << "Pushing parameter for put-callback in a queue" << std::endl;

         CallbackParam param = CallbackParam::createAsynPutWithHandlerParam(
            tid,
            m_pSpecificResources,
            m_pSharedResources,
            pHandler);

         m_pSharedResources->getPutQueue().push(param);

         m_pSpecificResources->incrementPendingRequests();

         w() << "Increment the number of pending requests ("
             << m_pSpecificResources->getPendingRequests() << ")" << std::endl;
      }
   }

   handleErrorCode(result);

   if(flush == true) ca_flush_io();

}

/*---------------------------------------------------------------------------*/

void PV::synPut(void* pData, int n)
{
      synPut(ca_field_type(m_pSharedResources->getChid()),
             pData,
             n);
}

void PV::synPut(int ca_type, void* pData, int n)
{

   unique_lock<mutex> lock(m_pSharedResources->getLocalMutex());

   IndentedWriter w = Logger::getIndentedWriter("PV: SynPut");

   int result = ca_array_put_callback(
      ca_type,
      n,
      m_pSharedResources->getChid(),
      pData,
      EpicsCallbacks::putCallback,
      m_pSharedResources->getGlobalRegister());

   if(result == ECA_NORMAL)
   {
      thread::id tid = std::this_thread::get_id();

      w() << "Pushing parameter for put-callback in a queue" << std::endl;

      CallbackParam param = CallbackParam::createSynPutParam(
         tid,
         m_pSpecificResources,
         m_pSharedResources);

      m_pSharedResources->getPutQueue().push(param);

      m_pSpecificResources->incrementPendingRequests();

      w() << "Increment the number of pending requests ("
          << m_pSpecificResources->getPendingRequests() << ")" << std::endl;
   }

   handleErrorCode(result);

   w() << "Flushing" << std::endl;
   ca_flush_io();

   w() << "Wait for completion notification" << std::endl;
   m_pSpecificResources->getPutCV().wait(lock);

   if(m_pSpecificResources->getLastPutOutcome() == false ||
      m_pSharedResources->getConnectionState() != PVSharedResources::CONNECTED)
   {
      w() << "Put-callback failed, throwing an exception" << std::endl;
      throw ChannelDisconnectedException();
   }
   else
   {
      w() << "Put-callback finished successfully" << std::endl;
   }

}

/*---------------------------------------------------------------------------*/

void PV::asynGet(int n, CAEventHandler* pHandler, bool flush)
{

   asynGet( ca_field_type(m_pSharedResources->getChid()), n, pHandler, flush);

}

void PV::asynGet(int ca_type, int n, CAEventHandler* pHandler, bool flush)
{

   std::unique_lock<std::mutex> lock(m_pSharedResources->getLocalMutex());

   IndentedWriter w = Logger::getIndentedWriter("PV: AsynGet");

   int result;

   result = ca_array_get_callback(ca_type,
                                  n,
                                  m_pSharedResources->getChid(),
                                  EpicsCallbacks::getCallback,
                                  m_pSharedResources->getGlobalRegister());

   if(result == ECA_NORMAL)
   {
      std::thread::id tid = std::this_thread::get_id();

      w() << "Pushing parameter for get-callback in a queue" << std::endl;

      CallbackParam param = CallbackParam::createAsynGetParam(
         tid,
         m_pSpecificResources,
         m_pSharedResources,
         pHandler);

      m_pSharedResources->getGetQueue().push(param);

      m_pSpecificResources->incrementPendingRequests();

      w() << "Increment the number of pending requests ("
          << m_pSpecificResources->getPendingRequests() << ")" << std::endl;
   }

   handleErrorCode(result);

   if(flush == true) ca_flush_io();

}

/*---------------------------------------------------------------------------*/

void PV::synGet(int n, CAEventHandler* pHandler)
{

   synGet(ca_field_type(m_pSharedResources->getChid()), n, pHandler);

}
/*---------------------------------------------------------------------------*/

void PV::synGet(int type, int n, CAEventHandler* pHandler)
{

   unique_lock<mutex> lock(m_pSharedResources->getLocalMutex());

   IndentedWriter w = Logger::getIndentedWriter("PV: SynGet");

   int result;

   result = ca_array_get_callback(type,
                                  n,
                                  m_pSharedResources->getChid(),
                                  EpicsCallbacks::getCallback,
                                  m_pSharedResources->getGlobalRegister());

   if(result == ECA_NORMAL)
   {
      thread::id tid = std::this_thread::get_id();

      w() << "Pushing parameter for get-callback in a queue" << std::endl;

      CallbackParam param = CallbackParam::createSynGetParam(
         tid,
         m_pSpecificResources,
         m_pSharedResources,
         pHandler);

      m_pSharedResources->getGetQueue().push(param);

      m_pSpecificResources->incrementPendingRequests();

      w() << "Increment the number of pending requests ("
          << m_pSpecificResources->getPendingRequests() << ")";
   }

   handleErrorCode(result);

   w() << "Flushing" << std::endl;
   ca_flush_io();

   w() << "Wait for completion notification" << std::endl;
   m_pSpecificResources->getGetCV().wait(lock);

   if(m_pSpecificResources->getLastGetOutcome() == false ||
      m_pSharedResources->getConnectionState() != PVSharedResources::CONNECTED)
   {
      w() << "Get-callback failed, throwing an exception" << std::endl;
      throw ChannelDisconnectedException();
   }
   else
   {
      w() << "Get-callback finished successfully" << std::endl;
   }

}

/*---------------------------------------------------------------------------*/

void PV::waitCompletion()
{

   unique_lock<mutex> localLock(m_pSharedResources->getLocalMutex());

   IndentedWriter w = Logger::getIndentedWriter("PV: waitCompletion");

   if(m_pSharedResources->getConnectionState() == PVSharedResources::CONNECTED)
   {
      while(m_pSpecificResources->arePendingRequests())
      {
         w() << "There are pending requests, waiting..." << std::endl;
         m_pSpecificResources->getPendingRequestsCV().wait(localLock);
         w() << "Notified, are there pending requests?" << std::endl;

      }

      w() << "No pending requests" << std::endl;
   }
   else
   {
      w() << "Channel disconnected, throwing an exception" << std::endl;
      throw ChannelDisconnectedException();
   }

}

/*---------------------------------------------------------------------------*/

void PV::subscribeConnectionEvent(CAConnectionHandler* pHandler,
                                           bool executedOnBind)
{

   unique_lock<mutex> localLock(m_pSharedResources->getLocalMutex());

   IndentedWriter w =
     Logger::getIndentedWriter("PVInterface: Subscribing to connection event");


   list<CAConnectionHandler*>::iterator iter
      = find(m_pSharedResources->getConnectionHandlers().begin(),
             m_pSharedResources->getConnectionHandlers().end(),
             pHandler);

   if(iter == m_pSharedResources->getConnectionHandlers().end())
   {
      w() << "Appending handler to the list of subscriptions" << std::endl;

      m_pSharedResources->getConnectionHandlers().push_back(pHandler);

      if(executedOnBind == true)
      {
         w() << "Requested to -execute-on-bind- for " << m_pSharedResources->getName() << std::endl;


         if( m_pSharedResources->getConnectionState() ==
            PVSharedResources::CONNECTED)
         {

            w() << "Executing onConnection()" << std::endl;
            pHandler->onConnection();

         }
         else
         {
            w() << "Executing onDisconnection() " << std::endl;
            pHandler->onDisconnection();
         }


      }
      else
      {

      }


   }
   else
   {
      w() << "Handler already subscribed!" << std::endl;
   }

}

/*---------------------------------------------------------------------------*/

void PV::unsubscribeConnectionEvent(CAConnectionHandler* pHandler)
{

   unique_lock<mutex> localLock(m_pSharedResources->getLocalMutex());

   IndentedWriter w =
      Logger::getIndentedWriter("PVInterface: Subscribing to connection "
         "event");

   list<CAConnectionHandler*>::iterator iter
      = find(m_pSharedResources->getConnectionHandlers().begin(),
             m_pSharedResources->getConnectionHandlers().end(),
             pHandler);

   if(iter != m_pSharedResources->getConnectionHandlers().end())
   {
      w() << "Removing handler from the list of subscriptions" << std::endl;

      m_pSharedResources->getConnectionHandlers().erase(iter);
   }
   else
   {
      w() << "Handler not subscribed" << std::endl;
   }

}

/*---------------------------------------------------------------------------*/

void PV::subscribeDataChangeEvent(CAEventHandler* pHandler, bool wait)
{

   unique_lock<mutex> localLock(m_pSharedResources->getLocalMutex());

   IndentedWriter w =
      Logger::getIndentedWriter(
         "PVInterface: Subscribing to data change event");

   list<CAEventHandler*>::iterator iter =
         find(m_pSharedResources->getDataChangeHandlers().begin(),
              m_pSharedResources->getDataChangeHandlers().end(),
              pHandler);

   if(iter == m_pSharedResources->getDataChangeHandlers().end())
   {
      if(wait == false)
      {
         w() << "Lazy binding" << std::endl;


            if(m_pSharedResources->getDataChangeHandlers().empty() == true)
            {
               w() << "First subscription, ca_create_subscription" << std::endl;

               int numBytes =
                  dbr_size[ca_field_type(m_pSharedResources->getChid())];
               int n =
                  numBytes / sizeof(
                     ca_field_type(m_pSharedResources->getChid()));

               int result = ca_create_subscription(
                  ca_field_type(m_pSharedResources->getChid()),
                  n,
                  m_pSharedResources->getChid(),
                  DBE_VALUE,
                  EpicsCallbacks::dataChangedCallback,
                  m_pSharedResources->getGlobalRegister(),
                  m_pSharedResources->getPDataChangeSubId());

               if(result != ECA_NORMAL)
               {
                  w() << "Requesting the connection callback to perform the "
                      "subscription" << std::endl;

                  m_pSharedResources->requestDataChangeToBeBound();
               }

               ca_flush_io();
            }
            else
            {
               w() << "Not first subscription, just appending the handler"
                   << std::endl;

               //Should execute on bind, but there is not args set
               //handler->onSuccess();
            }

            m_pSharedResources->getDataChangeHandlers().push_back(pHandler);

      }
      else
      {
         w() << "Synchronous binding" << std::endl;

         if(m_pSharedResources->getDataChangeHandlers().empty() == true)
         {

            w() << "First subscription, ca_create_subscription" << std::endl;

            bool done = false;
            while( done == false)
            {
               try
               {
                  int numBytes =
                     dbr_size[ca_field_type(m_pSharedResources->getChid())];
                  int n = numBytes /
                     sizeof(ca_field_type(m_pSharedResources->getChid()));

                  int result = ca_create_subscription(
                     ca_field_type(m_pSharedResources->getChid()),
                     n,
                     m_pSharedResources->getChid(),
                     DBE_VALUE,
                     EpicsCallbacks::dataChangedCallback,
                     m_pSharedResources->getGlobalRegister(),
                     m_pSharedResources->getPDataChangeSubId());

                  handleErrorCode(result);

                  done = true;
               }
               catch(ChannelAccessException& e)
               {
                  w() << "Subscription failed, waiting for a connection event"
                      << std::endl;

                  if(std::cv_status::timeout == m_pSharedResources->getConnectionCV().wait_for(localLock, std::chrono::seconds(5)))
                  {
                     w() << "Timeout, throwing exception" << std::endl;
                     throw ChannelDisconnectedException();
                  }
                  else
                  {
                     w() << "Connection notified, trying subscription again"
                         << std::endl;
                  }
               }
            }

            ca_flush_io();

            w() << "Subscription completed successfully" << std::endl;


         }
         else
         {
            w() << "Not first subscription, just appending the handler"
                << std::endl;

            //Should execute on bind, but there is not args set
            //handler->onSuccess();
         }

         m_pSharedResources->getDataChangeHandlers().push_back(pHandler);
      }
   }
   else
   {
      w() << "Handler already subscribed" << std::endl;
   }

}

/*---------------------------------------------------------------------------*/

void PV::unsubscribeDataChangeEvent(CAEventHandler* pHandler, bool wait)
{

   unique_lock<mutex> localLock(m_pSharedResources->getLocalMutex());

   IndentedWriter w =
      Logger::getIndentedWriter(
         "PVInterface: Unsubscribing to data change event");

   w() << m_pSharedResources->getName() << std::endl;

   list<CAEventHandler*>::iterator iter =
         find(m_pSharedResources->getDataChangeHandlers().begin(),
              m_pSharedResources->getDataChangeHandlers().end(),
              pHandler);

   if(iter != m_pSharedResources->getDataChangeHandlers().end())
   {
      if(wait == false)
      {
         w() << "Lazy unsubscription" << std::endl;

         w() << "Removing the handler for the list" << std::endl;
         m_pSharedResources->getDataChangeHandlers().erase(iter);

         if(m_pSharedResources->getDataChangeHandlers().empty() == true)
         {
            w() << "Last handler, calling ca_clear_subscription" << std::endl;

            if(!m_pSharedResources->isDataChangeToBeBound())
            {
               int result = ca_clear_subscription(
                  *m_pSharedResources->getPDataChangeSubId());

               if(result != ECA_NORMAL)
               {
                  w() << "Requesting the connection callback to perform the "
                      "unsubscription" << std::endl;

                  m_pSharedResources->requestDataChangeToBeUnbound();
               }
               else
               {
                  w() << "Successful unsubscription" << std::endl;
               }

               ca_flush_io();
            }
            else
            {
               w() << "Asked to bind, but never happened! Do nothing"
                   << std::endl;
            }

         }
         else
         {
            w() << "Not the last handler, not calling ca_clear_subscription"
                << std::endl;

            //Should execute on bind, but there is not args set
            //handler->onSuccess();
         }



      }
      else
      {
         w() << "Synchronous unsubscription" << std::endl;

         w() << "Removing the handler for the list" << std::endl;
         m_pSharedResources->getDataChangeHandlers().erase(iter);

         if(m_pSharedResources->getDataChangeHandlers().empty() == true)
         {

            w() << "Last handler, calling ca_clear_subscription" << std::endl;

            bool done = false;
            while( done == false)
            {
               try
               {
                  int result = ca_clear_subscription(
                     *m_pSharedResources->getPDataChangeSubId());

                  handleErrorCode(result);

                  done = true;
               }
               catch(ChannelAccessException& e)
               {
                  w() << "Unsubscription failed, waiting for a connection event"
                      << std::endl;

                  if(std::cv_status::timeout == m_pSharedResources->getConnectionCV().wait_for(localLock, std::chrono::seconds(5)))
                  {
                     w() << "Timeout, throwing exception" << std::endl;
                     throw ChannelDisconnectedException();
                  }
                  else
                  {
                     w() << "Connection notified, trying unsubscription again"
                         << std::endl;
                  }
               }
            }

            ca_flush_io();

            w() << "Unsubscription completed successfully" << std::endl;


         }
         else
         {
            w() << "Not the last handler, not calling ca_clear_subscription"
                << std::endl;

            //Should execute on bind, but there is not args set
            //handler->onSuccess();
         }

      }
   }
   else
   {
      w() << "Handler already unsubscribed" << std::endl;
   }

}

/*---------------------------------------------------------------------------*/

void PV::subscribeAlarmEvent(CAEventHandler* pHandler, bool wait)
{

   unique_lock<mutex> localLock(m_pSharedResources->getLocalMutex());

   IndentedWriter w =
      Logger::getIndentedWriter("PVInterface: Subscribing to alarm event");

   list<CAEventHandler*>::iterator iter =
         find(m_pSharedResources->getAlarmsHandlers().begin(),
              m_pSharedResources->getAlarmsHandlers().end(),
              pHandler);

   if(iter == m_pSharedResources->getAlarmsHandlers().end())
   {
      if(wait == false)
      {
         w() << "Lazy binding" << std::endl;

            if(m_pSharedResources->getAlarmsHandlers().empty() == true)
            {
               w() << "First subscription, ca_create_subscription" << std::endl;

               int numBytes =
                  dbr_size[ca_field_type(m_pSharedResources->getChid())];
               int n =
                  numBytes / sizeof(
                     ca_field_type(m_pSharedResources->getChid()));

               int result = ca_create_subscription(
                  ca_field_type(m_pSharedResources->getChid()),
                  n,
                  m_pSharedResources->getChid(),
                  DBE_ALARM,
                  EpicsCallbacks::alarmCallback,
                  m_pSharedResources->getGlobalRegister(),
                  m_pSharedResources->getPAlarmsSubId());

               if(result != ECA_NORMAL)
               {
                  w() << "Requesting the connection callback to perform the "
                      "subscription" << std::endl;

                  m_pSharedResources->requestAlarmToBeBound();
               }

               ca_flush_io();
            }
            else
            {
               w() << "Not first subscription, just appending the handler"
                   << std::endl;

               //Should execute on bind, but there is not args set
               //handler->onSuccess();
            }

            m_pSharedResources->getAlarmsHandlers().push_back(pHandler);

      }
      else
      {
         w() << "Synchronous binding" << std::endl;

         if(m_pSharedResources->getAlarmsHandlers().empty() == true)
         {

            w() << "First subscription, ca_create_subscription" << std::endl;

            bool done = false;
            while( done == false)
            {
               try
               {
                  int numBytes =
                     dbr_size[ca_field_type(m_pSharedResources->getChid())];
                  int n =
                     numBytes / sizeof(ca_field_type(
                        m_pSharedResources->getChid()));

                  int result = ca_create_subscription(
                     ca_field_type(m_pSharedResources->getChid()),
                     n,
                     m_pSharedResources->getChid(),
                     DBE_ALARM,
                     EpicsCallbacks::alarmCallback,
                     m_pSharedResources->getGlobalRegister(),
                     m_pSharedResources->getPAlarmsSubId());

                  handleErrorCode(result);

                  done = true;
               }
               catch(ChannelAccessException& e)
               {
                  w() << "Subscription failed, waiting for a connection event"
                      << std::endl;

                  if(std::cv_status::timeout == m_pSharedResources->getConnectionCV().wait_for(localLock, std::chrono::seconds(5)))
                  {
                     w() << "Timeout, throwing exception" << std::endl;
                     throw ChannelDisconnectedException();
                  }
                  else
                  {
                     w() << "Connection notified, trying subscription again"
                         << std::endl;
                  }
               }
            }

            ca_flush_io();

            w() << "Subscription completed successfully" << std::endl;


         }
         else
         {
            w() << "Not first subscription, just appending the handler"
                << std::endl;

            //Should execute on bind, but there is not args set
            //handler->onSuccess();
         }

         m_pSharedResources->getAlarmsHandlers().push_back(pHandler);
      }
   }
   else
   {
      w() << "Handler already subscribed" << std::endl;
   }

}

/*---------------------------------------------------------------------------*/

void PV::unsubscribeAlarmEvent(CAEventHandler* pHandler, bool wait)
{

   unique_lock<mutex> localLock(m_pSharedResources->getLocalMutex());

   IndentedWriter w =
      Logger::getIndentedWriter("PVInterface: Unsubscribing to alarm event");

   list<CAEventHandler*>::iterator iter =
         find(m_pSharedResources->getAlarmsHandlers().begin(),
              m_pSharedResources->getAlarmsHandlers().end(),
              pHandler);

   if(iter != m_pSharedResources->getAlarmsHandlers().end())
   {
      if(wait == false)
      {
         w() << "Lazy unsubscription" << std::endl;

         w() << "Removing the handler for the list" << std::endl;
         m_pSharedResources->getAlarmsHandlers().erase(iter);

         if(m_pSharedResources->getAlarmsHandlers().empty() == true)
         {
            w() << "Last handler, calling ca_clear_subscription" << std::endl;

            if(!m_pSharedResources->isAlarmToBeBound())
            {
               int result = ca_clear_subscription(
                  *m_pSharedResources->getPAlarmsSubId());

               if(result != ECA_NORMAL)
               {
                  w() << "Requesting the connection callback to perform the "
                     "unsubscription" << std::endl;

                  m_pSharedResources->requestAlarmToBeUnbound();
               }
               else
               {
                  w() << "Successful unsubscription" << std::endl;
               }

               ca_flush_io();
            }
            else
            {
               w() << "Asked to bind, but never happened! Do nothing"
                    << std::endl;
            }

         }
         else
         {
            w() << "Not the last handler, not calling ca_clear_subscription"
                << std::endl;

            //Should execute on bind, but there is not args set
            //handler->onSuccess();
         }
      }
      else
      {
         w() << "Synchronous unsubscription" << std::endl;

         w() << "Removing the handler for the list" << std::endl;
         m_pSharedResources->getAlarmsHandlers().erase(iter);

         if(m_pSharedResources->getAlarmsHandlers().empty() == true)
         {

            w() << "Last handler, calling ca_clear_subscription" << std::endl;

            bool done = false;
            while( done == false)
            {
               try
               {
                  int result = ca_clear_subscription(
                     *m_pSharedResources->getPAlarmsSubId());

                  handleErrorCode(result);

                  done = true;
               }
               catch(ChannelAccessException& e)
               {
                  w() << "Unsubscription failed, waiting for a connection event"
                      << std::endl;

                  if(std::cv_status::timeout == m_pSharedResources->getConnectionCV().wait_for(localLock, std::chrono::seconds(5)))
                  {
                     w() << "Timeout, throwing exception" << std::endl;
                     throw ChannelDisconnectedException();
                  }
                  else
                  {
                     w() << "Connection notified, trying unsubscription again"
                         << std::endl;
                  }
               }
            }

            ca_flush_io();

            w() << "Unsubscription completed successfully" << std::endl;


         }
         else
         {
            w() << "Not the last handler, not calling ca_clear_subscription"
                << std::endl;

            //Should execute on bind, but there is not args set
            //handler->onSuccess();
         }

      }
   }
   else
   {
      w() << "Handler already unsubscribed" << std::endl;
   }

}

/*---------------------------------------------------------------------------*/

void PV::handleErrorCode(int errorCode)
{

   IndentedWriter w =
      Logger::getIndentedWriter("PVInterface: Checking Error Code");

   switch(errorCode) {
      case ECA_NORMAL:
         w() << "ECA_NORMAL" << std::endl;
         break;
      case ECA_BADCHID:
         w() << "ECA_BADCHID" << std::endl;
         throw BadChidException();
         break;
      case ECA_BADTYPE:
         w() << "ECA_BADTYPE" << std::endl;
         throw BadTypeException();
         break;
      case ECA_BADCOUNT:
         w() << "ECA_BADCOUNT" << std::endl;
         throw BadCountException();
         break;
      case ECA_STRTOBIG:
         w() << "ECA_STRTOBIG" << std::endl;
         throw StrTooBigException();
         break;
      case ECA_NOWTACCESS:
         w() << "ECA_NOWTACCESS" << std::endl;
         throw WriteAccessException();
         break;
      case ECA_ALLOCMEM:
         w() << "ECA_ALLOCMEM" << std::endl;
         throw MemoryAllocationException();
         break;
      case ECA_DISCONN:
         w() << "ECA_DISCONN" << std::endl;
         m_pSharedResources->setConnectionState(
            PVSharedResources::DISCONNECTED);
         throw ChannelDisconnectedException();
         break;
      case ECA_ADDFAIL:
         w() << "ECA_ADDFAIL" << std::endl;
         throw AddFailException();
         break;
      default:
         w() << "UNKWOWN ERROR CODE" << std::endl;
         break;
   }

}

/*---------------------------------------------------------------------------*/
