
/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TXM_SCAN_SEQUENCE_COMMAND_H
#define TXM_SCAN_SEQUENCE_COMMAND_H

/*---------------------------------------------------------------------------*/

#include <scan/ScanCommand.h>
#include <scan/Command.h>

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

/*---------------------------------------------------------------------------*/

class ScanSequenceCommand
: public ScanCommand
{
public:

   ScanSequenceCommand();

   ScanSequenceCommand(const boost::shared_ptr<ScanSequenceCommand>& rhs);

   ScanSequenceCommand& operator=(const boost::shared_ptr<ScanSequenceCommand>& rhs);

   ~ScanSequenceCommand();

   void addCommand(const std::string& pvName, int data, Command::Operation op);
   
   void addCommand(const std::string& pvName, 
                   unsigned int data, 
                   Command::Operation op);
   
   void addCommand(const std::string& pvName, 
                   double data, 
                   Command::Operation op);
   
   void addCommand(const std::string& pvName, 
                   const std::string& data, 
                   Command::Operation op);

   void dump(int level);

   void execute();

private:
   
   std::vector<Command> m_commandList;

};

#endif
