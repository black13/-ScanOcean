/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example02.h>

#include <boost/shared_ptr.hpp>

#include <SStar.h>

/*---------------------------------------------------------------------------*/

using boost::shared_ptr;
using std::string;
using std::cout;
using std::endl;

/*---------------------------------------------------------------------------*/

Example02::Example02(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/


void Example02::run()
{

   ChannelAccess* ca = ChannelAccess::getInstance();

   shared_ptr<PV> motor1;
   shared_ptr<PV> motor2;
   shared_ptr<PV> motor3;
   shared_ptr<PV> motor4;

   try
   {
      // Introducing an error in the second PV name - m2
      motor1 = ca->getPV(m_name + ":m1.VAL",7,3);        // Ref Count = 1
      motor2 = ca->getPV(m_name + ":m2x.VAL",5,3);       // Ref Count = 1
                                                         // Because it fails
   }
   catch(ChannelAccessException& e)
   {
      cout << e.what() << endl;
   }

}

/*---------------------------------------------------------------------------*/
