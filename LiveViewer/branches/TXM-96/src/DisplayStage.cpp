/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <DisplayStage.h>

#include <stdio.h>

/*---------------------------------------------------------------------------*/

DisplayStage::DisplayStage()
: QObject(0), FinalStage()
{

}

/*---------------------------------------------------------------------------*/

DisplayStage::~DisplayStage()
{

}

/*---------------------------------------------------------------------------*/

QImage& DisplayStage::getImage()
{

   return m_img;

}

/*---------------------------------------------------------------------------*/

void DisplayStage::process(gstar::Array& input)
{

   // Emit new frame available
   emit newFrame(const_cast<gstar::Array*>(&input));

}

/*---------------------------------------------------------------------------*/
