/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CA_PRINT_TEXT_H
#define SSTAR_CA_PRINT_TEXT_H

/*---------------------------------------------------------------------------*/

#include <cadef.h>
#include <iostream>
#include <handlers/base/CAEventHandler.h>

/*---------------------------------------------------------------------------*/

/**
 * Simple Printing Handler class
 */
class CAPrintText : public CAEventHandler
{

public:

   /**
    * Constructor
    *
    * @param text Text to be printed in case of success
    */
   CAPrintText(std::string text);

   /**
    * Constructor
    */
   CAPrintText(std::string text, struct event_handler_args args);

   /**
    * Print text on standard output
    */
   void onSuccess();

   /**
    * Just prints FAILURE on standard output
    */
   void onFailure();

private:

   /**
    * Text to be printed
    */
   std::string m_text;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
