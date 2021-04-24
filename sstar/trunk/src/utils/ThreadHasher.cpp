/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <utils/ThreadHasher.h>

/*---------------------------------------------------------------------------*/

namespace boost
{

   bool operator==(boost::thread::id& p1, boost::thread::id& p2)
   {

      return p1 == p2;

   }
  /*
  std::size_t hash_value(boost::thread::id const& id)
  {

        std::ostringstream os;
        os << id;
        boost::hash<std::string> hasher;
        return hasher(os.str());

  }
	*/
}

/*---------------------------------------------------------------------------*/
