/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <scan/Scan.h>
#include <scan/Command.h>
#include <scan/ScanCommand.h>
#include <scan/ScanSequenceCommand.h>
#include <scan/CACallback.h>
#include <utils/ScanExceptions.h>

#include <string>

/*---------------------------------------------------------------------------*/

volatile bool Scan::s_stopFlag = false;
Scan* Scan::s_pInstance = NULL;

/*---------------------------------------------------------------------------*/

Scan::Scan()
: m_dataChange(NULL),
  m_readComplete(NULL),
  m_valueI(0),
  m_valueD(0),
  m_valueS(new char[256]),
  m_count(1)

{
}

/*---------------------------------------------------------------------------*/

Scan::~Scan()
{
    delete[] m_valueS;
}

/*---------------------------------------------------------------------------*/

void Scan::execute(const Command* cmd)
{

   if (cmd == NULL) 
   {
      return;
   }

   if (s_stopFlag == true)
   {
      throw ScanAbortException();
   }

   boost::shared_ptr<PV> pv = getPV(cmd->getPVName());

   void* data = NULL;

   switch (cmd->getOperation())
   {
      case Command::PV_PUT_SYNC:
         std::cout<<"synPut "<<cmd->getPVName();
         waitPVCallback(pv, cmd);
         break;
      case Command::PV_PUT_ASYNC:
         std::cout<<"asynPut " << cmd->getPVName();
         data = getValue(cmd);
         if (data == NULL) return;
         pv->asynPut(data, m_count);
         break;
      case Command::PV_WAIT:
         std::cout<<"pvWait " << cmd->getPVName()<<std::endl;
         waitPVSet(pv, cmd);   
         break;
   }

}

/*---------------------------------------------------------------------------*/

Scan* Scan::getInstance()
{

   if (s_pInstance == NULL)
   {
      s_pInstance = new Scan();
   }

   return s_pInstance;

}

/*---------------------------------------------------------------------------*/

boost::shared_ptr<PV> Scan::getPV(const std::string& pvName)
{

   std::map<std::string, boost::shared_ptr<PV> >::iterator it;
   it = m_pvList.find(pvName);
   // If we already have created a PV object, return it.
   if ( it != m_pvList.end() )
   {
      return m_pvList[pvName];

   }

   try
   {
      ChannelAccess* ca = ChannelAccess::getInstance();

      // The value of 1 in the second argument of getPV force the connection callback
      boost::shared_ptr<PV> pv = ca->getPV(pvName, 1, 2);
      m_pvList[pvName] = pv;
      return pv;
   }
   catch (ChannelAccessException& ce)
   {
      throw;
   }

}

/*---------------------------------------------------------------------------*/

void* Scan::getValue(const Command* cmd)
{
   void* data;

   m_count = 1;

   switch (cmd->getType())
   {
      case Command::SSTAR_INT:
         m_valueI = cmd->getValueI();
         std::cout<<" "<<m_valueI<<std::endl;
         data = &m_valueI;
         break;
      case Command::SSTAR_UINT:
         m_valueUI = cmd->getValueUI();
         std::cout<<" "<<m_valueUI<<std::endl;
         data = &m_valueUI;
      case Command::SSTAR_DOUBLE:
         m_valueD = cmd->getValueD();
         std::cout<<" "<<m_valueD<<std::endl;
         data = &m_valueD;
         break;
      case Command::SSTAR_STRING:
        strncpy(m_valueS, cmd->getValueS().c_str(), 256);
        std::cout<<" "<<m_valueS<<std::endl;
        data = m_valueS;
        m_count = 256;
        break;
      case Command::SSTAR_SHORT:
      case Command::SSTAR_FLOAT:
      case Command::SSTAR_LONG:
      default:
         data = NULL;
   }

   return data;
}

/*---------------------------------------------------------------------------*/

void Scan::onDataChange(bool isSuccess)
{

   // This method is used by the PV_WAIT operation for notification
   // of data change to a PV. 
   //
   // In order to avoid dead-lock, make sure to return immediately if not
   // possible to acquire lock. The dead-lock can occur if the PV object is
   // blocked in this call-back and we try to access any of the PV methods.
   
   bool lock = m_mutex.try_lock();

   if (lock == false) return;

   m_mutex.unlock();
   m_pvCallback.notify_one();

}

/*---------------------------------------------------------------------------*/

void Scan::onReadComplete(bool isSuccess)
{

   {
      boost::mutex::scoped_lock lock(m_mutex);
   }

   m_pvCallback.notify_one();

}


/*---------------------------------------------------------------------------*/

void Scan::reset()
{

   Scan::s_stopFlag = false;

}

/*---------------------------------------------------------------------------*/

void Scan::stop()
{

   Scan::s_stopFlag = true;

}

/*---------------------------------------------------------------------------*/

void Scan::waitPVCallback(boost::shared_ptr<PV> pv, const Command* cmd)
{

   if (m_readComplete == NULL)
   {
      m_readComplete = new CACallback(this, &Scan::onReadComplete);
   }

   boost::mutex::scoped_lock lock(m_mutex);
  
   void* data = getValue(cmd);
   pv->asynPut(data, m_count, m_readComplete);
   bool isDone = false;
   while (isDone == false)
   {
      boost::system_time const timeout = boost::get_system_time() 
         + boost::posix_time::milliseconds(1000);  
      isDone = m_pvCallback.timed_wait(lock, timeout);
      if (Scan::s_stopFlag == true)
      {
         // clean-up and bail-out
         throw ScanAbortException();
      }
   }

}

/*---------------------------------------------------------------------------*/

void Scan::waitPVSet(boost::shared_ptr<PV> pv, const Command* cmd)
{

   if (m_dataChange == NULL)
   {
      m_dataChange = new CACallback(this, &Scan::onDataChange);
   }

   pv->subscribeDataChangeEvent(m_dataChange);

   //TODO:: Handle all the supported data-type in the call-back.
   int value = 0;
   CAGetTotalCopy<int>  r(&value);
   pv->synGet(1, &r);

   boost::mutex::scoped_lock lock(m_mutex);

   bool ready = false;
   while (value != cmd->getValueI())
   {
      boost::system_time const timeout = boost::get_system_time() +
         boost::posix_time::milliseconds(500);
      ready = m_pvCallback.timed_wait(lock, timeout);

      if (Scan::s_stopFlag == true)
      {
         pv->unsubscribeDataChangeEvent(m_dataChange);
         throw ScanAbortException();
      }

      pv->synGet(1, &r);
   }

   pv->unsubscribeDataChangeEvent(m_dataChange);

}

/*---------------------------------------------------------------------------*/

