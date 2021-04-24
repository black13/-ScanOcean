/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef IMAGE_VIEW_SCENE_H
#define IMAGE_VIEW_SCENE_H

/*---------------------------------------------------------------------------*/

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>

/*---------------------------------------------------------------------------*/

/**
 * @brief The ImageViewScene class ...
 */
class ImageViewScene
: public QGraphicsScene
{

   Q_OBJECT

public:

   /**
    * Possible zoom modes.
    */
   enum Mode {
      None,        /*!< No zoom mode selected. */
      ZoomIn,      /*!< Zoom in mode. */
      ZoomOut,     /*!< Zoom out mode. */
      Fit          /*!< Fit mode; stretch or shrink image to fit in widget. */
   };

   /**
    * Constructor
    *
    * @param parent the Qt parent widget.
    */
   ImageViewScene(QWidget* parent = 0);

   /**
    * Destructor
    */
   ~ImageViewScene();

public slots:

   /**
    * Set zoom mode for view.
    *
    * @param mode - image zoom mode for view
    */
   void setMode(ImageViewScene::Mode mode);

   /**
    * Set current image to visualize.
    *
    * @param p - image to visualize
    */
   void setPixmap(QPixmap p);

   /**
    * Set zoom mode to ImageViewScene::Fit
    */
   void setZoomModeToFit();

   /**
    * Set zoom mode to ImageViewScene::None
    */
   void setZoomModeToNone();

   /**
    * Set zoom mode to ImageViewScene::ZoomIn
    */
   void setZoomModeToZoomIn();

   /**
    * Set zoom mode to ImageViewScene::ZoomOut
    */
   void setZoomModeToZoomOut();

signals:

   /**
    * Signal that a zoom in event took place. The view onto the scene should
    * handle it.
    */
   void zoomIn();

   /**
    * Signal that a zoom out event took place. The view onto the scene should
    * handle it.
    */
   void zoomOut();

protected:

   /**
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

   /**
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:

   /**
    * Zoom mode
    */
   Mode m_mode;

   /**
    * Pointer to pixmap item
    */
   QGraphicsPixmapItem* m_pixItem;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
