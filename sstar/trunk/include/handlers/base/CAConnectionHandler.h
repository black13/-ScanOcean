/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CA_CONNECTION_HANDLER_H
#define SSTAR_CA_CONNECTION_HANDLER_H

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

/**
 * A connection handler is executed by the connection callback when registered
 */
class CAConnectionHandler
{

public:

   /**
    * Function executed by the connection callback in case of a
    * connection event
    */
   virtual void onConnection() = 0;

   /**
    * Function executed by the connection callback in case of a
    * disconnection event
    */
   virtual void onDisconnection() = 0;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
