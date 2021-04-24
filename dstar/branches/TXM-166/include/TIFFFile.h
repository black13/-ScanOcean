/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_TIFF_FILE_H
#define DSTAR_TIFF_FILE_H

/*---------------------------------------------------------------------------*/

#include <HDF5Group.h>
#include <tiffio.h>

#include <string>

/*---------------------------------------------------------------------------*/

namespace dstar
{

class TIFFFile
/*: virtual public HDF5Group*/
{

public:

   /**
    * Default constructor.
    */
   TIFFFile();

   /**
    * Default destructor.
    */
   ~TIFFFile();

   /**
    * Get file name.return the object of a TIFF file object
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


   void ReadFile(const char* filename);

   TIFF* getTIFFImageHandler();

private:

   /**
    * HDF5 file's full path and filename.
    */
   std::string m_filename;

   // Dataset name
   std::string m_name;

   TIFF* m_img;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
