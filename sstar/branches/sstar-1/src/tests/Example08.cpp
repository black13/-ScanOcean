/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example08.h>

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


Example08::Example08(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void Example08::run()
{

   /**
    *    Shutter usage
    */


   Logger::setActive(false);

   ChannelAccess* ca;

   shared_ptr<PV> busyOpening;
   shared_ptr<PV> busyClosing;
   shared_ptr<PV> shutterState;

   int getValue;
   int putValue;
   CAGetTotalCopy<int>* reader = new CAGetTotalCopy<int>(&getValue);
   CAPrintDataChange<int>* dc = new CAPrintDataChange<int>(std::cout,1);

   /*********************************************/

   ca = ChannelAccess::getInstance();

   busyOpening = ca->getPV(m_name + ":shutterTest:busyOpening",1,5);
   busyClosing = ca->getPV(m_name + ":shutterTest:busyClosing",1,5);
   shutterState = ca->getPV(m_name + ":shutterTest:shutterState",1,5);

   shutterState->subscribeDataChangeEvent(dc,true);

   shutterState->synGet(1,reader);
   cout << "getValue(" << getValue << ")="
        << ((getValue == 1) ? "OPENED" : "CLOSED") << endl;

   sleep(2);

   for(int i = 0; i < 1; i++)
   {
      if(getValue == 0)
      {
         cout << "Opening..." << endl;
         putValue = 1;
         busyOpening->synPut(&putValue,1);
         getValue = 0;
      }
      else
      {
         cout << "Closing..." << endl;
         putValue = 1;
         busyClosing->synPut(&putValue,1);
         getValue = 1;

      }

      shutterState->synGet(1,reader);
      cout << "getValue(" << getValue << ")="
           << ((getValue == 1) ? "OPENED" : "CLOSED") << endl;
   }


}

/*---------------------------------------------------------------------------*/
