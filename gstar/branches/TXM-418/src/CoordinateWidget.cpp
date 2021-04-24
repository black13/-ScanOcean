/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <CoordinateWidget.h>

using namespace gstar;
/*---------------------------------------------------------------------------*/

CoordinateWidget::CoordinateWidget(QWidget* parent)
: QWidget(parent)
{

   m_model = NULL;
   m_lblPixelXCoordinate = NULL;
   m_lblPixelYCoordinate = NULL;

   //Add status bar underneath
   m_lblPixelXCoordinate = new QLabel(tr("0"));
   m_lblPixelYCoordinate = new QLabel(tr("0"));

   QHBoxLayout* coordHlayout = new QHBoxLayout();
   coordHlayout->addWidget( new QLabel(" X Coordinate :") );
   coordHlayout->addWidget( m_lblPixelXCoordinate );
   coordHlayout->addWidget( new QLabel(" Y Coordinate :") );
   coordHlayout->addWidget( m_lblPixelYCoordinate );
   coordHlayout->addStretch(1);

   setLayout(coordHlayout);

}

/*---------------------------------------------------------------------------*/

CoordinateWidget::~CoordinateWidget()
{

}

/*---------------------------------------------------------------------------*/

void CoordinateWidget::setCoordinate(int x, int y)
{

   if(m_model != NULL)
   {
      double dx = (m_model->getScaleX() * (double)x) + m_model->getTopLeftX();
      double dy = (m_model->getScaleY() * (double)y) + m_model->getTopLeftY();
      m_lblPixelXCoordinate->setText(QString::number(dx));
      m_lblPixelYCoordinate->setText(QString::number(dy));
   }
   else
   {
      m_lblPixelXCoordinate->setText(QString::number(x));
      m_lblPixelYCoordinate->setText(QString::number(y));
   }

}

/*---------------------------------------------------------------------------*/

void CoordinateWidget::setModel(CoordinateModel* model)
{

   m_model = model;

}

/*---------------------------------------------------------------------------*/

void CoordinateWidget::setNull()
{

   m_lblPixelXCoordinate->setText("");
   m_lblPixelYCoordinate->setText("");

}

/*---------------------------------------------------------------------------*/

