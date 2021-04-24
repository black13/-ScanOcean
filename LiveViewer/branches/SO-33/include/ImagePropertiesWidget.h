/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef IMAGE_PROPERTIES_WIDGET_H_
#define IMAGE_PROPERTIES_WIDGET_H_

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
    * Update the properties with new image width value.
    *
    * @param width - image width
    */
   void updateWidth(int width);

   /**
    * Update the properties with new image height value.
    *
    * @param height - image height
    */
   void updateHeight(int height);

   /**
    * Update the properties with new image data type value.
    *
    * @param datatype - one of the type from Array::DataType
    */
   void updateDataType(Array::DataType dt);


private:

   /**
    * Layout the GUI components.
    */
   void setupGUI();

private:

   /**
    * Display image width
    */
   QLabel *m_imageWidth;

   /**
    * Display image height
    */
   QLabel *m_imageHeight;

   /**
    * Display image data-type
    */
   QLabel *m_imageDataType;

 };


#endif /* IMAGEPROPERTIESWIDGET_H_ */
