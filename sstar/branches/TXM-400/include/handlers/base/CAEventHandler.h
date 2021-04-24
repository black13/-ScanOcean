/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CA_EVENT_HANDLER_H
#define SSTAR_CA_EVENT_HANDLER_H

/*---------------------------------------------------------------------------*/

#include <cadef.h>

#include <handlers/base/CAOutcomeHandler.h>
#include <handlers/base/CAParamHandler.h>

/*---------------------------------------------------------------------------*/

/**
 * This class can be used to implement subscription handlers and provides
 * already a dummy implementation (do nothing).
 */
class CAEventHandler
: public CAOutcomeHandler,
  public CAParamHandler<struct event_handler_args>
{

public:

   /**
    * Constructor without params
    */
   CAEventHandler();

   /**
    * Constructor with params
    */
   CAEventHandler(struct event_handler_args args);

   /**
    * Function to be executed in case of a success (do nothing implementation)
    */
   virtual void onSuccess();

   /**
    * Function to be executed in case of a failure (do nothing implementation)
    */
   virtual void onFailure();

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
