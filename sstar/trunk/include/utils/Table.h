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

#include <unordered_map>
#include <mutex>

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
    * Retrieve a list of the values stored in the table
    */
   std::list<T> getValues();

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
   std::unordered_map<K, T> m_table;

};

/*---------------------------------------------------------------------------*/

template <typename M, typename N>
std::ostream& operator<< (std::ostream& out, Table<M,N>& tt );

/*---------------------------------------------------------------------------*/

template <class K, class T>
void Table<K,T>::insert(K key, T element)
{

   std::unique_lock<std::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename std::unordered_map<K ,T>::const_iterator
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

   std::unique_lock<std::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename std::unordered_map<K , T >::const_iterator
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

   std::unique_lock<std::mutex> lock(AbstractTable<K,T>::m_mutex);
   return m_table.size();

}

/*---------------------------------------------------------------------------*/

template <class K, class T>
bool Table<K,T>::empty()
{

   std::unique_lock<std::mutex> lock(AbstractTable<K,T>::m_mutex);
   return m_table.empty();

}

/*---------------------------------------------------------------------------*/

template <class K, class T>
bool Table<K,T>::contains(K key)
{

   std::unique_lock<std::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename std::unordered_map<K , T >::const_iterator
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

   std::unique_lock<std::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename std::unordered_map<K , T >::const_iterator
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

   std::unique_lock<std::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename std::unordered_map<K , T >::const_iterator
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

   std::unique_lock<std::mutex> lock(tt.m_mutex);

   out << "TABLE (" << tt.m_table.size() << " elements) "<< std::endl;
   out << "-------------------------------------------" << std::endl;
   if(tt.m_table.empty())
   {
      out << "Empty" << std::endl;
   }
   else
   {
      for(typename std::unordered_map<M, N >::iterator
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

template <class K, class T>
std::list<T> Table<K,T>::getValues(){

   std::unique_lock<std::mutex> lock(AbstractTable<K,T>::m_mutex);
   std::list<T> values;
   typename std::unordered_map<K , T >::iterator
      iter;

   for (iter=m_table.begin(); iter != m_table.end(); iter++){
      values.push_back(iter->second);
   }


   return values;
}

/*---------------------------------------------------------------------------*/

#endif 

/*---------------------------------------------------------------------------*/
