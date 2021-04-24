/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <core/ChannelAccess.h>

#include <core/PV.h>
#include <core/GlobalRegister.h>
#include <utils/ChannelAccessExceptions.h>
#include <utils/Logger.h>

#include <cadef.h>

using std::string;
using std::endl;

using boost::mutex;
using boost::shared_ptr;
using boost::unique_lock;

/*---------------------------------------------------------------------------*/

ChannelAccess* ChannelAccess::s_pInstance = NULL;
ca_client_context* ChannelAccess::m_pContext = NULL;

/*---------------------------------------------------------------------------*/

mutex ChannelAccess::s_singletonMutex;

/*---------------------------------------------------------------------------*/

ChannelAccess* ChannelAccess::getInstance()
{

   unique_lock<mutex> lock(s_singletonMutex);

   IndentedWriter w = Logger::getIndentedWriter("CA: getInstance()");

   if(s_pInstance == NULL)
   {
      w() << "CA instance not created yet, calling constructor..." << endl;
      s_pInstance = new ChannelAccess;
   }

   w() << "Attaching context" << std::endl;
   ca_attach_context(m_pContext);

   w() << "Returning CA instance" << std::endl;
   return s_pInstance;

}

/*---------------------------------------------------------------------------*/

ChannelAccess::ChannelAccess()
{

   IndentedWriter w = Logger::getIndentedWriter("CA: Constructor");

   w() << "Creating Global Register" << endl;
   m_pGlobalRegister = new GlobalRegister;

   w() << "Initiating CA" << endl;
   initChannelAccess();

}

/*---------------------------------------------------------------------------*/

shared_ptr<PV> ChannelAccess::getPV(const string& name,
                                    int attempts,
                                    long timeoutSeconds)
{

   IndentedWriter w = Logger::getIndentedWriter("CA: getPV()");

   w() << "Getting a PVInterface from Global Register ("
	   << m_pGlobalRegister->getSharedResourcesNum() << "->"
	   << m_pGlobalRegister->getSharedResourcesNum() + 1 << ")"
	   << endl;

   shared_ptr<PV> pPV = m_pGlobalRegister->getPV(name);

   try
   {
      w() << "Connecting... <" << attempts << " attempts, "
          << timeoutSeconds << " seconds>" << endl;
      pPV->connect(attempts,timeoutSeconds);
   }
   catch(ChannelDisconnectedException& e)
   {
      w() << "Exception, connect did not work!" << endl;
      throw e;
   }

   return pPV;

}

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

void ChannelAccess::flush()
{

   unique_lock<mutex> lock(s_singletonMutex);

   IndentedWriter w = Logger::getIndentedWriter("CA: flush()");

   if(s_pInstance != NULL) ca_flush_io();
   else throw CANotInstaciatedException();

}

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

void ChannelAccess::initChannelAccess()
{

   IndentedWriter w = Logger::getIndentedWriter("CA: initChannelAccess()");

   w() << "ca_context_create(...)" << endl;
   ca_context_create(ca_enable_preemptive_callback);
   m_pContext = ca_current_context();

   w() << "Overriding exception callback..." << endl;
   ca_add_exception_event(exceptionCallback,NULL);

   w() << "Flushing" << endl;
   ca_flush_io();

}

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

void ChannelAccess::exceptionCallback(struct exception_handler_args args)
{

   unique_lock<mutex> lock(s_singletonMutex);

   IndentedWriter w = Logger::getIndentedWriter("CA: ExceptionCallback()");

   if(s_pInstance != NULL)
   {
      long int msgNo = CA_EXTRACT_MSG_NO(args.stat);

      switch(msgNo)
      {
         case VIRTUAL_CIRCUIT_DISCONNECT:
            w() << ca_message(args.stat) << endl;
         break;
         default:
            w() << "Unhandled Exception! - " << msgNo<< " = "
                << ca_message(args.stat) << endl;
         break;
      }
   }

}

/*---------------------------------------------------------------------------*/
