/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CHANNEL_ACCESS_H
#define SSTAR_CHANNEL_ACCESS_H

/*---------------------------------------------------------------------------*/

#include <list>
#include <boost/thread/mutex.hpp>

/*---------------------------------------------------------------------------*/

class PV;
class GlobalRegister;
class ca_client_context;
class PVSharedResources;

/**
 * ChannelAccess class is the entry point for every kind of interaction with
 * EPICS
 *
 * Uses:
 * - Get PV objects
 * - Register global-event handlers (e.g. exceptions)
 *
 * Features:
 * - Singleton
 * - ThreadSafe
 */
class ChannelAccess
{

public:

   /**
    * Get singleton instance of ChannelAccess
    */
	static ChannelAccess* getInstance();

   /**
    * Retrieve a boost Smart-Pointer to a PV object
    *
    * @param name String representation (e.g <ioc:m1.VAL>) of the PV
    *
    * @param attempts If 'attempts' is > 0 an 'attempts' number of attemps
    *                 is performed, each of duration 'timeoutSeconds' before
    *                 throwing an Exception.
    *                 If 'attempts' is 0, there will be only one attempt
    *                 of connection and no exception is thrown. If the
    *                 connection cannot be established, the returned
    *                 PV object will be in a DISCONNECTED state.
    *
    * @param timeoutSeconds Number of seconds before a timeout
    *
    * @throw ChannelAccessException Occurs when something goes wrong with the
    *                               connection attempt
    *
    * @return Smart-pointer to a PV Object
    */
	boost::shared_ptr<PV> getPV(const std::string& name,
	                            int attempts = 0,
	                            long timeoutSeconds = 5);

	/**
    * Flushes all the requests on the network
    */
   void flush();

   /**
    *
    */
   std::list<boost::shared_ptr<PVSharedResources> > getSharedResourcesList();

private:

   /**
    * Private Constructor
    */
	ChannelAccess();

	/**
	 * Declaration of the copy-constructor to make the object uncopyble
	 */
	ChannelAccess(const ChannelAccess&);

	/**
	 * Declaration of the assignment operator to make the object uncopyble
	 */
	ChannelAccess& operator=(const ChannelAccess&);

	/**
	 * Init Channel Access accessory function
	 */
	void initChannelAccess();

	/**
	 * EPICS exception callback
	 */
   static void exceptionCallback(struct exception_handler_args args);

private:

   /**
    * Singleton static pointer to the instance
    */
	static ChannelAccess* s_pInstance;

	/**
	 * Singleton mutex
	 */
   static boost::mutex s_singletonMutex;

   /**
    * Global Register
    */
   GlobalRegister* m_pGlobalRegister;

   /**
    * Channel Access context
    */
   static ca_client_context* m_pContext;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
