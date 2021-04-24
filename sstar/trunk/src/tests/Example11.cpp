/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <tests/Example11.h>

#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>

#include <tests/Utils.h>
#include <SStar.h>

/*---------------------------------------------------------------------------*/

using boost::shared_ptr;
using std::string;
using std::cout;
using std::endl;

/*---------------------------------------------------------------------------*/

Example11::Example11(string name)
: ThreadedTest()
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void Example11::run()
{

   Logger::setActive(false);

   ChannelAccess* ca;

   ca = ChannelAccess::getInstance();

   shared_ptr<PV> m_ArraySize0_RBV;
   shared_ptr<PV> m_ArraySize1_RBV;
   shared_ptr<PV> m_ArraySize2_RBV;
   shared_ptr<PV> m_ColorMode_RBV;
   shared_ptr<PV> m_ArrayData;
   shared_ptr<PV> m_UniqueId_RBV;

   m_ArraySize0_RBV = ca->getPV(m_name + ":image1:ArraySize0_RBV",1,5);
   m_ArraySize1_RBV = ca->getPV(m_name + ":image1:ArraySize1_RBV",1,5);
   m_ArraySize2_RBV = ca->getPV(m_name + ":image1:ArraySize2_RBV",1,5);
   m_ColorMode_RBV = ca->getPV(m_name + ":image1:ColorMode_RBV",1,5);
   m_ArrayData = ca->getPV(m_name + ":image1:ArrayData",1,5);
   m_UniqueId_RBV = ca->getPV(m_name + ":image1:UniqueId_RBV",1,5);

   CAPrintDataChange<int>* dc = new CAPrintDataChange<int>(std::cout,1);
   m_UniqueId_RBV->subscribeDataChangeEvent(dc);

   long width = 0;
   long height = 0;
   long depth = 0;
   int colorMode = 0;
   CAGetTotalCopy<long> widthReader(&width);
   CAGetTotalCopy<long> heightReader(&height);
   CAGetTotalCopy<long> depthReader(&depth);
   CAGetTotalCopy<int> colorModeReader(&colorMode);

   m_ArraySize0_RBV->synGet(1,&widthReader);
   m_ArraySize1_RBV->synGet(1,&heightReader);
   m_ArraySize2_RBV->synGet(1,&depthReader);
   m_ColorMode_RBV->synGet(1,&colorModeReader);

   cout << width << endl;
   cout << height << endl;
   cout << depth << endl;
   cout << colorMode << endl;

   while(true) sleep(5);
}

/*---------------------------------------------------------------------------*/
