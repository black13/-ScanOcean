/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2013, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include "AnnotationDisplayWidget.h"
#include "ImageViewWidget.h"

#include <QVBoxLayout>
#include <QPixmap>

/*---------------------------------------------------------------------------*/

using gstar::AbstractImageWidget;
using gstar::ImageViewWidget;

/*---------------------------------------------------------------------------*/

AnnotationDisplayWidget::AnnotationDisplayWidget(QWidget* parent)
   : AbstractImageWidget(parent)
{

   QVBoxLayout* mainLayout = (QVBoxLayout*)generateDefaultLayout();

   appendAnnotationTab();

   setLayout(mainLayout);

   QPixmap p;
   if (p.load("images/data.bmp"))
   {
      m_imageViewWidget->scene()->setPixmap(p);
   }

}

/*---------------------------------------------------------------------------*/
