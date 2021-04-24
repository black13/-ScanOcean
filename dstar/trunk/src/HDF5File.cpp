/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <HDF5File.h>

using namespace dstar;
#include <iostream>
/*---------------------------------------------------------------------------*/

HDF5File::HDF5File()
: HDF5Group()
{

}

/*---------------------------------------------------------------------------*/

HDF5File::~HDF5File()
{

   // Close file if it's open
   if (m_hdf5Id >= 0) {
      H5Fclose(m_hdf5Id);
      m_hdf5Id = -1;
      std::cerr << "Closing file. " << m_name << std::endl;
   }

}

/*---------------------------------------------------------------------------*/

std::string HDF5File::GetFilename()
{

   return m_filename;

}

/*---------------------------------------------------------------------------*/

void HDF5File::Read(std::string path)
{

   // Save filename
   m_filename = path;

   // Force everything to close when file is closed
   hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);
   H5Pset_fclose_degree(fapl, H5F_CLOSE_STRONG);

   // Try to open the file
   m_hdf5Id = H5Fopen(m_filename.c_str(), H5F_ACC_RDONLY, fapl);

   if (m_hdf5Id < 0) {
      return;
   }

   m_name = path;

   // Load file root
   loadFromHDF5Id(m_hdf5Id);

}

/*---------------------------------------------------------------------------*/
