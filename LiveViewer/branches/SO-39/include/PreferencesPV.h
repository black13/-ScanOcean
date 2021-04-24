/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef PREFERENCES_PV_H
#define PREFERENCES_PV_H

/*---------------------------------------------------------------------------*/

#include <QLabel>
#include <QLineEdit>
#include <QWidget>

/*---------------------------------------------------------------------------*/

/**
 * @brief Preferences dialog page for process variable prefix settings
 */
class PreferencesPV
: public QWidget
{

   Q_OBJECT

public:

   /**
    * Constructor
    *
    * @param parent - the Qt parent widget
    */
   PreferencesPV(QWidget* parent = 0);

   /**
    * Default destructor
    */
   ~PreferencesPV();

   /**
    * Process changes when the parent dialog calls its accept() method.
    */
   void acceptChanges();

   /**
    * Get PV prefix
    *
    * @return prefix of PV
    */
   QString getPVPrefix();

   /**
    * Set PV prefix
    *
    * @param uri - set prefix of PV
    */
   void setPVPrefix(QString uri);

private:

   /**
    * Text edit box for prefix of PV
    */
   QLineEdit* m_editPVPrefix;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
