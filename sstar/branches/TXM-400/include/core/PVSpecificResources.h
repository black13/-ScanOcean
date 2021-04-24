/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_PV_SPECIFIC_RESOURCES_H
#define SSTAR_PV_SPECIFIC_RESOURCES_H

/*---------------------------------------------------------------------------*/

#include <boost/thread/condition_variable.hpp>

/*---------------------------------------------------------------------------*/

/**
 * Class encapsulating thread specific PV Resources
 */
class PVSpecificResources
{

public:

   /**
    * Constructor
    */
   PVSpecificResources();

   /**
    * Get synchronous get condition variable
    *
    * @return Condition variable
    */
   boost::condition_variable& getGetCV();

   /**
    * Get synchronous put condition variable
    *
    * @return Condition variable
    */
   boost::condition_variable& getPutCV();

   /**
    * Get pending requests condition variable
    *
    * @return Condition variable
    */
   boost::condition_variable& getPendingRequestsCV();

   /**
    * Get outcome of the last put
    *
    * @return Outcome
    */
   bool getLastPutOutcome();

   /**
    * Get outcome of the last get
    *
    * @return Outcome
    */
   bool getLastGetOutcome();

   /**
    * Get the number of pending request
    *
    * @return Pending requests
    */
   int getPendingRequests();

   /**
    * Return true if there are pending requests
    *
    * @return True if there are pending requests, false otherwise
    */
   bool arePendingRequests();

   /**
    * Increment number of pending requests
    */
   void incrementPendingRequests();

   /**
    * Decrement number of pending requests
    */
   void decrementPendingRequests();

   /**
    * Set value of the last put outcome
    *
    * @param value Outcome
    */
   void setLastPutOutcome(bool value);

   /**
    * Set value of the last get outcome
    *
    * @param value Outcome
    */
   void setLastGetOutcome(bool value);

   /**
    * Get the number of retrieved PV
    *
    * @return Number of referenced PV
    */
   int interfacesCount();

   /**
    * Increment the number of retrieved PV
    */
   void incrementInterfacesCount();

   /**
    * Decrement the number of retrieved PV
    */
   void decrementInterfacesCount();

private:

   /**
    * SynGet Condition Variable
    */
   boost::condition_variable m_synGetCV;

   /**
    * SynPut Condition Variable
    */
   boost::condition_variable m_synPutCV;

   /**
    * Pending Requests condition variable
    */
   boost::condition_variable m_pendingRequestsCompletionCV;

   /**
    * Last put outcome
    */
   bool m_bSuccessfulPut;

   /**
    * Last get outcome
    */
   bool m_bSuccessfulGet;

   /**
    * Total number of pending requests
    */
   int m_totalPendingRequests;

   /**
    * Number of retrieved PV objects
    */
   int m_referenceCount;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
