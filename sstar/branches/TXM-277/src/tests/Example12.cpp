/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example12.h>

#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/random.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/generator_iterator.hpp>

#include <scan/ScanSequenceCommand.h>
#include <scan/ScanLoopCommand.h>
#include <scan/ScanMacroCommand.h>
#include <scan/ScanConditionCommand.h>
#include <tests/Utils.h>
#include <SStar.h>

#include <unistd.h>

/*---------------------------------------------------------------------------*/

using boost::shared_ptr;
using std::string;
using std::cout;
using std::endl;

/*---------------------------------------------------------------------------*/

Example12::Example12(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void Example12::run()
{

   Logger::setActive(false);

   Loop<double> loop(0.0, 1.0, 100.0);

   ScanMacroCommand* scan = new ScanMacroCommand();
   boost::shared_ptr<ScanMacroCommand> p_scan(scan);

   ScanSequenceCommand* preScan = new ScanSequenceCommand();
   boost::shared_ptr<ScanSequenceCommand> p_preScan(preScan);
   p_preScan->addCommand(m_name + ":SIM1:cam1:ImageMode", 0, Command::PV_PUT_ASYNC);
   p_preScan->addCommand(m_name + ":Nexus1:FilePath", "/tmp/", Command::PV_PUT_ASYNC);

   ScanSequenceCommand* postScan = new ScanSequenceCommand();
   boost::shared_ptr<ScanSequenceCommand> p_postScan(postScan);
   p_postScan->addCommand(m_name + ":SIM1:cam1:Acquire", 0, Command::PV_PUT_ASYNC);

   ScanLoopCommand* outcmd = new ScanLoopCommand(m_name + ":m1.VAL", loop);
   boost::shared_ptr<ScanLoopCommand> p_outcmd(outcmd);

   ScanSequenceCommand* innercmds = new ScanSequenceCommand();
   boost::shared_ptr<ScanSequenceCommand> p_innercmds(innercmds);
   p_innercmds->addCommand(m_name + ":SIM1:cam1:Acquire", 1, Command::PV_PUT_ASYNC);
   p_innercmds->addCommand(m_name + ":SIM1:cam1:Acquire", 0, Command::PV_WAIT);


   ScanConditionCommand* conditionCmd = new ScanConditionCommand(10);
   boost::shared_ptr<ScanConditionCommand> p_conditionCmd(conditionCmd);
   p_conditionCmd->addCommand(p_innercmds);

   p_outcmd->addCommand(p_conditionCmd);

   p_scan->addCommand(p_preScan);
   p_scan->addCommand(p_outcmd);
   p_scan->addCommand(p_postScan);

   p_scan->dump(0);
   p_scan->execute();

   std::cout<<"Done"<<std::endl; 

}

/*---------------------------------------------------------------------------*/
