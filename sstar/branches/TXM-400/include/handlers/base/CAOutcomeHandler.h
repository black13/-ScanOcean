/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CA_OUTCOME_HANDLER_H
#define SSTAR_CA_OUTCOME_HANDLER_H

/*---------------------------------------------------------------------------*/

#include <handlers/base/CAPositiveOutcomeHandler.h>
#include <handlers/base/CANegativeOutcomeHandler.h>

/*---------------------------------------------------------------------------*/

/**
 * This class groups the two different interfaces of outcome handlers in one
 */
class CAOutcomeHandler
: public CAPositiveOutcomeHandler,
  public CANegativeOutcomeHandler
{

public:

   /**
    * Abstract Function to be executed in case of a success
    */
   virtual void onSuccess() = 0;

   /**
    * Abstract Function to be executed in case of a failure
    */
   virtual void onFailure() = 0;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
