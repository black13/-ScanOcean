/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <handlers/base/CAEventHandler.h>

/*---------------------------------------------------------------------------*/

CAEventHandler::CAEventHandler()
:
CAParamHandler<struct event_handler_args>()
{

}

/*---------------------------------------------------------------------------*/

CAEventHandler::CAEventHandler(struct event_handler_args args)
:
CAParamHandler<struct event_handler_args>(args)
{

}

/*---------------------------------------------------------------------------*/

void CAEventHandler::onSuccess()
{
   //Dummy implementation
}

/*---------------------------------------------------------------------------*/

void CAEventHandler::onFailure()
{
   //Dummy implementation
}

/*---------------------------------------------------------------------------*/
