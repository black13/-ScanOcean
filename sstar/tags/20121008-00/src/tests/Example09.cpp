/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example09.h>

#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>

#include <tests/Utils.h>
#include <SStar.h>

/*---------------------------------------------------------------------------*/

using boost::shared_ptr;
using std::string;
using std::cout;
using std::endl;

/*---------------------------------------------------------------------------*/

Example09::Example09(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void Example09::run()
{

   /**
    *    Objectives usage
    */

   ChannelAccess* ca;

   shared_ptr<PV> objSelector;

   ca = ChannelAccess::getInstance();

   objSelector = ca->getPV(m_name + ":obj:mode",1,5);

   mode writeMode;
   mode readMode;

   CAGetTotalCopy<mode>* reader = new CAGetTotalCopy<mode>(&readMode);

   writeMode = Example09::ONE;
   objSelector->synPut(&writeMode,1);

   objSelector->synGet(1,reader);
   printMode(readMode);

   sleep(5);

   writeMode = Example09::FIVE;
   objSelector->synPut(&writeMode,1);

   objSelector->synGet(1,reader);
   printMode(readMode);

   sleep(5);

   writeMode = Example09::TWENTY;
   objSelector->synPut(&writeMode,1);

   objSelector->synGet(1,reader);
   printMode(readMode);

   sleep(5);

}

/*---------------------------------------------------------------------------*/

void Example09::printMode(mode m)
{

   switch(m)
   {
      case Example09::ONE:
         cout << "1x" << endl;
      break;
      case Example09::FIVE:
         cout << "5x" << endl;
      break;
      case Example09::TWENTY:
         cout << "20x" << endl;
      break;
   }

}

/*---------------------------------------------------------------------------*/
