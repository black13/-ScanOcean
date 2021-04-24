/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <scan/ScanConditionCommand.h>
#include <scan/Scan.h>
#include <utils/ScanExceptions.h>

using namespace std;

/*---------------------------------------------------------------------------*/

ScanConditionCommand::ScanConditionCommand()
:  ScanCommand(),
   m_countCondition(0),
   m_count(0)
{

}

/*---------------------------------------------------------------------------*/

ScanConditionCommand::ScanConditionCommand(unsigned int count)
:  ScanCommand(), 
   m_countCondition(count),
   m_count(0)
{

}

/*---------------------------------------------------------------------------*/

ScanConditionCommand::ScanConditionCommand(const boost::shared_ptr<ScanConditionCommand>& rhs)
{

   m_count = rhs->m_count;
   m_commandList = rhs->m_commandList;

}


/*---------------------------------------------------------------------------*/

ScanConditionCommand& ScanConditionCommand::operator=(
   const boost::shared_ptr<ScanConditionCommand>& rhs)
{

   m_count = rhs->m_count;
   m_commandList = rhs->m_commandList;

   return *this;

}

/*---------------------------------------------------------------------------*/

ScanConditionCommand::~ScanConditionCommand()
{


}


/*---------------------------------------------------------------------------*/

void ScanConditionCommand::addCommand(const boost::shared_ptr<ScanCommand>& command)
{

   m_commandList.push_back(command);

}

/*---------------------------------------------------------------------------*/

void ScanConditionCommand::dump(int level)
{

   for (int i=0; i<level; i++)
   {
      std::cout<<"  ";
   }

   std::cout<<"if ( count "<<" == "<<m_countCondition;
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

void ScanConditionCommand::execute()
{

   m_count++;

   // Only execute scan when the desired condition is meet. 
   if (m_count < m_countCondition) return;


   Scan* scan = Scan::getInstance();
   bool noException = true;

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

    m_count = 0;
}

/*---------------------------------------------------------------------------*/
