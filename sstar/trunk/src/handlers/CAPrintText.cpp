/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <handlers/CAPrintText.h>

/*---------------------------------------------------------------------------*/

CAPrintText::CAPrintText(std::string text)
: CAEventHandler()
{

   m_text = text;

}

/*---------------------------------------------------------------------------*/

CAPrintText::CAPrintText(std::string text, struct event_handler_args args)
: CAEventHandler(args)
{

   m_text = text;

}

/*---------------------------------------------------------------------------*/

void CAPrintText::onSuccess ()
{

   std::cout << m_text.c_str() << std::endl;

}

/*---------------------------------------------------------------------------*/

void CAPrintText::onFailure ()
{

   std::cout << "FAILURE" << std::endl;

}

/*---------------------------------------------------------------------------*/
