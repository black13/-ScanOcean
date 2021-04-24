/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_LISTTABLE_H
#define SSTAR_LISTTABLE_H

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
 *    ListTable implements the interface of the class AbstractTable
 *    It maps a key to a list of elements
 *
 *    K1    |    T1 -> T3 -> T4 -> T5
 *
 *    K2    |    T2 -> T1
 *
 *          ...
 *
 *    Kn    |    Tn -> Tx -> Ty
 */
template <class K, class T>
class ListTable : public AbstractTable<K,T>
{

public:

   /**
    * Insert element T in the list in the row with key K.
    * If the element is already present in the list, do nothing
    *
    * @param key Key
    * @param element Element
    */
   virtual void insert(K key, T element);

   /**
    * Remove the element in the list associated with the key K
    * , otherwise throw an exception
    *
    * @param key Key
    * @param element Element
    *
    * @throw ElementNotInTableException
    */
   virtual void remove(K key, T element);

   /**
    * Return the number of rows in the table
    *
    * @return Number of rows
    */
   virtual int size();

   /**
    * Return true is empty, false otherwise
    *
    * @return True if empty, false otherwise
    */
   virtual bool empty();

   /**
    * Check if the key K is contained in the table
    *
    * @param key Key
    *
    * @return True if it is contained, false otherwise
    */
   virtual bool contains(K key);

   /**
    * Return the element T associated with the key K, otherwise
    * throw an exception
    *
    * @param key Key
    *
    * @return The element associated with the key
    *
    * @throw ElementNotInTableException
    */
   std::list<T> get(K key) const;

   /**
    * Return the element T associated with the key K, otherwise
    * throw an exception
    *
    * @param key Key
    *
    * @return The element associated with the key
    *
    * @throw ElementNotInTableException
    */
   std::list<T>& get(K key);


   /**
    * Print on the output stream passed by reference the
    * table
    */
   template <typename M, typename N>
   friend std::ostream& operator<< (std::ostream& out, ListTable<M,N>& tt );

   protected:

      /**
       * Hash Table
       */
      boost::unordered_map<K,std::list<T> > m_table;

};

/*---------------------------------------------------------------------------*/

template <class M, class N>
std::ostream& operator<< (std::ostream& out, ListTable<M,N>& tt );

/*---------------------------------------------------------------------------*/

template <class K, class T>
void ListTable<K,T>::insert(K key, T element)
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);

   typename boost::unordered_map<K , std::list<T> >::const_iterator
      iter = m_table.find(key);

   if(iter == m_table.end())
   {
      m_table[key].push_back(element);
   }
   else
   {
      std::list<T> list = m_table[key];
      typename std::list<T>::iterator iter =
         std::find(list.begin(),list.end(),element);
      //If not in the list, append it
      if(iter == list.end()) m_table[key].push_back(element);

   }

}

/*---------------------------------------------------------------------------*/

template <class K, class T>
void ListTable<K,T>::remove(K key, T element)
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename boost::unordered_map<K , std::list<T> >::const_iterator
      iter = m_table.find(key);

   //If there is a row for this ID
   if(iter != m_table.end())
   {
	  std::list<T> elements = m_table[key];

      //Remove the element from the list
	  elements.remove(element);
      //If the list becomes empty
      if(elements.empty())
      {
         //Erase the row from the table
         m_table.erase(key);
      }
   }
   else
   {
      //Throw an exception
      throw ElementNotInTableException();
   }

}

/*---------------------------------------------------------------------------*/

template <class K, class T>
int ListTable<K,T>::size()
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);
   return m_table.size();

}

/*---------------------------------------------------------------------------*/

template <class K, class T>
bool ListTable<K,T>::empty()
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);
   return m_table.empty();

}

/*---------------------------------------------------------------------------*/

template <class K, class T>
bool ListTable<K,T>::contains(K key)
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename boost::unordered_map<K , std::list<T> >::const_iterator
      iter = m_table.find(key);

   //If found the list for the currently executing thread
   if(iter != m_table.end()) return true; else return false;

}

/*---------------------------------------------------------------------------*/

template <class K, class T>
std::list<T> ListTable<K,T>::get(K key) const
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename boost::unordered_map<K , std::list<T> >::const_iterator
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
std::list<T>& ListTable<K,T>::get(K key)
{

   boost::unique_lock<boost::mutex> lock(AbstractTable<K,T>::m_mutex);
   typename boost::unordered_map<K , std::list<T> >::const_iterator
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

template <class M, class N>
std::ostream& operator<< (std::ostream& out, ListTable<M,N>& tt )
{

   boost::unique_lock<boost::mutex> lock(tt.m_mutex);
   out << "TABLE" << std::endl;
   out << "-------------------------------------------" << std::endl;

   if(tt.m_table.empty())
   {
      out << "Empty" << std::endl;
   }
   else
   {
      typename boost::unordered_map<M , std::list<N> >::iterator iter;
      for(iter = tt.m_table.begin(); iter != tt.m_table.end(); ++iter)
      {
         out << iter->first << "\t";
         typename std::list<N >::iterator i;
         for(i = iter->second.begin(); i != iter->second.end(); ++i)
         {
            N e = (N) *i;
            out << e << " -> ";
         }
         out << std::endl;
      }
   }

   out << "-------------------------------------------" << std::endl;
   return out;

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
