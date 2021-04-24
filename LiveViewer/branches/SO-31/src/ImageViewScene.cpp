/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ImageViewScene.h>
#include <QDebug>

/*---------------------------------------------------------------------------*/

ImageViewScene::ImageViewScene(QWidget* parent)
{

   Q_UNUSED(parent)

   // Initialize pointers to NULL
   m_pixItem = NULL;
   m_roiTableModel = NULL;
   m_roiSelectionModel = NULL;
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
           this, SLOT(roiItemSelectionChanged()));

}

/*---------------------------------------------------------------------------*/

ImageViewScene::~ImageViewScene()
{

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::enableROIs(bool state)
{

   // Show/hide each ROI item
   for (int i = 0 ; i < m_rois.size() ; i++) {
      m_rois.at(i) -> setVisible(state);
   }

   // Reset view; just in case...
   setSceneRect(m_pixItem -> boundingRect());

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

   if ((m_mode == ZoomIn) && (m_zoomSelection != NULL)) {

      QGraphicsView* view = qobject_cast<QGraphicsView*> (
         m_zoomSelection -> parent() -> parent());
      Q_ASSERT(view);

      // Resize rubber band based on initial mouse press and current mouse drag.
      QRectF rect(m_zoomOrigin, view -> mapFromScene(event -> scenePos()));
      m_zoomSelection -> setGeometry(rect.toRect().normalized());

      // Rubber band should only becomes visible, if the mouse is dragged.
      if (!m_zoomSelection -> isVisible())
         m_zoomSelection -> show();
      m_zoomRect = rect;

   }

   else {

      QGraphicsScene::mouseMoveEvent(event);

   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

   // Left click and mode is ZoomIn
   if ((event -> button() == Qt::LeftButton) && (m_mode == ZoomIn)) {

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
   else if ((event -> button() == Qt::LeftButton) && (m_mode == ZoomOut)) {

      // Emit zoomOut signal
      emit zoomOut();

   }

   // Propagate event
   if ((event -> button() == Qt::LeftButton ||
        event -> button() == Qt::RightButton) &&
       (m_mode == None || m_mode == Fit)) {
      QGraphicsScene::mousePressEvent(event);
   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

   if ((m_mode == ZoomIn) && m_zoomSelection != NULL) {

      delete m_zoomSelection;
      m_zoomSelection = NULL;

      emit zoomIn(m_zoomRect);

   }

   else {

      QGraphicsScene::mouseReleaseEvent(event);

   }

}

/*---------------------------------------------------------------------------*/

QRectF ImageViewScene::pixRect()
{

   return m_pixItem -> boundingRect();

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::roiChanged(const QModelIndex &topLeft,
                                const QModelIndex &bottomRight)
{

   // Mark unused
   Q_UNUSED(bottomRight)

   // Get ROI property / column
   int column = topLeft.column();

   // Get ROI graphics item index
   int row = topLeft.row();

   // Get graphics item
   RectItem* item = m_rois.at(row);

   // Get new data
   QVariant data = m_roiTableModel -> data(topLeft);


   // Get item position and bounds
   QPointF pt = item -> pos();
   QRectF rect = item -> boundingRect();

   // Set name
   if (column == ROITableModel::Name) {
      item -> setText(data.toString());
   }

   // Set color
   else if (column == ROITableModel::Color) {
      item -> setColor(QColor(data.toString()));
   }

   // Set x position
   else if (column == ROITableModel::X) {
      item -> setX(data.toDouble() * pixRect().width());
   }

   // Set y position
   else if (column == ROITableModel::Y) {
      item -> setY(data.toDouble() * pixRect().height());
   }

   // Set width
   else if (column == ROITableModel::Width) {
      item -> setWidth(data.toDouble() * pixRect().width());
   }

   // Set height
   else if (column == ROITableModel::Height) {
      item -> setHeight(data.toDouble() * pixRect().height());
   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::roiInserted(const QModelIndex &parent, int start, int end)
{

   // Mark unused
   Q_UNUSED(parent);


   // Check for model
   if (m_roiTableModel == NULL) {
      return;
   }

   // Model index
   QModelIndex index;

   // Graphics item pointer
   RectItem* roi = NULL;

   // Add a graphics item for each item inserted in model
   for (int row = start ; row <= end ; row++) {

      // Determine center of view for item
      QGraphicsView* view = views().at(0);
      QPointF topLeft = view -> mapToScene(0, 0);
      QPointF bottomRight = view -> mapToScene(view -> width(),
                                               view -> height());
      QPointF cent((bottomRight.x() - topLeft.x()) / 2 + topLeft.x(),
                   (bottomRight.y() - topLeft.y()) / 2 + topLeft.y());
      double deltaW = (bottomRight.x() - topLeft.x()) / 10;
      double deltaH = (bottomRight.y() - topLeft.y()) / 10;

      // X, Y position
      index = m_roiTableModel -> index(row, ROITableModel::X);
      double x = (m_roiTableModel -> data(index)).toDouble();
      index = m_roiTableModel -> index(row, ROITableModel::Y);
      double y = (m_roiTableModel -> data(index)).toDouble();

      // Width, height
      index = m_roiTableModel -> index(row, ROITableModel::Width);
      double w = (m_roiTableModel -> data(index)).toDouble();
      index = m_roiTableModel -> index(row, ROITableModel::Height);
      double h = (m_roiTableModel -> data(index)).toDouble();

      // Create graphics item - center item in view if all position info
      // is negative.
      if (x < 0 && y < 0 && w < 0 && h < 0) {
         roi = new RectItem(cent.x() - deltaW / 2,
                            cent.y() - deltaH / 2,
                            deltaW,
                            deltaH);
      }
      else {
         roi = new RectItem(x * pixRect().width(),
                            y * pixRect().height(),
                            w * pixRect().width(),
                            h * pixRect().height());
      }

      // Set name and color
      index = m_roiTableModel -> index(row, ROITableModel::Name);
      roi -> setText((m_roiTableModel -> data(index)).toString());
      index = m_roiTableModel -> index(row, ROITableModel::Color);
      roi -> setColor(QColor((m_roiTableModel -> data(index)).toString()));

      // Add to list
      m_rois.insert(row, roi);

      // Add item to scene
      addItem(roi);

      // Force model update
      roiItemChanged(roi);

      // Connect item's ItemChanged signal
      connect(roi, SIGNAL(itemChanged(RectItem*)),
              this, SLOT(roiItemChanged(RectItem*)));

   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::roiItemChanged(RectItem* roi)
{

   // NULL pointer check
   if (roi == NULL) {
      return;
   }


   // Find modified item in list and update ROIModel
   for (int i = 0 ; i < m_rois.size() ; i++) {

      // Check for ROI model
      if (m_roiTableModel != NULL) {

         // Get item bounding rectangle and position
         QRectF boundRect = m_rois.at(i) -> boundingRect();
         QPointF pt = m_rois.at(i) -> pos();

         // Set X
         QModelIndex iX = m_roiTableModel -> index(i, ROITableModel::X);
         m_roiTableModel -> setData(iX, pt.x() / pixRect().width());

         // Set Y
         QModelIndex iY = m_roiTableModel -> index(i, ROITableModel::Y);
         m_roiTableModel -> setData(iY, pt.y() / pixRect().height());

         // Set W
         QModelIndex iW = m_roiTableModel -> index(i, ROITableModel::Width);
         m_roiTableModel -> setData(iW,
                                    boundRect.width() / pixRect().width());

         // Set H
         QModelIndex iH = m_roiTableModel -> index(i, ROITableModel::Height);
         m_roiTableModel -> setData(iH,
                                    boundRect.height() / pixRect().height());

      }

   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::roiItemSelectionChanged()
{

   // Get selected items; only one item should be selected at a time
   QList<QGraphicsItem*> sel = selectedItems();

   // If there is no selection; empty selection
   if (sel.size() == 0) {
      m_roiSelectionModel -> select(
         QModelIndex(),
         QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
      return;
   }

   // Compare selection ROI to ROIs in ROI list
   RectItem* roi = NULL;
   QItemSelection itemSel;
   for (int i = 0 ; i < sel.size() ; i++) {

      // Get item in selection
      roi = (RectItem*) sel.at(i);

      // Find selected ROI index in ROI item list
      for (int j = 0 ; j < m_rois.size() ; j++) {
         if (roi == m_rois.at(j)) {

            // Create selection based on model index
            QModelIndex l = m_roiTableModel -> index(j, 0);
            itemSel.select(l, l);

         }
      }

   }

   // Set selection
   m_roiSelectionModel -> select(
      itemSel,
      QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::roiRemoved(const QModelIndex& parent, int start, int end)
{

   // Mark unused
   Q_UNUSED(parent);


   // Check for model
   if (m_roiTableModel == NULL) return;

   // Temp graphics item
   RectItem* item = NULL;

   // Remove count rows
   for (int r = end ; r >= start ; r--) {

      // Get item
      item = m_rois.at(r);

      // Remove item from scene
      removeItem(item);

      // Remove row from list of graphics items
      m_rois.removeAt(r);

      // Disconnect item's ItemChanged signal
      disconnect(item, SIGNAL(itemChanged(RectItem*)),
                 this, SLOT(roiItemChanged(RectItem*)));

      // Delete graphics item
      delete(item);

   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::roiSelectionChanged(const QItemSelection& selected,
                                         const QItemSelection& deselected)
{

   // Get selected indices
   QModelIndexList l = selected.indexes();

   // If selected indices exist
   if (l.size() > 0) {

      // Get first selected item
      int i = l.at(0).row();

      // Check that value is within roi list bounds
      if (i >= 0 && i < m_rois.size()) {

         // NULL pointer check
         if (m_rois.at(i) != NULL) {

            // Set selected to true
            m_rois.at(i) -> setSelected(true);

         }

      }

   }


   // Get deselected indices
   l = deselected.indexes();

   // If deselected indices exist
   if (l.size() > 0) {

      // Deselect each item
      for (int d = 0 ; d < l.size() ; d++) {

         // Get item index
         int i = l.at(d).row();

         // Check that value is within roi list bounds
         if (i >= 0 && i < m_rois.size()) {

            // NULL pointer check
            if (m_rois.at(i) != NULL) {
               m_rois.at(i) -> setSelected(false);
            }

         }

      }

   }

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
   if (m_pixItem != NULL) {

      // Check against old image size and reset scene if necessary
      if ((m_pixItem -> boundingRect()).width() != p.width() ||
          (m_pixItem -> boundingRect()).height() != p.height()) {
         m_pixItem -> setPixmap(p);
         setSceneRect(m_pixItem -> boundingRect());
         updateROIs();
      }

      // New and old images have matching dimensions
      else {
         m_pixItem -> setPixmap(p);
      }

   }

   // Set first pixmap
   else {
      m_pixItem = addPixmap(p);
      updateROIs();
   }

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setROIModel(ROITableModel* model)
{

   // Remove old connections
   if (m_roiTableModel != NULL) {
      disconnect(m_roiTableModel,
                 SIGNAL(dataChanged(const QModelIndex&,
                                    const QModelIndex&)),
                 this,
                 SLOT(roiChanged(const QModelIndex&, const QModelIndex&)));
      disconnect(m_roiTableModel,
                 SIGNAL(rowsInserted(const QModelIndex&, int, int)),
                 this,
                 SLOT(roiInserted(const QModelIndex&, int, int)));
      disconnect(m_roiTableModel,
                 SIGNAL(rowsRemoved(const QModelIndex&, int, int)),
                 this,
                 SLOT(roiRemoved(const QModelIndex&, int, int)));
   }

   // Set model
   m_roiTableModel = model;

   // Connect signals/slots to inserting and removing ROIs
   connect(m_roiTableModel,
           SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
           this,
           SLOT(roiChanged(const QModelIndex&, const QModelIndex&)));
   connect(m_roiTableModel,
           SIGNAL(rowsInserted(const QModelIndex&, int, int)),
           this,
           SLOT(roiInserted(const QModelIndex&, int, int)));
   connect(m_roiTableModel,
           SIGNAL(rowsRemoved(const QModelIndex&, int, int)),
           this,
           SLOT(roiRemoved(const QModelIndex&, int, int)));

}

/*---------------------------------------------------------------------------*/

void ImageViewScene::setROISelectionModel(QItemSelectionModel* selectionModel)
{

   // Remove old connections
   if (m_roiSelectionModel != NULL) {
      disconnect(m_roiSelectionModel,
                 SIGNAL(selectionChanged(const QItemSelection&,
                                         const QItemSelection&)),
                 this,
                 SLOT(roiSelectionChanged(const QItemSelection&,
                                          const QItemSelection&)));
   }

   // Set ROI selection model
   m_roiSelectionModel = selectionModel;

   // Set new connections
   connect(m_roiSelectionModel,
           SIGNAL(selectionChanged(const QItemSelection&,
                                   const QItemSelection&)),
           this,
           SLOT(roiSelectionChanged(const QItemSelection&,
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

void ImageViewScene::updateROIs()
{

   // Model index
   QModelIndex index;

   // Update each ROI
   for (int i = 0 ; i < m_rois.size() ; i++) {

      // Get and recalculate ROI positions and size
      index = m_roiTableModel -> index(i, ROITableModel::X);
      double x = (m_roiTableModel -> data(index)).toDouble() *
                 pixRect().width();
      index = m_roiTableModel -> index(i, ROITableModel::Y);
      double y = (m_roiTableModel -> data(index)).toDouble() *
                 pixRect().height();
      index = m_roiTableModel -> index(i, ROITableModel::Width);
      double w = (m_roiTableModel -> data(index)).toDouble() *
                 pixRect().width();
      index = m_roiTableModel -> index(i, ROITableModel::Height);
      double h = (m_roiTableModel -> data(index)).toDouble() *
                 pixRect().height();

      // Update graphics item
      m_rois.at(i) -> setX(x);
      m_rois.at(i) -> setY(y);
      m_rois.at(i) -> setWidth(w);
      m_rois.at(i) -> setHeight(h);

   }

}

/*---------------------------------------------------------------------------*/
