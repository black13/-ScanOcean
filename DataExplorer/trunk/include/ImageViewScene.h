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
#include <QItemSelectionModel>
#include <QList>
#include <QModelIndex>
#include <QPixmap>

/*---------------------------------------------------------------------------*/

/**
 * @brief The ImageView class ...
 */
class ImageViewScene
: public QGraphicsScene
{

   Q_OBJECT

public:

   /**
    * Possible zoom modes.
    */
   enum Mode {None, ZoomIn, ZoomOut, Fit};

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

   /**
    * Set data storage order to column major.
    */
   void setColumnMajor();

   /**
    * Set data storage order to row major.
    */
   void setRowMajor();

public slots:

   void setMode(Mode mode);
   void setPixmap(QPixmap p);
   void setZoomInMode();
   void setZoomModeToNone();
   void setZoomModeToFit();
   void setZoomOutMode();

signals:

   /**
    * Signal that a zoom in event took place. The view onto the scene should
    * handle it.
    */
   void zoomIn();

   /**
    * Signal that a zoom out event took place. The view onto the scene should
    * hnalde it.
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
    * Data is column major, not row major
    */
   bool m_isColumnMajor;

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
