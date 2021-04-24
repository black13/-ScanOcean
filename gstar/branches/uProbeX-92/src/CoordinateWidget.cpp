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

   m_lblXUnits = new QLabel("");
   m_lblYUnits = new QLabel("");

   //Add status bar underneath
   m_lblPixelXCoordinate = new QLabel(tr("0"));
   m_lblPixelYCoordinate = new QLabel(tr("0"));

   m_lblPixelXLabel = new QLabel(" X Coordinate :");
   m_lblPixelYLabel = new QLabel(" Y Coordinate :");

   QHBoxLayout* coordHlayout = new QHBoxLayout();
   coordHlayout->addWidget( m_lblPixelXLabel );
   coordHlayout->addWidget( m_lblPixelXCoordinate );
   coordHlayout->addWidget( m_lblXUnits );
   coordHlayout->addWidget( m_lblPixelYLabel );
   coordHlayout->addWidget( m_lblPixelYCoordinate );
   coordHlayout->addWidget( m_lblYUnits );
   coordHlayout->addStretch(1);

   setLayout(coordHlayout);

}

/*---------------------------------------------------------------------------*/

CoordinateWidget::~CoordinateWidget()
{

}


/*---------------------------------------------------------------------------*/

void CoordinateWidget::setLabel(QString xLabel, QString yLabel)
{

   m_lblPixelXLabel->setText(xLabel);
   m_lblPixelYLabel->setText(yLabel);

}

/*---------------------------------------------------------------------------*/

void CoordinateWidget::setCoordinate(int x, int y)
{

   if(m_model != NULL)
   {
      double dx = 0.0;
      double dy = 0.0;
      double dz = 0.0;
      m_model->runTransformer(x, y, 0.0, &dx, &dy, &dz);
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

void CoordinateWidget::setCoordinate(double x, double y, double z)
{

   if(m_model != NULL)
   {
      double dx = 0.0;
      double dy = 0.0;
      double dz = 0.0;
      m_model->runTransformer(x, y, z, &dx, &dy, &dz);
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

void CoordinateWidget::setUnitsLabel(QString units)
{

   m_lblXUnits->setText(units);
   m_lblYUnits->setText(units);

}

/*---------------------------------------------------------------------------*/


