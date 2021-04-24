/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ColorTransferFunction.h>
#include <QDebug>

using namespace gstar;

/*---------------------------------------------------------------------------*/

ColorTransferFunction::ColorTransferFunction()
{
}

/*---------------------------------------------------------------------------*/

ColorTransferFunction::ColorTransferFunction(const ColorTransferFunction& s)
{

   m_redSubRange[0] = s. m_redSubRange[0];
   m_redSubRange[1] = s. m_redSubRange[1];
   m_greenSubRange[0] = s.m_greenSubRange[0];
   m_greenSubRange[1] = s.m_greenSubRange[1];
   m_blueSubRange[0] = s.m_blueSubRange[0];
   m_blueSubRange[1] = s.m_blueSubRange[1];

   m_totalRange[0] = s.m_totalRange[0];
   m_totalRange[1] = s.m_totalRange[1];

   m_iRed = s.m_iRed;
   m_vRed = s.m_vRed;

   m_iGreen = s.m_iGreen;
   m_vGreen = s.m_vGreen;

   m_iBlue = s.m_iBlue;
   m_vBlue = s.m_vBlue;

}

/*---------------------------------------------------------------------------*/

ColorTransferFunction&
ColorTransferFunction::operator=(const ColorTransferFunction& s)
{

   m_redSubRange[0] = s. m_redSubRange[0];
   m_redSubRange[1] = s. m_redSubRange[1];
   m_greenSubRange[0] = s.m_greenSubRange[0];
   m_greenSubRange[1] = s.m_greenSubRange[1];
   m_blueSubRange[0] = s.m_blueSubRange[0];
   m_blueSubRange[1] = s.m_blueSubRange[1];

   m_totalRange[0] = s.m_totalRange[0];
   m_totalRange[1] = s.m_totalRange[1];

   m_iRed = s.m_iRed;
   m_vRed = s.m_vRed;

   m_iGreen = s.m_iGreen;
   m_vGreen = s.m_vGreen;

   m_iBlue = s.m_iBlue;
   m_vBlue = s.m_vBlue;

   return *this;

}

/*---------------------------------------------------------------------------*/

void ColorTransferFunction::getColorAt(double index,
                                       double* r, double* g, double* b)
{

   // Check for values in transfer function
   if (m_iRed.size() <= 0 || m_iGreen.size() <= 0 || m_iBlue.size() <= 0) {
      *r = 0.0;
      *g = 0.0;
      *b = 0.0;
      return;
   }


   // Found index
   int fi = -1;

   // Find red index and value
   for (int i = 0 ; i < m_iRed.size() ; i++) {
      if (index <= m_iRed[i]) {
         fi = i;
         break;
      }
   }

   // Lower clamp
   if (fi == 0) {
      *r = m_vRed[fi];
   }

   // Upper clamp
   else if (fi == -1) {
      *r = m_vRed[m_vRed.size() - 1];
   }

   // Interpolate
   else {
      *r = m_vRed[fi - 1] + (index - m_iRed[fi - 1]) * 
         ((m_vRed[fi] - m_vRed[fi - 1]) / (m_iRed[fi] - m_iRed[fi - 1]));
   }


   // Found index
   fi = -1;

   // Find red index and value
   for (int i = 0 ; i < m_iGreen.size() ; i++) {
      if (index <= m_iGreen[i]) {
         fi = i;
         break;
      }
   }

   // Lower clamp
   if (fi == 0) {
      *g = m_vGreen[fi];
   }

   // Upper clamp
   else if (fi == -1) {
      *g = m_vGreen[m_vGreen.size() - 1];
   }

   // Interpolate
   else {
      *g = m_vGreen[fi - 1] + (index - m_iGreen[fi - 1]) * 
         ((m_vGreen[fi] - m_vGreen[fi - 1]) / (m_iGreen[fi] - m_iGreen[fi - 1]));
   }


   // Found index
   fi = -1;

   // Find red index and value
   for (int i = 0 ; i < m_iBlue.size() ; i++) {
      if (index <= m_iBlue[i]) {
         fi = i;
         break;
      }
   }

   // Lower clamp
   if (fi == 0) {
      *b = m_vBlue[fi];
   }

   // Upper clamp
   else if (fi == -1) {
      *b = m_vBlue[m_vBlue.size() - 1];
   }

   // Interpolate
   else {
      *b = m_vBlue[fi - 1] + (index - m_iBlue[fi - 1]) * 
         ((m_vBlue[fi] - m_vBlue[fi - 1]) / (m_iBlue[fi] - m_iBlue[fi - 1]));
   }

}

/*---------------------------------------------------------------------------*/

vector<double> ColorTransferFunction::getRedIndex()
{

   return m_iRed;

}

/*---------------------------------------------------------------------------*/

vector<double> ColorTransferFunction::getGreenIndex()
{

   return m_iGreen;

}

/*---------------------------------------------------------------------------*/

vector<double> ColorTransferFunction::getBlueIndex()
{

   return m_iBlue;

}

/*---------------------------------------------------------------------------*/

vector<double> ColorTransferFunction::getRedValue()
{

   return m_vRed;

}

/*---------------------------------------------------------------------------*/

vector<double> ColorTransferFunction::getGreenValue()
{

   return m_vGreen;

}

/*---------------------------------------------------------------------------*/

vector<double> ColorTransferFunction::getBlueValue()
{

   return m_vBlue;

}

/*---------------------------------------------------------------------------*/

void ColorTransferFunction::getRedSubRange(double* min, double* max)
{

   *min = m_redSubRange[0];
   *max = m_redSubRange[1];

}

/*---------------------------------------------------------------------------*/

void ColorTransferFunction::getGreenSubRange(double* min, double* max)
{

   *min = m_greenSubRange[0];
   *max = m_greenSubRange[1];

}

/*---------------------------------------------------------------------------*/

void ColorTransferFunction::getBlueSubRange(double* min, double* max)
{

   *min = m_blueSubRange[0];
   *max = m_blueSubRange[1];

}

/*---------------------------------------------------------------------------*/

void ColorTransferFunction::getTotalRange(double* min, double* max)
{

   *min = m_totalRange[0];
   *max = m_totalRange[1];

}

/*---------------------------------------------------------------------------*/

void ColorTransferFunction::setRed(vector<double> i, vector<double> v)
{

   m_iRed = i;
   m_vRed = v;

}

/*---------------------------------------------------------------------------*/

void ColorTransferFunction::setGreen(vector<double> i, vector<double> v)
{

   m_iGreen = i;
   m_vGreen = v;

}

/*---------------------------------------------------------------------------*/

void ColorTransferFunction::setBlue(vector<double> i, vector<double> v)
{

   m_iBlue = i;
   m_vBlue = v;

}

/*---------------------------------------------------------------------------*/

void ColorTransferFunction::setRedSubRange(double min, double max)
{

   m_redSubRange[0] = min;
   m_redSubRange[1] = max;

}

/*---------------------------------------------------------------------------*/

void ColorTransferFunction::setGreenSubRange(double min, double max)
{

   m_greenSubRange[0] = min;
   m_greenSubRange[1] = max;

}

/*---------------------------------------------------------------------------*/

void ColorTransferFunction::setBlueSubRange(double min, double max)
{

   m_blueSubRange[0] = min;
   m_blueSubRange[1] = max;

}

/*---------------------------------------------------------------------------*/

void ColorTransferFunction::setTotalRange(double min, double max)
{

   m_totalRange[0] = min;
   m_totalRange[1] = max;

}

/*---------------------------------------------------------------------------*/
