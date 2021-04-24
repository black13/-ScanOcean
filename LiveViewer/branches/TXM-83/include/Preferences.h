/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef PREFERENCES_H
#define PREFERENCES_H

/*---------------------------------------------------------------------------*/

#include <QMap>
#include <QString>
#include <QVariant>

/*---------------------------------------------------------------------------*/

/**
 * @brief Read and save preferences between application restarts
 */
class Preferences
{

public:

   /**
    * List of enumerated values that may be stored in the application's
    * preferences file.
    */
   enum ValueKey {
      PVPrefixString,   /*!< Prefix for PV. */
      HISTBins,         /*!< Number of bins for histogram. */
      HISTType,         /*!< Type of histogram. */
      ROIPVString,      /*!< ROI to PV mappings. */
      ROICountLimit,    /*!< Max number of ROIs that can be defined */
   };

   /**
    * Constructor
    */
   Preferences();

   /**
    * Read a ValueKey from persistent storage.
    *
    * @param key - the ValueKey enum for the key to read
    * @return value for given key as a QVariant
    */
   QVariant readValueKey(Preferences::ValueKey key);

   /**
    * Save a ValueKey to persistent storage.
    *
    * @param key - the ValueKey enum for the key to read
    * @param value - the value to store as a QVariant
    */
   void saveValueKey(Preferences::ValueKey key, QVariant value);

private:

   /**
    * Helper method to create value-key map
    */
   void createValueKeyMap();

   /**
    * Map storing value keys and their text descriptions
    */
   QMap<Preferences::ValueKey, QString> m_mapValueKey;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
