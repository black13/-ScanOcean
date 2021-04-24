/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_EXAMPLE1_H
#define SSTAR_EXAMPLE1_H

/*---------------------------------------------------------------------------*/

#include <string>

#include <tests/ThreadedTest.h>

/*---------------------------------------------------------------------------*/

class Example01 : public ThreadedTest
{

public:

   /**
    * Constructor
    *
    * @param name Machine name (e.g. walleye)
    */
   Example01(std::string name);

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
