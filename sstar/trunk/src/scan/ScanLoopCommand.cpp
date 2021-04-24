/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <scan/ScanLoopCommand.h>
#include <scan/Scan.h>
#include <utils/ScanExceptions.h>

using namespace std;
/*---------------------------------------------------------------------------*/

ScanLoopCommand::ScanLoopCommand(const std::string& pv,
                                 Loop<double> loop)
:  ScanCommand(), 
   m_loopPV(pv), 
   m_loopVariable(loop)
{
   m_hasPv = true;
}

/*---------------------------------------------------------------------------*/

ScanLoopCommand::ScanLoopCommand(Loop<double> loop)
:  ScanCommand(), 
   m_loopVariable(loop)
{
   m_hasPv = false;
}


/*---------------------------------------------------------------------------*/

ScanLoopCommand::ScanLoopCommand(const std::shared_ptr<ScanLoopCommand>& rhs)
{

   m_loopPV = rhs->m_loopPV;
   m_hasPv = rhs->m_hasPv;
   m_loopVariable = rhs->m_loopVariable;
   m_commandList = rhs->m_commandList;

}


/*---------------------------------------------------------------------------*/

ScanLoopCommand& ScanLoopCommand::operator=(
   const std::shared_ptr<ScanLoopCommand>& rhs)
{

   m_commandList = rhs->m_commandList;

   return *this;

}

/*---------------------------------------------------------------------------*/

ScanLoopCommand::~ScanLoopCommand()
{


}


/*---------------------------------------------------------------------------*/

void ScanLoopCommand::addCommand(const std::shared_ptr<ScanCommand>& command)
{

   m_commandList.push_back(command);

}

/*---------------------------------------------------------------------------*/

void ScanLoopCommand::dump(int level)
{

   for (int i=0; i<level; i++)
   {
      std::cout<<"  ";
   }

   std::cout<<"for ( "<<m_loopPV<<" = "<<m_loopVariable.first();
   std::cout<<" , "<<m_loopPV<<" <= " <<m_loopVariable.last();
   std::cout<<" , "<<m_loopPV<<" += " <<m_loopVariable.step();
   std::cout<<" ) { "<<std::endl;

   for (std::vector<std::shared_ptr<ScanCommand> >::iterator it = m_commandList.begin();
         it != m_commandList.end(); it++)
   {
      (*it)->dump(level+1);
   }

   for (int i=0; i<level; i++)
   {
      std::cout<<"  ";
   }

   std::cout<<"}"<<std::endl;

}

/*---------------------------------------------------------------------------*/

void ScanLoopCommand::execute()
{

   Scan* scan = Scan::getInstance();

   // set the loop command
   Command cmd(m_loopPV, 0.0, Command::PV_PUT_SYNC);
   std::cout<<"LOOP START>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> "<<m_loopPV<<std::endl;

   while ( m_loopVariable.hasNext() )
   {

      cmd.setValueD(m_loopVariable.getNext());
      scan->execute(&cmd);
      
      for (std::vector<std::shared_ptr<ScanCommand> >::iterator it = m_commandList.begin();
         it != m_commandList.end(); it++)
      {
         (*it)->execute();
      }

   }

   std::cout<<"LOOP END>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> "<<m_loopPV<<std::endl;
   // If this object is nested, reset the loop so that we could restart
   m_loopVariable.reset();

}

/*---------------------------------------------------------------------------*/

void ScanLoopCommand::reset()
{

   Scan::reset();
   for (std::vector<std::shared_ptr<ScanCommand> >::iterator it = m_commandList.begin();
       it != m_commandList.end(); it++)
   {
      (*it)->reset();
   }

}

/*---------------------------------------------------------------------------*/
