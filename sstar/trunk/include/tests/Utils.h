/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_EXAMPLEUTILS_H
#define SSTAR_EXAMPLEUTILS_H

/*---------------------------------------------------------------------------*/

#include <iostream>

#include <std/shared_ptr.hpp>

#include <SStar.h>
#include <tests/ThreadedTest.h>

using namespace std;

/*---------------------------------------------------------------------------*/

template <class T>
T readValue(std::shared_ptr<PV>& pv);

/*---------------------------------------------------------------------------*/

template <class T>
T readValue(std::shared_ptr<PV>& pv)
{

   T read;
   CAGetTotalCopy<T> reader(&read);  //1) Define the reading operation
   pv->synGet(1,&reader);            //2) Perform the synGet
   return read;

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
