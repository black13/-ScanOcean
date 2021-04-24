
#ifndef COLORTRANSFERFUNCTION_H_
#define COLORTRANSFERFUNCTION_H_

#include <ColorTransferMapping.h>

/**
 * Abstract interface for a ColorTransferFunction. Implementations can vary:
 *
 * e.g.
 * 1) Linear interpolation (e.g. LIColorTransferFunction)
 * 2) Spline interpolation
 * 3) etc.
 */
class AbstractColorTransferFunction
{

public:
   /**
    * Constructor
    */
   AbstractColorTransferFunction();

   /**
    * Destructor
    */
   virtual ~AbstractColorTransferFunction();

   /**
    * Get the color transfer mapping
    */
   ColorTransferMapping& getColorMap();

protected:

   /**
    * Color transfer mapping
    */
   ColorTransferMapping* m_colorMap;

};


#endif
