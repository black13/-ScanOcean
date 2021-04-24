/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_EXAMPLE3_H
#define SSTAR_EXAMPLE3_H

/*---------------------------------------------------------------------------*/

#include <string>

#include <tests/ThreadedTest.h>

/*---------------------------------------------------------------------------*/

using namespace std;

/*---------------------------------------------------------------------------*/

class Example03 : public ThreadedTest
{

public:

   /**
    * Constructor
    *
    * @param name Machine name (e.g. walleye)
    */
   Example03(std::string name);

protected:

   /**
    * Code
    */
   virtual void run();

private:

   /**
    * Machine name
    */
   std::string m_name;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
