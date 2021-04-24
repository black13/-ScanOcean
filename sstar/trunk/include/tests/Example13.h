/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_EXAMPLE13_H
#define SSTAR_EXAMPLE13_H

/*---------------------------------------------------------------------------*/

#include <tests/ThreadedTest.h>

/*---------------------------------------------------------------------------*/

class Example13 : public ThreadedTest
{

public:

   /**
    * Constructor
    *
    * @param name Machine name (e.g. walleye)
    */
   Example13(std::string name);

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
