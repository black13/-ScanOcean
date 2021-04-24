/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <TIFFFile.h>

using namespace dstar;
#include <iostream>
/*---------------------------------------------------------------------------*/

TIFFFile::TIFFFile()
{


}

/*---------------------------------------------------------------------------*/

TIFFFile::~TIFFFile()
{

   // Close file
   TIFFClose(m_img);

}

/*---------------------------------------------------------------------------*/

std::string TIFFFile::GetFilename()
{

   return m_filename;

}

/*---------------------------------------------------------------------------*/

void TIFFFile::Read(std::string path)
{

   // Save filename
   m_filename = path;

   ReadFile(m_filename.c_str());

   m_name = path;

   // Load file root

}

/*---------------------------------------------------------------------------*/
void TIFFFile::ReadFile(const char* filename)
{

   // Supress warnings and errors
   TIFFSetWarningHandler(NULL);
   TIFFSetErrorHandler(NULL);

   // Attempt to open TIFF file
   m_img = TIFFOpen(filename, "r");

   // Return if can't open file
   if (m_img == NULL) {
      return;
   }

   // Return
   return;

}

/*---------------------------------------------------------------------------*/
TIFF* TIFFFile::getTIFFImageHandler()
{
   return m_img;
}


/*---------------------------------------------------------------------------*/
