#include <scan/CAConnectionCallback.h>

/*---------------------------------------------------------------------------*/

CAConnectionCallback::CAConnectionCallback(Scan* scan,
                                           void (Scan::*fptr) (bool))
{
   m_scan = scan;
   cb = fptr;
}

/*---------------------------------------------------------------------------*/

void CAConnectionCallback::onConnection()
{

   (m_scan->*cb)(true);

}

/*---------------------------------------------------------------------------*/

void CAConnectionCallback::onDisconnection()
{

   (m_scan->*cb)(false);

}

/*---------------------------------------------------------------------------*/


