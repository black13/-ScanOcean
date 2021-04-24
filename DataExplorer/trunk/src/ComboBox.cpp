/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ComboBox.h>

/*---------------------------------------------------------------------------*/

ComboBox::ComboBox(int did, QWidget* parent)
: QComboBox(parent)
{

   m_did = did;

   connect(this, SIGNAL(currentIndexChanged(const QString&)),
           this, SLOT(textChangedSlot(const QString&)));

   connect(this, SIGNAL(currentIndexChanged(int)),
           this, SLOT(indexChangedSlot(int)));

}

/*---------------------------------------------------------------------------*/

void ComboBox::indexChangedSlot(int newIndex)
{

   emit indexChanged(m_did, m_oldIndex, newIndex);
   m_oldIndex = newIndex;

}

/*---------------------------------------------------------------------------*/

void ComboBox::textChangedSlot(const QString& newText)
{

   emit textChanged(m_did, m_oldText, newText);
   m_oldText = newText;

}

/*---------------------------------------------------------------------------*/
