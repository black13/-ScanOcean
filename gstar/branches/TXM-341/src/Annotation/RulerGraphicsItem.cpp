/*-----------------------------------------------------------------------------
 * Copyright (c) 2013, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include "RulerGraphicsItem.h"

#include "AnnotationProperty.h"

#include <QLineF>

using namespace gstar;

/*---------------------------------------------------------------------------*/

RulerGraphicsItem::RulerGraphicsItem(AbstractGraphicsItem* parent)
   : LineGraphicsItem(parent)
{

   m_length = new AnnotationProperty();
   m_length->setName("Length");
   m_length->setValue(0.0);

   m_scalePerPixel = new AnnotationProperty();
   m_scalePerPixel->setName("Scale Per Pixel");
   m_scalePerPixel->setValue(1.0);
/*
   appendChild(new AbstractGraphicsItem(m_length, this));
   appendChild(new AbstractGraphicsItem(m_scalePerPixel, this));
*/
//   m_data.push_back(me("Ruler");

   m_data.push_back(m_length);

}

/*---------------------------------------------------------------------------*/

void RulerGraphicsItem::calculate()
{

   double scale = m_scalePerPixel->getValue().toDouble();
   double len = m_line->line().length() * scale;
   m_length->setValue(len);
   m_text = QString("%1").arg(len);

}

/*---------------------------------------------------------------------------*/

const QString RulerGraphicsItem::displayName() const
{

   const QString name = QString("Ruler");
   return name;

}

/*---------------------------------------------------------------------------*/

AbstractGraphicsItem* RulerGraphicsItem::duplicate()
{

   RulerGraphicsItem* item = new RulerGraphicsItem();

   item->setPos(pos());
   item->setStartPos(m_line->line().p1());
   item->setEndPos(m_line->line().p2());
   item->setLinkColor(m_lineColor);
   item->calculate();
   return item;

}

/*---------------------------------------------------------------------------*/
