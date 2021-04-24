/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef COLOR_LIST_COMBO_BOX_DELEGATE_H
#define COLOR_LIST_COMBO_BOX_DELEGATE_H

/*---------------------------------------------------------------------------*/

#include <ColorListComboBox.h>

#include <QItemDelegate>
#include <QPainter>

/*---------------------------------------------------------------------------*/

class ColorListComboBoxDelegate
: public QItemDelegate
{

   Q_OBJECT

public:

   /**
    * Constructor
    *
    * @param parent - the Qt parent widget
    */
   ColorListComboBoxDelegate(QObject* parent = 0);

   /**
    * Reimplemented createEditor() method. See Qt's
    * QItemDelegate documentation.
    */
   QWidget* createEditor(QWidget* parent,
                         const QStyleOptionViewItem& option,
                         const QModelIndex& index) const;

   /**
    * Reimplemented paint() method. See Qt's QItemDelegate documentation.
    */
   void paint(QPainter* painter,
              const QStyleOptionViewItem& option,
              const QModelIndex& index) const;

   /**
    * Reimplemented setEditorData() method. See Qt's
    * QItemDelegate documentation.
    */
   void setEditorData(QWidget* editor, const QModelIndex& index) const;

   /**
    * Reimplemented setModelData() method. See Qt's
    * QItemDelegate documentation.
    */
   void setModelData(QWidget* editor,
                     QAbstractItemModel* model,
                     const QModelIndex& index) const;

   /**
    * Reimplemented updateEditorGeometry() method. See Qt's
    * QItemDelegate documentation.
    */
   void updateEditorGeometry(QWidget* editor,
                             const QStyleOptionViewItem& option,
                             const QModelIndex& index) const;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
