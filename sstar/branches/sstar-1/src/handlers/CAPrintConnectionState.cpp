/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <iostream>

#include <handlers/CAPrintConnectionState.h>

using std::cout;
using std::endl;

/*---------------------------------------------------------------------------*/

void CAPrintConnectionState::onConnection()
{

   cout << "CONNECTED" << endl;

}

/*---------------------------------------------------------------------------*/

void CAPrintConnectionState::onDisconnection()
{

   cout << "DISCONNECTED" << endl;

}

/*---------------------------------------------------------------------------*/
