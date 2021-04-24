/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <QApplication>

#include <SplashExample.h>

/*---------------------------------------------------------------------------*/

int main(int argc, char** argv)
{

   QApplication a(argc, argv);

   SplashExample* splashExample = new SplashExample();
   splashExample -> show();

   return a.exec();

}

/*---------------------------------------------------------------------------*/
