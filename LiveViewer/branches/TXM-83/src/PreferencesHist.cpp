/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <PreferencesHist.h>

#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QRadioButton>

/*---------------------------------------------------------------------------*/

PreferencesHist::PreferencesHist(QWidget *parent)
   : QWidget(parent)
{

   // Edit fields
   m_histBins= new QDoubleSpinBox();
   m_histBins->setMinimum(5.0);
   m_histBins->setMaximum(100.0);

   m_typeDisc = new QRadioButton("Discrete");
   m_typeDisc->setChecked(true);
   m_typeCont = new QRadioButton("Continuous");


   // Main layout
   QFormLayout* mainLayout = new QFormLayout();
   mainLayout->addRow(tr("Number of bins"), m_histBins);
   mainLayout->addRow(m_typeDisc, m_typeCont);

   setLayout(mainLayout);

}

/*---------------------------------------------------------------------------*/

PreferencesHist::~PreferencesHist()
{

}

/*---------------------------------------------------------------------------*/

void PreferencesHist::acceptChanges()
{

}

/*---------------------------------------------------------------------------*/


void PreferencesHist::setHistBins(double bins)
{

   m_histBins->setValue(bins);

}

/*---------------------------------------------------------------------------*/

void PreferencesHist::setHistType(int type)
{

   if (type == 1)
   {
      m_typeCont->setChecked(true);
   }
   else
   {
      m_typeDisc->setChecked(true);
   }

}

/*---------------------------------------------------------------------------*/

double PreferencesHist::getHistBins()
{

   return m_histBins->value();

}

/*---------------------------------------------------------------------------*/

int PreferencesHist::getHistType()
{

   if (m_typeCont->isChecked()) return 1;

   return 0;

}

/*---------------------------------------------------------------------------*/
