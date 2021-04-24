#ifndef SSTAR_CA_CALLBACK_H
#define SSTAR_CA_CALLBACK_H


#include <cadef.h>
#include <handlers/base/CAEventHandler.h>
#include <scan/Scan.h>

class CACallback 
:  public CAEventHandler
{

public:

   CACallback(Scan* op, 
              void (Scan::*fptr) (bool));

   virtual void onSuccess();

   virtual void onFailure();

private:

  Scan* m_scan;

   void (Scan::*cb) (bool);

};


#endif
