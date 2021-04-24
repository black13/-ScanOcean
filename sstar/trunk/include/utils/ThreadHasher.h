/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_THREADHASHER_H
#define SSTAR_THREADHASHER_H

/*---------------------------------------------------------------------------*/

#include <boost/thread/thread.hpp>
#include <boost/functional/hash.hpp>

/*---------------------------------------------------------------------------*/

/**
 * Adding the function to compute the hash for boost::thread::id
 * in the boost namespace
 */
namespace boost
{

   bool operator==(boost::thread::id& p1, boost::thread::id& p2);
//boost 1.5 > has this function
//   std::size_t hash_value(boost::thread::id const& id);

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
