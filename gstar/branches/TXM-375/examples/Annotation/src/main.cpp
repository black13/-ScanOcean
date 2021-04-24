/*-----------------------------------------------------------------------------
 * Copyright (c) 2013, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <QApplication>

#include "AnnotationDisplayWidget.h"

/*---------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AnnotationDisplayWidget* displayWidget = new AnnotationDisplayWidget();
    displayWidget->resize(800 , 600);
    displayWidget->show();


    return a.exec();
}

/*---------------------------------------------------------------------------*/
