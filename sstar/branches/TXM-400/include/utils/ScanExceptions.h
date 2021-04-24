/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_SCAN_EXCEPTIONS_H
#define SSTAR_SCAN_EXCEPTIONS_H

/*---------------------------------------------------------------------------*/

#include <exception>

/*---------------------------------------------------------------------------*/

enum ScanExceptionCode
{
   SCAN_ABORT  =   24
};

/*---------------------------------------------------------------------------*/

/**
 *    Abstract Scan Exception
 */
class ScanException : public std::exception
{

public:

   virtual const char* what() const throw() = 0;

};

/*---------------------------------------------------------------------------*/

/**
 *    Scan Abort Exception
 */
class ScanAbortException : public ScanException
{

public:

   virtual const char* what() const throw()
   {
      return "Scan was aborted";
   }

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
