/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example04.h>

#include <boost/shared_ptr.hpp>

#include <SStar.h>
#include <tests/Utils.h>

/*---------------------------------------------------------------------------*/

using boost::shared_ptr;
using std::string;
using std::cout;
using std::endl;

/*---------------------------------------------------------------------------*/

Example04::Example04(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void Example04::run()
{

   //Getting an instance of Channel Access
   ChannelAccess* ca = ChannelAccess::getInstance();

   shared_ptr<PV> motor1;
   shared_ptr<PV> motor2;
   shared_ptr<PV> motor3;
   shared_ptr<PV> motor4;

   double put1 = 0;
   double put2 = 0;
   double put3 = 0;
   double put4 = 0;

   CAPrintText h("Done!");

   try
   {
      //Getting some PVs
      motor1 = ca->getPV(m_name + ":m1.VAL",7);
      motor2 = ca->getPV(m_name + ":m2.VAL",5);
      motor3 = ca->getPV(m_name + ":m3.VAL",5);
      motor4 = ca->getPV(m_name + ":m4.VAL",3);

      readValue<double>(motor1) < 50 ? put1 = 100 : put1 = 0.0;
      readValue<double>(motor2) < 50 ? put2 = 100 : put2 = 0.0;
      readValue<double>(motor3) < 50 ? put3 = 100 : put3 = 0.0;
      readValue<double>(motor4) < 50 ? put4 = 100 : put4 = 0.0;

      //Preparing parallel operations
      motor1->asynPut(&put1,1,&h,false);
      motor2->asynPut(&put2,1,&h,false);
      motor3->asynPut(&put3,1,&h,false);
      motor4->asynPut(&put4,1,&h,false);

      //Flush
      ca->flush();

      //Work as the join for threads
      motor1->waitCompletion();
      motor2->waitCompletion();
      motor3->waitCompletion();
      motor4->waitCompletion();

      cout << "ALL THE OPERATIONS ARE FINISHED" << endl;


   }
   catch(ChannelAccessException& e)
   {
      cout << e.what() << endl;
   }

}

/*---------------------------------------------------------------------------*/
