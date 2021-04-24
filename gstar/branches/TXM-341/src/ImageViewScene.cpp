/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include "ImageViewScene.h"

#include "AbstractGraphicsItem.h"
#include "AnnotationTreeModel.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <typeinfo>

using namespace gstar;

/*---------------------------------------------------------------------------*/

ImageViewScene::ImageViewScene(QWidget* parent) : QGraphicsScene(parent)
{

   Q_UNUSED(parent)

   // Initialize pointers to NULL
   m_pixItem = NULL;
   m_model = NULL;
   m_selectionModel = NULL;
   m_zoomSelection = NULL;

   // Initialize mode
   m_mode = None;

   // Set initial pixmap
   QPixmap p(1024, 1024);
   p.fill(Qt::gray);
   m_pixItem = addPixmap(p);
   setSceneRect(m_pixItem -> boundingRect());

   // Connect selectionChanged signal to annotation slot
   connect(this, SIGNAL(selectionChanged()),
           this, SLOT(sceneSelectionChanged()));

}

/*---------------------------------------------------------------------------*/

ImageViewScene::~ImageViewScene()
{

}

/*---------------------------------------------------------------------------*/

const QAbstractItemModel* ImageViewScene::getModel() const
{

   return m_model;

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::modelRowsInserted(const QModelIndex& parent,
                                      int start,
                                      int end)
{

   Q_UNUSED(start);
   Q_UNUSED(end);
   if (parent.isValid())
   {
      const QAbstractItemModel* pm = parent.model();
      if (typeid(*pm) == typeid(AnnotationTreeModel))
      {
         AbstractGraphicsItem* cItem = NULL;
         AbstractGraphicsItem* item =
            static_cast<AbstractGraphicsItem*>(parent.internalPointer());

         if (item != NULL)
         {
            cItem = item->child(start);
            if (cItem != NULL)
            {
               addItem(cItem);
            }
         }
      }
   }

}

/*---------------------------------------------------------------------------*/
/*
void ImageViewScene::enableAnnotations(bool state)
{

   // Show/hide each ROI item
   for (int i = 0 ; i < m_rois.size() ; i++) {
      m_rois.at(i) -> setVisible(state);
   }

   // Reset view; just in case...
   setSceneRect(m_pixItem -> boundingRect());

}
*/
/*---------------------------------------------------------------------------*/
/*
void ImageViewScene::getROIMask(int i, Array& mask)
{

   // Get graphics item
   RectItem* item = m_rois.at(i);

   // Get actual mask
   item -> getMask(mask);

}
*/
/*---------------------------------------------------------------------------*/
/*
void ImageViewScene::lockROIs(bool state)
{

   // Clear selection
   m_selectionModel -> clearSelection();

   // Set flags on gRectItems
   for (int i = 0 ; i < m_rois.size() ; i++) {
      m_rois.at(i)->setFlag(QGraphicsItem::ItemIsMovable, !state);
      m_rois.at(i)->setFlag(QGraphicsItem::ItemIsSelectable, !state);
      m_rois.at(i)->setFlag(QGraphicsItem::ItemSendsGeometryChanges, !state);
   }

}
*/
/*---------------------------------------------------------------------------*/

void ImageViewScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

   // Zoom in mode
   if ((m_mode == ZoomIn) && (m_zoomSelection != NULL))
   {

      /// Get attached view
      QGraphicsView* view = qobject_cast<QGraphicsView*> (
         m_zoomSelection -> parent() -> parent());
      Q_ASSERT(view);

      // Resize rubber band based on initial mouse press and current mouse drag
      QRectF rect(m_zoomOrigin, view -> mapFromScene(event -> scenePos()));
      m_zoomSelection -> setGeometry(rect.toRect().normalized());

      // Rubber band should only becomes visible, if the mouse is dragged.
      if (!m_zoomSelection -> isVisible())
      {
         m_zoomSelection -> show();
      }
      m_zoomRect = rect;

   }
   else
   {
      QGraphicsScene::mouseMoveEvent(event);
   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

   // Left click and mode is ZoomIn
   if ((event -> button() == Qt::LeftButton) && (m_mode == ZoomIn))
   {
      // Get attached view
      QGraphicsView* view = qobject_cast<QGraphicsView*>(
         event -> widget() -> parent());
      Q_ASSERT(view);

      // Construct a rubber band object for the view.
      m_zoomSelection = new QRubberBand(QRubberBand::Rectangle,
                                        view -> viewport());
      m_zoomOrigin = view -> mapFromScene(event -> scenePos());

      // Store the size of rubber band rectangle in a QRectF object.
      m_zoomRect = QRectF(m_zoomOrigin, m_zoomOrigin);
   }

   // Left click and mode is ZoomOut
   else if ((event -> button() == Qt::LeftButton) && (m_mode == ZoomOut))
   {
      // Emit zoomOut signal
      emit zoomOut();
   }

   // Propagate event
   if ((event -> button() == Qt::LeftButton ||
        event -> button() == Qt::RightButton) &&
       (m_mode == None || m_mode == Fit))
   {
      QGraphicsScene::mousePressEvent(event);
   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

   if ((m_mode == ZoomIn) && m_zoomSelection != NULL)
   {
      delete m_zoomSelection;
      m_zoomSelection = NULL;
      emit zoomIn(m_zoomRect);
   }
   else
   {
      QGraphicsScene::mouseReleaseEvent(event);
   }

}

/*---------------------------------------------------------------------------*/

QRectF ImageViewScene::pixRect()
{

   return m_pixItem -> boundingRect();

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::sceneSelectionChanged()
{
   if (m_model != NULL && m_selectionModel != NULL)
   {

    disconnect(m_selectionModel,
               SIGNAL(selectionChanged(const QItemSelection &,
                                       const QItemSelection &)),
               this,
               SLOT(modelSelectionChanged(const QItemSelection &,
                                          const QItemSelection &)));

    disconnect(this,
               SIGNAL(selectionChanged()),
               this,
               SLOT(sceneSelectionChanged()));

   m_selectionModel->clear();

   QList<QGraphicsItem*> sItems = selectedItems();
   foreach (QGraphicsItem* item, sItems)
   {
      AbstractGraphicsItem* tItem = (AbstractGraphicsItem*)item;
      AbstractGraphicsItem* parent = tItem->parent();
      if (parent != NULL)
      {
         QModelIndex groupIndex =
                 m_model->index(parent->row(), 0, QModelIndex());
         if (groupIndex.isValid())
         {
            QModelIndex cIndex = groupIndex.child(tItem->row(), 0);
            if (cIndex.isValid())
            {
               for (int i = 0; i < tItem->columnCount(); i++)
               {
               cIndex = groupIndex.child(tItem->row(), i);
               m_selectionModel->select(cIndex, QItemSelectionModel::Select);
               }
            }
         }
      }
   }
}

connect(m_selectionModel,
        SIGNAL(selectionChanged(const QItemSelection &,
                                const QItemSelection &)),
        this,
        SLOT(modelSelectionChanged(const QItemSelection &,
                                   const QItemSelection &)));

connect(this,
        SIGNAL(selectionChanged()),
        this,
        SLOT(sceneSelectionChanged()));

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::modelSelectionChanged(const QItemSelection& selected,
                                           const QItemSelection& deselected)
{

   if (m_selectionModel == NULL || m_model == NULL)
   {
      return;
   }

   disconnect(m_selectionModel,
              SIGNAL(selectionChanged(const QItemSelection &,
                                      const QItemSelection &)),
              this,
              SLOT(modelSelectionChanged(const QItemSelection &,
                                         const QItemSelection &)));

   disconnect(this,
              SIGNAL(selectionChanged()),
              this,
              SLOT(sceneSelectionChanged()));

   clearFocus();

   foreach (QModelIndex dIndex, deselected.indexes())
   {
      AbstractGraphicsItem* item =
            (AbstractGraphicsItem*)(dIndex.internalPointer());
      item->setSelected(false);
   }

   foreach (QModelIndex sIndex, selected.indexes())
   {
      AbstractGraphicsItem* item =
            (AbstractGraphicsItem*)(sIndex.internalPointer());
      item->setSelected(true);
   }

   connect(m_selectionModel,
           SIGNAL(selectionChanged(const QItemSelection &,
                                   const QItemSelection &)),
           this,
           SLOT(modelSelectionChanged(const QItemSelection &,
                                      const QItemSelection &)));

   connect(this,
           SIGNAL(selectionChanged()),
           this,
           SLOT(sceneSelectionChanged()));

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setMode(Mode mode)
{

   // Set mode for mouse clicks
   m_mode = mode;

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setPixmap(QPixmap p)
{

   // Set pixmap
   if (m_pixItem != NULL)
   {
      // Check against old image size and reset scene if necessary
      if ((m_pixItem -> boundingRect()).width() != p.width() ||
          (m_pixItem -> boundingRect()).height() != p.height())
      {
         m_pixItem -> setPixmap(p);
         setSceneRect(m_pixItem -> boundingRect());
         //updateROIs();
      }
      // New and old images have matching dimensions
      else
      {
         m_pixItem -> setPixmap(p);
      }

   }
   // Set first pixmap
   else
   {
      m_pixItem = addPixmap(p);
      //updateROIs();
   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setModel(QAbstractItemModel* model)
{

   // Remove old connections
   if (m_model != NULL)
   {
      disconnect(m_model,
                 SIGNAL(rowsInserted(const QModelIndex&, int, int)),
                 this,
                 SLOT(modelRowsInserted(const QModelIndex&, int, int)));
   }

   // Set model
   m_model = model;

   // Connect signals/slots to inserting and removing ROIs
   connect(m_model,
           SIGNAL(rowsInserted(const QModelIndex&, int, int)),
           this,
           SLOT(modelRowsInserted(const QModelIndex&, int, int)));

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setSelectionModel(QItemSelectionModel* selectionModel)
{

   // Remove old connections
   if (m_selectionModel != NULL)
   {
      disconnect(m_selectionModel,
                 SIGNAL(selectionChanged(const QItemSelection&,
                                         const QItemSelection&)),
                 this,
                 SLOT(modelSelectionChanged(const QItemSelection&,
                                            const QItemSelection&)));
   }

   // Set ROI selection model
   m_selectionModel = selectionModel;

   // Set new connections
   connect(m_selectionModel,
           SIGNAL(selectionChanged(const QItemSelection&,
                                   const QItemSelection&)),
           this,
           SLOT(modelSelectionChanged(const QItemSelection&,
                                      const QItemSelection&)));

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setZoomModeToFit()
{

   m_mode = Fit;

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setZoomModeToNone()
{

   m_mode = None;

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setZoomModeToZoomIn()
{

   m_mode = ZoomIn;

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setZoomModeToZoomOut()
{

   m_mode = ZoomOut;

}

/*---------------------------------------------------------------------------*/
/*
void ImageViewScene::updateROIs()
{

   // Model index
   QModelIndex index;

   // Update each ROI
   for (int i = 0 ; i < m_rois.size() ; i++) {

      // Get and recalculate ROI positions and size
      index = m_model -> index(i, ROITableModel::X);
      double x = (m_model -> data(index)).toDouble() *
                 pixRect().width();
      index = m_model -> index(i, ROITableModel::Y);
      double y = (m_model -> data(index)).toDouble() *
                 pixRect().height();
      index = m_model -> index(i, ROITableModel::Width);
      double w = (m_model -> data(index)).toDouble() *
                 pixRect().width();
      index = m_model -> index(i, ROITableModel::Height);
      double h = (m_model -> data(index)).toDouble() *
                 pixRect().height();

      // Update graphics item
      m_rois.at(i) -> setX(x);
      m_rois.at(i) -> setY(y);
      m_rois.at(i) -> setWidth(w);
      m_rois.at(i) -> setHeight(h);

   }

}
*/
/*---------------------------------------------------------------------------*/
