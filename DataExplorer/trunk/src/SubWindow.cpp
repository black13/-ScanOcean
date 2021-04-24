/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <SubWindow.h>

/*---------------------------------------------------------------------------*/

SubWindow::SubWindow(QWidget* parent, Qt::WindowFlags flags)
: QMdiSubWindow(parent, flags)
{
}

/*---------------------------------------------------------------------------*/

SubWindow::~SubWindow()
{
}

/*---------------------------------------------------------------------------*/

void SubWindow::closeEvent(QCloseEvent* closeEvent)
{

   emit windowClosing(this);

}

/*---------------------------------------------------------------------------*/
