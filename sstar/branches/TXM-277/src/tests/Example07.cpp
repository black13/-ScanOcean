/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example07.h>

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

Example07::Example07(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void Example07::run()
{

   /**
    *    Simple monitor for motors
    *
    */
   Logger::getInstance()->setActive(false);

   ChannelAccess* ca;

   shared_ptr<PV> r1;
   shared_ptr<PV> r2;
   shared_ptr<PV> r3;
   shared_ptr<PV> r4;

   CAPrintDataChange<double>* dc1 = new CAPrintDataChange<double>(std::cout,0);
   CAPrintDataChange<double>* dc2 = new CAPrintDataChange<double>(std::cout,2);
   CAPrintDataChange<double>* dc3 = new CAPrintDataChange<double>(std::cout,4);
   CAPrintDataChange<double>* dc4 = new CAPrintDataChange<double>(std::cout,6);

   CAPrintConnectionState* cs = new CAPrintConnectionState;

   ca = ChannelAccess::getInstance();

   //Bind these PV channels, even if the IOC is down
   r1 = ca->getPV(m_name + ":m1.RBV");
   r2 = ca->getPV(m_name + ":m2.RBV");
   r3 = ca->getPV(m_name + ":m3.RBV");
   r4 = ca->getPV(m_name + ":m4.RBV");

   //Subscribe to connection event
   r1->subscribeConnectionEvent(cs,true);
   r2->subscribeConnectionEvent(cs,true);
   r3->subscribeConnectionEvent(cs,true);
   r4->subscribeConnectionEvent(cs,true);

   //This subscription will block until the succeed
   r1->subscribeDataChangeEvent(dc1,false);
   r2->subscribeDataChangeEvent(dc2,false);
   r3->subscribeDataChangeEvent(dc3,false);
   r4->subscribeDataChangeEvent(dc4,false);

   cout << "Waiting for events on motors..." << endl << endl;
   while(true)
   {
      sleep(5);
   }

}

/*---------------------------------------------------------------------------*/
