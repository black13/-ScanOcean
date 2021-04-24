/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <scan/ScanSequenceCommand.h>
#include <scan/Scan.h>
#include <scan/Command.h>
#include <utils/ScanExceptions.h>

using namespace std;

/*---------------------------------------------------------------------------*/

ScanSequenceCommand::ScanSequenceCommand()
:  ScanCommand()
{

}

/*---------------------------------------------------------------------------*/

ScanSequenceCommand::~ScanSequenceCommand()
{

}


/*---------------------------------------------------------------------------*/

ScanSequenceCommand::ScanSequenceCommand(
   const std::shared_ptr<ScanSequenceCommand>& rhs)
{

   m_commandList = rhs->m_commandList;
   cout<<"Copying ScanSequenceCommand"<<endl;

}


/*---------------------------------------------------------------------------*/

ScanSequenceCommand& ScanSequenceCommand::operator=(
   const std::shared_ptr<ScanSequenceCommand>& rhs)
{

   m_commandList = rhs->m_commandList;
   cout<<"Assigning ScanSequenceCommand"<<endl;
   return *this;

}


/*---------------------------------------------------------------------------*/

void ScanSequenceCommand::addCommand(const std::string& pvName, 
                                     int data,
                                     Command::Operation op,
                                     int postDelay)
{

   Command cmd(pvName, data, op, postDelay);
   m_commandList.push_back(cmd);

}

/*---------------------------------------------------------------------------*/

void ScanSequenceCommand::addCommand(const std::string& pvName, 
                                     unsigned int data,
                                     Command::Operation op,
                                     int postDelay)
{

   Command cmd(pvName, data, op, postDelay);
   m_commandList.push_back(cmd);

}

/*---------------------------------------------------------------------------*/

void ScanSequenceCommand::addCommand(const std::string& pvName, 
                                     double data,
                                     Command::Operation op,
                                     int postDelay)
{

   Command cmd(pvName, data, op, postDelay);
   m_commandList.push_back(cmd);

}

/*---------------------------------------------------------------------------*/

void ScanSequenceCommand::addCommand(const std::string& pvName, 
                                     const std::string& data,
                                     Command::Operation op,
                                     int postDelay)
{

   Command cmd(pvName, data, op, postDelay);
   m_commandList.push_back(cmd);

}

/*---------------------------------------------------------------------------*/

void ScanSequenceCommand::dump(int level)
{

   for (std::vector<Command>::iterator it = m_commandList.begin(); 
      it != m_commandList.end(); it++)
   {

      Command cmd = *it;
      cmd.print(level);
   }

}

/*---------------------------------------------------------------------------*/

void ScanSequenceCommand::execute()
{

   Scan* scan = Scan::getInstance();

   for (std::vector<Command>::iterator it = m_commandList.begin(); 
      it != m_commandList.end(); it++)
   {
      scan->execute(&(*it)); 
      (*it).print(0);
   }

}

/*---------------------------------------------------------------------------*/

void ScanSequenceCommand::reset()
{

   Scan::reset();

}

/*---------------------------------------------------------------------------*/
