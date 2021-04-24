/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <Buffer.h>

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

   // Clean up
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

Array* Buffer::getNext()
{

   Array* buf = NULL;
   m_buffer.pop(buf);
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

   m_buffer.push(item);
   m_pool.push(item);

}

/*---------------------------------------------------------------------------*/
