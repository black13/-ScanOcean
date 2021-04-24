
#include <AbstractColorTransferFunction.h>

AbstractColorTransferFunction::AbstractColorTransferFunction()
{

   m_colorMap = new ColorTransferMapping;

}

AbstractColorTransferFunction::~AbstractColorTransferFunction()
{

   delete m_colorMap;

}


ColorTransferMapping& AbstractColorTransferFunction::getColorMap()
{

   return *m_colorMap;

}
