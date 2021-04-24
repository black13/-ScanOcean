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

}

/*---------------------------------------------------------------------------*/

ScanLoopCommand::ScanLoopCommand(const boost::shared_ptr<ScanLoopCommand>& rhs)
{

   m_loopPV = rhs->m_loopPV;
   m_loopVariable = rhs->m_loopVariable;
   m_commandList = rhs->m_commandList;

   cout<<"copying ScanLoopCommand"<<endl;

}


/*---------------------------------------------------------------------------*/

ScanLoopCommand& ScanLoopCommand::operator=(
   const boost::shared_ptr<ScanLoopCommand>& rhs)
{

   m_commandList = rhs->m_commandList;
   cout<<"Assigning ScanLoopCommand"<<endl;

   return *this;

}

/*---------------------------------------------------------------------------*/

ScanLoopCommand::~ScanLoopCommand()
{


   cout<<"Destroying ScanLoopCommand"<<endl;

}


/*---------------------------------------------------------------------------*/

void ScanLoopCommand::addCommand(const boost::shared_ptr<ScanCommand>& command)
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

   for (std::vector<boost::shared_ptr<ScanCommand> >::iterator it = m_commandList.begin();
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
   bool noException = true;

   // set the loop command
   Command cmd(m_loopPV, 0.0, Command::PV_PUT_SYNC);

   while ( m_loopVariable.hasNext() && (noException == true) )
   {

      cmd.setValueD(m_loopVariable.getNext());
      try 
      {
         scan->execute(&cmd);
      }
      catch (ScanAbortException& e)
      {
         break;
      }
      
      for (std::vector<boost::shared_ptr<ScanCommand> >::iterator it = m_commandList.begin();
         it != m_commandList.end(); it++)
      {
         try
         {
            (*it)->execute();
         } 
         catch (ScanAbortException& se)
         {
            noException = false; // force outer loop to exit. 
            break;
         }
      }
   }

   // If this object is nested, reset the loop so that we could restart
   m_loopVariable.reset();

}

/*---------------------------------------------------------------------------*/
