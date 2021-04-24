/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <Preferences.h>

#include <QSettings>

/*---------------------------------------------------------------------------*/

Preferences::Preferences()
{

   // Create map of value keys to string names
   createValueKeyMap();

}

/*---------------------------------------------------------------------------*/

void Preferences::createValueKeyMap()
{

   m_mapValueKey.insert(PVPrefixString, "PVPrefixString");
   m_mapValueKey.insert(ROIPVString, "ROIPVString");

}

/*---------------------------------------------------------------------------*/

QVariant Preferences::readValueKey(Preferences::ValueKey key)
{

   // Settings
   QSettings s(QSettings::IniFormat,
               QSettings::UserScope,
               "UChicagoArgonneLLC",
               "LiveViewer");

   // Read value
   s.beginGroup("Values");
   QVariant value = s.value(m_mapValueKey[key]);
   s.endGroup();

   // Return value
   return value;

}

/*---------------------------------------------------------------------------*/

void Preferences::saveValueKey(Preferences::ValueKey key, QVariant value)
{

   // Settings
   QSettings s(QSettings::IniFormat,
               QSettings::UserScope,
               "UChicagoArgonneLLC",
               "LiveViewer");

   // Write value
   s.beginGroup("Values");
   s.setValue(m_mapValueKey[key], value);
   s.endGroup();

}

/*---------------------------------------------------------------------------*/
