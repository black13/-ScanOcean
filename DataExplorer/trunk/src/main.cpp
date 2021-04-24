/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <DStar.h>
#include <DataExplorer.h>

#include <boost/shared_ptr.hpp>

#include <QApplication>

using dstar::HDF5File;

/*---------------------------------------------------------------------------*/

int main(int argc, char** argv)
{

   // Startup Qt
   QApplication a(argc, argv);

   // Startup application
   DataExplorer w;
   w.show();

   //boost::shared_ptr<HDF5File> file = boost::shared_ptr<HDF5File>(new HDF5File());
   //file -> Read("/Users/schwarz/Desktop/Sam_test_sinogram_small.h5");

   return a.exec();

}

/*---------------------------------------------------------------------------*/
