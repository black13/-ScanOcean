/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_EPICS_CALLBACKS_H
#define SSTAR_EPICS_CALLBACKS_H

/*---------------------------------------------------------------------------*/

#include <cadef.h>

/*---------------------------------------------------------------------------*/

class CAConnectionHandler;

/**
 * Epics PV Static Callbacks
 */
class EpicsCallbacks
{

public:

   /**
    * Epics Get Callback
    *
    * @param args Epics event_handler_args
    */
   static void getCallback(struct event_handler_args args);

   /**
    * Epics Put Callback
    *
    * @param args Epics event_handler_args
    */
   static void putCallback(struct event_handler_args args);

   /**
    * Epics Connection Callback
    *
    * @param args Epics struct connection_handler_args
    */
   static void connectionCallback(struct connection_handler_args args);

   /**
    * Epics Alarm Callback
    *
    * @param args Epics event_handler_args
    */
   static void alarmCallback(struct event_handler_args args);

   /**
    * Epics DataChange Callback
    *
    * @param args Epics event_handler_args
    */
   static void dataChangedCallback(struct event_handler_args args);

private:

   /**
    * Executes onConnection()
    */
   static void executeConnectionHandler(CAConnectionHandler* pHandler);

   /**
    * Executes onDisconnection()
    */
   static void executeDisconnectionHandler(CAConnectionHandler* pHandler);

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
