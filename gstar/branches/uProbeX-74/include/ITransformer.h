/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef ITRANSFORMER_H
#define ITRANSFORMER_H

#include <QString>

/*---------------------------------------------------------------------------*/

namespace gstar
{

/**
 * @brief Transformation Interface
 *
 */
class ITransformer
{

public:

   /**
    * Constructor.
    */
   ITransformer();

   /**
    * Destructor.
    */
   ~ITransformer();

   /**
    * @brief getVariable
    * @param name
    * @param val
    * @return
    */
   virtual bool getVariable(QString name, double *val) = 0;

   /**
    * @brief setVariable
    * @param name
    * @param val
    * @return
    */
   virtual bool setVariable(QString name, double val) = 0;

   /**
    * @brief transformCommand
    * @param inX
    * @param inY
    * @param inZ
    * @param outX
    * @param outY
    */
   virtual void transformCommand(double inX,
                                 double inY,
                                 double inZ,
                                 double *outX,
                                 double *outY,
                                 double *outZ) = 0;

};

}
/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
