/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CA_PRINT_CONNECTIONSTATE_H
#define SSTAR_CA_PRINT_CONNECTIONSTATE_H

/*---------------------------------------------------------------------------*/

#include <handlers/base/CAConnectionHandler.h>

/*---------------------------------------------------------------------------*/

/**
 * Example of concrete implementation of a connection handler, which
 * just prints the change in connection state on the standard output
 */
class CAPrintConnectionState : public CAConnectionHandler
{

public:

   /**
    * Prints on standard output "CONNECTED"
    */
   void onConnection();

   /**
    * Prints on standard output "DISCONNECTED"
    */
   void onDisconnection();

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
