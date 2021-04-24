/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef GSTAR_COLOR_GRADIENT_DISPLAY_H
#define GSTAR_COLOR_GRADIENT_DISPLAY_H

/*---------------------------------------------------------------------------*/

#include <QWidget>
#include <QPainter>

#include <ColorTransferFunction.h>

/*---------------------------------------------------------------------------*/

namespace gstar
{

class ColorGradientDisplay
: public QWidget
{

   Q_OBJECT

public:

   ColorGradientDisplay(QWidget* widget = 0);
   void paintEvent(QPaintEvent* event);
   void setColorTransferFunction(ColorTransferFunction ctf);

private:

   ColorTransferFunction m_ctf;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
