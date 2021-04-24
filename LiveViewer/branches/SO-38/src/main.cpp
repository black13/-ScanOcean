/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <QApplication>

#include <LiveViewer.h>

/*---------------------------------------------------------------------------*/

int main(int argc, char** argv)
{

   // Startup Qt
   QApplication a(argc, argv);

   // Startup application
   LiveViewer w;
   w.show();

   // Run
   return a.exec();

}

/*---------------------------------------------------------------------------*/
