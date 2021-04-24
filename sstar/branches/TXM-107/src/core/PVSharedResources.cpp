/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <core/PVSharedResources.h>

#include <core/GlobalRegister.h>
#include <handlers/base/CAConnectionHandler.h>
#include <handlers/base/CAEventHandler.h>
#include <utils/ThreadHasher.h>

using std::queue;
using std::list;
using std::string;

using boost::mutex;
using boost::condition_variable;

/*---------------------------------------------------------------------------*/

PVSharedResources::PVSharedResources(const string& name,
                                     GlobalRegister* pGlobalRegister)
: m_pGlobalRegister(pGlobalRegister),
  m_name(name),
  m_pChid(NULL),
  m_connectionState(PVSharedResources::NOT_BOUND),
  m_dataChangeToBeBound(false),
  m_dataChangeToBeUnbound(false),
  m_alarmToBeBound(false),
  m_alarmToBeUnbound(false)
{

}

/*---------------------------------------------------------------------------*/

GlobalRegister* PVSharedResources::getGlobalRegister()
{

   return m_pGlobalRegister;

}

/*---------------------------------------------------------------------------*/

mutex& PVSharedResources::getLocalMutex()
{

   return m_localMutex;

}

/*---------------------------------------------------------------------------*/

PVSharedResources::ConnectionState PVSharedResources::getConnectionState()
{

   return m_connectionState;

}

/*---------------------------------------------------------------------------*/

list<CAConnectionHandler*>& PVSharedResources::getConnectionHandlers()
{

   return m_connectionHandlers;

}

/*---------------------------------------------------------------------------*/

const string& PVSharedResources::getName()
{

   return m_name;

}

/*---------------------------------------------------------------------------*/

condition_variable& PVSharedResources::getPutQueueEmptyCV()
{

   return m_putQueueEmptyCV;

}

/*---------------------------------------------------------------------------*/

queue<CallbackParam, list<CallbackParam> >& PVSharedResources::getPutQueue()
{

   return m_putQueue;

}

/*---------------------------------------------------------------------------*/

queue<CallbackParam, list<CallbackParam> >& PVSharedResources::getGetQueue()
{

   return m_getQueue;

}

/*---------------------------------------------------------------------------*/

list<CAEventHandler*>& PVSharedResources::getDataChangeHandlers()
{

   return m_dataChangedHandlers;

}

/*---------------------------------------------------------------------------*/

list<CAEventHandler*>& PVSharedResources::getAlarmsHandlers()
{

   return m_alarmHandlers;

}

/*---------------------------------------------------------------------------*/

chid PVSharedResources::getChid()
{

   return m_pChid;

}

/*---------------------------------------------------------------------------*/

chid* PVSharedResources::getPChid()
{

   return &m_pChid;

}

/*---------------------------------------------------------------------------*/

evid* PVSharedResources::getPDataChangeSubId()
{

   return &m_dataChangeSubID;

}

/*---------------------------------------------------------------------------*/

evid* PVSharedResources::getPAlarmsSubId()
{

   return &m_alarmsSubID;

}

/*---------------------------------------------------------------------------*/

condition_variable& PVSharedResources::getConnectionCV()
{

   return m_connectionCV;

}

/*---------------------------------------------------------------------------*/

bool PVSharedResources::isDataChangeToBeBound()
{

   return m_dataChangeToBeBound;

}

/*---------------------------------------------------------------------------*/

bool PVSharedResources::isDataChangeToBeUnbound()
{

   return m_dataChangeToBeUnbound;

}

/*---------------------------------------------------------------------------*/

void PVSharedResources::requestDataChangeToBeBound()
{

   m_dataChangeToBeBound = true;
   m_dataChangeToBeUnbound = false;

}

/*---------------------------------------------------------------------------*/

void PVSharedResources::requestDataChangeToBeUnbound()
{

   m_dataChangeToBeBound = false;
   m_dataChangeToBeUnbound = true;

}

/*---------------------------------------------------------------------------*/

void PVSharedResources::dataChangeBindingCompleted()
{

   m_dataChangeToBeBound = false;

}

/*---------------------------------------------------------------------------*/

void PVSharedResources::dataChangeUnbindingCompleted()
{

   m_dataChangeToBeUnbound = false;

}

/*---------------------------------------------------------------------------*/

bool PVSharedResources::isAlarmToBeBound()
{

   return m_alarmToBeBound;

}

/*---------------------------------------------------------------------------*/

bool PVSharedResources::isAlarmToBeUnbound()
{

   return m_alarmToBeUnbound;

}

/*---------------------------------------------------------------------------*/

void PVSharedResources::requestAlarmToBeBound()
{

   m_alarmToBeBound = true;
   m_alarmToBeUnbound = false;

}

/*---------------------------------------------------------------------------*/

void PVSharedResources::requestAlarmToBeUnbound()
{

   m_alarmToBeBound = false;
   m_alarmToBeUnbound = true;

}

/*---------------------------------------------------------------------------*/

void PVSharedResources::alarmBindingCompleted()
{

   m_alarmToBeBound = false;

}

/*---------------------------------------------------------------------------*/

void PVSharedResources::alarmUnbindingCompleted()
{

   m_alarmToBeUnbound = false;

}

/*---------------------------------------------------------------------------*/

void PVSharedResources::setConnectionState(
   PVSharedResources::ConnectionState connectionState)
{

   m_connectionState = connectionState;

}

/*---------------------------------------------------------------------------*/
