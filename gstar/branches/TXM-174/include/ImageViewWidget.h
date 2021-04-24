/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef GSTAR_IMAGE_VIEW_WIDGET_H
#define GSTAR_IMAGE_VIEW_WIDGET_H

/*---------------------------------------------------------------------------*/

#include <ImageViewScene.h>
#include <RangeWidget.h>

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
#include <QToolButton>

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
    * Returns a pointer to the scene that is currently visualized in the view.
    * If no scene is currently visualized, 0 is returned.
    *
    * @return the current scene.
    */
   ImageViewScene* scene();

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
    * Set height dimension
    */
   void setHeightDims(int h);

   /**
    * Set width dimension
    */
   void setWidthDims(int w);

protected:

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

private slots:

   /**
    * Handle click on cursor tool bar icon
    */
   void clickCursor();

   /**
    * Slot when the line buttion is triggerd
    */
   void lineButtonTriggered();

   /**
    * Handle click on fill tool bar icon. Switch to fill mode.
    */
   void clickFill();

   /**
    * Handle click on zoom in tool bar icon. Switch to zoom in mode.
    */
   void clickZoomIn();

   /**
    * Handle click on zoom back to original tool bar icon.
    */
   void clickZoomOriginal();

   /**
    * Handle click on zoom out tool bar icon. Switch to zoom out mode.
    */
   void clickZoomOut();

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

   /**
    * Slot to handle the Width combo box's valueChanged() signal.
     */
   void comboWidthChanged(int value);

   /**
    * Slot to handle the Height combo box's valueChanged() signal.
     */
   void comboHeightChanged(int value);

   /**
    * Slot to handle the range Widget's valueChanged() signal.
     */
   void rangeChanged(int value ,int id);

private:

   qreal getCurrentZoomPercent();

   /**
    * Create standard actions used on the menu bar.
    */
   void createActions();

   /**
    * Create layout for widget
    */
   void createLayout();

   /**
    * Create graphics scene and graphics view
    */
   void createSceneAndView();

   /**
    * Create and setup the tool bar and connections for standard actions.
    */
   void createToolBar();

   /**
    * Create and setup the rangewidget.
    */
   void createRangewidget();

private:

   /**
    * Tool bar for zoom tools
    */
   QToolBar* m_toolbar;

   /**
    * Group for zoom in, out and fill tools
    */
   QActionGroup* m_zoomGroup;

   /**
    * Cursor
    */
   QAction* m_cursorAction;

   /**
    * Zoom in
    */
   QAction* m_zoomInAction;

   /**
    * Zoom out
    */
   QAction* m_zoomOutAction;

   /**
    * Zoom to original
    */
   QAction* m_zoomOriginalAction;

   /**
    * Fill
    */
   QAction* m_fillAction;

   /**
    * Line
    */
   QAction* m_lineDrawAction;

   /**
    * The QGraphicsScene subclass for the QGraphicsView
    */
   ImageViewScene* m_scene;

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
    * Current image zoom value.
    */
   QComboBox* m_zoomPercent;

   QList<float> m_zoomSettings;

   /**
    * Range widget.
    */
   RangeWidget* m_range;

   /**
    * ComboBox control.
    */
   QComboBox* m_comboWidth;
   QComboBox* m_comboHeight;

   /**
    * Label control.
    */
   QLabel* m_higlbl;
   QLabel* m_widlbl;

   /**
    * Action control.
    */
   QAction* m_ahiglbl;
   QAction* m_awidlbl;
   QAction* m_acomboHeight;
   QAction* m_acomboWidth;


   /**
    * QAction control.
    */
   QAction* m_widsep;



};

}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
