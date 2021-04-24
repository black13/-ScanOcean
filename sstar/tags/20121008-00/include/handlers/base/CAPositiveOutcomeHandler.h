/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CA_POSITIVE_OUTCOME_HANDLER_H
#define SSTAR_CA_POSITIVE_OUTCOME_HANDLER_H

/*---------------------------------------------------------------------------*/

#include <handlers/base/CAHandler.h>

/*---------------------------------------------------------------------------*/

/**
 * Abstract class which provides the interface for the onSuccess
 * function
 */
class CAPositiveOutcomeHandler : public CAHandler
{

public:

   /**
    * Abstract Function to be executed in case of a success
    */
   virtual void onSuccess() = 0;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
