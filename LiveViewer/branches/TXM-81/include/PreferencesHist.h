/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef PREFERENCES_HIST_H
#define PREFERENCES_HIST_H

/*---------------------------------------------------------------------------*/

#include <QLabel>
#include <QLineEdit>
#include <QWidget>

class QDoubleSpinBox;
class QRadioButton;

/*---------------------------------------------------------------------------*/

/**
 * @brief Preferences dialog page for configuring histogram plots.
 */
class PreferencesHist
: public QWidget
{

   Q_OBJECT

public:

   /**
    * Constructor
    *
    * @param parent - the Qt parent widget
    */
   PreferencesHist(QWidget* parent = 0);

   /**
    * Default destructor
    */
   ~PreferencesHist();

   /**
    * Process changes when the parent dialog calls its accept() method.
    */
   void acceptChanges();

   /**
    * Set Histogram bins
    *
    * @param uri - set histogram bins
    */
   void setHistBins(double bins);

   void setHistType(int type);

   /**
    * Get Histogram bins
    *
    * @return number of bins specified by the user
    */
   double getHistBins();

   int getHistType();

private:

   QDoubleSpinBox* m_histBins;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
