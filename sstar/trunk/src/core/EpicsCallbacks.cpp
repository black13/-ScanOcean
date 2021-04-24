/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <core/EpicsCallbacks.h>

#include <string>
#include <list>
#include <algorithm>

#include <core/PVResources.h>
#include <core/PVSharedResources.h>
#include <core/PVSpecificResources.h>
#include <core/GlobalRegister.h>
#include <handlers/base/CAConnectionHandler.h>
#include <handlers/base/CAEventHandler.h>
#include <utils/Logger.h>

using std::string;
using std::for_each;
using std::list;
using std::endl;

using std::shared_ptr;
using std::unique_lock;
using std::mutex;

/*---------------------------------------------------------------------------*/

void EpicsCallbacks::executeConnectionHandler(CAConnectionHandler* pHandler)
{

   pHandler->onConnection();

}

/*---------------------------------------------------------------------------*/

void EpicsCallbacks::executeDisconnectionHandler(CAConnectionHandler* pHandler)
{

   pHandler->onDisconnection();

}

/*---------------------------------------------------------------------------*/

void EpicsCallbacks::getCallback(struct event_handler_args args)
{

   chid pCh = args.chid;
   string pvname = ca_name(pCh);
   GlobalRegister* pGlobalRegister = ((GlobalRegister*) args.usr);

   IndentedWriter w = Logger::getIndentedWriter("EPICS: GetCallback()");

   try
   {

      shared_ptr<PVSharedResources> pSharedResources =
         pGlobalRegister->getSharedResources(pvname);

      w() << "Retrieving PVSharedResources" << endl;

      unique_lock<mutex> localLock(pSharedResources->getLocalMutex());

      CallbackParam params = pSharedResources->getGetQueue().front();
      pSharedResources->getGetQueue().pop();

      w() << "Popping next get-callback parameter" << endl;

      shared_ptr<PVSpecificResources> pSpecificResources =
         pGlobalRegister->getSpecificResources(pvname,
                                                 params.getThreadID());

      w() << "Retrieving PVSpecificResources" << endl;

      pSpecificResources->decrementPendingRequests();

      w() << "Decrement the number of pending requests ("
          << pSpecificResources->getPendingRequests() << ")" << endl;

      if(pSpecificResources->getPendingRequests() <= 0)
      {
         w() << "Last pending request, notifying waiting threads" << endl;
         pSpecificResources->getPendingRequestsCV().notify_all();
      }

      if(args.status == ECA_NORMAL)
      {
         w() << "Successful GET" << endl;
         pSpecificResources->setLastGetOutcome(true);

         switch(params.getType())
         {
            case CallbackParam::ASYN_GET:
               w() << "Executing get-handler" << endl;
               params.getHandler()->setArgs(args);
               params.getHandler()->onSuccess();
               break;
            case CallbackParam::SYN_GET:
               w() << "Notifying waiting thread" << endl;
               params.getHandler()->setArgs(args);
               params.getHandler()->onSuccess();
               pSpecificResources->getGetCV().notify_all();
               break;
            default:
               abort();
               break;
         }

      }
      else
      {
         w() << "Failure PUT" << endl;
         pSpecificResources->setLastGetOutcome(false);

         switch(params.getType())
         {
            case CallbackParam::ASYN_GET:
               w() << "Executing get-handler" << endl;
               params.getHandler()->setArgs(args);
               params.getHandler()->onFailure();
               break;
            case CallbackParam::SYN_GET:
               w() << "Notifying waiting thread" << endl;
               params.getHandler()->setArgs(args);
               params.getHandler()->onSuccess();
               pSpecificResources->getGetCV().notify_all();
               break;
            default:
               abort();
               break;
         }
      }

   }
   catch (ElementNotInTableException& e)
   {
      w() << "Can't retrieve shared resources! Do nothing!" << endl;
   }

}

/*---------------------------------------------------------------------------*/

void EpicsCallbacks::putCallback(struct event_handler_args args)
{

   chid pCh = args.chid;
   string name = ca_name(pCh);
   GlobalRegister* pGlobalRegister = ((GlobalRegister*) args.usr);

   IndentedWriter w = Logger::getIndentedWriter("EPICS: PutCallback()");

   try
   {

      shared_ptr<PVSharedResources> pSharedResources =
         pGlobalRegister->getSharedResources(name);

      w() << "Retrieving PVSharedResources" << endl;

      unique_lock<mutex> localLock(pSharedResources->getLocalMutex());

      CallbackParam params = pSharedResources->getPutQueue().front();
      pSharedResources->getPutQueue().pop();

      w() << "Popping next put-callback parameter" << endl;

      shared_ptr<PVSpecificResources> pSpecificResources =
         pGlobalRegister->getSpecificResources(name,
                                                 params.getThreadID());

      w() << "Retrieving PVSpecificResources" << endl;

      pSpecificResources->decrementPendingRequests();

      w() << "Decrement the number of pending requests ("
          << pSpecificResources->getPendingRequests() << ")" << endl;

      if(pSpecificResources->getPendingRequests() <= 0)
      {
         w() << "Last pending request, notifying waiting threads" << endl;
         pSpecificResources->getPendingRequestsCV().notify_all();
      }

      if(args.status == ECA_NORMAL)
      {
         w() << "Successful PUT" << endl;
         pSpecificResources->setLastPutOutcome(true);

         switch(params.getType())
         {
            case CallbackParam::ASYN_PUT_WITH_HANDLER:
               w() << "Executing put-handler" << endl;
               params.getHandler()->setArgs(args);
               params.getHandler()->onSuccess();
               break;
            case CallbackParam::SYN_PUT:
               w() << "Notifying waiting thread" << endl;
               pSpecificResources->getPutCV().notify_all();
               break;
            default:
               abort();
               break;
         }

      }
      else
      {
         w() << "Failure PUT" << endl;
         pSpecificResources->setLastPutOutcome(false);

         switch(params.getType())
         {
            case CallbackParam::ASYN_PUT_WITH_HANDLER:
               w() << "Executing put-handler" << endl;
               params.getHandler()->setArgs(args);
               params.getHandler()->onFailure();
               break;
            case CallbackParam::SYN_PUT:
               w() << "Notifying waiting thread" << endl;
               pSpecificResources->getPutCV().notify_all();
               break;
            default:
               abort();
               break;
         }
      }

      if(pSharedResources->getPutQueue().empty())
      {
         w() << "Put Queue is empty, notifying waiting asynPut without handler"
             << endl;
         pSharedResources->getPutQueueEmptyCV().notify_all();
      }

   }
   catch (ElementNotInTableException& e)
   {
      w() << "Can't retrieve shared resources! Do nothing!" << endl;
   }

}

/*---------------------------------------------------------------------------*/

void EpicsCallbacks::connectionCallback(struct connection_handler_args args)
{

   chid pCh = args.chid;
   string name = ca_name(pCh);
   GlobalRegister* pGlobalRegister = ((GlobalRegister*) ca_puser(pCh));

   IndentedWriter w = Logger::getIndentedWriter("EPICS: ConnectionCallback()");

   try
   {
      shared_ptr<PVSharedResources> pSharedResources =
         pGlobalRegister->getSharedResources(name);

      w() << "Retrieved shared resources" << endl;

      unique_lock<mutex> localLock(pSharedResources->getLocalMutex());

      if(pSharedResources->isDataChangeToBeBound())
      {
         w() << "Performing the request of subscription" << endl;

         int numBytes = dbr_size[ca_field_type(pSharedResources->getChid())];
         int n = numBytes / sizeof(ca_field_type(pSharedResources->getChid()));

         int result = ca_create_subscription(
            ca_field_type(pSharedResources->getChid()),
            n,
            pSharedResources->getChid(),
            DBE_VALUE,
            EpicsCallbacks::dataChangedCallback,
            pSharedResources->getGlobalRegister(),
            pSharedResources->getPDataChangeSubId());

         if(result != ECA_NORMAL)
         {

            w() << "Binding failed, trying next time" << endl;

         }
         else
         {

            w() << "Binding successful" << endl;
            pSharedResources->dataChangeBindingCompleted();

         }
      }

      if(pSharedResources->isDataChangeToBeUnbound())
      {
         w() << "Performing the request of unsubscription" << endl;

         int result = ca_clear_subscription(
            *pSharedResources->getPDataChangeSubId());

         if(result != ECA_NORMAL)
         {
            w() << "Unsubscription failed, trying next time" << endl;

         }
         else
         {
            w() << "Unsubscription successful" << endl;

            pSharedResources->dataChangeUnbindingCompleted();
         }
      }

      if(pSharedResources->getConnectionState() !=
         PVSharedResources::NOT_BOUND)
      {
         switch (ca_state(pCh)) {
            case cs_conn:

               w() << "PV " << name << " connected!" << endl;

               pSharedResources->setConnectionState(
                  PVSharedResources::CONNECTED);

               w() << "Executing onConnection handlers!" << endl;

               for_each(pSharedResources->getConnectionHandlers().begin(),
                        pSharedResources->getConnectionHandlers().end(),
                        executeConnectionHandler);

               break;
            case cs_never_conn:
               //TODO -  Valid CHID, server not found or unavailable
               //Not documented..
               break;
            case cs_prev_conn:

               w() << "PV " << name << " disconnected!" << endl;

               pSharedResources->setConnectionState(
                  PVSharedResources::DISCONNECTED);

               w() << "Executing onDisconnection handlers!" << endl;

               for_each(pSharedResources->getConnectionHandlers().begin(),
                        pSharedResources->getConnectionHandlers().end(),
                        executeDisconnectionHandler);

               break;
            case cs_closed:
               //TODO - Channel deleted by user?
               //Not documented..

               break;
         }

         //Notify a change of connection for waiting threads
         pSharedResources->getConnectionCV().notify_all();

      }

   }
   catch (ElementNotInTableException& e)
   {
      w() << "Can't retrieve shared resources! Do nothing!" << endl;
   }

}

/*---------------------------------------------------------------------------*/

void EpicsCallbacks::alarmCallback(struct event_handler_args args)
{

   chid pCh = args.chid;
   string name = ca_name(pCh);
   GlobalRegister* pGlobalRegister = ((GlobalRegister*) args.usr);

   IndentedWriter w = Logger::getIndentedWriter("EPICS: AlarmCallback()");

   try
   {
      std::shared_ptr<PVSharedResources> pSharedResources =
         pGlobalRegister->getSharedResources(name);

      w() << "Retrieved shared resources" << endl;

      unique_lock<mutex> localLock(pSharedResources->getLocalMutex());

      w() << "Executing handlers" << endl;

      for(list<CAEventHandler*>::iterator
          i = pSharedResources->getAlarmsHandlers().begin();
          i != pSharedResources->getAlarmsHandlers().end();
          ++i)
      {
         CAEventHandler* pHandler = (CAEventHandler*) *i;
         pHandler->setArgs(args);
         pHandler->onSuccess();
      }
   }
   catch (ElementNotInTableException& e)
   {
      w() << "Can't retrieve shared resources! Do nothing!" << endl;
   }

}

/*---------------------------------------------------------------------------*/

void EpicsCallbacks::dataChangedCallback(struct event_handler_args args)
{

   chid pCh = args.chid;
   string name = ca_name(pCh);
   GlobalRegister* pGlobalRegister = ((GlobalRegister*) args.usr);

   //IndentedWriter w =
   //   Logger::getIndentedWriter("EPICS: DataChangeCallback()");

   try
   {
      shared_ptr<PVSharedResources> pSharedResources =
         pGlobalRegister->getSharedResources(name);

      //w() << "Retrieved shared resources" << std::endl;

      unique_lock<mutex> localLock(pSharedResources->getLocalMutex());

      //w() << "Executing handlers" << std::endl;

      for(list<CAEventHandler*>::iterator
          i = pSharedResources->getDataChangeHandlers().begin();
          i != pSharedResources->getDataChangeHandlers().end();
          ++i)
      {
         CAEventHandler* pHandler = (CAEventHandler*) *i;
         pHandler->setArgs(args);
         pHandler->onSuccess();
      }
   }
   catch (ElementNotInTableException& e)
   {
      //w() << "Can't retrieve shared resources! Do nothing!" << endl;
   }

}

/*---------------------------------------------------------------------------*/
