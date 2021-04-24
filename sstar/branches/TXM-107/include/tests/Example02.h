/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_EXAMPLE2_H
#define SSTAR_EXAMPLE2_H

/*---------------------------------------------------------------------------*/

#include <string>

#include <tests/ThreadedTest.h>

/*---------------------------------------------------------------------------*/

using namespace std;

/*---------------------------------------------------------------------------*/

class Example02 : public ThreadedTest
{

public:

   /**
    * Constructor
    *
    * @param name Machine name (e.g. walleye)
    */
   Example02(std::string name);

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
