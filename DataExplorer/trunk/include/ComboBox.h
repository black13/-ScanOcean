/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef COMBO_BOX_H
#define COMBO_BOX_H

/*---------------------------------------------------------------------------*/

#include <QComboBox>

/*---------------------------------------------------------------------------*/

/**
 * @brief The ComboBox class is an extension of QComboBox that emits
 * signals with the old and new values when updated.
 */
class ComboBox
: public QComboBox
{
   Q_OBJECT

public:

   /**
    * Constructor.
    *
    * @param did an arbitrary id value associated with this widget.
    * @param parent the Qt parent widget.
    */
   ComboBox(int did = 0, QWidget* parent = 0);

private slots:

   /**
    * Handle change in the current selected index.
    *
    * @param index
    */
   void indexChangedSlot(int index);

   /**
    * Handle change in the current selected text.
    *
    * @param newText
    */
   void textChangedSlot(const QString& newText);

signals:

   /**
    * This signal is emitted when the selection (index) is changed.
    *
    * @param id internal object id.
    * @param oldIndex the previously selected index.
    * @param newIndex the currently selected index.
    */
   void indexChanged(int id, int oldIndex, int newIndex);

   /**
    * This signal is emitted when the selection is changed.
    *
    * @param id internal object id.
    * @param oldText the previously selected text.
    * @param newText the currently selected text.
    */
   void textChanged(int id, const QString& oldText, const QString& newText);

private:

   /**
    * Internal arbitrary id associated with this object.
    */
   int m_did;

   /**
    * The old index.
    */
   int m_oldIndex;

   /**
    * The old string.
    */
   QString m_oldText;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
