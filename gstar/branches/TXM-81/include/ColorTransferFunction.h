/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef GSTAR_COLOR_TRANSFER_FUNCTION_H
#define GSTAR_COLOR_TRANSFER_FUNCTION_H

/*---------------------------------------------------------------------------*/

#include <vector>

/*---------------------------------------------------------------------------*/

using namespace std;

/*---------------------------------------------------------------------------*/

namespace gstar
{

class ColorTransferFunction
{

public:

   ColorTransferFunction();

   ColorTransferFunction(const ColorTransferFunction& s);

   ColorTransferFunction& operator=(const ColorTransferFunction& s);

   void getColorAt(double index, double* r, double* g, double* b);

   vector<double> getRedIndex();
   vector<double> getGreenIndex();
   vector<double> getBlueIndex();

   vector<double> getRedValue();
   vector<double> getGreenValue();
   vector<double> getBlueValue();

   void getRedSubRange(double* min, double* max);
   void getGreenSubRange(double* min, double* max);
   void getBlueSubRange(double* min, double* max);

   void getTotalRange(double* min, double* max);

   void setRed(vector<double> i, vector<double> v);
   void setGreen(vector<double> i, vector<double> v);
   void setBlue(vector<double> i, vector<double> v);

   void setRedSubRange(double min, double max);
   void setGreenSubRange(double min, double max);
   void setBlueSubRange(double min, double max);

   void setTotalRange(double min, double max);

private:

   double m_redSubRange[2];
   double m_greenSubRange[2];
   double m_blueSubRange[2];

   double m_totalRange[2];

   vector<double> m_iRed;
   vector<double> m_vRed;

   vector<double> m_iGreen;
   vector<double> m_vGreen;   
   
   vector<double> m_iBlue;
   vector<double> m_vBlue;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
