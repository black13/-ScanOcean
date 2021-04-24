/*-----------------------------------------------------------------------------
 * Copyright (c) 2013, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef ANNOTATIONDISPLAYWIDGET_H
#define ANNOTATIONDISPLAYWIDGET_H

/*---------------------------------------------------------------------------*/

#include "AbstractImageWidget.h"

/*---------------------------------------------------------------------------*/

/**
 * @brief The DisplayWidget class sets up the GraphicsView, TreeView, and
 *          Toolbar to add graphics annotations.
 */
class AnnotationDisplayWidget : public gstar::AbstractImageWidget
{

   Q_OBJECT

public:

   /**
   * @brief DisplayWidget : Constructor.
   * @param parent
   */
   AnnotationDisplayWidget(QWidget* parent = 0);

};

/*---------------------------------------------------------------------------*/

#endif // ANNOTATIONDISPLAYWIDGET_H

/*---------------------------------------------------------------------------*/
