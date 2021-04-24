/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example10.h>

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

Example10::Example10(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void Example10::run()
{

   /**
    *    Objectives usage
    */

   Logger::setActive(false);

   ChannelAccess* ca;

   shared_ptr<PV> beamEnergy;
   shared_ptr<PV> beamEnergyTran;
   shared_ptr<PV> beamEnergyTranRBV;
   shared_ptr<PV> beamEnergyCalc;
   shared_ptr<PV> beamEnergyBusy;

   CAPrintDataChange<double> dc1;
   CAPrintDataChange<double> dc2(std::cout,1);
   CAPrintDataChange<int> dc3(std::cout,2);
   CAPrintDataChange<char> dc4(std::cout,3);

   ca = ChannelAccess::getInstance();

   // Subscribe to monochromator data change
   beamEnergy = ca->getPV(m_name + ":beamEnergy",1,5);
   beamEnergy->subscribeDataChangeEvent(&dc1);

   beamEnergyTran = ca->getPV(m_name + ":beamEnergyTran.B",1,5);

   // Subscribe to undulator data change (RBV)
   beamEnergyTranRBV = ca->getPV(m_name + ":IDenergyReadback",1,5);
   beamEnergyTranRBV->subscribeDataChangeEvent(&dc2);

   // 0 when done, 1 when busy. It is done only when both the
   // monochromator and the undulator are done
   beamEnergyBusy = ca->getPV(m_name + ":beamEnergySseq.BUSY",1,5);
   beamEnergyBusy->subscribeDataChangeEvent(&dc3);

   // Subscribe to the calc PV
   // It is a string datatype, 40 chars (including the /0)
   beamEnergyCalc = ca->getPV(m_name + ":beamEnergyTran.CLCB",1,5);
   beamEnergyCalc->subscribeDataChangeEvent(&dc4);

   // writing the calc expression
   string expression = "1.3*a + 2.0";
   const char* cstring = expression.c_str();
   //cout << "WRITING CALC EXP: " << expression << endl;
   beamEnergyCalc->synPut((void*) cstring,1);
   //cout << "WRITING CALC EXP DONE" << endl;

   // reading the calc expression
   char stringBuffer[40];
   CAGetTotalCopy<char> reader(stringBuffer);
   //cout << "READING CALC EXP" << endl;
   beamEnergyCalc->synGet(0,&reader);
   //cout << "READ CALC EXP: " << stringBuffer << endl;

   double value;
   CAGetTotalCopy<double> doubleReader(&value);
   beamEnergy->synGet(0,&doubleReader);

   cout << "Going to sleep and waiting for events...." << endl;
   while(true) sleep(5);

}

/*---------------------------------------------------------------------------*/
