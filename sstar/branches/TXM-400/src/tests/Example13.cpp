/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example13.h>

#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>

#include <scan/ScanSequenceCommand.h>
#include <scan/ScanLoopCommand.h>
#include <scan/ScanMacroCommand.h>
#include <tests/Utils.h>
#include <SStar.h>

/*---------------------------------------------------------------------------*/

using boost::shared_ptr;
using std::string;
using std::cout;
using std::endl;

/*---------------------------------------------------------------------------*/

Example13::Example13(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void Example13::run()
{

   Logger::setActive(false);

   std::cout<<"Running scan with two nested levels"<<std::endl;

   ScanMacroCommand* tomoScan = new ScanMacroCommand();
   boost::shared_ptr<ScanMacroCommand> p_tomoScan(tomoScan);

   Loop<double> innerLoop;
   innerLoop.setLoop(0.0, 10.0, 50.0);

   Loop<double> outerLoop;
   outerLoop.setLoop(0.0, 1.0, 10.0);
   
   // INNER Loop
   ScanLoopCommand* innerLoopCmd = new ScanLoopCommand(m_name + ":m1.VAL", innerLoop);
   boost::shared_ptr<ScanLoopCommand> p_innerLoopCmd(innerLoopCmd);
   
   // Operation for inner loop
   ScanSequenceCommand* innercmds = new ScanSequenceCommand();
   boost::shared_ptr<ScanSequenceCommand> p_innercmds(innercmds);

   p_innercmds->addCommand(m_name + ":SIM1:cam1:ImageMode", 0, Command::PV_PUT_ASYNC);
   p_innercmds->addCommand(m_name + ":SIM1:cam1:Acquire", 1, Command::PV_PUT_ASYNC);
   p_innercmds->addCommand(m_name + ":SIM1:cam1:Acquire", 0, Command::PV_WAIT);

   boost::shared_ptr<ScanCommand> pp_innercmds = p_innercmds;
   p_innerLoopCmd->addCommand(pp_innercmds);

   // OUTER Loop
   ScanLoopCommand* outerLoopCmd = new ScanLoopCommand(m_name + ":m2.VAL", outerLoop);
   boost::shared_ptr<ScanLoopCommand> p_outerLoopCmd(outerLoopCmd);

   boost::shared_ptr<ScanCommand> pp_innerLoopCmd = p_innerLoopCmd;
   p_outerLoopCmd->addCommand(pp_innerLoopCmd);

   boost::shared_ptr<ScanCommand> pp_outerLoopCmd = p_outerLoopCmd;
   p_tomoScan->addCommand(pp_outerLoopCmd);

   p_tomoScan->dump(0);
   p_tomoScan->execute();

   std::cout<<"Done"<<std::endl;
}

/*---------------------------------------------------------------------------*/
