/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <scan/ScanMacroCommand.h>
#include <utils/ScanExceptions.h>
#include <utils/ChannelAccessExceptions.h>
#include <scan/Scan.h>

#include <thread>

using namespace std;

/*---------------------------------------------------------------------------*/

ScanMacroCommand::ScanMacroCommand()
:  ScanCommand()
{


}

/*---------------------------------------------------------------------------*/

ScanMacroCommand::ScanMacroCommand(const std::shared_ptr<ScanMacroCommand>& cmd)
{

   m_commandList = cmd->m_commandList;

}

/*---------------------------------------------------------------------------*/

ScanMacroCommand& ScanMacroCommand::operator=(
   const std::shared_ptr<ScanMacroCommand>& rhs)
{

   m_commandList = rhs->m_commandList;
   return *this;

}

/*---------------------------------------------------------------------------*/

ScanMacroCommand::~ScanMacroCommand()
{


}

/*---------------------------------------------------------------------------*/

void ScanMacroCommand::addCommand(const std::shared_ptr<ScanCommand>& command)
{

   m_commandList.push_back(command);

}

/*---------------------------------------------------------------------------*/

void ScanMacroCommand::dump(int level)
{

   for (std::vector<std::shared_ptr<ScanCommand> >::iterator it = m_commandList.begin();
         it != m_commandList.end(); it++)
   {
      (*it)->dump(level);

   }

}


/*---------------------------------------------------------------------------*/

void ScanMacroCommand::reset()
{

   Scan::reset();

   for (std::vector<std::shared_ptr<ScanCommand> >::iterator it = m_commandList.begin();
         it != m_commandList.end(); it++)
   {
      (*it)->reset();
   }

}

/*---------------------------------------------------------------------------*/

void ScanMacroCommand::execute()
{

   for (std::vector<std::shared_ptr<ScanCommand> >::iterator it = m_commandList.begin();
         it != m_commandList.end(); it++)
   {
      try
      {
         (*it)->execute();
      } 
      catch (ScanAbortException& se)
      {
         std::cout<<"Scan aborted"<<std::endl;
//         (*it)->dump(0);
         throw;
      }
      catch (ChannelAccessException& ce)
      {
         std::cout<<"Scan failed with channel-access exception"<<std::endl;
         (*it)->dump(0);
         throw;
      }
      catch (std::exception const & i)
      {
         std::cout<<"Scan interuppted"<<std::endl;
//         (*it)->dump(0);
         Scan::stop();
         throw ScanAbortException();
      }

   }

}

/*---------------------------------------------------------------------------*/
