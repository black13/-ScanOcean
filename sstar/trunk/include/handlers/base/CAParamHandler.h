/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_CA_PARAM_HANDLER_H
#define SSTAR_CA_PARAM_HANDLER_H

/*---------------------------------------------------------------------------*/

#include <handlers/base/CAHandler.h>

/*---------------------------------------------------------------------------*/

/**
 * This class allows to be set with a param (template). This param can then
 * be used by derived classed (e.g. CAEventHandler, CAExceptionHandler)
 */
template <class T>
class CAParamHandler : public CAHandler
{

public:

   /**
    * Constructor without param
    */
   CAParamHandler();

   /**
    * Constructor with param
    *
    * @param args Parameter to be set
    */
   CAParamHandler(T args);

   /**
    * Function to set the param
    *
    * @param args Parameter to be set
    */
   void setArgs(T args);

protected:

   /**
    * Boolean indicating when the parameter has been set
    */
   bool m_bParamSet;

   /**
    * Parameter
    */
   T m_args;

};

/*---------------------------------------------------------------------------*/

template <class T>
CAParamHandler<T>::CAParamHandler()
: m_bParamSet(false)
{

}

/*---------------------------------------------------------------------------*/

template <class T>
CAParamHandler<T>::CAParamHandler(T args)
: m_bParamSet(true),
  m_args(args)
{

}

/*---------------------------------------------------------------------------*/

template <class T>
void CAParamHandler<T>::setArgs(T args)
{

   m_args = args;
   m_bParamSet = true;

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
