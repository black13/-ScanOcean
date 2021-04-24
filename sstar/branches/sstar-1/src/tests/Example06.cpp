/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example06.h>

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

Example06::Example06(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void Example06::run()
{

   ChannelAccess* ca;

   shared_ptr<PV> motor1;
   shared_ptr<PV> speed;
   shared_ptr<PV> rbv;

   CAPrintText* h1 = new CAPrintText("Number 1");
   CAPrintText* h2 = new CAPrintText("Number 2");
   CAPrintText* h3 = new CAPrintText("Number 3");

   CAPrintDataChange<double> dc(std::cout);

   double speedValue = 10;
   double put;

   ca = ChannelAccess::getInstance();

   motor1 = ca->getPV(m_name + ":m1.VAL",1,5);

   speed = ca->getPV(m_name + ":m1.S",1,5);
   speed->synPut(&speedValue,1);

   rbv = ca->getPV(m_name + ":m1.RBV",1,5);
   rbv->subscribeDataChangeEvent(&dc);

   cout << "Resources bound, now disconnect IOC (you have 10 seconds)" << endl;
   sleep(10);

   try
   {
      readValue<double>(motor1) < 50 ? put = 100 : put = 0;
      motor1->asynPut(&put,1,h1);
   }
   catch(ChannelAccessException& e)
   {
      cout << "CA disconnected, now reconnect IOC (you have 10 seconds)" << endl;
      sleep(10);

      speed->synPut(&speedValue,1);
   }

   put < 50 ? put = 100 : put = 0;
   motor1->asynPut(&put,1,h2);
   put < 50 ? put = 100 : put = 0;
   motor1->asynPut(&put,1,h3);

}

/*---------------------------------------------------------------------------*/
