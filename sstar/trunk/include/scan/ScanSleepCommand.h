
/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_SCAN_SLEEP_COMMAND_H
#define SSTAR_SCAN_SLEEP_COMMAND_H

/*---------------------------------------------------------------------------*/

#include <scan/ScanCommand.h>
#include <scan/Command.h>

#include <memory>
#include <memory>
#include <thread>

#include <string>
#include <vector>

/*---------------------------------------------------------------------------*/

class ScanSleepCommand
: public ScanCommand
{
public:

	ScanSleepCommand();

	ScanSleepCommand(unsigned int sleepTime);

	ScanSleepCommand(const std::shared_ptr<ScanSleepCommand>& rhs);

	ScanSleepCommand& operator=(const std::shared_ptr<ScanSleepCommand>& rhs);

   ~ScanSleepCommand();

//   void addCommand(const std::shared_ptr<ScanCommand>& command);
   
   void dump(int level);

   void execute();

   void reset();

   void setSleepTime(unsigned int sleepTime);

private:
   
   std::vector<std::shared_ptr<ScanCommand> > m_commandList;

//   unsigned int m_countCondition;

   unsigned int m_sleepTime;

};

#endif
