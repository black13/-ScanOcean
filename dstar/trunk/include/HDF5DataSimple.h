/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_HDF5_DATA_SIMPLE_H
#define DSTAR_HDF5_DATA_SIMPLE_H

/*---------------------------------------------------------------------------*/

#include <HDF5Data.h>

#include <boost/smart_ptr/shared_array.hpp>
#include <hdf5.h>
#include <sstream>

/*---------------------------------------------------------------------------*/

namespace dstar
{

/**
 * HDF5DataSimple class
 */
class HDF5DataSimple
: virtual public HDF5Data
{

public:

   /**
    * Default constructor.
    */
   HDF5DataSimple();

   /**
    * Virtual destructor.
    */
   virtual ~HDF5DataSimple();

   /**
    * Get data in current selection.
    *
    * Use getType() to determine the data type and cast it appropriately.
    *
    * @return Data in current selection as a shared_array of char.
    */
   virtual boost::shared_array<char> getData() const;

   /**
    * Get a list of object property descriptions. Properties
    * are stored as pairs of strings where the first element in the pair is
    * the name of the property and the second element in the pair is the value.
    *
    * @return List of object property descriptions.
    */
   virtual
   std::vector<std::pair<std::string, std::string> > getProperties() const;

   /**
    * Load this object from a specified HDF5 object id.
    *
    * The HDF5 object id must be opened by the caller, and the caller is
    * responsible for the HDF5 resource. Currently, DStar keeps all HDF5
    * resources open, and closes them when the HDF5 file is closed.
    *
    * @param id HDF5 object id to load.
    */
   virtual void loadFromHDF5Id(hid_t id);

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
