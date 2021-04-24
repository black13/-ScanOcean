/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef COLOR_LIST_COMBO_BOX_H
#define COLOR_LIST_COMBO_BOX_H

/*---------------------------------------------------------------------------*/

#include <QComboBox>

/*---------------------------------------------------------------------------*/

class QColor;
class QWidget;

/*---------------------------------------------------------------------------*/

class ColorListComboBox
: public QComboBox
{

   Q_OBJECT
   Q_PROPERTY(QColor color READ color WRITE setColor USER true)

public:

   /**
    * Constructor
    *
    * @param parent - the Qt parent widget
    */
   ColorListComboBox(QWidget* widget = 0);

public:

   /**
    * Return the color
    *
    * @return color
    */
   QColor color() const;

   /**
    * Return the color name
    *
    * @return color name
    */
   QString name() const;

   /**
    * Set the color
    *
    * @param color - the color
    */
   void setColor(QColor color);

private:

   /**
    * Populate the list box with Qt color names
    */
   void populateList();

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
