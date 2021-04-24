/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example01.h>

#include <boost/shared_ptr.hpp>

#include <SStar.h>

/*---------------------------------------------------------------------------*/

using boost::shared_ptr;
using std::string;
using std::cout;
using std::endl;

/*---------------------------------------------------------------------------*/

Example01::Example01(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void Example01::run()
{

   //Getting an instance of Channel Access
   ChannelAccess* ca;

   shared_ptr<PV> motor1;
   shared_ptr<PV> motor2;
   shared_ptr<PV> motor3;
   shared_ptr<PV> motor4;

   ca = ChannelAccess::getInstance();

   try
   {
      //Getting some PVs
      motor1 = ca->getPV(m_name + ":m1.VAL",7);
      motor2 = ca->getPV(m_name + ":m2.VAL",5, 3);
      motor3 = ca->getPV(m_name + ":m3.VAL",5);
      motor4 = ca->getPV(m_name + ":m4.VAL",3);

      //Getting a PV which was already created
      motor4 = ca->getPV(m_name + ":m4.VAL",3);

   }
   catch(ChannelAccessException& e)
   {
      cout << e.what() << endl;
   }

}

/*---------------------------------------------------------------------------*/
