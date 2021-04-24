/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example05.h>

#include <boost/shared_ptr.hpp>

#include <SStar.h>
#include <tests/Utils.h>

/*---------------------------------------------------------------------------*/

using boost::shared_ptr;
using std::string;
using std::cout;
using std::endl;

/*---------------------------------------------------------------------------*/

Example05::Example05(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void Example05::run()
{

   /*
    *    This example shows how to subscribe an event handler
    *    to be called whenever there is a data change
    *
    *
    *
    */


   ChannelAccess* ca;

   shared_ptr<PV> motor1;
   shared_ptr<PV> motorrbv;

   double put = 0;

   //Getting an instance of Channel Access
   ca = ChannelAccess::getInstance();

   try
   {
      //Getting some PVs
      motor1 = ca->getPV(m_name + ":m1.VAL",7);
      motorrbv = ca->getPV(m_name + ":m1.RBV",7);

      //Setting up put value
      readValue<double>(motor1) < 50 ? put = 100 : put = 0.0;

      //Just prints on the standard output
      CAPrintDataChange<double>* pPrinter =
         new CAPrintDataChange<double>(std::cout);

      //Subscribe the handler to the event
      motorrbv->subscribeDataChangeEvent(pPrinter);

      //Asyn Put with handler
      CAPrintText* h = new CAPrintText("DONE!");
      motor1->asynPut(&put,1,h);

      sleep(1);
      //Unsubscribe
      motorrbv->unsubscribeDataChangeEvent(pPrinter);

      sleep(1);
      //Subscribe
      motorrbv->subscribeDataChangeEvent(pPrinter);

      sleep(7);

   }
   catch(ChannelAccessException& e)
   {

      cout << e.what() << endl;

   }

}

/*---------------------------------------------------------------------------*/
