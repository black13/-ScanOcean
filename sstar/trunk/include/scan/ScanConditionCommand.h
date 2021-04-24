
/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_SCAN_CONDITION_COMMAND_H
#define SSTAR_SCAN_CONDITION_COMMAND_H

/*---------------------------------------------------------------------------*/

#include <scan/ScanCommand.h>
#include <scan/Command.h>

#include <memory>

#include <string>
#include <vector>

/*---------------------------------------------------------------------------*/

class ScanConditionCommand
: public ScanCommand
{
public:

   ScanConditionCommand();

   ScanConditionCommand(unsigned int count);

   ScanConditionCommand(const std::shared_ptr<ScanConditionCommand>& rhs);

   ScanConditionCommand& operator=(const std::shared_ptr<ScanConditionCommand>& rhs);

   ~ScanConditionCommand();

   void addCommand(const std::shared_ptr<ScanCommand>& command);
   
   void dump(int level);

   void execute();

   void reset();

private:
   
   std::vector<std::shared_ptr<ScanCommand> > m_commandList;

   unsigned int m_countCondition;

   unsigned m_count;

};

#endif
