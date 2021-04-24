/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef BUFFER_H
#define BUFFER_H

/*---------------------------------------------------------------------------*/

#include <CircularBuffer.h>
#include <Queue.h>

#include <map>
#include <string>

namespace gstar
{
  class Array;
}

/*---------------------------------------------------------------------------*/

/**
 * @brief Buffer...
 */
class Buffer
{

public:

   /**
    * Create and initialize a buffer of gstar::Array objects
    *
    * @param capacity - the number of objects in the buffer
    * @param bytes - the number of bytes for each gstar::Array to allocate
    */
   Buffer(unsigned int capacity, unsigned long long bytes);

   /**
    * Destructor
    */
   ~Buffer();

   /**
    * Get next memory buffer from pool for writing
    *
    * @return pointer to gstar::Array
    */
   gstar::Array* getMemory();

   /**
    * Get next memory buffer from circular buffer for processing
    *
    * @return pointer to gstar::Array
    */
   gstar::Array* getNext(const std::string& destinationName);

   /**
    * Insert next gstar::Array for processing
    *
    * @param item - pointer to gstar::Array
    */
   void insertNext(gstar::Array* item);

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
    * Total number of gstar::Arrays
    */
   unsigned int m_capacity;

   /**
    * Total number of bytes each gstar::Array allocates
    */
   unsigned long long m_bytes;

   /**
    * Circular buffer
    */
   std::map<std::string, CircularBuffer<gstar::Array*>* > m_buffer;

   /**
    * Memory
    */
   std::vector<gstar::Array*> m_memory;

   /**
    * Memory pool
    */
   Queue<gstar::Array*> m_pool;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
