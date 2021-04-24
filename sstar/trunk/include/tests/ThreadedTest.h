/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_THREADEDTEST_H
#define SSTAR_THREADEDTEST_H

/*---------------------------------------------------------------------------*/

#include <std/random.hpp>
#include <std/generator_iterator.hpp>
#include <std/thread/thread.hpp>
#include <std/bind.hpp>

#include <SStar.h>
#include <tests/ThreadedTest.h>

/*---------------------------------------------------------------------------*/

/**
 * Base class for tests which use an arbitrary number of threads,
 * all executing the same function. Diversity is obtained by mean
 * of random parameters
 */
class ThreadedTest
{

public:

   /**
    * Constructor
    */
   ThreadedTest();

   /**
    * Launch the test
    *
    * @param n Number of threads which will execute the abstract
    *          function run
    */
   void launch(int n);

   /**
    * Randomic sleep with a value which ranged between 1 and 3 seconds
    */
   void randomWait();

protected:

   /**
    * Abstract test code
    */
   virtual void run() = 0;

   /**
    * Generation algorithm
    */
   std::mt19937 rng;

   /**
    * Boost uniform int (1 to 3)
    */

   std::uniform_int<> one_to_three;

   /**
    * Random numbers generator
    */
   std::variate_generator< std::mt19937, std::uniform_int<> > dice2;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
