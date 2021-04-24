/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <Buffer.h>
#include <Array.h>

using gstar::Array;

using std::map;
using std::string;


/*---------------------------------------------------------------------------*/

Buffer::Buffer(unsigned int capacity, unsigned long long bytes)
: m_capacity(capacity), m_bytes(bytes)
{

   // Initialize memory, pool and circular buffer
   init();

}

/*---------------------------------------------------------------------------*/

Buffer::~Buffer()
{

   // Clean up circular buffers
   map<string, CircularBuffer<Array*>* >::iterator it;
   for (it = m_buffer.begin() ; it != m_buffer.end() ; ++it) {
      if (it -> second != NULL) {
         delete it -> second;
      }
   }

   // Clean up memory
   for (unsigned int i = 0 ; i < m_capacity ; i++) {
      if (m_memory[i] != NULL) {
         delete m_memory[i];
      }
   }

}

/*---------------------------------------------------------------------------*/

Array* Buffer::getMemory()
{

   Array* buf = NULL;
   m_pool.waitPop(buf);
   return buf;

}

/*---------------------------------------------------------------------------*/

Array* Buffer::getNext(const std::string& destinationName)
{

   // Get circular buffer for destination
   map<string, CircularBuffer<Array*>* >::iterator it;
   it = m_buffer.find(destinationName);

   // Check that destination is registered
   if (it == m_buffer.end()) {
       return NULL;
   }

   // Get and return next buffer
   Array* buf = NULL;
   (it -> second) -> pop(buf);
   return buf;

}

/*---------------------------------------------------------------------------*/

void Buffer::init()
{

   // Allocate memory
   m_memory.resize(m_capacity);
   for (unsigned int i = 0 ; i < m_capacity ; i++) {
      m_memory[i] = new Array(m_bytes);
      m_memory[i] -> setRank(2);
   }

   // Create memory pool
   for (unsigned int i = 0 ; i < m_capacity ; i++) {
      m_pool.push(m_memory[i]);
   }

}

/*---------------------------------------------------------------------------*/

void Buffer::insertNext(Array* item)
{

   // Push to each registered circular buffer
   map<string, CircularBuffer<Array*>* >::iterator it;
   for (it = m_buffer.begin() ; it != m_buffer.end() ; ++it) {
      (it -> second) -> push(item);
   }

   // Push back to buffer pool
   m_pool.push(item);

}

/*---------------------------------------------------------------------------*/

void Buffer::registerDestination(const string& destinationName)
{

   // Create a new circular buffer and add it to the map with
   // destination name as its key
   m_buffer[destinationName] = new CircularBuffer<Array*>;

}

/*---------------------------------------------------------------------------*/
