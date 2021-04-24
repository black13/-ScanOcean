/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <core/PVGroup.h>

#include <core/PV.h>
#include <core/PVSharedResources.h>
#include <handlers/base/CAConnectionHandler.h>
#include <utils/ChannelAccessExceptions.h>
#include <utils/Logger.h>
#include<mutex>
using std::pair;
using std::list;
using std::string;

using std::shared_ptr;
using std::unordered_set;

/*---------------------------------------------------------------------------*/

PVGroup::PVGroup()
: m_isGroupConnected(false),
  m_totalPV(0),
  m_isFinalized(false),
  m_pHandler(NULL)
{

}

/*---------------------------------------------------------------------------*/

PVGroup::~PVGroup()
{

   std::unique_lock<std::recursive_mutex> localLock(m_mutex);

   list<pair<shared_ptr<PV>, CAUpdateGroupState*> >::iterator iter;
   for(iter = m_subscriptionList.begin();
       iter != m_subscriptionList.end();
       ++iter)
   {
      pair<shared_ptr<PV>, CAUpdateGroupState*> pair = *iter;
      shared_ptr<PV> pv = pair.first;
      CAUpdateGroupState* pHandler = pair.second;

      try {
         pv->unsubscribeConnectionEvent(pHandler);
      }
      catch(ChannelAccessException& e) {

      }

      delete pHandler;
   }

}

/*---------------------------------------------------------------------------*/

void PVGroup::addPV(const shared_ptr<PV>& pPV)
{

   std::unique_lock<std::recursive_mutex> localLock(m_mutex);

   if(m_isFinalized == false) {

      pair<shared_ptr<PV>, CAUpdateGroupState*> pair;
      pair.first = pPV;
      pair.second = new CAUpdateGroupState(pPV->getName(),this);
      m_subscriptionList.push_back(pair);

      m_totalPV++;


   }
   else
   {
      //TODO throw exception
   }

}

/*---------------------------------------------------------------------------*/

bool PVGroup::isGroupConnected()
{

   return m_isGroupConnected;

}

/*---------------------------------------------------------------------------*/

void PVGroup::finalize()
{

   std::unique_lock<std::recursive_mutex> localLock(m_mutex);

   if(m_isFinalized == false)
   {

      list<pair<shared_ptr<PV>, CAUpdateGroupState*> >::iterator iter;
      for(iter = m_subscriptionList.begin();
          iter != m_subscriptionList.end();
          ++iter)
      {
         pair<shared_ptr<PV>, CAUpdateGroupState*> pair = *iter;

         shared_ptr<PV> pv = pair.first;
         CAUpdateGroupState* handler = pair.second;

         pv->subscribeConnectionEvent(handler,true);

      }


      m_isFinalized = true;
   }
   else
   {
      //TODO throw exception
   }

}

/*---------------------------------------------------------------------------*/

void PVGroup::subscribeConnectionEvent(CAConnectionHandler* pHandler)
{

   std::unique_lock<std::recursive_mutex> localLock(m_mutex);

   m_pHandler = pHandler;

}

/*---------------------------------------------------------------------------*/

CAUpdateGroupState::CAUpdateGroupState(const string& name, PVGroup* pGroup)
: m_name(name),
  m_pGroup(pGroup)
{

}

/*---------------------------------------------------------------------------*/

void CAUpdateGroupState::onConnection()
{

   IndentedWriter w =
      Logger::getIndentedWriter("GlobalRegister: onConnection()");

   std::unique_lock<std::recursive_mutex> localLock(m_pGroup->m_mutex);

   int oldSize = m_pGroup->m_connectedPVSet.size();

   unordered_set<string>::iterator iter =
      m_pGroup->m_connectedPVSet.find(m_name);
   // not found
   if(iter == m_pGroup->m_connectedPVSet.end()) {



      m_pGroup->m_connectedPVSet.insert(m_name);

      w() << "Not found, updating set " << m_pGroup->m_connectedPVSet.size()
          << std::endl;

      int newSize = m_pGroup->m_connectedPVSet.size();




      if(newSize == m_pGroup->m_totalPV && oldSize < m_pGroup->m_totalPV) {


         m_pGroup->m_isGroupConnected = true;

         w() << "All PVs are now connected" << std::endl;

         if(m_pGroup->m_pHandler != NULL) {

            w() << "Executing on connection handler" << std::endl;

            m_pGroup->m_pHandler->onConnection();

         }
      }
   }

}

/*---------------------------------------------------------------------------*/

void CAUpdateGroupState::onDisconnection()
{

   std::unique_lock<std::recursive_mutex> localLock(m_pGroup->m_mutex);

   int oldSize = m_pGroup->m_connectedPVSet.size();

   unordered_set<string>::iterator iter =
      m_pGroup->m_connectedPVSet.find(m_name);
   // found
   if(iter != m_pGroup->m_connectedPVSet.end()) {
      m_pGroup->m_connectedPVSet.erase(iter);

      int newSize = m_pGroup->m_connectedPVSet.size();

      if(newSize < m_pGroup->m_totalPV && oldSize == m_pGroup->m_totalPV) {

         m_pGroup->m_isGroupConnected = false;

         if(m_pGroup->m_pHandler != NULL)
            m_pGroup->m_pHandler->onDisconnection();
      }
   }

}

/*---------------------------------------------------------------------------*/
