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

   m_type = dstar::UnsignedShort;

   m_bytesPerElement = 0;

   // Read in the TIFF attribute and initialize them.
   initializeTIFFAttribute();

}

/*---------------------------------------------------------------------------*/

TIFFData::~TIFFData()
{
   //_TIFFfree(raster);

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

   const std::vector<std::pair<std::string, std::string> > retVal;
   return retVal;

}

/*---------------------------------------------------------------------------*/

list<list<pair<string, shared_ptr<const AbstractData> > > >
TIFFData::getScaleList() const
{

   const list<list<pair<string, shared_ptr<const AbstractData> > > > retVal;
   return retVal;

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

   // Set the dim number to the TIFF data attribute
   for (unsigned int d = 0 ; (d < m_rank) && (d < sz) ; d++) {
      m_dataDims[d] = dims[d];
   }

}

/*---------------------------------------------------------------------------*/

void TIFFData::setRank(unsigned long rank)
{
   // Set the new rank
   m_rank = rank;

   // Set the selection rank
   m_selection.setRank(m_rank);

   // Resize the data dims for different rank size
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

   m_bitsPerPixel = 0;  // Bits per pixel
   m_fill = 0;          // Fill order
   m_imageWidth = 0;    // Image width in pixels
   m_imageHeight = 0;   // Image height in rows
   m_numStrips = 0;     // Number of strips
   m_scanlineSize = 0;  // Scan line size in bytes
   m_stripSize = 0;     // Strip size
   m_tileWidth = 0;
   m_photometric = 0;

   // Get image properties
   TIFFGetField(m_img, TIFFTAG_BITSPERSAMPLE, &m_bitsPerPixel);
   TIFFGetField(m_img, TIFFTAG_FILLORDER, &m_fill);
   TIFFGetField(m_img, TIFFTAG_IMAGEWIDTH, &m_imageWidth);
   TIFFGetField(m_img, TIFFTAG_IMAGELENGTH, &m_imageHeight);
   TIFFGetField(m_img, TIFFTAG_TILELENGTH, &m_tileWidth);
   TIFFGetField(m_img, TIFFTAG_PHOTOMETRIC, &m_photometric);
   TIFFGetField(m_img, TIFFTAG_SAMPLESPERPIXEL, &m_samplesPerPixel);
   TIFFGetField(m_img, TIFFTAG_ORIENTATION, &m_orientation);
   
   switch(m_photometric)
   {
      case PHOTOMETRIC_MINISWHITE:
      case PHOTOMETRIC_MINISBLACK:
         m_type = dstar::UnsignedShort;
         std::cerr<<"DSTAR:: white black"<<std::endl;
         break;
      case PHOTOMETRIC_RGB:
         m_type = dstar::UnsignedInt;
         std::cerr<<"DSTAR:: photometric_RGB"<<std::endl;
         break;
      default:
         std::cerr<<"DSTAR:: Defualt"<<std::endl;
         m_type = dstar::UnsignedShort;
         break;
   }

   m_numStrips = TIFFNumberOfStrips(m_img);
   m_scanlineSize = TIFFScanlineSize(m_img);
   m_stripSize = TIFFStripSize(m_img);

   const uint32 rank = 3; // For tiff  the rank is 3

   unsigned long long  dims [rank];

   // Initial is the rank 3
   setRank(rank);

   dims[0] = 1;
   dims[1] = m_imageHeight;
   dims[2] = m_imageWidth;

   setDims(dims, rank);

   m_selection.setRank(rank);

   m_selection.setDims(dims, rank);//  selection to initialize

}

/*---------------------------------------------------------------------------*/

shared_array<char> TIFFData::getData() const
{

   if(m_photometric == PHOTOMETRIC_RGB)
   {
      return getRGBData();
   }
   return getEncodedData();

}

/*---------------------------------------------------------------------------*/

shared_array<char> TIFFData::getEncodedData() const
{

   uint32 result = 0;        // Number of bytes read
   uint32 imgOffset = 0;     // Offset for reading strips

   m_shBuffer = shared_array<char>(new char[m_numStrips * m_stripSize]);


   m_buffer = m_shBuffer.get();

   // Read each strip into image buffer
   for (unsigned int strip = 0 ; strip < m_numStrips ; strip++) {
      // Read strip
      result =
         TIFFReadEncodedStrip(m_img, strip, m_buffer + imgOffset, m_stripSize);

      if (result == -1) 
      {
         std::cerr << "Read error on input strip number " << strip << std::endl;
      }

      // Increment location in destination buffer
      imgOffset += result;
   }

   return m_shBuffer;

}

/*---------------------------------------------------------------------------*/

shared_array<char> TIFFData::getRGBData() const
{

   m_shBuffer = shared_array<char>(new char[m_imageWidth * m_imageHeight * sizeof(uint32)]);

   m_buffer = m_shBuffer.get();

   if(TIFFReadRGBAImageOriented(m_img, m_imageWidth, m_imageHeight, (uint32*)m_buffer, m_orientation, 0) != 1)
   {
      std::cerr << "Error for TIFFData::getRGBData::TIFFReadRGBAImageOriented() " << std::endl;
   }
   

   return m_shBuffer;

}

/*---------------------------------------------------------------------------*/

uint32 TIFFData::getTileWidth()
{
   return m_tileWidth;
}

/*---------------------------------------------------------------------------*/

uint32 TIFFData::getBitsPerPixel()
{
   return m_bitsPerPixel;
}

/*---------------------------------------------------------------------------*/
