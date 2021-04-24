/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef QUEUE_H
#define QUEUE_H

/*---------------------------------------------------------------------------*/

#include <boost/thread.hpp>
#include <queue>

/*---------------------------------------------------------------------------*/

/**
 * @brief Thread safe queue
 */
template <class T>
class Queue
{

public:

   /**
    * Constructor.
    */
   Queue();

   /**
    * Constructor.
    *
    * @param queue - queue to copy
    */
   Queue(Queue const& queue);

   /**
    * Destructor.
    */
   ~Queue();

   /**
    * Check if queue is empty.
    *
    * @return true, if queue is empty, otherwise, false.
    */
   bool empty();

   /**
    * Push an item on the queue.
    *
    * @param item -
    */
   void push(T item);

   /**
    * Pop an item from the queue. If no item is available return false.
    *
    * @param item -
    * @return
    */
   bool tryPop(T& item);

   /**
    * Pop an item from the queue. Block until an item is available.
    *
    * @param item -
    */
   void waitPop(T& item);

private:

   // Mutex variable
   boost::mutex m_mutex;

   // Condition variable
   boost::condition_variable m_cond;

   // Data queue
   std::queue<T> m_queue;

};

/*---------------------------------------------------------------------------*/

template <class T>
Queue<T>::Queue()
{

}

/*---------------------------------------------------------------------------*/

template <class T>
Queue<T>::Queue(Queue const& queue)
{

   boost::lock_guard<boost::mutex> lock(m_mutex);
   m_queue = queue.m_queue;

}

/*---------------------------------------------------------------------------*/

template <class T>
Queue<T>::~Queue()
{

}

/*---------------------------------------------------------------------------*/

template <class T>
bool Queue<T>::empty()
{

   boost::lock_guard<boost::mutex> lock(m_mutex);
   return m_queue.empty();

}

/*---------------------------------------------------------------------------*/

template <class T>
void Queue<T>::push(T item)
{

   boost::lock_guard<boost::mutex> lock(m_mutex);
   m_queue.push(item);
   m_cond.notify_all();

}

/*---------------------------------------------------------------------------*/

template <class T>
bool Queue<T>::tryPop(T& item)
{

   boost::lock_guard<boost::mutex> lock(m_mutex);

   if(m_queue.empty()) {
       return false;
   }

   item = m_queue.front();

   m_queue.pop();

   return true;

}

/*---------------------------------------------------------------------------*/

template <class T>
void Queue<T>::waitPop(T& item)
{

   boost::unique_lock<boost::mutex> lock(m_mutex);

   while (m_queue.empty()) {
      m_cond.wait(lock);
   }

   item = m_queue.front();

   m_queue.pop();

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
