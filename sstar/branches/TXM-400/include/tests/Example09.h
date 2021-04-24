/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_EXAMPLE9_H
#define SSTAR_EXAMPLE9_H

/*---------------------------------------------------------------------------*/

#include <tests/ThreadedTest.h>

/*---------------------------------------------------------------------------*/

class Example09 : public ThreadedTest
{

public:

   enum mode
   {
      ONE = 0,
      FIVE,
      TWENTY
   };

   /**
    * Constructor
    *
    * @param name Machine name (e.g. walleye)
    */
   Example09(std::string name);

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

   /**
    * Print Utility
    */
   void printMode(mode m);

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
