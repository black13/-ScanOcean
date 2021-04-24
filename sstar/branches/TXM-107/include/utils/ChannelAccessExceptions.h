/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CA_EXCEPTIONS_H
#define SSTAR_CA_EXCEPTIONS_H

/*---------------------------------------------------------------------------*/

#include <exception>

/*---------------------------------------------------------------------------*/

enum CAExceptionCode
{
   VIRTUAL_CIRCUIT_DISCONNECT   =   24
};

/*---------------------------------------------------------------------------*/

/**
 *    Abstract Channel Access Exception
 */
class ChannelAccessException : public std::exception
{

public:

   virtual const char* what() const throw() = 0;

};

/*---------------------------------------------------------------------------*/

/**
 *    TimeoutException Exception
 */
class TimeoutException : public ChannelAccessException
{

public:

   virtual const char* what() const throw()
   {
      return "ECA_TIMEOUT";
   }

};

/*---------------------------------------------------------------------------*/

/**
 *    ChannelDisconnectedException Exception
 */
class ChannelDisconnectedException : public ChannelAccessException
{

public:

   virtual const char* what() const throw()
   {
      return "ECA_DISCONN";
   }

};

/*---------------------------------------------------------------------------*/

/**
 *    ChannelNotBound Exception
 */
class ChannelNotBoundException : public ChannelAccessException
{

public:

   virtual const char* what() const throw()
   {
      return "Channel Not Bound";
   }

};

/*---------------------------------------------------------------------------*/

/**
 *    ChannelDisconnectedException Exception
 */
class BadTypeException : public ChannelAccessException
{

public:

   virtual const char* what() const throw()
   {
      return "ECA_BADTYPE";
   }

};

/*---------------------------------------------------------------------------*/

/**
 *    StrTooBigException Exception
 */
class StrTooBigException : public ChannelAccessException
{

public:
   virtual const char* what() const throw()
   {
      return "ECA_STRTOBIG";
   }

};

/*---------------------------------------------------------------------------*/

/**
 *    MemoryAllocationException Exception
 */
class MemoryAllocationException : public ChannelAccessException
{

public:

   virtual const char* what() const throw()
   {
      return "ECA_ALLOCMEM";
   }

};

/*---------------------------------------------------------------------------*/

/**
 *    BadChidException Exception
 */
class BadChidException : public ChannelAccessException
{

public:

   virtual const char* what() const throw()
   {
      return "ECA_BADCHID";
   }

};

/*---------------------------------------------------------------------------*/

/**
 *    BadCountException Exception
 */
class BadCountException : public ChannelAccessException
{

public:
   virtual const char* what() const throw()
   {
      return "ECA_BADCOUNT";
   }

};

/*---------------------------------------------------------------------------*/

/**
 *    WriteAccessException Exception
 */
class WriteAccessException : public ChannelAccessException
{

public:

   virtual const char* what() const throw()
   {
      return "ECA_NOWTACCESS";
   }

};

/*---------------------------------------------------------------------------*/

/**
 *    AddFail Exception
 */
class AddFailException : public ChannelAccessException
{

public:

   virtual const char* what() const throw()
   {
      return "ECA_ADDFAIL";
   }

};

/*---------------------------------------------------------------------------*/

/**
 *    CANotInstaciated Exception
 */
class CANotInstaciatedException : public ChannelAccessException
{

public:

   virtual const char* what() const throw()
   {
      return "CA is not instanciated";
   }

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
