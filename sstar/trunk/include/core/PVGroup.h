/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_PV_GROUP_H
#define SSTAR_PV_GROUP_H

/*---------------------------------------------------------------------------*/

#include <list>

#include <memory>
#include <mutex>
#include <unordered_set>

#include <handlers/base/CAConnectionHandler.h>

/*---------------------------------------------------------------------------*/

class PV;
class CAUpdateGroupState;

/*---------------------------------------------------------------------------*/

/**
 * Class Used to get notifications about the connection state of a group of
 * PV.
 * OnConnection is called only when all the PV are connected.
 * OnDisconnection is called as soon as at least one PV is down.
 */
class PVGroup
{

public:

   /**
    * Constructor
    */
   PVGroup();

   /**
    * Destructor
    */
   ~PVGroup();

   /**
    * Get group connection state
    *
    * @return True is the group is connected, false otherwise
    */
   bool isGroupConnected();

   /**
    * Add PV to the list of PV-of-interest
    */
   void addPV(const std::shared_ptr<PV>& pv);

   /**
    * Finalize the PV Group. No more PV can be added to the group
    */
   void finalize();

   /**
    * Subscribe to a connection event - TODO execute on bind
    */
   void subscribeConnectionEvent(CAConnectionHandler* pHandler);

   /**
    * Friend Handler Class
    */
   friend class CAUpdateGroupState;

private:

   /**
    * Group connection state
    */
   bool m_isGroupConnected;

   /**
    * Number of PV in the group
    */
   int m_totalPV;

   /**
    * True is the group is finalized, false otherwise
    */
   bool m_isFinalized;

   /**
    * Connection subscription - TODO make multiple subscriptions possible
    */
   CAConnectionHandler* m_pHandler;

   /**
    * Subscription list, used during the building-phase
    */
   std::list<std::pair<std::shared_ptr<PV>, CAUpdateGroupState*> >
      m_subscriptionList;

   /**
    * Set of connected PV
    */
   std::unordered_set<std::string> m_connectedPVSet;

   /**
    * Group recursive mutex
    */
   std::recursive_mutex m_mutex;

};

/*---------------------------------------------------------------------------*/

/**
 * Handler used to update the state of the group
 */
class CAUpdateGroupState : public CAConnectionHandler
{

public:

   /**
    * Constructor
    *
    * @param name PV Name
    * @param pGroup Pointer to the PVGroup object
    */
   CAUpdateGroupState(const std::string& name, PVGroup* pGroup);

   /**
    * On connection function
    */
   void onConnection();

   /**
    * On disconnection function
    */
   void onDisconnection();

private:

   /**
    * PV name
    */
   std::string m_name;

   /**
    * Pointer to the group
    */
   PVGroup* m_pGroup;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
