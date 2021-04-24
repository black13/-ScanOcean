/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef IMAGE_PROPERTIES_WIDGET_H
#define IMAGE_PROPERTIES_WIDGET_H

/*---------------------------------------------------------------------------*/

#include <QWidget>
#include <QLabel>

#include <Array.h>

/*---------------------------------------------------------------------------*/

/**
 * @brief Widget for displaying load image properties.
 */
class ImagePropertiesWidget
: public QWidget
 {

   Q_OBJECT

public:

   /**
    * Default constructor.
    *
    * @param parent - the Qt parent widget
    */
   ImagePropertiesWidget(QWidget* parent = 0);

   /**
     * Update the properties with new image data type value.
     *
     * @param dt - one of the types from Array::DataType
     */
    void updateDataType(Array::DataType dt);

   /**
    * Update the properties with new image height value.
    *
    * @param height - image height
    */
   void updateHeight(int height);

   /**
    * Update the properties with new image width value.
    *
    * @param width - image width
    */
   void updateWidth(int width);

private:

   /**
    * Layout the GUI components.
    */
   void setupGUI();

private:

   /**
    * Display image width
    */
   QLabel* m_imageWidth;

   /**
    * Display image height
    */
   QLabel* m_imageHeight;

   /**
    * Display image data-type
    */
   QLabel* m_imageDataType;

 };

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
