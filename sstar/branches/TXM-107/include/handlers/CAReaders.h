/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CA_GET_TOTAL_COPY_H
#define SSTAR_CA_GET_TOTAL_COPY_H

/*---------------------------------------------------------------------------*/

#include <cadef.h>
#include <handlers/base/CAEventHandler.h>

#include <iostream>

/*---------------------------------------------------------------------------*/

/**
 * Once a get operation is finished (asynchronous or synchronous) the
 * onSuccess function copies all the data to the specified memory location
 * , provided as a pointer in the constructor
 *
 * The class is a template class, so to handle the different data type
 */

template <class T>
class CAGetTotalCopy : public CAEventHandler
{

public:

   /**
    * Constructor
    *
    * @param data Pointer to the memory location where to write the
    *             data
    */
   CAGetTotalCopy(T* data);

   /**
    * Constructor
    *
    * @param data Pointer to the memory location where to write the
    *                data
    * @param args Epics arg
    */
   CAGetTotalCopy(T* data, struct event_handler_args args);

   /**
    * onSuccess performs a total copy of the data obtained from
    * Channel Access to the provided memory location
    */
   virtual void onSuccess();

   /**
    * Dummy implementation
    */
   virtual void onFailure();

private:

   /**
    * Data
    */
   T* m_data;

};

/*---------------------------------------------------------------------------*/

template <class T>
CAGetTotalCopy<T>::CAGetTotalCopy(T* data)
: CAEventHandler(),
  m_data(data)
{

}

/*---------------------------------------------------------------------------*/

template <class T>
CAGetTotalCopy<T>::CAGetTotalCopy(T* data, struct event_handler_args args)
: CAEventHandler(args),
  m_data(data)
{

}

/*---------------------------------------------------------------------------*/

template <class T>
void CAGetTotalCopy<T>::onSuccess()
{

   chid pCh = m_args.chid;
   T* data = ((T*) m_args.dbr);

   int numBytes = dbr_size_n(m_args.type, m_args.count);
   int n = numBytes / sizeof(T);

   memcpy(m_data,data,numBytes);

}

/*---------------------------------------------------------------------------*/

template <class T>
void CAGetTotalCopy<T>::onFailure()
{

}

//TODO - Write other reader implementations

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
