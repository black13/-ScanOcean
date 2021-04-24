/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_EXAMPLE12_H
#define SSTAR_EXAMPLE12_H

/*---------------------------------------------------------------------------*/

#include <tests/ThreadedTest.h>

/*---------------------------------------------------------------------------*/

class Example12 : public ThreadedTest
{

public:

   /**
    * Constructor
    *
    * @param name Machine name (e.g. walleye)
    */
   Example12(std::string name);

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
