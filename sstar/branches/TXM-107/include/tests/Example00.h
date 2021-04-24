/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_EXAMPLE0_H
#define SSTAR_EXAMPLE0_H

/*---------------------------------------------------------------------------*/

#include <string>

#include <tests/ThreadedTest.h>

/*---------------------------------------------------------------------------*/

using namespace std;

/*---------------------------------------------------------------------------*/

class Example00 : public ThreadedTest
{

public:

   /**
    * Constructor
    *
    * @param name Machine name (e.g. walleye)
    */
   Example00(std::string name);

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
