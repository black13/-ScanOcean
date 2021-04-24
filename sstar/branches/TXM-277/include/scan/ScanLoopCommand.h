/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TXM_SCAN_LOOP_COMMAND_H
#define TXM_SCAN_LOOP_COMMAND_H

/*---------------------------------------------------------------------------*/

#include <scan/Command.h>
#include <scan/ScanCommand.h>
#include <scan/Loop.h>

#include <boost/shared_ptr.hpp>

#include <vector>

/*---------------------------------------------------------------------------*/

class ScanLoopCommand
: public ScanCommand
{

public:

   ScanLoopCommand(const std::string& pv, Loop<double> loop);

   ScanLoopCommand(const boost::shared_ptr<ScanLoopCommand>& loop);

   ScanLoopCommand& operator=(const boost::shared_ptr<ScanLoopCommand>& command);

   ~ScanLoopCommand();

   void addCommand(const boost::shared_ptr<ScanCommand>& command);

   void dump(int level);

   void execute();

private:
   
   std::vector<boost::shared_ptr<ScanCommand> > m_commandList;
  
   //PV operation that will run in a loop
   std::string m_loopPV;

   Loop<double> m_loopVariable;

};


/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
