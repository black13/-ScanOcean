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
   m_histBins->setMinimum(1.0);
   m_histBins->setMaximum(256.0);

   // Main layout
   QFormLayout* mainLayout = new QFormLayout();
   mainLayout->addRow(tr("Number of bins"), m_histBins);

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

double PreferencesHist::getHistBins()
{

   return m_histBins->value();

}

/*---------------------------------------------------------------------------*/
