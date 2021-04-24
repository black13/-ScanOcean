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
    * Read a tiff file.
    *
    * @param path Full path of tiff file to read.
    */
   void Read(std::string path);

   /**
    * Read a tiff file.
    *
    * @param path Full path of tiff file to read.
    */
   void ReadFile(const char* filename);

   /**
    * Get tiff image handler.
    *
    */
   TIFF* getTIFFImageHandler();

private:

   /**
    * TIff file's full path and filename.
    */
   std::string m_filename;

   /**
    * Tiff name
    */
   std::string m_name;

   /**
    * Tiff image handler
    */
   TIFF* m_img;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
