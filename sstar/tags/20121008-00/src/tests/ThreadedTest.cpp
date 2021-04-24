/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/ThreadedTest.h>

/*---------------------------------------------------------------------------*/

ThreadedTest::ThreadedTest()
: one_to_three( 1, 3 ),
  dice2(rng, one_to_three)
{

}

/*---------------------------------------------------------------------------*/

void ThreadedTest::launch(int n)
{

   boost::thread** threads;

   //Create and launch n threads
   threads = new boost::thread*[n];
   for(int i = 0; i < n; i++)
   {
      threads[i] = new boost::thread(boost::bind(&ThreadedTest::run, this));
   }

   //Wait for all the threads to finish
   for(int i = 0; i < n; i++)
   {
      threads[i]->join();
   }

   //Free memory
   for(int i = 0; i < 0; i++)
   {
      delete threads[i];
   }
   delete[] threads;

}

/*---------------------------------------------------------------------------*/

void ThreadedTest::randomWait()
{

   sleep(dice2());

}

/*---------------------------------------------------------------------------*/
