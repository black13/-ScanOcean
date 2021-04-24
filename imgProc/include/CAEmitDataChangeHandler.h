/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef CA_EMIT_DATA_CHANGE_HANDLER_H
#define CA_EMIT_DATA_CHANGE_HANDLER_H

/*---------------------------------------------------------------------------*/

#include <cadef.h>
#include <iostream>
#include <handlers/base/CAEventHandler.h>

/*---------------------------------------------------------------------------*/

template <class T, class K>
class CAEmitDataChangeHandler
: public CAEventHandler
{

public:

   /**
    * Constructor
    *
    * @param model
    * @param funcPtr
    *
    */
   CAEmitDataChangeHandler(K* model, void (K::*funcPtr)(T));

   /**
    * On failure function
    */
   virtual void onFailure();

   /**
    * On success function
    */
   virtual void onSuccess();

private:

   /**
    * Motor model
    */
   K* m_model;

   /**
    * Function pointer
    */
   void (K::*m_funcPtr)(T);

};

/*---------------------------------------------------------------------------*/

template <class T, class K>
CAEmitDataChangeHandler<T,K>::CAEmitDataChangeHandler(K* model,
                            void (K::*funcPtr)(T))
: CAEventHandler(), m_model(model), m_funcPtr(funcPtr)
{

}

/*---------------------------------------------------------------------------*/

template <class T, class K>
void CAEmitDataChangeHandler<T,K>::onFailure()
{

   std::cout << "FAILURE" << std::endl;

}

/*---------------------------------------------------------------------------*/

template <class T, class K>
void CAEmitDataChangeHandler<T,K>::onSuccess()
{

   T* val = (T*) m_args.dbr;

   (m_model->*m_funcPtr)((T) val[0]);

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
