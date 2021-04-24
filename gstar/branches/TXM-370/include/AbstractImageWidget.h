/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TXM_ABSTRACT_IMAGE_WIDGET_H
#define TXM_ABSTRACT_IMAGE_WIDGET_H

/*---------------------------------------------------------------------------*/

#include <QWidget>

namespace gstar
{
   class AbstractGraphicsItem;
   class AnnotationToolBarWidget;
   class Array;
   class AnnotationTreeModel;
   class ImageViewWidget;
   class ImageViewToolBar;
   class RangeWidget;
}

class QAbstractTableModel;
class QComboBox;
class QItemSelectionModel;
class QTabWidget;
class QToolBar;
class QTreeView;
class QModelIndex;

/*---------------------------------------------------------------------------*/

namespace gstar
{

/**
 * @brief When open the acquisition window, the widget is showing for capturing
 * the image from the area detector writer, the window will also be updated to
 * show the image.
 */
class AbstractImageWidget
: public QWidget
{

   Q_OBJECT

public:

   /**
    * Constructor.
    */
   AbstractImageWidget(QWidget* parent = NULL);

   /**
    * Destructor.
    */
   ~AbstractImageWidget();

   /**
    * @brief getImageViewWidget
    * @return
    */
   ImageViewWidget* imageViewWidget() const;

public slots:

   /**
    *  Set height dimension.
    *
    *  @param d - Dimension
    */
   void setHeightDims(int d);

   /**
    * Set number of images that can be viewed.
    *
    * @param i # of images.
    */
   void setNumberOfImages(int i);

   /**
    * Total number of dimension in the image
    *
    * @param r - Rank or number of dimension for the image.
    */
   void setRank(int r);
 
   /**
    * The current index of the image loaded in the widget.
    *
    * @param index - Image number.
    */
   void setRangeWidgetStartIndex(int index);

   /**
    * Set the dimension number for the width of the image.
    *
    * @param w - dimension number. 
    */
   void setWidthDims(int w);

   /**
    * Updat the frame when new image shows.
    *
    */
   void updateFrame(const Array* image);

signals:
  
   /**
    * The height dimension was modified
    *
    * @param The new dimension
    */
   void imageHeightDimChanged(int);

   /**
    * The width dimension was modified
    *
    * @param The new dimension
    */
   void imageWidthDimChanged(int);

   /**
    * The range of images that can be viewed in the widget changed.
    *
    * @param The new value.
    * @param Id
    */
   void rangeChanged(int, int);

protected slots:

   /**
    * @brief addMarker
    */
   void addMarker();

   /**
    * @brief addRuler
    */
   void addRuler();

   /**
    * @brief deleteItem
    */
   void deleteItem();

   /**
    * @brief duplicateItem
    */
   void duplicateItem();

   /**
    * @brief modelDataChanged
    */
   void modelDataChanged(const QModelIndex &, const QModelIndex &);

   /**
    * @brief treeContextMenu
    * @param pos
    */
   void treeContextMenu(const QPoint &pos);

   /**
    * @brief treeDoubleClicked
    * @param index
    */
   void treeDoubleClicked(const QModelIndex &index);

   /**
    * @brief viewContextMenu
    * @param pos
    */
   void viewContextMenu(const QPoint& pos);

protected:

   /**
    * @brief appendAnnotationTab
    */
   void appendAnnotationTab();

   /**
    * @brief createActions
    */
   void createActions();

   /**
    * Virtual method that must be overidden by base classes.
    */
   QLayout* generateDefaultLayout();

   /**
    * Create tool bar
    */
   virtual void createToolBar();

   /**
    * @brief createAnnotationToolBar
    */
   void createAnnotationToolBar();

   /**
    * Range widget
    */
   void createRangeWidget();

   /**
    * @brief displayContextMenu
    * @param parent
    * @param pos
    */
   void displayContextMenu(QWidget* parent, const QPoint& pos);

   /**
    * @brief insertAndSelectAnnotation
    * @param annotation
    */
   void insertAndSelectAnnotation(AbstractGraphicsItem* annotation);

protected:

   /**
    * @brief m_addMarkerAction
    */
   QAction* m_addMarkerAction;

   /**
    * @brief m_addRulerAction
    */
   QAction* m_addRulerAction;

   /**
    * @brief m_deleteAction
    */
   QAction* m_deleteAction;

   /**
    * @brief m_duplicateAction
    */
   QAction* m_duplicateAction;

   /**
    * @brief m_annotationToolbar
    */
   AnnotationToolBarWidget* m_annotationToolbar;

   /**
    * Pick dimension for image height.
    */
   QComboBox* m_imageHeightDim;

   /**
    * Pick dimension for image width.
    */
   QComboBox* m_imageWidthDim;

   /**
    * Toolbar contains action for manipulating image settings such as zoom.
    */
   ImageViewToolBar* m_imageWidgetToolBar;

   /**
    * Widget for viewing/manipulating image
    */
   ImageViewWidget* m_imageViewWidget;

   /**
    * Range widget.
    */
   RangeWidget* m_range;

   /**
     * @brief m_selectionModel
     */
   QItemSelectionModel* m_selectionModel;

   /**
    * @brief m_tabWidget
    */
   QTabWidget* m_tabWidget;

   /**
    * Toolbar
    */
   QToolBar* m_toolbar;

   /**
    * @brief m_annoTreeView
    */
   QTreeView* m_annoTreeView;

   /**
    * @brief m_treeModel
    */
   AnnotationTreeModel* m_treeModel;

   /**
    * @brief m_treeTabWidget
    */
   QWidget* m_treeTabWidget;

};

}

/*---------------------------------------------------------------------------*/

#endif /* ImageWidget_H_ */

/*---------------------------------------------------------------------------*/
