#ifndef SSTAR_CA_CONNECTION_CALLBACK_H
#define SSTAR_CA_CONNECTION_CALLBACK_H

/*---------------------------------------------------------------------------*/

#include <handlers/base/CAConnectionHandler.h>

#include <cadef.h>
#include <scan/Scan.h>

/*---------------------------------------------------------------------------*/

class CAConnectionCallback
:  public CAConnectionHandler
{

public:

   CAConnectionCallback(Scan* op, void (Scan::*fptr) (bool));

   void onConnection();

   void onDisconnection();

private:

   Scan* m_scan;

   void (Scan::*cb) (bool);

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/


