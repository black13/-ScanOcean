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

   /**
    * Get bounding rectangle of current pixItem
    *
    * @return current pixItem boudning rectangle
    */
   QRectF pixRect();

   /**
    * @brief getModel
    * @return
    */
   const QAbstractItemModel* getModel() const;

   /**
    * @brief getUnitsLabel
    * @return
    */
   const QString getUnitsLabel() const;

   /**
    * @brief getUnitsPerPixelX
    * @return
    */
   double getUnitsPerPixelX() const;

   /**
    * @brief getUnitsPerPixelY
    * @return
    */
   double getUnitsPerPixelY() const;

   /**
    * Set ROI movel
    *
    * @param model - ROI model
    */
   void setModel(QAbstractItemModel* model);

   /**
    * Set the selection model for ROIs
    *
    * @param selectionModel - ROI selection model
    */
   void setSelectionModel(QItemSelectionModel* selectionModel);

public slots:

   /**
    * Enable(show) / Disable(hide) annotations in scene
    *
    * @param state - true = enable, false = disable
    */
   //void enableAnnotations(bool state);

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
    * @brief setUnitsLabel
    * @param label
    */
   void setUnitsLabel(QString label);

   /**
    * @brief setUnitsPerPixelX
    * @param x
    */
   void setUnitsPerPixelX(double x);

   /**
    * @brief setUnitsPerPixelY
    * @param y
    */
   void setUnitsPerPixelY(double y);

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
    * @brief updateModel
    */
   void updateModel();

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
    * @brief modelRowsInserted
    * @param parent
    * @param start
    * @param end
    */
   void modelRowsInserted(const QModelIndex& parent, int start, int end);

   /**
    * Internal slot called when the ROI selection in the scene is changed
    * interactively by the user. Reimplemented from QAbstractItemModel.
    * See Qt documentation.
    */
   void sceneSelectionChanged();

   /**
    * @brief selectionChanged
    * @param selected
    * @param deselected
    */
   void modelSelectionChanged(const QItemSelection& selected,
                              const QItemSelection& deselected);

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
    * Annotation model
    */
   QAbstractItemModel* m_model;

   /**
    * Annotation selection model
    */
   QItemSelectionModel* m_selectionModel;

   /**
    * @brief m_unitsLabel
    */
   QString m_unitsLabel;

   /**
    * @brief m_unitsPerPixelX
    */
   double m_unitsPerPixelX;

   /**
    * @brief m_unitsPerPixelY
    */
   double m_unitsPerPixelY;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
