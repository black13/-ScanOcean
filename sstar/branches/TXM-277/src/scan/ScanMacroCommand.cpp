/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <scan/ScanMacroCommand.h>
#include <utils/ScanExceptions.h>
#include <utils/ChannelAccessExceptions.h>

using namespace std;

/*---------------------------------------------------------------------------*/

ScanMacroCommand::ScanMacroCommand()
:  ScanCommand()
{


}

/*---------------------------------------------------------------------------*/

ScanMacroCommand::ScanMacroCommand(const boost::shared_ptr<ScanMacroCommand>& cmd)
{

   m_commandList = cmd->m_commandList;

}

/*---------------------------------------------------------------------------*/

ScanMacroCommand& ScanMacroCommand::operator=(
   const boost::shared_ptr<ScanMacroCommand>& rhs)
{

   m_commandList = rhs->m_commandList;
   return *this;

}

/*---------------------------------------------------------------------------*/

ScanMacroCommand::~ScanMacroCommand()
{
   std::cout<<"Destroying ScanMacroCommand";
}

/*---------------------------------------------------------------------------*/

void ScanMacroCommand::addCommand(const boost::shared_ptr<ScanCommand>& command)
{

   m_commandList.push_back(command);

}

/*---------------------------------------------------------------------------*/

void ScanMacroCommand::dump(int level)
{

   for (std::vector<boost::shared_ptr<ScanCommand> >::iterator it = m_commandList.begin();
         it != m_commandList.end(); it++)
   {
      (*it)->dump(level);

   }

}

/*---------------------------------------------------------------------------*/

void ScanMacroCommand::execute()
{

   for (std::vector<boost::shared_ptr<ScanCommand> >::iterator it = m_commandList.begin();
         it != m_commandList.end(); it++)
   {
      try
      {
         (*it)->execute();
      } 
      catch (ScanAbortException& se)
      {
         std::cout<<"Scan aborted"<<std::endl;
         (*it)->dump(0);
         break;
      }
      catch (ChannelAccessException& ce)
      {
         std::cout<<"Scan failed with channel-access exception"<<std::endl;
         (*it)->dump(0);
         break;
      }

   }

}

/*---------------------------------------------------------------------------*/
