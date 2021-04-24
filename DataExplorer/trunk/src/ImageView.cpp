/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ImageView.h>

using namespace dstar;
using boost::dynamic_pointer_cast;
using boost::shared_array;
using boost::shared_ptr;
using std::pair;
using std::string;
using std::vector;

#include <iostream>

/*---------------------------------------------------------------------------*/

ImageView::ImageView(QWidget* parent)
: QWidget(parent), AbstractView()
{

   // Initialize everything
   m_bufferRGB = NULL;
   m_dims = NULL;
   m_ignore = false;
   m_propertiesTable = NULL;
   m_rank = 0;
   m_scene = NULL;


   // Toolbar cursor action
   m_cursorAction = new QAction(QIcon(":images/cursor.png"),
                                tr("Cursor"), this);
   m_cursorAction -> setCheckable(true);
   m_cursorAction -> setChecked(true);
   connect(m_cursorAction, SIGNAL(triggered()), this, SLOT(clickCursor()));

   // Toolbar zoom in action
   m_zoomInAction = new QAction(QIcon(":/images/zoomin.png"),
                                tr("Zoom In"), this);
   m_zoomInAction -> setCheckable(true);
   connect(m_zoomInAction, SIGNAL(triggered()), this, SLOT(clickZoomIn()));

   // Toolbar zoom out action
   m_zoomOutAction = new QAction(QIcon(":/images/zoomout.png"),
                                 tr("Zoom Out"), this);
   m_zoomOutAction -> setCheckable(true);
   connect(m_zoomOutAction, SIGNAL(triggered()), this, SLOT(clickZoomOut()));

   // Zoom action group
   m_zoomGroup = new QActionGroup(this);
   m_zoomGroup -> addAction(m_cursorAction);
   m_zoomGroup -> addAction(m_zoomInAction);
   m_zoomGroup -> addAction(m_zoomOutAction);

   // Toolbar fill action
   m_fillAction = new QAction(QIcon(":/images/fill.png"),
                              tr("Fill"), this);
   m_fillAction -> setCheckable(true);
   connect(m_fillAction, SIGNAL(triggered()), this, SLOT(clickFill()));

   // Create toolbar
    m_toolbar = new QToolBar(this);
    m_toolbar -> setFloatable(false);
    m_toolbar -> setMovable(false);

    // Add toolbar actions
    m_toolbar -> addAction(m_cursorAction);
    m_toolbar -> addAction(m_zoomInAction);
    m_toolbar -> addAction(m_zoomOutAction);
    m_toolbar -> addAction(m_fillAction);

    // Zoom in/out cursors
    m_zoomInCursor = QCursor(QPixmap(":/images/zoomin.png"));
    m_zoomOutCursor = QCursor(QPixmap(":/images/zoomout.png"));

}

/*---------------------------------------------------------------------------*/

ImageView::~ImageView()
{

   // Clean up dimension extents
   if (m_dims != NULL) {
      delete [] m_dims;
   }

   // Clean up RGB buffer
   if (m_bufferRGB != NULL) {
      delete [] m_bufferRGB;
      m_bufferRGB = NULL;
   }

}

/*---------------------------------------------------------------------------*/

void ImageView::clickCursor()
{

   // Set scene mode
   m_scene -> setZoomModeToNone();

   // Set regular cursor
   m_view -> viewport() -> setCursor(Qt::ArrowCursor);

}

/*---------------------------------------------------------------------------*/

void ImageView::clickFill()
{

   // Make toolbar button look checked
   m_cursorAction -> setChecked(true);

   // Get out of zoom mode
   clickCursor();

   // Set scene mode
   if (m_fillAction -> isChecked()) {
      m_zoomGroup -> setEnabled(false);
      m_scene -> setZoomModeToFit();
      resizeEvent(NULL);
   }
   else {
      m_zoomGroup -> setEnabled(true);
   }

   // Set regular cursor
   m_view -> viewport() -> setCursor(Qt::ArrowCursor);

}

/*---------------------------------------------------------------------------*/

void ImageView::clickZoomIn()
{

   // Set zoom in mode
   m_scene -> setZoomInMode();

   // Change cursor
   m_view -> viewport() -> setCursor(m_zoomInCursor);

}

/*---------------------------------------------------------------------------*/

void ImageView::clickZoomOut()
{

   // Set zoom out mode
   m_scene -> setZoomOutMode();

   // Change cursor
   m_view -> viewport() -> setCursor(m_zoomOutCursor);

}

/*---------------------------------------------------------------------------*/

void ImageView::dataAdded(shared_ptr<AbstractObject> obj)
{

   // Initial data setup

   // Convert to AbstractData and store
   m_data = dynamic_pointer_cast<AbstractData>(obj);

   // Get selection
   m_selCur = m_data -> getSelection();
   m_selFull = m_data -> getSelection();

   // Get data's rank
   m_rank = m_data -> getRank();

   // Allocate memory for dimension extents
   m_dims = new unsigned long long[m_rank];
   for (unsigned long d = 0 ; d < m_rank ; d++) {
      m_dims[d] = 0;
   }

   // Get data dimension extents
   m_data -> getDims(m_dims, m_rank);

   // Select full extents for final dimensions
   for (int d = m_rank - 1 ; d >= 0 ; d--) {
      m_selCur.setStart((unsigned long long) 0, (unsigned long) d);
      //m_selCur.setCount((unsigned long long) 1, d - 2);
   }


   // Create main layout for widget
   QVBoxLayout* layout = new QVBoxLayout();
   layout -> setContentsMargins(0, 0, 0, 0);
   layout -> setSpacing(0);
   layout -> setAlignment(Qt::AlignLeft | Qt::AlignTop);
   layout -> addWidget(m_toolbar);


   // Setup range widgets

   // Create range widgets for all dimensions > 2
   for (unsigned long d = 2 ; d < m_rank ; d++) {

      // ComboBox for this dimension/range mapping
      ComboBox* combo = new ComboBox((int) d - 2);
      combo -> setMaximumWidth(75);
      combo -> setMinimumWidth(75);
      for (unsigned long i = 0 ; i < m_rank ; i++) {
         combo -> addItem(tr("dim %1").arg(i));
      }
      combo -> setCurrentIndex(d - 2);
      connect(combo, SIGNAL(indexChanged(int, int, int)),
              this, SLOT(updateCombo(int, int, int)));
      m_listCombo.append(combo);

      // RangeWidget for this dimension
      RangeWidget* range = new RangeWidget();
      range -> setId(d - 2);
      range -> setMaximum(m_dims[d - 2] - 1);
      range -> setMinimum(0);
      connect(range, SIGNAL(valueChanged(int, int)),
              this, SLOT(rangeChanged(int, int)));
      m_listRange.append(range);

      // Create range window layout
      QHBoxLayout* rlayout = new QHBoxLayout();
      rlayout -> setContentsMargins(0, 0, 0, 0);
      rlayout -> setSpacing(3);
      rlayout -> setAlignment(Qt::AlignLeft | Qt::AlignTop);
      rlayout -> addWidget(combo);
      rlayout -> addWidget(range);

      // Setup current selection for this dimension
      m_selCur.setStart((unsigned long long) 0, (unsigned long) d - 2);
      m_selCur.setCount((unsigned long long) 1, (unsigned long) d - 2);

      // Add range layout to main layout
      layout -> addLayout(rlayout);

   }


   // Setup image view and scene

   // Create the graphics view
   m_view = new QGraphicsView();
   m_view -> setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
   m_scene = new ImageViewScene();
   m_view -> setScene(m_scene);
   connect(m_scene, SIGNAL(zoomIn()), this, SLOT(zoomIn()));
   connect(m_scene, SIGNAL(zoomOut()), this, SLOT(zoomOut()));
   //m_scene -> SetZoomOutMode();


   // Layout for view and combo boxes
   QHBoxLayout* tlayout = new QHBoxLayout();
   tlayout -> setContentsMargins(0, 0, 0, 0);
   tlayout -> setSpacing(3);
   tlayout -> setAlignment(Qt::AlignLeft | Qt::AlignTop);

   // If there's more than one dimension, create combo boxes for
   // dimension choices
   if (m_rank > 1) {

      // ComboBox for table columns (width)
      ComboBox* comboCol = new ComboBox((int) (m_rank - 2));
      comboCol -> setMaximumWidth(75);
      comboCol -> setMinimumWidth(75);
      m_listCombo.append(comboCol);
      for (unsigned long d = 0 ; d < m_rank ; d++) {
         comboCol-> addItem(tr("dim %1").arg(d));
      }
      comboCol -> setCurrentIndex(m_rank - 2);
      connect(comboCol, SIGNAL(indexChanged(int, int, int)),
              this, SLOT(updateCombo(int, int, int)));

      // ComboBox for table rows (height)
      ComboBox* comboRow = new ComboBox((int) (m_rank - 1));
      comboRow -> setMaximumWidth(75);
      comboRow -> setMinimumWidth(75);
      m_listCombo.append(comboRow);
      for (unsigned long d = 0 ; d < m_rank ; d++) {
         comboRow-> addItem(tr("dim %1").arg(d));
      }
      comboRow -> setCurrentIndex(m_rank - 1);
      connect(comboRow, SIGNAL(indexChanged(int, int, int)),
              this, SLOT(updateCombo(int, int, int)));

      // Layout for two combo boxes
      QVBoxLayout* vlayout = new QVBoxLayout();
      vlayout -> addWidget(comboCol);
      vlayout -> addWidget(comboRow);
      vlayout -> setContentsMargins(0, 0, 0, 0);
      vlayout -> setSpacing(3);
      vlayout -> setAlignment(Qt::AlignLeft | Qt::AlignTop);
      tlayout -> addLayout(vlayout);

   }

   // Add view to view layout
   tlayout -> addWidget(m_view);

   // Create a widget simply to contain the view layout
   // This is used for the QSplitter later
   QWidget* tableWidgets = new QWidget();
   tableWidgets -> setLayout(tlayout);


   // Properties display widgets

   // Create properties table
   m_propertiesTable = new QTableView();
   (m_propertiesTable -> horizontalHeader()) -> setStretchLastSection(true);
   (m_propertiesTable -> horizontalHeader()) ->
     setResizeMode(QHeaderView::ResizeToContents);
   (m_propertiesTable -> verticalHeader()) ->
     setDefaultSectionSize(m_propertiesTable -> verticalHeader() ->
                           minimumSectionSize());
   m_propertiesTable -> verticalHeader() -> hide();
   m_propertiesTable -> horizontalHeader() -> hide();
   m_propertiesTable -> setAlternatingRowColors(true);
   m_propertiesTable -> setShowGrid(false);
   m_propertiesTable -> setSelectionMode(QAbstractItemView::NoSelection);
   m_propertiesTable -> setSelectionBehavior(QAbstractItemView::SelectRows);
   m_propertiesTable -> setEditTriggers(QAbstractItemView::NoEditTriggers);

   // Set model for properties table
   vector<pair<string, string> > props = obj -> getProperties();
   QStandardItemModel* propertiesModel =
      new QStandardItemModel(props.size(), 2);
   for (unsigned int row = 0; row < props.size(); ++row) {
      QStandardItem* item =
         new QStandardItem(QString(props[row].first.c_str()));
      propertiesModel -> setItem(row, 0, item);
      item = new QStandardItem(QString(props[row].second.c_str()));
      propertiesModel -> setItem(row, 1, item);
   }
   m_propertiesTable -> setModel(propertiesModel);


   // Add everything to the widget

   // Splitter for data and properties tables
   QSplitter* splitter = new QSplitter();
   splitter -> setOrientation(Qt::Vertical);
   splitter -> addWidget(tableWidgets);
   splitter -> addWidget(m_propertiesTable);
   splitter -> setStretchFactor(0, 1);
   splitter -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   layout -> addWidget(splitter);

   // Set widget's layout
   setLayout(layout);

   // Create initial list of ranks
   for (unsigned long i = 0 ; i < m_rank ; i++) {
      m_listRank.append(i);
   }

   // Set major order
   if (m_rank >= 2) {
      if (m_listRank[m_listRank.size() - 1] <
          m_listRank[m_listRank.size() - 2]) {
         m_scene -> setRowMajor();
      }
      else {
         m_scene -> setColumnMajor();
      }
   }

   // Show it
   show();

   if (m_bufferRGB != NULL) {
      delete [] m_bufferRGB;
      m_bufferRGB = NULL;
   }

   if (m_rank == 1) {
      m_bufferRGB = new char[m_dims[0] * 4];
   }
   else {
      m_bufferRGB = new char[m_dims[m_listRank[m_rank - 1]] *
                             m_dims[m_listRank[m_rank - 2]] * 4];
   }

   // Update the model and display
   update();

   // Force fill mode
   m_fillAction -> trigger();
   resizeEvent(NULL);

}

/*---------------------------------------------------------------------------*/

void ImageView::dataRemoved(shared_ptr<AbstractObject> obj)
{
}

/*---------------------------------------------------------------------------*/

void ImageView::rangeChanged(int value, int id)
{

   // Ignore nested updates
   if (m_ignore == true) {
      return;
   }

   // Update the model and display
   updateSelection();
   update();

}

/*---------------------------------------------------------------------------*/

void ImageView::resizeEvent(QResizeEvent* event)
{

   // Check if fill is not enabled
   if (!m_fillAction -> isChecked()) {
      return;
   }

   // Get image size
   QRectF r(0, 0,
            (m_scene -> sceneRect()).width(),
            (m_scene -> sceneRect()).height());

   // Make image fit window
   m_view -> fitInView(r, Qt::KeepAspectRatio);

}

/*---------------------------------------------------------------------------*/

void ImageView::update()
{

   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

   // Update selection
   m_data -> setSelection(m_selCur);

   // Get the data
   shared_array<char> arr = m_data -> getData();

   double o = 0.0;
   double value = 0.0;
   double r, g, b;

   // Get data and cast for type
   // Try to template all of this, if possible...
   switch (m_data -> getType()) {
   case dstar::Char: {
      char* orig = (char*) arr.get();
      for (int row = 0 ; row < m_dims[m_listRank[m_rank - 1]] ; row++) {
         for (int col = 0 ; col < m_dims[m_listRank[m_rank - 2]] ; col++) {
            o = (double) orig[row * m_dims[m_listRank[m_rank - 2]] + col];
            o = (o / 255.0) * 255.0;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 0] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 1] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 2] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 3] = 0;
         }
      }
   }
   break;
   case dstar::ShortChar: {
      char* orig = (char*) arr.get();
      for (int row = 0 ; row < m_dims[m_listRank[m_rank - 1]] ; row++) {
         for (int col = 0 ; col < m_dims[m_listRank[m_rank - 2]] ; col++) {
            o = (double) orig[row * m_dims[m_listRank[m_rank - 2]] + col];
            o = (o / 255.0) * 255.0;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 0] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 1] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 2] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 3] = 0;
         }
      }
   }
   break;
   case dstar::UnsignedChar: {
      unsigned char* orig = (unsigned char*) arr.get();
      for (int row = 0 ; row < m_dims[m_listRank[m_rank - 1]] ; row++) {
         for (int col = 0 ; col < m_dims[m_listRank[m_rank - 2]] ; col++) {
            o = (double) orig[row * m_dims[m_listRank[m_rank - 2]] + col];
            o = (o / 255.0) * 255.0;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 0] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 1] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 2] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 3] = 0;
         }
      }
   }
   break;
   case dstar::Short: {
      short* orig = (short*) arr.get();
      for (int row = 0 ; row < m_dims[m_listRank[m_rank - 1]] ; row++) {
         for (int col = 0 ; col < m_dims[m_listRank[m_rank - 2]] ; col++) {
            o = (double) orig[row * m_dims[m_listRank[m_rank - 2]] + col];
            o = (o / 4095.0) * 255.0;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 0] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 1] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 2] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 3] = 0;
         }
      }
   }
   break;
   case dstar::UnsignedShort: {
      unsigned short* orig = (unsigned short*) arr.get();
      for (int row = 0 ; row < m_dims[m_listRank[m_rank - 1]] ; row++) {
         for (int col = 0 ; col < m_dims[m_listRank[m_rank - 2]] ; col++) {
            o = (double) orig[row * m_dims[m_listRank[m_rank - 2]] + col];
            o = (o / 4095.0) * 255.0;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 0] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 1] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 2] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 3] = 0;
         }
      }
   }
   break;
   case dstar::Int: {
      int* orig = (int*) arr.get();
      for (int row = 0 ; row < m_dims[m_listRank[m_rank - 1]] ; row++) {
         for (int col = 0 ; col < m_dims[m_listRank[m_rank - 2]] ; col++) {
            o = (double) orig[row * m_dims[m_listRank[m_rank - 2]] + col];
            o = (o / 255.0) * 255.0;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 0] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 1] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 2] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 3] = 0;
         }
      }
   }
   break;
   case dstar::UnsignedInt: {
      unsigned int* orig = (unsigned int*) arr.get();
      for (int row = 0 ; row < m_dims[m_listRank[m_rank - 1]] ; row++) {
         for (int col = 0 ; col < m_dims[m_listRank[m_rank - 2]] ; col++) {
            o = (double) orig[row * m_dims[m_listRank[m_rank - 2]] + col];
            o = (o / 255.0) * 255.0;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 0] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 1] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 2] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 3] = 0;
         }
      }
   }
   break;
   case dstar::Long: {
      (long*) arr.get();
   }
   break;
   case dstar::UnsignedLong: {
      (unsigned long*) arr.get();
   }
   break;
   case dstar::LongLong: {
      (long long*) arr.get();
   }
   break;
   case dstar::UnsignedLongLong: {
      (unsigned long long*) arr.get();
   }
   break;
   case dstar::Float: {
      (float*) arr.get();
   }
   break;
   case dstar::Double: {
      double* orig = (double*) arr.get();
      for (int row = 0 ; row < m_dims[m_listRank[m_rank - 1]] ; row++) {
         for (int col = 0 ; col < m_dims[m_listRank[m_rank - 2]] ; col++) {
            o = (double) orig[row * m_dims[m_listRank[m_rank - 2]] + col];
            o = (o / 4095.0) * 255.0;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 0] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 1] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 2] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 3] = 0;
         }
      }
   }
   break;
   case dstar::LongDouble: {
      float* orig = (float*) arr.get();
      for (int row = 0 ; row < m_dims[m_listRank[m_rank - 1]] ; row++) {
         for (int col = 0 ; col < m_dims[m_listRank[m_rank - 2]] ; col++) {
            o = (double) orig[row * m_dims[m_listRank[m_rank - 2]] + col];
            o = (o / 4095.0) * 255.0;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 0] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 1] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 2] = (int) o;
            m_bufferRGB[(row * m_dims[m_listRank[m_rank - 2]] * 4) +
                        (col * 4) + 3] = 0;
         }
      }
   }
   break;

   default: {

   }
   break;
   };


   // Create image from buffer
   if (m_bufferRGB != NULL) {
      if (m_listRank[m_listRank.size() - 1] <
          m_listRank[m_listRank.size() - 2]) {
         QImage img((uchar*)m_bufferRGB,
               m_dims[m_listRank[m_rank - 2]],
               m_dims[m_listRank[m_rank - 1]],
               QImage::Format_RGB32);
         m_scene -> setPixmap(QPixmap::fromImage(img));
      }
      else {
         QImage img((uchar*)m_bufferRGB,
               m_dims[m_listRank[m_rank - 1]],
               m_dims[m_listRank[m_rank - 2]],
               QImage::Format_RGB32);
         m_scene -> setPixmap(QPixmap::fromImage(img.mirrored(true, false)));
      }
   }

   QApplication::restoreOverrideCursor();

}

/*---------------------------------------------------------------------------*/

void ImageView::updateCombo(int id, int oldI, int newI)
{

   // Ignore nested updates
   if (m_ignore == true) {
      return;
   }

   // Find existing combo box with the updated value and change it to the
   // updated box's old value.
   for (int j = 0 ; j < m_listCombo.size() ; j++) {
      if (j != id) {
         if (m_listCombo[j] -> currentIndex() == newI) {
            m_ignore = true;
            m_listCombo[j] -> setCurrentIndex(oldI);
            m_ignore = false;
            break;
         }
      }
   }

   // Update dimension list
   for (int i = 0 ; i < m_listCombo.size() ; i++) {
      m_listRank[i] = m_listCombo[i] -> currentIndex();
   }

   if (m_bufferRGB != NULL) {
      delete [] m_bufferRGB;
      m_bufferRGB = NULL;
   }

   if (m_rank == 1) {
      m_bufferRGB = new char[m_dims[0] * 4];
   }
   else {
      m_bufferRGB = new char[m_dims[m_listRank[m_rank - 1]] *
                             m_dims[m_listRank[m_rank - 2]] * 4];
   }

   // Set major order
   if (m_rank >= 2) {
      if (m_listRank[m_listRank.size() - 1] <
          m_listRank[m_listRank.size() - 2]) {
         m_scene -> setRowMajor();
      }
      else {
         m_scene -> setColumnMajor();
      }
   }

   // Now, update the range widgets
   updateRange();

}

/*---------------------------------------------------------------------------*/

void ImageView::updateRange()
{

   // Update range widgets based on rank list
   for (int i = 0 ; i < m_listRange.size() ; i++) {
      m_ignore = true;
      unsigned long ind = m_listRank[i];
      m_listRange[i] -> setId(ind);
      m_listRange[i] -> setMaximum(m_dims[ind] - 1);
      m_listRange[i] -> setMinimum(0);
      m_ignore = false;
   }

   // Update selection and display
   updateSelection();
   update();

}

/*---------------------------------------------------------------------------*/

void ImageView::updateSelection()
{

   if (m_rank >= 2) {

      for (int i = 0 ; i < m_listRange.size() ; i++) {
         unsigned long d = (unsigned long) m_listCombo[i] -> currentIndex();
         unsigned long long s = m_listRange[i] -> value();

         m_selCur.setStart(s, d);
         m_selCur.setCount(1, d);
      }

      unsigned long d =
        (unsigned long) m_listCombo[m_rank - 2] -> currentIndex();
      unsigned long long c = m_dims[d];

      m_selCur.setStart((unsigned long long) 0, d);
      m_selCur.setCount(c, d);

      d = (unsigned long) m_listCombo[m_rank - 1] -> currentIndex();
      c = m_dims[d];

      m_selCur.setStart((unsigned long long) 0, d);
      m_selCur.setCount(c, d);

   }

}

/*---------------------------------------------------------------------------*/

void ImageView::zoomIn()
{

   // Zoom in
   m_view -> scale(1.25, 1.25);

   // Force update scroll bars
   m_view -> setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   m_view -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

}

/*---------------------------------------------------------------------------*/

void ImageView::zoomOut()
{

   // Zoom out
   m_view -> scale(0.75, 0.75);

   // Force update scroll bars
   m_view -> setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   m_view -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

}

/*---------------------------------------------------------------------------*/
