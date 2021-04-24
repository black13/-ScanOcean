/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_THREADEDTEST_H
#define SSTAR_THREADEDTEST_H

/*---------------------------------------------------------------------------*/

#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

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
   boost::mt19937 rng;

   /**
    * Boost uniform int (1 to 3)
    */

   boost::uniform_int<> one_to_three;

   /**
    * Random numbers generator
    */
   boost::variate_generator< boost::mt19937, boost::uniform_int<> > dice2;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
