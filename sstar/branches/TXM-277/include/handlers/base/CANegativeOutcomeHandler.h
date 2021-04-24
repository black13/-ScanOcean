/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CA_NEGATIVE_OUTCOME_HANDLER_H
#define SSTAR_CA_NEGATIVE_OUTCOME_HANDLER_H

/*---------------------------------------------------------------------------*/

#include <handlers/base/CAHandler.h>

/*---------------------------------------------------------------------------*/

/**
 * Abstract class which provides the interface for the onFailure
 * function
 */
class CANegativeOutcomeHandler : public CAHandler
{

public:

   /**
    * Abstract Function to be executed in case of a failure
    */
   virtual void onFailure() = 0;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
