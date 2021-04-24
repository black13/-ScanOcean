/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_LOGGER_H
#define SSTAR_LOGGER_H

/*---------------------------------------------------------------------------*/

#include <iostream>

#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/unordered_map.hpp>

#include <utils/ThreadHasher.h>

/*---------------------------------------------------------------------------*/

class Logger;

/*---------------------------------------------------------------------------*/

/**
 * Output Stream class
 */
class Writer
{

public:

   /**
    * Constructor
    *
    * @param logger Pointer to the logger
    */
   Writer(Logger* logger);

   /**
    * << Operator Overloading
    */
   Writer& operator<<( std::ostream&(*f)(std::ostream&) );

   /**
    * << Operator Overloading
    */
   friend Writer& operator<< (Writer& w, std::string s);

   /**
    * << Operator Overloading
    */
   friend Writer& operator<< (Writer& w, const char* s);

   /**
    * << Operator Overloading
    */
   friend Writer& operator<< (Writer& w, int v);

private:

   /**
    * Pointer to the logger
    */
   Logger* m_logger;

};

/*---------------------------------------------------------------------------*/

/**
 * Indented writer
 */
class IndentedWriter
{

public:

   /**
    * Constructor
    *
    * @param logger Pointer to the logger
    * @param title Used string title
    */
   IndentedWriter(Logger* logger, std::string title);

   /**
    * Destructor
    */
   ~IndentedWriter();

   /**
    * () operator overloading to obtain the output stream
    */
   Writer& operator()();

private:

   /**
    * Output stream object
    */
   Writer m_writer;

   /**
    * Pointer to the logger
    */
   Logger* m_logger;

   /**
    * Title string
    */
   std::string m_title;

   /**
    * Add Indent Accessory
    */
   void addIndent();

   /**
    * Remove Indent Accessory
    */
   void removeIndent();

   /**
    * Get Indents Accessory
    */
   int getIndents();

};

/*---------------------------------------------------------------------------*/

/**
 * Logger class
 */
class Logger
{

public:

   /**
    * Get the singleton instance
    *
    * @return Logger instance
    */
   static Logger* getInstance();

   /**
    * Get indented writer
    *
    * @return Indented writer
    */
   static IndentedWriter getIndentedWriter(std::string title);

   /**
    * Check if the logger is active
    *
    * @return True if the logger is active, false otherwise
    */
   static bool isActive();

   /**
    * Set the logger active
    *
    * @param value Value to activate or deactivate the logger
    */
   static void setActive(bool value);

   /**
    * Friend IndentedWriter
    */
   friend class IndentedWriter;

   /**
    * Friend Writer
    */
   friend class Writer;

private:

   /**
    * Private Constructor
    */
   Logger() ;

   /**
    * Instance pointer
    */
   static Logger* s_pInstance;

   /**
    * Mutex
    */
   static boost::mutex s_mutex;

   /**
    * ID Generator
    */
   int idGen;

   /**
    * Indents Map
    */
   boost::unordered_map<boost::thread::id, int> m_tabsMap;

   /**
    * Threads name Map
    */
   boost::unordered_map<boost::thread::id, std::string> m_threadNamesMap;

   /**
    * State flag
    */
   static bool m_isActive;

};

/*---------------------------------------------------------------------------*/

/**
 * << Operator overloading
 */
Writer& operator<< (Writer& w, std::string s);

/*---------------------------------------------------------------------------*/

/**
 * << Operator overloading
 */
Writer& operator<< (Writer& w, const char* s);

/*---------------------------------------------------------------------------*/

/**
 * << Operator overloading
 */
Writer& operator<< (Writer& w, int v);

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
