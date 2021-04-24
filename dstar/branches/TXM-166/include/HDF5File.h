/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_HDF5_FILE_H
#define DSTAR_HDF5_FILE_H

/*---------------------------------------------------------------------------*/

#include <HDF5Group.h>

#include <string>

/*---------------------------------------------------------------------------*/

namespace dstar
{

class HDF5File
: virtual public HDF5Group
{

public:

   /**
    * Default constructor.
    */
   HDF5File();

   /**
    * Default destructor.
    */
   ~HDF5File();

   /**
    * Get file name.
    *
    * @return File name.
    */
   std::string GetFilename();

   /**
    * Read a HDF5 file.
    *
    * @param path Full path of HDF5 file to read.
    */
   void Read(std::string path);

private:

   /**
    * HDF5 file's full path and filename.
    */
   std::string m_filename;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
