/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef GSTAR_IMAGE_VIEW_SCENE_H
#define GSTAR_IMAGE_VIEW_SCENE_H

/*---------------------------------------------------------------------------*/

#include <Array.h>

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QItemSelectionModel>
#include <QRubberBand>
#include <QPixmap>

/*---------------------------------------------------------------------------*/

namespace gstar
{

class RectItem;
class ROITableModel;

/**
 * @brief The ImageViewScene class ...
 */
class ImageViewScene
: public QGraphicsScene
{

   Q_OBJECT

public:
   //enum drawMode { InsertLine, InsertRect };
   /**
    * Possible zoom modes.
    */
   enum Mode {
      None,        /*!< No zoom mode selected. */
      ZoomIn,      /*!< Zoom in mode. */
      ZoomOut,     /*!< Zoom out mode. */
      Fit,          /*!< Fit mode; stretch or shrink image to fit in widget. */
      InsertLine
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

   /**
    * Get ROI mask for specified ROI
    *
    * @param i - ROI index
    * @param mask - Array in which to place the ROI mask
    */
   void getROIMask(int i, Array& mask);

   /**
    * Lock ROIs so they can not be moved, selected or resized
    *
    * @param state - true, locks ROIs; false unlocks ROIs
    */
   void lockROIs(bool state);

   /**
    * Get bounding rectangle of current pixItem
    *
    * @return current pixItem boudning rectangle
    */
   QRectF pixRect();

   /**
    * Set ROI movel
    *
    * @param model - ROI model
    */
   void setROIModel(ROITableModel* model);

   /**
    * Set the selection model for ROIs
    *
    * @param selectionModel - ROI selection model
    */
   void setROISelectionModel(QItemSelectionModel* selectionModel);

public slots:

   /**
    * Enable(show) / Disable(hide) ROIs in scene
    *
    * @param state - true = enable, false = disable
    */
   void enableROIs(bool state);

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

   /**
    * Set mode to ImageViewScene::InsertLine
    */
   void setDrawLineMode();

signals:

   /**
    * Signal that a zoom in event took place. The view onto the scene should
    * handle it.
    *
    * @param zoomRect - rubber band selection rectangle.
    */
   void zoomIn(QRectF zoomRect);

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

   /**
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private slots:

   /**
    * Internal slot called when a ROI is changed in the ROI model.
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   void roiChanged(const QModelIndex& topLeft,
                   const QModelIndex& bottomRight);

   /**
    * Internal slot called when a ROI is inserted in the ROI model.
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   void roiInserted(const QModelIndex &parent, int start, int end);

   /**
    * Internal slot called when a ROI graphics item in the scene is changed
    * interactively by the user.
    *
    * @param roi - pointer to the updated ROI graphics item
    */
   void roiItemChanged(RectItem* roi);

   /**
    * Internal slot called when the ROI selection in the scene is changed
    * interactively by the user. Reimplemented from QAbstractItemModel.
    * See Qt documentation.
    */
   void roiItemSelectionChanged();

   /**
    * Internal slot called when a ROI is removed from the ROI model.
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   void roiRemoved(const QModelIndex& parent, int start, int end);

   /**
    * Internal slot called when the ROI selection in the ROI model is changed.
    * Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   void roiSelectionChanged(const QItemSelection& selected,
                            const QItemSelection& deselected);

   /**
    * Update ROIs to fit in current bounds
    */
   void updateROIs();

private:

   /**
    * Zoom mode
    */
   Mode m_mode;

   /**
    * Pointer to pixmap item
    */
   QGraphicsPixmapItem* m_pixItem;

   /**
    * For drawing rubber-band on the image.
    */
   QRubberBand* m_zoomSelection;

   /**
    * Starting point of zoom selection
    */
   QPointF m_zoomOrigin;

   /**
    * Rubber band selection rect
    */
   QRectF m_zoomRect;

   /**
    * ROI model
    */
   ROITableModel* m_roiTableModel;

   /*
    * ROI selection model
    */
   QItemSelectionModel* m_roiSelectionModel;

   /**
    * List of ROI graphics items
    */
   QList<RectItem*> m_rois;

   /**
    * Lines of the QGraphicLineItem
    */
   QGraphicsLineItem *line;


};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
