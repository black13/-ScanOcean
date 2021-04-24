/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <iostream>
#include <vector>

#include <SStar.h>

#include <tests/Example00.h>
#include <tests/Example01.h>
#include <tests/Example02.h>
#include <tests/Example03.h>
#include <tests/Example04.h>
#include <tests/Example05.h>
#include <tests/Example06.h>
#include <tests/Example07.h>
#include <tests/Example08.h>
#include <tests/Example09.h>
#include <tests/Example10.h>
#include <tests/Example11.h>
#include <tests/Example12.h>
#include <tests/Example13.h>

#include <tests/ThreadedTest.h>

/*---------------------------------------------------------------------------*/

using std::cout;
using std::endl;
using std::vector;
using std::string;

/*---------------------------------------------------------------------------*/

int main(int argc, char** argv)
{

   if (argc == 3)
   {
      string machineName = argv[1];
      unsigned int number = atoi(argv[2]);

      vector<ThreadedTest*> m_exampleCode;
      vector<ThreadedTest*> m_testCode;       //TODO

      m_exampleCode.push_back(new Example00(machineName));
      m_exampleCode.push_back(new Example01(machineName));
      m_exampleCode.push_back(new Example02(machineName));
      m_exampleCode.push_back(new Example03(machineName));
      m_exampleCode.push_back(new Example04(machineName));
      m_exampleCode.push_back(new Example05(machineName));
      m_exampleCode.push_back(new Example06(machineName));
      m_exampleCode.push_back(new Example07(machineName));
      m_exampleCode.push_back(new Example08(machineName));
      m_exampleCode.push_back(new Example09(machineName));
      m_exampleCode.push_back(new Example10(machineName));
      m_exampleCode.push_back(new Example11(machineName));
      m_exampleCode.push_back(new Example12(machineName));
      m_exampleCode.push_back(new Example13(machineName));

      if(number >= 0 && number <= m_exampleCode.size()-1)
      {
         m_exampleCode[number]->launch(1);
      }
      else
      {
         cout << "Examples numbers are between (0-"
              << m_exampleCode.size() - 1
              << ")"
              << endl;
         return 1;
      }

   }
   else
   {
      cout << "Wrong number of parameters:- 1) IOC name 2) example number"
           << endl;
      return 1;
   }

   return 0;

}

/*---------------------------------------------------------------------------*/
