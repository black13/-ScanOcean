/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef GSTAR_IMAGE_VIEW_WIDGET_H
#define GSTAR_IMAGE_VIEW_WIDGET_H

/*---------------------------------------------------------------------------*/

#include <CoordinateWidget.h>
#include <ImageViewScene.h>
#include <RangeWidget.h>

#include <QResizeEvent>
#include <QAction>
#include <QCursor>
#include <QGraphicsView>
#include <QIcon>
#include <QPixmap>
#include <QStandardItemModel>
#include <QTableView>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

/*---------------------------------------------------------------------------*/

class QComboBox;

/*---------------------------------------------------------------------------*/

namespace gstar
{
/**
 * @brief The ImageViewWidget class ...
 */
class ImageViewWidget
: public QWidget
{

   Q_OBJECT

public:

   enum ZoomMode
   {
      ZOOM_NONE,
      ZOOM_IN,
      ZOOM_OUT,
      ZOOM_FIT
   };

   /**
    * Constructor
    *
    * @param parent the Qt parent widget.
    */
   ImageViewWidget(QWidget* parent = 0);

   /**
    * Destructor
    */
   ~ImageViewWidget();

   /**
    * @brief coordinateWidget
    * @return
    */
   CoordinateWidget* coordinateWidget();

   /**
    * Widget for controlling image setting. 
    */
   QToolBar* getImageControlsWidget();

   /**
    * @brief getCenterPoint
    * @return
    */
   QPointF getCenterPoint() const;

   /**
    * Even when the mouse leave the widget
    */
   void leaveEvent(QEvent * event);

   /**
    * Returns a pointer to the scene that is currently visualized in the view.
    * If no scene is currently visualized, 0 is returned.
    *
    * @return the current scene.
    */
   ImageViewScene* scene();

   /**
    * sets the coordinate model for coordinate widget
    */
   void setCoordinateModel(CoordinateModel* model);

   /**
    *  Set the number of images for range widget.
    */
   void setNumberOfImages(int images);

   /**
    * Set the dim of the two comboxes.
    */
   void setRank(int m_rankDim);

   /**
    * Set the enable status of the rangeWidget.
    */
   void setRangeWidgetEnable(bool m_rangeEnable = false);

   /**
    * Set starting index for the range widget
    */
   void setRangeWidgetStartIndex(int index);

   /**
    * Set the visible status of the rangeWidget.
    */
   void setRangewidgetVisible(bool m_rangeVisible = false);

   /**
    * Sets the current scene to scene. If scene is already being viewed,
    * this function does nothing.
    *
    * @param scene - The scene to set.
    */
   void setScene(ImageViewScene* scene);

   /**
    * The widget to display current zoom value.
    *
    * This widget is created in ImageViewToolBar.
    */
   void setZoomPercentWidget(QComboBox* zoomPercent);

   /**
    * Event filter
    */
   //bool eventFilter(QObject* object, QEvent* event);

public slots:

   /**
    * Handle click on cursor tool bar icon
    */
   void clickCursor();

   /**
    * Handle click on zoom in tool bar icon. Switch to zoom in mode.
    */
   void clickZoomIn();

   /**
    * Handle click on fill tool bar icon. Switch to fill mode.
    *
    * @param check - The flag for the fill button state. 
    */
   void clickFill(bool check);
   /**
    * Handle click on zoom back to original tool bar icon.
    */
   void clickZoomOriginal();

   /**
    * Handle click on zoom out tool bar icon. Switch to zoom out mode.
    */
   void clickZoomOut();

//protected:

   /**
    * Overridden resize handler
    *
    * See Qt documentation
    */
   void resizeEvent(QResizeEvent* event);

signals:

   /**
    ** This signal is emitted whenever the combox1's value is changed.
    * The new value is passed in value.
    * @param value the widget's new value.
    */
   void valueChangedWidth(int value);

   /**
    ** This signal is emitted whenever the combox1's value is changed.
    * The new value is passed in value.
    * @param value the widget's new value.
    */
   void valueChangedHeight(int value);

   /**
    ** This signal is emitted whenever the combox1's value is changed.
    * The new value is passed in value.
    * @param value the widget's new value.
    */
   void imageViewSignal(int value, int id);

protected slots:

   /**
    * The coordinates that when mouse moves over
    *
    * @param x - x coordinate.
    * @param y - y coordinate.
    */
   virtual void mouseOverPixel(int x, int y);

private slots:

   /**
    * Handle change to scene rectangle
    *
    * @param rect - scene rectangle
    */
   void sceneRectUpdated(const QRectF& rect);

   /**
    * Handle change to image zoom percentage factor.
    */
   void updateZoomPercentage();

   /**
    * Zoom in the region of the image selected by the user.
    * In case no selection was made, zoom-in on the image
    * by a fixed scale and anchor the image at center.
    *
    * @param zoomRect - zoom selection rectangle.
    */
   void zoomIn(QRectF zoomRect);

   /**
    * Zoom out
    */
   void zoomOut();

   /**
    * Called when zoom percentage is updated by the user.
    */
   void zoomValueChanged();

private:

   /**
    * @brief getCurrentZoomPercent
    * @return
    */
   qreal getCurrentZoomPercent();
   
   /**
    * Create layout for widget
    */
   void createLayout();

   /**
    * Create graphics scene and graphics view
    */
   void createSceneAndView();

   /**
    * Create and setup the rangewidget.
    */
   void createRangewidget();


private:

   /**
    * Coordinate widget
    */
   CoordinateWidget* m_coordWidget;

   /**
    * The QGraphicsScene subclass for the QGraphicsView
    */
   ImageViewScene* m_scene;

   /**
    * Widget
    */
   QWidget* m_widget;

   /**
    * QGraphicsView for displaying the scene graph
    */
   QGraphicsView* m_view;

   /**
    * Zoom in cursor
    */
   QCursor m_zoomInCursor;

   /**
    * Zoom out cursor
    */
   QCursor m_zoomOutCursor;

   /**
    * Zoom percent combobox
    */
   QComboBox* m_zoomPercent;

   /**
    * Fill action requires us to maintain a state
    *  that is used during resize event of the widget
    */
   bool m_fillState;

};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
