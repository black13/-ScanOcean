/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef DISPLAY_STAGE_H
#define DISPLAY_STAGE_H

/*---------------------------------------------------------------------------*/

#include <QImage>
#include <QObject>

#include <Array.h>
#include <FinalStage.h>

/*---------------------------------------------------------------------------*/

class DisplayStage
: public QObject, public FinalStage
{

   Q_OBJECT

public:

   /**
    * Constructor.
    */
   DisplayStage();

   /**
    * Destructor.
    */
   ~DisplayStage();

   /**
    * Get current image
    *
    * @return the current image
    */
   QImage& getImage();

signals:

   /**
    * Signal that a new frame is available
    *
    * @param inputData - image information including raw data and metadata.
    */
   void newFrame(const gstar::Array* inputData);

protected:

   /**
    * Send image to the GUI
    *
    * @param input - the image to send to the GUI
    */
   void process(gstar::Array& input);

private:

   /**
    * Current image
    */
   QImage m_img;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
