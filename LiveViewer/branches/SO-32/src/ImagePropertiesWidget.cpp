/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <QLabel>
#include <QFormLayout>

#include <ImagePropertiesWidget.h>

/*---------------------------------------------------------------------------*/

ImagePropertiesWidget::ImagePropertiesWidget(QWidget *parent)
: QWidget(parent)
{

   setupGUI();

}

/*---------------------------------------------------------------------------*/

void ImagePropertiesWidget::setupGUI()
{

   // Width of image.
   QLabel* lbliw = new QLabel(tr("Width (in px):"));
   m_imageWidth  = new QLabel();

   // Height of image.
   QLabel* lblih = new QLabel(tr("Height (in px):"));
   m_imageHeight = new QLabel();

   // Image data type
   QLabel* lblitype = new QLabel(tr("Type:"));
   m_imageDataType = new QLabel();

   //layout these properties.
   QGridLayout* mainLayout = new QGridLayout();
   mainLayout -> setAlignment(Qt::AlignTop | Qt::AlignLeft);
   mainLayout -> addWidget(new QLabel, 0, 0);
   mainLayout -> addWidget(lbliw, 1, 0, Qt::AlignLeading);
   mainLayout -> addWidget(m_imageWidth, 1, 1);
   mainLayout -> addWidget(lblih, 2, 0, Qt::AlignLeading);
   mainLayout -> addWidget(m_imageHeight, 2, 1);
   mainLayout -> addWidget(lblitype, 3, 0, Qt::AlignLeading);
   mainLayout -> addWidget(m_imageDataType, 3, 1);

   //set the main layout
   setLayout(mainLayout);

}

/*---------------------------------------------------------------------------*/

void ImagePropertiesWidget::updateHeight(int h)
{

   m_imageHeight -> setText(QString::number(h));

}

/*---------------------------------------------------------------------------*/

void ImagePropertiesWidget::updateWidth(int w)
{

   m_imageWidth -> setText(QString::number(w));

}

/*---------------------------------------------------------------------------*/

void ImagePropertiesWidget::updateDataType(Array::DataType dt)
{

   switch(dt) {
   case Array::UINT8:
      m_imageDataType -> setText(tr("8 bit UINT"));
      break;
   case Array::UINT16:
      m_imageDataType -> setText(tr("16 bit UINT"));
      break;
   case Array::BGRA32:
      m_imageDataType -> setText(tr("32 bit BGR"));
      break;
   default:
      m_imageDataType -> setText(tr("Invalid"));
      break;
   }
}

/*---------------------------------------------------------------------------*/

