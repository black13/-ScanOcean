/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_GLOBALREGISTER_H
#define SSTAR_GLOBALREGISTER_H

/*---------------------------------------------------------------------------*/


#include <list>

#include <mutex>
#include <memory>
#include <thread>

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
   std::shared_ptr<PV> getPV(const std::string& name);

   /**
    * Get the number of shared resources
    *
    * @return Number of shared resources
    */
   int getSharedResourcesNum();

   /**
    * Get Resources
    *
    * @param name PV Name
    * @param tid Thread ID
    *
    * @return Smart-Pointer to the resources
    */
   const std::shared_ptr<PVResources>& getResources(
      const std::string& name,
      const std::thread::id& tid);

   /**
    * Get Shared Resources
    *
    * @param name PV Name
    *
    * @return Smart-Pointer to the resources
    */
   const std::shared_ptr<PVSharedResources>& getSharedResources(
      const std::string& name);

   /**
     * Retrieve a list of share resources
     */
   std::list <std::shared_ptr<PVSharedResources> > getSharedResourcesList();

   /**
    * Get Specific Resources
    *
    * @param name PV Name
    * @param tid Thread ID
    *
    * @return Smart-Pointer to the resources
    */
   const std::shared_ptr<PVSpecificResources>& getSpecificResources(
      const std::string& name,
      const std::thread::id& tid);

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
   std::mutex m_globalMutex;

   /**
    * Table which maps 'PV Names' to 'PV Shared Resources'
    */
   Table<std::string,
         std::shared_ptr<PVSharedResources> > m_sharedResourcesTable;

   /**
    * Table which maps 'Thread ID' to the thread specific PV table.
    * The latter maps 'PV names' to 'PV Resources'
    */
   Table<std::thread::id,
         std::shared_ptr<Table<std::string,
                                 std::shared_ptr<PVResources> > > >
                                    m_threadsResourcesTable;

   /**
    * List Table which maps 'PV Names' to the list of using 'Thread ID'
    */
   ListTable<std::string, std::thread::id> m_threadAccessTable;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
