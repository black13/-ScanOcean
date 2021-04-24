/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <scan/ScanSleepCommand.h>
#include <scan/Scan.h>
#include <utils/ScanExceptions.h>
#include <chrono>
using namespace std;

/*---------------------------------------------------------------------------*/

ScanSleepCommand::ScanSleepCommand()
:  ScanCommand(),
   m_sleepTime(0)
{

}

/*---------------------------------------------------------------------------*/

ScanSleepCommand::ScanSleepCommand(unsigned int sleepTime)
:  ScanCommand(), 
   m_sleepTime(sleepTime)
{

}

/*---------------------------------------------------------------------------*/

ScanSleepCommand::ScanSleepCommand(const std::shared_ptr<ScanSleepCommand>& rhs)
{

   m_sleepTime = rhs->m_sleepTime;

}


/*---------------------------------------------------------------------------*/

ScanSleepCommand& ScanSleepCommand::operator=(
   const std::shared_ptr<ScanSleepCommand>& rhs)
{

   m_sleepTime = rhs->m_sleepTime;

   return *this;

}

/*---------------------------------------------------------------------------*/

ScanSleepCommand::~ScanSleepCommand()
{


}


/*---------------------------------------------------------------------------*/

void ScanSleepCommand::dump(int level)
{

   std::cout<<"Scan sleep for"<<m_sleepTime<<"milliseconds"<<std::endl;

}

/*---------------------------------------------------------------------------*/

void ScanSleepCommand::execute()
{

	if(m_sleepTime >= 0)
	std::this_thread::sleep_for(std::chrono::milliseconds(m_sleepTime));

}

/*---------------------------------------------------------------------------*/

void ScanSleepCommand::reset()
{

	m_sleepTime = 0;

}

/*---------------------------------------------------------------------------*/

void ScanSleepCommand::setSleepTime(unsigned int sleepTime)
{

	m_sleepTime = sleepTime;

}

/*---------------------------------------------------------------------------*/




