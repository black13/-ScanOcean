/*-----------------------------------------------------------------------------
 * Copyright (c) 2014, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef GSTAR_COORDINATE_MODEL_H
#define GSTAR_COORDINATE_MODEL_H

/*---------------------------------------------------------------------------*/

#include <QtGui>

/*---------------------------------------------------------------------------*/

namespace gstar
{

class CoordinateModel
{

public:
   /**
    * Constructor
    */
   CoordinateModel();

   /**
    * Destructor
    */
   ~CoordinateModel();

public:

   /**
    * Get scale X
    */
   double getScaleX();

   /**
    * Get scale Y
    */
   double getScaleY();

   /**
    * Get scale Z
    */
   double getScaleZ();

   /**
    * Get the top left X
    */ 
   double getTopLeftX();

   /**
    * Get the top left Y
    */ 
   double getTopLeftY();

   /**
    * Set scale X
    */
   void setScaleX(double x);

   /**
    * Set scale Y
    */
   void setScaleY(double y);

   /**
    * Set scale Z
    */
   void setScaleZ(double z);

   /**
    * Set the top left X and Y 
    */ 
   void setTopLeft(double x, double y);

   /**
    * Get scale X
    */
   void transformPixelToSwsCoor(int pixelX, int pixelY, int swsX, int swsY, int swsZ);

private:

   /**
   * Top left x position
   */
   double m_topLeftX;

   /**
   * Top left y position
   */
   double m_topLeftY;
   /**
    * m_scaleX
    */
   double m_scaleX;

   /**
    * m_scaleY
    */
   double m_scaleY;

   /**
    * m_scaleZ
    */
   double m_scaleZ;

};

}

#endif
