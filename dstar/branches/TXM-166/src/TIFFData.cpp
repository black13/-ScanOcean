/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <TIFFData.h>

using namespace dstar;
using boost::shared_array;
using boost::shared_ptr;
using boost::weak_ptr;
using std::list;
using std::pair;
using std::string;
using std::vector;

/*---------------------------------------------------------------------------*/

TIFFData::TIFFData(std::string filepath)
: TIFFObject(), AbstractData()
{

   m_tiffFile = shared_ptr<dstar::TIFFFile>(new TIFFFile());
   m_tiffFile->Read(filepath);

   m_img = m_tiffFile->getTIFFImageHandler();
   m_rank = 0;


   initializeTIFFAttribute();

   //getData();

   std::cerr << "Here is the dstar Failed 4" << std::endl;


   m_type = dstar::Short;
   //m_dataSpaceId = -1;
   m_bytesPerElement = 0;

}

/*---------------------------------------------------------------------------*/

TIFFData::~TIFFData()
{

}

/*---------------------------------------------------------------------------*/

void TIFFData::attachScale(unsigned long dim, shared_ptr<AbstractData> obj)
{

}

/*---------------------------------------------------------------------------*/

void TIFFData::getDims(unsigned long long* dims, unsigned long sz) const
{

   for (unsigned int d = 0 ; (d < m_rank) && (d < sz) ; d++) {
      dims[d] = (unsigned long long) m_dataDims[d];
   }

}

/*---------------------------------------------------------------------------*/

unsigned long long TIFFData::getNumberOfBytesInSelection() const
{

   return m_bytesPerElement * m_selection.getNumberOfElements();

}

/*---------------------------------------------------------------------------*/

unsigned long TIFFData::getNumberOfBytesPerElement() const
{

   return m_bytesPerElement;

}

/*---------------------------------------------------------------------------*/

unsigned long TIFFData::getRank() const
{

   return m_rank;

}

/*---------------------------------------------------------------------------*/

std::vector<std::pair<std::string, std::string> >
TIFFData::getProperties() const
{

}


/*---------------------------------------------------------------------------*/
list<list<pair<string, shared_ptr<const AbstractData> > > >
TIFFData::getScaleList() const
{

   //return vector<shared_ptr<const AbstractAttribute> >(m_attributes.begin(),
//      m_attributes.end());

   // Fix this
   //return m_scales;

}

/*---------------------------------------------------------------------------*/

Selection TIFFData::getSelection() const
{

   return m_selection;

}

/*---------------------------------------------------------------------------*/

DataType TIFFData::getType() const
{

   return m_type;

}

/*---------------------------------------------------------------------------*/

void TIFFData::removeScale(unsigned long dim, shared_ptr<AbstractData> obj)
{

   // Dimension is not valid
   if (dim >= m_scales.size()) {
      return;
   }

   // Get list for specified dimension
   list<list<pair<string, weak_ptr<AbstractData> > > >::iterator i;
   i = m_scales.begin();
   std::advance(i, dim);

   // Search through dimension for item and erase it
   list<pair<string, weak_ptr<AbstractData> > >::iterator j;
   for (j = i -> begin() ; j != i -> end() ; j++) {
      if ((j -> second).lock() == obj) {
         i -> erase(j);
         return;
      }
   }

}

/*---------------------------------------------------------------------------*/

void TIFFData::setDims(unsigned long long* dims, unsigned long sz) const
{

   for (unsigned int d = 0 ; (d < m_rank) && (d < sz) ; d++) {
      m_dataDims[d] = dims[d];
   }

}

/*---------------------------------------------------------------------------*/

void TIFFData::setRank(unsigned long rank)
{

   m_rank = rank;
   m_selection.setRank(m_rank);

   m_dataDims.resize(m_rank, 0);

}

/*---------------------------------------------------------------------------*/

void TIFFData::setSelection(Selection selection)
{

   // Validate rank
   if (selection.getRank() != m_rank) {
      throw std::out_of_range("Rank does not match. " + m_name);
      return;
   }

   // Update selection
   m_selection = selection;

}

/*---------------------------------------------------------------------------*/

void TIFFData::setType(DataType type)
{

   m_type = type;

}

/*---------------------------------------------------------------------------*/
void TIFFData::initializeTIFFAttribute()
{
    bitsPerPixel = 0;  // Bits per pixel
    fill = 0;          // Fill order
   imageWidth = 0;    // Image width in pixels
   imageHeight = 0;   // Image height in rows

   numStrips = 0;     // Number of strips

   scanlineSize = 0;  // Scan line size in bytes
   stripSize = 0;     // Strip size

   // Get image properties
   TIFFGetField(m_img, TIFFTAG_BITSPERSAMPLE, &bitsPerPixel);
   TIFFGetField(m_img, TIFFTAG_FILLORDER, &fill);
   TIFFGetField(m_img, TIFFTAG_IMAGEWIDTH, &imageWidth);
   TIFFGetField(m_img, TIFFTAG_IMAGELENGTH, &imageHeight);
   numStrips = TIFFNumberOfStrips(m_img);
   scanlineSize = TIFFScanlineSize(m_img);
   stripSize = TIFFStripSize(m_img);

   uint32 rank = 3; // For tiff is 3

   // Initial is the rank 3
   setRank(rank);

   m_dataDims[0] = 1;
   m_dataDims[1] = imageWidth;
   m_dataDims[2] = imageHeight;

   m_selection.setRank(rank);

   //m_selection.setDims(dims, rank);// ? selection to initialize

}
shared_array<char> TIFFData::getData() const
{


   uint32 result = 0;        // Number of bytes read
   uint32 imgOffset = 0;     // Offset for reading strips

   buffer = shared_array<char>(new char[numStrips * stripSize]);
   m_buffer = buffer.get();

   // Read each strip into image buffer
   for (int strip = 0 ; strip < numStrips ; strip++) {

      // Read strip
      result =
         TIFFReadEncodedStrip(m_img, strip, m_buffer + imgOffset, stripSize);

      if (result == -1) {
         std::cerr << "Read error on input strip number " << strip << std::endl;
      }

      // Increment location in destination buffer
      imgOffset += result;

   }

   return buffer;

}

/*---------------------------------------------------------------------------*/

