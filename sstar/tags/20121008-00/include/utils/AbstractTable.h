/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_ABSTRACTTABLE_H
#define SSTAR_ABSTRACTTABLE_H

/*---------------------------------------------------------------------------*/

#include <iostream>
#include <exception>

#include <boost/thread/mutex.hpp>

/*---------------------------------------------------------------------------*/

/**
 *    AbstractTable is a class which provides the basic interface for
 *    other concrete table classes
 */
template <class K, class T>
class AbstractTable
{

public:

   /**
    *    Insert element T at the row with key K
    *
    *    @param key Key
    *    @param element Element
    */
   virtual void insert(K key, T element) = 0;

   /**
    *    Return the number of rows in the table
    *
    *    @return Number of rows
    */
   virtual int size() = 0;

   /**
    *    Return true is empty, false otherwise
    *
    *    @return True if empty, false otherwise
    */
   virtual bool empty() = 0;

   /**
    *    Check if the key K is contained in the table
    *
    *    @param key Key
    *
    *    @return True if it is contained, false otherwise
    */
   virtual bool contains(K key) = 0;

protected:

   /**
    *    Mutex for synchronization
    */
   boost::mutex m_mutex;      //TODO synchronization not needed anymore

};

/*---------------------------------------------------------------------------*/

/**
 *    Basic exception that occurs when the element is not found
 *    in an AbstractTable
 */
class ElementNotInTableException : public std::exception {

public:

   virtual const char* what() const throw()
   {

      return "Not in table";

   }

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
