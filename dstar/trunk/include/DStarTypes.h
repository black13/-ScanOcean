/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DSTAR_TYPES_H
#define DSTAR_TYPES_H

/*---------------------------------------------------------------------------*/

#include <string>

/*---------------------------------------------------------------------------*/

/**
 * @brief The DStar data model namespace
 *
 * This is the namespace for all things related to the DStar data model
 * namespace.
 */
namespace dstar {

   /**
    * DStar data C type enumerations.
    */
   enum DataType {

      /** A native char */
      Char = 1,

      /** A native short char */
      ShortChar,

      /** A native unsigned char */
      UnsignedChar,

      /** A native short */
      Short,

      /** A native unsigned short */
      UnsignedShort,

      /** A native short - only 12 bits are used */
      Short12,

      /** A native short - only 12 bits are used */
      UnsignedShort12,

      /** A native int */
      Int,

      /** A native unsigned int */
      UnsignedInt,

      /** A native long */
      Long,

      /** A native unsigned long */
      UnsignedLong,

      /** A native long long */
      LongLong,

      /** A native unsigned long long */
      UnsignedLongLong,

      /** A native float */
      Float,

      /** A native double */
      Double,

      /** A native long double */
      LongDouble,

      /** A string */
      String
   };

   /**
    * DStar byte order indicators.
    */
   enum Endianness {

      /** Big Endian - most-significant byte first */
      BigEndian,

      /** Little Endian - least-significant byte first */
      LittleEndian
   };

   /**
    * Get a textual description of a DataType
    *
    * @param type The DataType.
    * @return Textual description of DataType as a string.
    */
   static std::string getDataTypeAsString(DataType type) {

      switch (type) {
      case Char:
         return "Char";
         break;
      case ShortChar:
         return "ShortChar";
         break;
      case UnsignedChar:
         return "UnsignedChar";
         break;
      case Short:
         return "Short";
         break;
      case UnsignedShort:
         return "UnsignedShort";
         break;
      case Int:
         return "Int";
         break;
      case UnsignedInt:
         return "UnsignedInt";
         break;
      case Long:
         return "Long";
         break;
      case UnsignedLong:
         return "UnsignedLong";
         break;
      case LongLong:
         return "LongLong";
         break;
      case UnsignedLongLong:
         return "UnsignedLongLong";
         break;
      case Float:
         return "Float";
         break;
      case Double:
         return "Double";
         break;
      case LongDouble:
         return "LongDouble";
         break;
      case String:
         return "String";
         break;
      default:
         break;
      };

      return "Unknown";

   }

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
