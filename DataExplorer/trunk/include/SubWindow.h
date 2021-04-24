/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SUB_WINDOW_H
#define SUB_WINDOW_H

/*---------------------------------------------------------------------------*/

#include <QMdiSubWindow>

/*---------------------------------------------------------------------------*/

/**
 * @brief The SubWindow class provides a QMdiSubWindow that emits a signal
 * when it's closed.
 *
 * SubWindow is derived from QMdiSubWindow.
 */
class SubWindow
: public QMdiSubWindow
  {

   Q_OBJECT

public:

   /**
    * Constructor - See QMdiSubWindow for more information.
    *
    * @param parent the parent widget.
    * @param flags window flags.
    */
   SubWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

   /**
    * Destructor
    */
   ~SubWindow();

protected:

   /**
    * Overridden closeEvent() from QMdiSubWindow
    *
    * @param closeEvent the QCloseEvent from Qt.
    */
   virtual void closeEvent(QCloseEvent* closeEvent);

signals:

   /**
    * Window is closing signal. Emitted from within overridden closeEvent().
    *
    * @param subWin pointer to the SubWindow that is closing.
    */
   void windowClosing(SubWindow* subwin);

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
