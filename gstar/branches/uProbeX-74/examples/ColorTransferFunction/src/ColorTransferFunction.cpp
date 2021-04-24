/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <QApplication>
#include <QMainWindow>

#include <ColorTransferFunctionEditor.h>

using namespace gstar;

/*---------------------------------------------------------------------------*/

int main(int argc, char** argv)
{

   QApplication a(argc, argv);
   Q_INIT_RESOURCE(GStar);

   QMainWindow* win = new QMainWindow();

   ColorTransferFunctionEditor* m_color = new ColorTransferFunctionEditor();
   m_color -> setTotalRange(0.0, 4095.0);
   m_color -> setDisabled(false);

   win -> setCentralWidget(m_color);
   win -> show();

   return a.exec();

}

/*---------------------------------------------------------------------------*/
