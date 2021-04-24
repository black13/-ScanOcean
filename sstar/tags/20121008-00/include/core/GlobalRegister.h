/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_GLOBALREGISTER_H
#define SSTAR_GLOBALREGISTER_H

/*---------------------------------------------------------------------------*/

#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include <utils/Table.h>
#include <utils/ListTable.h>

/*---------------------------------------------------------------------------*/

class PV;
class PVSharedResources;
class PVSpecificResources;
class PVResources;

/**
 * Synchronized data structure used to manage the used resources
 */
class GlobalRegister
{

public:

   /**
    * Constructor
    */
   GlobalRegister();

   /**
    * Destructor
    */
   ~GlobalRegister();

   /**
    * Get PV Object
    *
    * @param name PV Name
    *
    * @return PV Smart-Pointer
    */
   boost::shared_ptr<PV> getPV(const std::string& name);

   int getSharedResourcesNum();

   /**
    * Get Resources
    *
    * @param name PV Name
    * @param tid Thread ID
    *
    * @return Smart-Pointer to the resources
    */
   const boost::shared_ptr<PVResources>& getResources(
      const std::string& name,
      const boost::thread::id& tid);

   /**
    * Get Shared Resources
    *
    * @param name PV Name
    *
    * @return Smart-Pointer to the resources
    */
   const boost::shared_ptr<PVSharedResources>& getSharedResources(
      const std::string& name);

   /**
    * Get Specific Resources
    *
    * @param name PV Name
    * @param tid Thread ID
    *
    * @return Smart-Pointer to the resources
    */
   const boost::shared_ptr<PVSpecificResources>& getSpecificResources(
      const std::string& name,
      const boost::thread::id& tid);

   /**
    * Returns true if the current thread is the last one using specific
    * resources
    *
    * @param name PV Name
    *
    * @return True if this is the last thread, false otherwise
    */
   bool isLastThread(const std::string& name);

   /**
    * Dispose the PV Resources for the current thread
    *
    * @param name PV Name
    */
   void disposeResources(const std::string& name);

private:

   /**
    * Global mutex
    */
   boost::mutex m_globalMutex;

   /**
    * Table which maps 'PV Names' to 'PV Shared Resources'
    */
   Table<std::string,
         boost::shared_ptr<PVSharedResources> > m_sharedResourcesTable;

   /**
    * Table which maps 'Thread ID' to the thread specific PV table.
    * The latter maps 'PV names' to 'PV Resources'
    */
   Table<boost::thread::id,
         boost::shared_ptr<Table<std::string,
                                 boost::shared_ptr<PVResources> > > >
                                    m_threadsResourcesTable;

   /**
    * List Table which maps 'PV Names' to the list of using 'Thread ID'
    */
   ListTable<std::string, boost::thread::id> m_threadAccessTable;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
