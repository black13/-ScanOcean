/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ColorGradientDisplay.h>

using namespace gstar;

/*---------------------------------------------------------------------------*/

ColorGradientDisplay::ColorGradientDisplay(QWidget* widget)
   : QWidget(widget)
{

   setMaximumHeight(25);

}

/*---------------------------------------------------------------------------*/

void ColorGradientDisplay::paintEvent(QPaintEvent* event)
{

   Q_UNUSED(event)

   double r, g, b;
   double min, max;

   QPainter p(this);

   QImage sim(size(), QImage::Format_RGB32);
   QLinearGradient sg(0, 0, width(), 0);

   m_ctf.getTotalRange(&min, &max);
   for (double i = min ; i < max ; i += 1.0) {
      m_ctf.getColorAt(i, &r, &g, &b);
      sg.setColorAt((i - min) / (max - min), QColor(r, g, b));
   }

   QPainter pim(&sim);
   pim.fillRect(rect(), sg);

   p.drawImage(rect(), sim, sim.rect());

   p.setPen(QColor(128, 128, 128));
   p.drawRect(0, 0, width() - 1, height() - 1);

}

/*---------------------------------------------------------------------------*/

void ColorGradientDisplay::setColorTransferFunction(ColorTransferFunction ctf)
{

   m_ctf = ctf;

   update();

}

/*---------------------------------------------------------------------------*/
