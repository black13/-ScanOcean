/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef GSTAR_COLOR_TRANSFER_FUNCTION_EDITOR_H
#define GSTAR_COLOR_TRANSFER_FUNCTION_EDITOR_H

/*---------------------------------------------------------------------------*/

#include <QGridLayout>
#include <QWidget>

#include <ColorGradientDisplay.h>
#include <ControlPointWidget.h>

/*---------------------------------------------------------------------------*/

namespace gstar
{

class ColorTransferFunctionEditor
: public QWidget
{

   Q_OBJECT

public:

   ColorTransferFunctionEditor(QWidget* widget = 0);
   ColorTransferFunction getColorTransferFunction();
   void setColorFunction(ColorTransferFunction ctf);
   void setSubRange(double min, double max);
   void setTotalRange(double min, double max);

signals:

   void requestAutoLevels();
   void requestPredefinedColor(QString);
   void transferFunctionUpdated(ColorTransferFunction ctf);

private slots:

   void redRangeChanged(double min, double max);
   void greenRangeChanged(double min, double max);
   void blueRangeChanged(double min, double max);
   void pointsChanged();
   void predefinedColorClicked();

private:

   QString m_appPath;

   ControlPointWidget* m_red;
   ControlPointWidget* m_green;
   ControlPointWidget* m_blue;
   ColorGradientDisplay* m_display;

   QPushButton* m_btnLock;
   QPushButton* m_btnAuto;

   QPushButton* m_btnColorRed;
   QPushButton* m_btnColorGreen;
   QPushButton* m_btnColorBlue;
   QPushButton* m_btnColorHot;
   QPushButton* m_btnColorGray;
   QPushButton* m_btnColorIce;

   ColorTransferFunction m_ctf;

   double m_totalRange[2];

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
