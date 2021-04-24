/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_TABLE_H
#define SSTAR_TABLE_H

/*---------------------------------------------------------------------------*/

#include <iostream>
#include <exception>
#include <list>

#include <utils/AbstractTable.h>

#include <boost/functional/hash.hpp>
#include <boost/unordered_map.hpp>
#include <boost/thread/mutex.hpp>

/*---------------------------------------------------------------------------*/

/**
 *    Table implements the interface of the class AbstractTable
 *
 *    K1    |    T1
 *
 *    K2    |    T2
 *
 *          ...
 *
 *    Kn    |    Tn
 *
 */
template <class K, class T>
class Table : public AbstractTable<K,T>
{

public:

   /**
    *    Insert element T at the row with key K. If the row is
    *    already present, do nothing
    *
    *    @param key Key
    *    @param element Element
    */
   virtual void insert(K key, T element);

   /**
    *    Remove the element associated with the key K
    *
    *    @param key Key
    *
    *    @throw ElementNotInTableException
    */
   virtual void remove(K key);

   /**
    *    Return the number of rows in the table
    *
    *    @return Number of rows
    */
   virtual int size();

   /**
    *    Return true is empty, false otherwise
    *
    *    @return True if empty, false otherwise
    */
   virtual bool empty();

   /**
    *    Check if the key K is contained in the table
    *
    *    @param key Key
    *
    *    @return True if it is contained, false otherwise
    */
   virtual bool contains(K key);

   /**
    *    Return the element T associated with the key K
    *
    *    @param key Key
    *
    *    @return The element associated with the key
    *
    *    @throw ElementNotInTableException
    */
   T get(K key) const;

   /**
    *    Return the element T associated with the key K
    *
    *    @param key Key
    *
    *    @return The element associated with the key
    *
    *    @throw ElementNotInTableException
    */
   T& get(K key);

   /**
    *    Print on the output stream passed by reference the
    *    table
    *
    */
   template <typename M, typename N>
   friend std::ostream& operator<< (std::ostream& out, Table<M,N>& tt );

protected:

   /**
    *    HashTable Object
    */
   boost::unordered_map<K,T > m_table;

};

/*---------------------------------------------------------------------------*/

template <typename M, typename N>
std::ostream& operator<< (std::ostream& out, Table<M,N>& tt );

/*---------------------------------------------------------------------------*/

template <class K, class T>
void Table<K,T>::insert(K key, T element)
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename boost::unordered_map<K ,T >::const_iterator
      iter = m_table.find(key);

   if(iter == m_table.end())
   {
      m_table[key] = element;
   }

}

/*---------------------------------------------------------------------------*/

template <class K, class T>
void Table<K,T>::remove(K key)
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename boost::unordered_map<K , T >::const_iterator
      iter = m_table.find(key);
   //If there is a row for this ID
   if(iter != m_table.end())
   {
         m_table.erase(key);
   }
   else
   {
      throw ElementNotInTableException();
   }

}

/*---------------------------------------------------------------------------*/

template <class K, class T>
int Table<K,T>::size()
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);
   return m_table.size();

}

/*---------------------------------------------------------------------------*/

template <class K, class T>
bool Table<K,T>::empty()
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);
   return m_table.empty();

}

/*---------------------------------------------------------------------------*/

template <class K, class T>
bool Table<K,T>::contains(K key)
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename boost::unordered_map<K , T >::const_iterator
      iter = m_table.find(key);

   //If found the list for the currently executing thread
   if(iter != m_table.end())
   {
      return true;
   }
   else return false;

}

/*---------------------------------------------------------------------------*/

template <class K, class T>
T Table<K,T>::get(K key) const
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename boost::unordered_map<K , T >::const_iterator
      iter = m_table.find(key);

   //If found the list for the currently executing thread
   if(iter != m_table.end())
   {
      //Return it
      return m_table[key];
   }
   else
   {
      //Throw an exception
      throw ElementNotInTableException();
   }

}

/*---------------------------------------------------------------------------*/

template <class K, class T>
T& Table<K,T>::get(K key)
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename boost::unordered_map<K , T >::const_iterator
      iter = m_table.find(key);
   //If found the list for the currently executing thread
   if(iter != m_table.end())
   {
      //Return it
      return m_table[key];
   }
   else
   {
      //Throw an exception
      throw ElementNotInTableException();
   }

}

/*---------------------------------------------------------------------------*/

template <typename M, typename N>
std::ostream& operator<< (std::ostream& out, Table<M,N>& tt )
{

   boost::unique_lock<boost::mutex> lock(tt.m_mutex);

   out << "TABLE (" << tt.m_table.size() << " elements) "<< std::endl;
   out << "-------------------------------------------" << std::endl;
   if(tt.m_table.empty())
   {
      out << "Empty" << std::endl;
   }
   else
   {
      for(typename boost::unordered_map<M, N >::iterator
          i = tt.m_table.begin();
          i != tt.m_table.end();
          ++i)
      {
            out << i->first << "\t";
            out << i->second << std::endl;
      }
   }
   out << "-------------------------------------------" << std::endl;
   return out;

}

/*---------------------------------------------------------------------------*/

#endif 

/*---------------------------------------------------------------------------*/
