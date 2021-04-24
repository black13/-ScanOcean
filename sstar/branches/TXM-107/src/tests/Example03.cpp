/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example03.h>

#include <boost/shared_ptr.hpp>

#include <SStar.h>

/*---------------------------------------------------------------------------*/

using boost::shared_ptr;
using std::string;
using std::cout;
using std::endl;

/*---------------------------------------------------------------------------*/

Example03::Example03(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void Example03::run()
{

   ChannelAccess* ca = ChannelAccess::getInstance();

   shared_ptr<PV> motor1;
   shared_ptr<PV> motor2;
   shared_ptr<PV> motor3;
   shared_ptr<PV> motor4;

   double read;
   double put;

   try
   {
      motor1 = ca->getPV(m_name + ":m1.VAL",7);

      //Synchronous reader
      CAGetTotalCopy<double> reader(&read);  //1) Define the reading operation
      motor1->synGet(1,&reader);             //2) Perform the synGet

      cout << "READ VALUE IS = " << read << endl;

      //Synchronous put
      read < 50.0 ? put = 75.0 : put = 25.0;
      motor1->synPut(&put,1);                //Blocks until it is finished

      /*--------------------------------------------------------------------*/

      //Asynchronous put without handler
      read < 50.0 ? put = 75.0 : put = 25.0;
      motor1->asynPut(&put,1);               //Does not block

      sleep(3);

      //Asynchronous put without handler
      put < 50.0 ? put = 75.0 : put = 25.0;
      motor1->asynPut(&put,1);               //Overrides previous asynchronous
                                             //put without handler

      sleep(3);

      //Asynchronous put with handler
      CAPrintText printer("HELLO CHICO");   //Printed asynchronously at the end

      put < 50.0 ? put = 100.0 : put = 0;
      motor1->asynPut(&put,1,&printer);     //Overrides previous asynchronous
                                            //put without handler

      put < 50.0 ? put = 100 : put = 0;
      motor1->asynPut(&put,1,&printer);     //There is (probably) an asynch
                                            //put with handler which is
                                            //still running, the request is
                                            //buffered

      put < 50.0 ? put = 100 : put = 0;     //There is (probably) an asynch
      motor1->synPut(&put,1);               //put with handler which is
                                            //still running, the request is
                                            //buffered

      /*--------------------------------------------------------------------*/

      put < 50.0 ? put = 100 : put = 0;
      motor1->asynPut(&put,1,&printer);


      put < 50.0 ? put = 100 : put = 0;      //The asynPut without handler
      motor1->asynPut(&put,1);               //blocks because there are
                                             //asynPut with handler/synPut
                                             //and cannot be overridden

   }
   catch(ChannelAccessException& e)
   {
      cout << e.what() << endl;
   }

}

/*---------------------------------------------------------------------------*/
