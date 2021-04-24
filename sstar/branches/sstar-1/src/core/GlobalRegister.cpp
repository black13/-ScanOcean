/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <core/GlobalRegister.h>

#include <core/PVSharedResources.h>
#include <core/PVSpecificResources.h>
#include <core/PVResources.h>
#include <core/PV.h>

#include <utils/ThreadHasher.h>
#include <utils/Logger.h>

/*---------------------------------------------------------------------------*/

using std::string;
using boost::shared_ptr;
using boost::thread;
using boost::unique_lock;
using boost::mutex;

/*---------------------------------------------------------------------------*/

GlobalRegister::GlobalRegister()
{

}

/*---------------------------------------------------------------------------*/

GlobalRegister::~GlobalRegister()
{

}

/*---------------------------------------------------------------------------*/

shared_ptr<PV> GlobalRegister::getPV(const string& name)
{

   unique_lock<mutex> lock(m_globalMutex);

   IndentedWriter w =
      Logger::getIndentedWriter("GlobalRegister: getPVInterface");

   thread::id tid = boost::this_thread::get_id();

   shared_ptr<PVSharedResources> pSharedResources;
   shared_ptr<PVResources> pResources;
   shared_ptr<Table <string, shared_ptr<PVResources> > >
      pSingleThreadResourcesTable;

   // Mark this pv as accessed by the thread
   if(m_threadAccessTable.contains(name))
   {
      int oldSize = m_threadAccessTable.get(name).size();
      m_threadAccessTable.insert(name, tid);
      int newSize = m_threadAccessTable.get(name).size();

      if(oldSize == newSize)
      {
         w() << "TID already in row ("<< name << " -> T1 T2)"<< std::endl;
      }
      else
      {
         w() << "Inserted TID in row ("<< name << " -> T1 T2)" << std::endl;
      }
   }
   else
   {
      m_threadAccessTable.insert(name, tid);

      w() << "Inserted TID in row ("<< name << " -> T1 T2)" << std::endl;
   }


   if(m_threadsResourcesTable.contains(tid))
   {
      w() << "Retrieving PVResourcesTable" << std::endl;
      pSingleThreadResourcesTable = m_threadsResourcesTable.get(tid);
   }
   else
   {

      w() << "Creating PVResourcesTable" << std::endl;
      pSingleThreadResourcesTable =
         shared_ptr <Table <string, shared_ptr<PVResources> > >
            (new Table <string, shared_ptr<PVResources> >);
      m_threadsResourcesTable.insert(tid, pSingleThreadResourcesTable);
   }


   if(pSingleThreadResourcesTable->contains(name))
   {
      w() << "Retrieving PVResources" << std::endl;
      pResources = pSingleThreadResourcesTable->get(name);

   }
   else
   {

      // Get or create a PVResource object
      if(m_sharedResourcesTable.contains(name))
      {
         w() << "Retrieving PVSharedResources" << std::endl;

         pSharedResources = m_sharedResourcesTable.get(name);
      }
      else
      {
         w() << "Creating PVSharedResources" << std::endl;

         pSharedResources = shared_ptr<PVSharedResources>(
            new PVSharedResources(name,this));
         m_sharedResourcesTable.insert(name, pSharedResources);
      }

      w() << "Creating PVResources" << std::endl;
      w() << "Inserting PVResources in table T->("<< name
          <<" -> PVResources*)" << std::endl;
      pResources = shared_ptr<PVResources>(new PVResources(pSharedResources));
      pSingleThreadResourcesTable->insert(name,pResources);
   }

   w() << "Returning a Smart Pointer to a newly created PVInterface"
       << std::endl;
   return boost::shared_ptr<PV>(new PV(pResources));

}

/*---------------------------------------------------------------------------*/

int GlobalRegister::getSharedResourcesNum()
{

	return m_sharedResourcesTable.size();

}

/*---------------------------------------------------------------------------*/

const shared_ptr<PVSharedResources>& GlobalRegister::getSharedResources(
   const string& name)
{

   unique_lock<mutex> lock(m_globalMutex);

   //IndentedWriter w =
   //   Logger::getIndentedWriter("GlobalRegister: getPVSharedResources");

   if(m_sharedResourcesTable.contains(name))
   {
      //w() << "Returning found PVSharedResources" << std::endl;
      return m_sharedResourcesTable.get(name);
   }
   else
   {
      //w() << "PVSharedResources not found, throwing an exception" << std::endl;
      throw ElementNotInTableException();
   }
}

/*---------------------------------------------------------------------------*/

const shared_ptr<PVResources>& GlobalRegister::getResources(
   const string& name,
   const thread::id& tid)
{

   unique_lock<mutex> lock(m_globalMutex);

   IndentedWriter w =
      Logger::getIndentedWriter("GlobalRegister: getPVResources");

   if(m_threadsResourcesTable.contains(tid) == true)
   {

      w() << "Retrieving Thread PV Table" << std::endl;
      shared_ptr <Table <string, shared_ptr<PVResources> > >
         pSingleThreadResourcesTable = m_threadsResourcesTable.get(tid);

      if(pSingleThreadResourcesTable->contains(name))
      {
         w() << "Retrieving PVResources" << std::endl;
         return pSingleThreadResourcesTable->get(name);
      }
      else
      {
         w() << "PVResources not found, throwing an exception" << std::endl;
         throw ElementNotInTableException();
      }
   }
   else
   {
      w() << "Thread PV Table not founcd, throwing an exception" << std::endl;
      throw ElementNotInTableException();
   }

}

/*---------------------------------------------------------------------------*/

const shared_ptr<PVSpecificResources>& GlobalRegister::getSpecificResources(
   const string& name,
   const thread::id& tid)
{

   unique_lock<mutex> lock(m_globalMutex);

   IndentedWriter w =
      Logger::getIndentedWriter("GlobalRegister: getPVSpecificResources");

   if(m_threadsResourcesTable.contains(tid) == true)
   {

      w() << "Retrieving Thread PV Table" << std::endl;
      shared_ptr <Table <string, shared_ptr<PVResources> > >
         pSingleThreadResourcesTable = m_threadsResourcesTable.get(tid);

      if(pSingleThreadResourcesTable->contains(name))
      {
         w() << "Retrieving PVSpecificResources" << std::endl;
         return pSingleThreadResourcesTable->get(name)->getSpecificResources();
      }
      else
      {
         w() << "PVSpecificResources not found, throwing an exception"
             << std::endl;
         throw ElementNotInTableException();
      }
   }
   else
   {
      w() << "Thread PV Table not found, throwing an exception" << std::endl;
      throw ElementNotInTableException();
   }

}

/*---------------------------------------------------------------------------*/

bool GlobalRegister::isLastThread(const string& name)
{
   unique_lock<mutex> lock(m_globalMutex);

   IndentedWriter w =
      Logger::getIndentedWriter("GlobalRegister: isLastThread");

   w() << "Am I the last thread using "<< name << "?" << std::endl;

   if(m_threadAccessTable.contains(name))
   {
      if( m_threadAccessTable.get(name).size() == 1)
      {
         w() << "Yes I am!" << std::endl;
         return true;
      }
      else
      {
         w() << "No I am not!" << std::endl;
         return false;
      }
   }
   else
   {
      w() << "The table does not contain this PVName" << std::endl;
      return false;
   }
}

/*---------------------------------------------------------------------------*/

void GlobalRegister::disposeResources(const string& name)
{

   unique_lock<mutex> lock(m_globalMutex);
   thread::id tid = boost::this_thread::get_id();

   shared_ptr<Table <string, shared_ptr<PVResources> > >
      pSingleThreadResourcesTable;

   IndentedWriter w =
      Logger::getIndentedWriter("GlobalRegister: disposePVResources");

   if(m_threadsResourcesTable.contains(tid))
   {
      w() << "Retrieving PVResources Table" << std::endl;
      pSingleThreadResourcesTable = m_threadsResourcesTable.get(tid);

      //If the thread is using the pv
      if(pSingleThreadResourcesTable->contains(name))
      {
         w() << "Eliminating row (" << name << " -> PVResources*)" << std::endl;
         pSingleThreadResourcesTable->remove(name);

         // If the thread is not using PV anymore
         if(pSingleThreadResourcesTable->empty())
         {
            w() << "PVResourcesTable is empty, removing row" << std::endl;
            // Remove the row
            m_threadsResourcesTable.remove(tid);

         }

      }

   }

   // Mark this pv as not accessed by the thread
   if(m_threadAccessTable.contains(name))
   {
	   std::list<boost::thread::id> threads = m_threadAccessTable.get(name);
       w() << "Removing TID from row (" << name << " -> T1 T2) "
           << threads.size() << "->"<< threads.size() -1 << std::endl;

      m_threadAccessTable.remove(name, tid);

      // No other thread is using this PV
      if(!m_threadAccessTable.contains(name))
      {
         w() << "No other thread is using " << name
             << " , removing PVSharedResources" << std::endl;
         m_sharedResourcesTable.remove(name);
      }
      else
      {
    	  w() << "Another thread is using " << name << std::endl;
      }

   }

}

/*---------------------------------------------------------------------------*/
