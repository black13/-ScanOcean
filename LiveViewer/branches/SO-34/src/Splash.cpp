/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <Splash.h>

/*---------------------------------------------------------------------------*/

Splash::Splash(QWidget* parent, Qt::WindowFlags f, bool aboutMode)
: QDialog(parent, f), m_aboutMode(aboutMode)
{

   // Background color
   QPalette pal = this -> palette();
   pal.setColor(this -> backgroundRole(), Qt::white);
   this -> setPalette(pal);

   // Autofill background
   setAutoFillBackground(true);

   // Make label for pixmap
   //QLabel* lblPix = new QLabel();
   //lblPix -> setPixmap(icon);

   // Make label for name
   QFont font;
   font.setPointSize(22);
   QLabel* lblName = new QLabel();
   lblName -> setText(tr("TomoUI"));
   lblName -> setFont(font);

   // Make label for date
   QLabel* lblDate = new QLabel();
   lblDate -> setText(QString::fromLocal8Bit(__DATE__));

   // Status
   m_status = new QTextEdit;
   m_status -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   m_status -> setReadOnly(true);

   // Set fixed size
   setFixedSize(320, 240);

   // Text layout
   QVBoxLayout* txtlayout = new QVBoxLayout();
   txtlayout -> setSpacing(0);
   txtlayout -> setContentsMargins(0, 0, 0, 4);
   txtlayout -> setAlignment(Qt::AlignTop);
   txtlayout -> addWidget(lblName);
   txtlayout -> addWidget(lblDate);

   // Layout
   QVBoxLayout* layout = new QVBoxLayout();
   layout -> setAlignment(Qt::AlignTop);
   //layout -> addWidget(lblPix);
   layout -> addLayout(txtlayout);
   layout -> addWidget(m_status);

   // OK button
   m_btnOK = NULL;
   if (m_aboutMode == true) {

      // Create button
      m_btnOK = new QPushButton(tr("OK"));
      connect(m_btnOK, SIGNAL(clicked()),
              this, SLOT(hide()));

      // Add to layout
      layout -> addWidget(m_btnOK);

   }

   // Set main layout
   setLayout(layout);

}

/*---------------------------------------------------------------------------*/

void Splash::appendMessage(QString msg)
{

   // Append message
   m_status -> append(msg);

   // Scroll to top
   if (m_aboutMode) {
      m_status -> moveCursor(QTextCursor::Start);
   }

   // Repaint
   repaint();

}

/*---------------------------------------------------------------------------*/

void Splash::clear()
{

   // Clear messages
   m_status -> clear();
   repaint();

}

/*---------------------------------------------------------------------------*/
