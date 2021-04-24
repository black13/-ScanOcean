#include <scan/CACallback.h>


CACallback::CACallback(Scan* scan, 
                       void (Scan::*fptr) (bool))
{

   m_scan = scan;
   cb = fptr;

}


void CACallback::onSuccess()
{

   (m_scan->*cb)(true);

}

void CACallback::onFailure()
{

   (m_scan->*cb)(false);

}
