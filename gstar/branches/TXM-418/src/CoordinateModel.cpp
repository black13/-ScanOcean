/*-----------------------------------------------------------------------------
 * Copyright (c) 2014, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <CoordinateModel.h>

using namespace gstar;

/*---------------------------------------------------------------------------*/

CoordinateModel::CoordinateModel()
:m_scaleX(0)
{

}

/*---------------------------------------------------------------------------*/

CoordinateModel::~CoordinateModel()
{


}

/*---------------------------------------------------------------------------*/

double CoordinateModel::getScaleX()
{

   return m_scaleX;

}

/*---------------------------------------------------------------------------*/

double CoordinateModel::getScaleY()
{

   return m_scaleY;

}

/*---------------------------------------------------------------------------*/

double CoordinateModel::getScaleZ()
{

   return m_scaleZ;

}

/*---------------------------------------------------------------------------*/

double CoordinateModel::getTopLeftX()
{

   return m_topLeftX;

}

/*---------------------------------------------------------------------------*/

double CoordinateModel::getTopLeftY()
{

   return m_topLeftY;

}

/*---------------------------------------------------------------------------*/

void CoordinateModel::setScaleX(double x)
{

   m_scaleX =  x;

}

/*---------------------------------------------------------------------------*/

void CoordinateModel::setScaleY(double y)
{

   m_scaleY = y;

}

/*---------------------------------------------------------------------------*/

void CoordinateModel::setScaleZ(double z)
{

   m_scaleZ = z;

}


/*---------------------------------------------------------------------------*/

void CoordinateModel::setTopLeft(double x, double y)
{

   m_topLeftX = x;
   m_topLeftY = y;

}

/*---------------------------------------------------------------------------*/

void CoordinateModel::transformPixelToSwsCoor(int pixelX, int pixelY, int swsX,
                                              int swsY, int swsZ)
{

   swsX = pixelX * m_scaleX;
   swsY = pixelY * m_scaleY;
   swsZ = m_scaleZ;

}


/*---------------------------------------------------------------------------*/
