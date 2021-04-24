/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example00.h>

#include <boost/shared_ptr.hpp>

#include <SStar.h>

/*---------------------------------------------------------------------------*/

using boost::shared_ptr;
using std::string;
using std::cout;
using std::endl;

/*---------------------------------------------------------------------------*/

Example00::Example00(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void Example00::run()
{

   ChannelAccess* ca;

   shared_ptr<PV> motor1;
   shared_ptr<PV> motor2;
   shared_ptr<PV> motor3;

   // Get singleton
   ca = ChannelAccess::getInstance();

   // Attempt 5 times, each with a timeout of 1 second
   // If unsuccessful, throw an exception
   motor1 = ca->getPV(m_name + ":m1.VAL",5,1);           // RefCount = 1

   // Don't throw, return object even if disconnected    // RefCount = 2
   motor2 = ca->getPV(m_name + ":m1.VAL");

   motor3 = motor1;                                      // RefCount = 2

   motor1 = ca->getPV(m_name + ":m1.VAL");               // RefCount = 3

   // PV are automatically disposed

}

/*---------------------------------------------------------------------------*/

