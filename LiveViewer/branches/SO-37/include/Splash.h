/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SPLASH_H
#define SPLASH_H

/*---------------------------------------------------------------------------*/

#include <QCoreApplication>
#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

/*---------------------------------------------------------------------------*/

/**
 * @brief Splash screen and About dialog
 */
class Splash
: public QDialog
{

   Q_OBJECT

public:

   /**
    * Constructor
    *
    * @param parent - the Qt parent widget
    * @param f - Qt window flags
    * @param aboutMode - true if it's to function as an about dialog, false
    *                    for a splash screen
    */
   Splash(QWidget* parent = 0,
          Qt::WindowFlags f = Qt::Popup,
          bool aboutMode = false);

   /**
    * Append a message to the splash screen message box
    */
   void appendMessage(QString msg);

   /**
    * Clear all messages in splash screen message box
    */
   void clear();

private:

   /**
    * Message / status box
    */
   QTextEdit* m_status;

   /**
    * About mode flag
    */
   bool m_aboutMode;

   /**
    * OK button for about mode
    */
   QPushButton* m_btnOK;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
