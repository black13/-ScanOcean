/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CA_EXCEPTION_HANDLER_H
#define SSTAR_CA_EXCEPTION_HANDLER_H

/*---------------------------------------------------------------------------*/

#include <cadef.h>

#include <handlers/base/CANegativeOutcomeHandler.h>
#include <handlers/base/CAParamHandler.h>

/*---------------------------------------------------------------------------*/

/**
 * This class can be used to implement exception handlers and provides
 * already dummy implementation (do nothing).
 */
class CAExceptionHandler
: public CANegativeOutcomeHandler,
  public CAParamHandler<struct exception_handler_args>
{

public:

   /**
    * Constructor without params
    */
   CAExceptionHandler();

   /**
    * Constructor with params
    */
   CAExceptionHandler(struct exception_handler_args);

   /**
    * Function executed in case of a failure (exception is always considered
    * as a failure) (do nothing implementation)
    */
   virtual void onFailure();

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
