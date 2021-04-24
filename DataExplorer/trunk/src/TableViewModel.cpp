/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <TableViewModel.h>

using boost::shared_array;
using boost::shared_ptr;

/*---------------------------------------------------------------------------*/

TableViewModel::TableViewModel(QObject* parent)
: QAbstractTableModel(parent)
{

   m_displayDims[0] = 0;
   m_displayDims[1] = 0;
   m_isColumnMajor = false;
   m_validFlag = false;

}

/*---------------------------------------------------------------------------*/

TableViewModel::~TableViewModel()
{

}

/*---------------------------------------------------------------------------*/

int TableViewModel::columnCount(const QModelIndex& parent) const
{

   Q_UNUSED(parent)

   return m_displayDims[1];

}

/*---------------------------------------------------------------------------*/

QVariant TableViewModel::data(const QModelIndex& index, int role) const
{

   if (!m_validFlag) return QVariant();

   // Check for a valid index
   if (!index.isValid())
      return QVariant();

   // Return an empty QVariant for other roles
   if (role != Qt::DisplayRole)
      return QVariant();

   // Get desired index
   int c = index.column();
   int r = index.row();

   // Calculate index based on major order
   int ind = 0;
   if (m_isColumnMajor == true) {
      ind = (c * m_displayDims[0]) + r;
   }
   else {
      ind = (r * m_displayDims[1]) + c;
   }

   // Get data and cast for type
   switch (m_type) {
   case dstar::Char: {
      return ((char*) m_data.get())[ind];
   }
   break;
   case dstar::ShortChar: {
      return ((char*) m_data.get())[ind];
   }
   break;
   case dstar::UnsignedChar: {
      return ((unsigned char*) m_data.get())[ind];
   }
   break;
   case dstar::Short: {
      return QString::number(((short*) m_data.get())[ind]);
   }
   break;
   case dstar::UnsignedShort: {
      return QString::number(((unsigned short*) m_data.get())[ind]);
   }
   break;
   case dstar::Int: {
      return QString::number(((int*) m_data.get())[ind]);
   }
   break;
   case dstar::UnsignedInt: {
      return QString::number(((unsigned int*) m_data.get())[ind]);
   }
   break;
   case dstar::Long: {
      return QString::number(((long*) m_data.get())[ind]);
   }
   break;
   case dstar::UnsignedLong: {
      return QString::number(((unsigned long*) m_data.get())[ind]);
   }
   break;
   case dstar::LongLong: {
      return QString::number(((long long*) m_data.get())[ind]);
   }
   break;
   case dstar::UnsignedLongLong: {
      return QString::number(((unsigned long long*) m_data.get())[ind]);
   }
   break;
   case dstar::Float: {
      return QString::number(((float*) m_data.get())[ind], 'f', 6 );
   }
   break;
   case dstar::Double: {
      return QString::number(((double*) m_data.get())[ind], 'f', 6 );
   }
   break;
   case dstar::LongDouble: {
      return QString::number(((double*) m_data.get())[ind]);
   }
   break;
   case dstar::String: {
      return QString((char*) m_data.get());
   }
   break;
   default: {

   }
   break;
   };

   return tr("Unknown Data Type");

}

/*---------------------------------------------------------------------------*/

Qt::ItemFlags TableViewModel::flags(const QModelIndex& index) const
{

   // Check for valid index
   if (!index.isValid())
      return 0;

   // Return appropriate flags
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

}

/*---------------------------------------------------------------------------*/

QVariant TableViewModel::headerData(int section,
                                    Qt::Orientation orientation,
                                    int role) const
{

   // Check this is DisplayRole
   if (role != Qt::DisplayRole)
      return QVariant();

   // Headers
   return QString::number(section);

}

/*---------------------------------------------------------------------------*/

int TableViewModel::rowCount(const QModelIndex& parent) const
{

   Q_UNUSED(parent)

   return m_displayDims[0];

}

/*---------------------------------------------------------------------------*/

void TableViewModel::setColumnMajor()
{

   m_isColumnMajor = true;

}

/*---------------------------------------------------------------------------*/

void TableViewModel::setData(shared_array<char> arr, dstar::DataType type)
{

   m_type = type;
   m_data = arr;

   QModelIndex start = createIndex(0, 0);
   QModelIndex end = createIndex(m_displayDims[0] - 1, m_displayDims[1] - 1);

   m_validFlag = true;

   emit dataChanged(start, end);

}

/*---------------------------------------------------------------------------*/

void TableViewModel::setDisplayDimensions(int v, int h)
{

   m_displayDims[0] = v;
   m_displayDims[1] = h;

   emit reset();

}

/*---------------------------------------------------------------------------*/

void TableViewModel::setRowMajor()
{

   m_isColumnMajor = false;

}

/*---------------------------------------------------------------------------*/
