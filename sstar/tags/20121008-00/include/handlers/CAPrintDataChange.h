/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CA_PRINT_DATA_CHANGE_H
#define SSTAR_CA_PRINT_DATA_CHANGE_H

/*---------------------------------------------------------------------------*/

#include <cadef.h>
#include <iostream>
#include <handlers/base/CAEventHandler.h>

/*---------------------------------------------------------------------------*/

/**
 * Example of subscription handler which just prints a data change
 * on a given output stream
 *
 * The class is a template, so to handle different data type
 */

template <class T>
class CAPrintDataChange : public CAEventHandler
{

public:

   /**
    * Constructor
    *
    * @param out Output stream
    * @param tabs Number of tabs before printing
    */
   CAPrintDataChange(std::ostream& out = std::cout, int tabs = 0);

   /**
    * Constructor
    *
    * @param arg Epics args
    * @param out Output stream
    * @param tabs Number of tabs before printing
    */
   CAPrintDataChange(struct event_handler_args args,
                     std::ostream& out = std::cout,
                     int tabs = 0);

   /**
    * The function prints the data change on the output
    * stream
    */
   virtual void onSuccess ();

   /**
    * The function just prints FAILURE
    */
   virtual void onFailure ();

private:

   /**
    * Output stream reference
    */
   std::ostream& m_out;

   /**
    * Number of tabs
    */
   int m_tabs;

};

/*---------------------------------------------------------------------------*/

template <class T>
CAPrintDataChange<T>::CAPrintDataChange(std::ostream& out, int tabs)
: CAEventHandler(),
  m_out(out),
  m_tabs(tabs)
{

}

/*---------------------------------------------------------------------------*/

template <class T>
CAPrintDataChange<T>::CAPrintDataChange(struct event_handler_args args,
                                        std::ostream& out,
                                        int tabs)
: CAEventHandler(args),
  m_out(out),
  m_tabs(tabs)
{

}

/*---------------------------------------------------------------------------*/

template <class T>
void CAPrintDataChange<T>::onSuccess ()
{

   chid pCh = m_args.chid;
   T* val = (T*) m_args.dbr;

   int numBytes = dbr_size_n(m_args.type, m_args.count);
   int n = numBytes / sizeof(T);

   for(int i = 0; i < m_tabs; i++)
      m_out << "\t";


   m_out << val[0];
   for(int i = 1; i < n; i++)
      m_out << " " << val[i];
   m_out << std::endl;

}

/*---------------------------------------------------------------------------*/

template <class T>
void CAPrintDataChange<T>::onFailure ()
{

   m_out << "FAILURE" << std::endl;

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
