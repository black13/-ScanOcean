/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <handlers/base/CAExceptionHandler.h>

/*---------------------------------------------------------------------------*/

CAExceptionHandler::CAExceptionHandler()
:
CAParamHandler<struct exception_handler_args>()
{

}

/*---------------------------------------------------------------------------*/

CAExceptionHandler::CAExceptionHandler(struct exception_handler_args args)
:
CAParamHandler<struct exception_handler_args>(args)
{

}

/*---------------------------------------------------------------------------*/

void CAExceptionHandler::onFailure()
{
   //Dummy implementation
}

/*---------------------------------------------------------------------------*/
