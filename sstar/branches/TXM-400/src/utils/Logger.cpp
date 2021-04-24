/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <utils/Logger.h>

/*---------------------------------------------------------------------------*/

boost::mutex Logger::s_mutex;

/*---------------------------------------------------------------------------*/

Logger* Logger::s_pInstance = NULL;

/*---------------------------------------------------------------------------*/

bool Logger::m_isActive = true;

/*---------------------------------------------------------------------------*/

IndentedWriter::IndentedWriter(Logger* logger, std::string title)
:  m_writer(logger),
   m_logger(logger),
   m_title(title)

{

   m_logger->s_mutex.lock();
   boost::thread::id tid = boost::this_thread::get_id();

   if(m_logger->m_isActive)
   {
      for(int i = 0 ; i < getIndents(); i++) std::cout << "   ";
      std::cout << m_logger->m_threadNamesMap[tid] << ": ";
      std::cout << "--" << m_title << " START--" << std::endl;

   }

   addIndent();

   m_logger->s_mutex.unlock();

}

/*---------------------------------------------------------------------------*/

IndentedWriter::~IndentedWriter()
{

   m_logger->s_mutex.lock();
   removeIndent();
   boost::thread::id tid = boost::this_thread::get_id();

   if(m_logger->m_isActive)
   {
      for(int i = 0 ; i < getIndents(); i++) std::cout << "   ";
      std::cout << m_logger->m_threadNamesMap[tid] << ": ";
      std::cout << "--" << m_title << " END--" << std::endl;
   }

   m_logger->s_mutex.unlock();

}

/*---------------------------------------------------------------------------*/

Writer& IndentedWriter::operator()()
{

   m_logger->s_mutex.lock();
   boost::thread::id tid = boost::this_thread::get_id();

   if(m_logger->m_isActive)
   {
      for(int i = 0 ; i < getIndents(); i++) std::cout << "   ";
      std::cout << m_logger->m_threadNamesMap[tid] << ": ";
   }


   m_logger->s_mutex.unlock();
   return m_writer;

}

/*---------------------------------------------------------------------------*/

void IndentedWriter::addIndent()
{

   boost::thread::id tid = boost::this_thread::get_id();
   boost::unordered_map<boost::thread::id, int >::const_iterator
         iter = m_logger->m_tabsMap.find(tid);
   if(iter == m_logger->m_tabsMap.end())
   {
      //m_tabsMap[tid] = 0;
      m_logger->m_tabsMap[tid] = m_logger->idGen * 10;
      std::ostringstream os;
      os << "T" << m_logger->idGen;
      m_logger->m_threadNamesMap[tid] = os.str();
      m_logger->idGen++;
   }
   else
   {
      m_logger->m_tabsMap[tid]++;
   }

}

/*---------------------------------------------------------------------------*/

void IndentedWriter::removeIndent()
{

   boost::thread::id tid = boost::this_thread::get_id();
   boost::unordered_map<boost::thread::id, int >::const_iterator
         iter = m_logger->m_tabsMap.find(tid);
   if(iter == m_logger->m_tabsMap.end())
   {
      //m_tabsMap[tid] = 0;
      m_logger->m_tabsMap[tid] = m_logger->idGen * 10;
      std::ostringstream os;
      os << "T" << m_logger->idGen;
      m_logger->m_threadNamesMap[tid] = os.str();
      m_logger->idGen++;
   }
   else
   {
      if(m_logger->m_tabsMap[tid] > 0)
         m_logger->m_tabsMap[tid]--;
   }

}

/*---------------------------------------------------------------------------*/

int IndentedWriter::getIndents()
{

   boost::thread::id tid = boost::this_thread::get_id();
   boost::unordered_map<boost::thread::id, int >::const_iterator
      iter = m_logger->m_tabsMap.find(tid);

   if(iter == m_logger->m_tabsMap.end())
   {
      //m_tabsMap[tid] = 0;
      m_logger->m_tabsMap[tid] = m_logger->idGen * 10;
      std::ostringstream os;
      os << "T" << m_logger->idGen;
      m_logger->m_threadNamesMap[tid] = os.str();
      m_logger->idGen++;
   }

   int result = m_logger->m_tabsMap[tid];
   return result;

}

/*---------------------------------------------------------------------------*/

Logger* Logger::getInstance()
{

   if(s_pInstance == NULL)
   {
      s_mutex.lock();
      if(s_pInstance == NULL)
      {
         s_pInstance = new Logger;
      }

      s_mutex.unlock();
   }
   return s_pInstance;

}

/*---------------------------------------------------------------------------*/

IndentedWriter Logger::getIndentedWriter(std::string title)
{

   Logger* instance = Logger::getInstance();
   return IndentedWriter(instance,title);

}

/*---------------------------------------------------------------------------*/

Logger::Logger()
{

   idGen = 0;

}

/*---------------------------------------------------------------------------*/

void Logger::setActive(bool value)
{

   m_isActive = value;

}

/*---------------------------------------------------------------------------*/

bool Logger::isActive()
{

   return m_isActive;

}

/*---------------------------------------------------------------------------*/

Writer::Writer(Logger* logger)
: m_logger(logger)
{

}

/*---------------------------------------------------------------------------*/

Writer& operator<< (Writer& w, std::string s)
{

   if(w.m_logger->isActive())
   {
      std::cout << s;
   }
   return w;

}

/*---------------------------------------------------------------------------*/

Writer& operator<< (Writer& w, const char* s)
{

   if(w.m_logger->isActive())
   {
      std::cout << s;
   }
   return w;

}

/*---------------------------------------------------------------------------*/

Writer& operator<< (Writer& w, int v)
{

   if(w.m_logger->isActive())
   {
      std::cout << v;
   }
   return w;

}

/*---------------------------------------------------------------------------*/

Writer& Writer::operator<<( std::ostream&(*f)(std::ostream&) )
{

   if(m_logger->isActive())
   {
      std::cout << f;
   }
   return *this;

}

/*---------------------------------------------------------------------------*/
