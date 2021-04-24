/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ColorListComboBox.h>

/*---------------------------------------------------------------------------*/

ColorListComboBox::ColorListComboBox(QWidget* widget)
: QComboBox(widget)
{

   populateList();

}

/*---------------------------------------------------------------------------*/

QColor ColorListComboBox::color() const
{

   return qVariantValue<QColor>(itemData(currentIndex(), Qt::DecorationRole));

}

/*---------------------------------------------------------------------------*/

QString ColorListComboBox::name() const
{

   return qVariantValue<QString>(itemData(currentIndex(), Qt::DisplayRole));

}

/*---------------------------------------------------------------------------*/

void ColorListComboBox::setColor(QColor color)
{

   setCurrentIndex(findData(color, int(Qt::DecorationRole)));

}

/*---------------------------------------------------------------------------*/

void ColorListComboBox::populateList()
{

   QStringList colorNames = QColor::colorNames();

   for (int i = 0 ; i < colorNames.size() ; ++i) {
      QColor color(colorNames[i]);
      insertItem(i, colorNames[i]);
      setItemData(i, color, Qt::DecorationRole);
   }

}

/*---------------------------------------------------------------------------*/
