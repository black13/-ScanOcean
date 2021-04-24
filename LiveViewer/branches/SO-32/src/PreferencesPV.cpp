/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <PreferencesPV.h>
#include <QFormLayout>

/*---------------------------------------------------------------------------*/

PreferencesPV::PreferencesPV(QWidget *parent)
   : QWidget(parent)
{

   // Edit fields
   m_editPVPrefix= new QLineEdit();

   // Main layout
   QFormLayout* mainLayout = new QFormLayout();
   mainLayout -> addRow(tr("PV Prefix"), m_editPVPrefix);
   setLayout(mainLayout);

}

/*---------------------------------------------------------------------------*/

PreferencesPV::~PreferencesPV()
{

}

/*---------------------------------------------------------------------------*/

void PreferencesPV::acceptChanges()
{

}

/*---------------------------------------------------------------------------*/

QString PreferencesPV::getPVPrefix()
{

   return m_editPVPrefix -> text();

}

/*---------------------------------------------------------------------------*/

void PreferencesPV::setPVPrefix(QString str)
{

	m_editPVPrefix -> setText(str);

}

/*---------------------------------------------------------------------------*/
