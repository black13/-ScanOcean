/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <ColorListComboBoxDelegate.h>

/*---------------------------------------------------------------------------*/

ColorListComboBoxDelegate::ColorListComboBoxDelegate(QObject* parent)
: QItemDelegate(parent)
{

}

/*---------------------------------------------------------------------------*/

QWidget* ColorListComboBoxDelegate::createEditor(
   QWidget* parent,
   const QStyleOptionViewItem& option,
   const QModelIndex& index) const
{

   // Create new ColorListComboBox
   ColorListComboBox* colorList = new ColorListComboBox(parent);

   // Return combo box
   return colorList;

}

/*---------------------------------------------------------------------------*/

void ColorListComboBoxDelegate::paint(QPainter* painter,
                                      const QStyleOptionViewItem& option,
                                      const QModelIndex& index) const
{

   // Create rectangle for color
   QRect colorRect;
   colorRect.setX(option.rect.x() + 4);
   colorRect.setY(option.rect.y() + 4);
   colorRect.setWidth(option.rect.width() - 8);
   colorRect.setHeight(option.rect.height() - 8);

   // Get color from model
   QColor color = (index.model() -> data(
      index, Qt::DisplayRole)).value<QColor>();

   // Selected and Active
   if ((option.state & QStyle::State_Selected) &&
       (option.state & QStyle::State_Active)) {
      painter -> fillRect(option.rect, option.palette.highlight());
      painter -> fillRect(colorRect, color);
   }

   // Selected but not Active
   else if (option.state & QStyle::State_Selected) {
      QPalette p = option.palette;
      painter -> fillRect(option.rect,
                          p.color(QPalette::Inactive, QPalette::Background));
      painter -> fillRect(colorRect, color);
   }

   // Not selected
   else {
      painter -> fillRect(option.rect, option.palette.base());
      painter -> fillRect(colorRect, color);
   }

}

/*---------------------------------------------------------------------------*/

void ColorListComboBoxDelegate::setEditorData(QWidget* editor,
                                              const QModelIndex& index) const
{

   // Get color value from model
   QColor value =
      (index.model() -> data(index, Qt::EditRole)).value<QColor>();

   // Cast combo box editor
   ColorListComboBox* box = static_cast<ColorListComboBox*>(editor);

   // Set color value in box
   box -> setColor(value);

}

/*---------------------------------------------------------------------------*/

void ColorListComboBoxDelegate::setModelData(QWidget* editor,
                                             QAbstractItemModel* model,
                                             const QModelIndex& index) const
{

   // Case combo box editor
   ColorListComboBox* box = static_cast<ColorListComboBox*>(editor);

   // Get color
   QColor color = box -> color();

   // Get name
   QString name = box -> name();

   // Update model
   model -> setData(index, color, Qt::EditRole);
   model -> setData(index, name, Qt::DisplayRole);

}

/*---------------------------------------------------------------------------*/

void ColorListComboBoxDelegate::updateEditorGeometry(
   QWidget* editor,
   const QStyleOptionViewItem& option,
   const QModelIndex& index) const
{

   // Set combo box geometry
   editor -> setGeometry(option.rect);

}

/*---------------------------------------------------------------------------*/
