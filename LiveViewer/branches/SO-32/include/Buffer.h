/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef BUFFER_H
#define BUFFER_H

/*---------------------------------------------------------------------------*/

#include <Array.h>
#include <CircularBuffer.h>
#include <Queue.h>

#include <map>
#include <string>

/*---------------------------------------------------------------------------*/

/**
 * @brief Buffer...
 */
class Buffer
{

public:

   /**
    * Create and initialize a buffer of Array objects
    *
    * @param capacity - the number of objects in the buffer
    * @param bytes - the number of bytes for each Array to allocate
    */
   Buffer(unsigned int capacity, unsigned long long bytes);

   /**
    * Destructor
    */
   ~Buffer();

   /**
    * Get next memory buffer from pool for writing
    *
    * @return pointer to Array
    */
   Array* getMemory();

   /**
    * Get next memory buffer from circular buffer for processing
    *
    * @return pointer to Array
    */
   Array* getNext(const std::string& destinationName);

   /**
    * Insert next array for processing
    *
    * @param item - pointer to Array
    */
   void insertNext(Array* item);

   /**
    * Register a destination name with the buffer
    *
    * @param destinationName - destination name to register
    */
   void registerDestination(const std::string& destinationName);

private:

   /**
    * Initialize memory, pool and circular buffer
    */
   void init();

private:

   /**
    * Total number of Arrays
    */
   unsigned int m_capacity;

   /**
    * Total number of bytes each Array allocates
    */
   unsigned long long m_bytes;

   /**
    * Circular buffer
    */
   //CircularBuffer<Array*> m_buffer;
   std::map<std::string, CircularBuffer<Array*>* > m_buffer;

   /**
    * Memory
    */
   std::vector<Array*> m_memory;

   /**
    * Memory pool
    */
   Queue<Array*> m_pool;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
