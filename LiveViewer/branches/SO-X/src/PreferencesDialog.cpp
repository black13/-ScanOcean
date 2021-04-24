/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <PreferencesDialog.h>

/*---------------------------------------------------------------------------*/

PreferencesDialog::PreferencesDialog(QWidget* parent, Qt::WindowFlags f)
   : QDialog(parent, f)
{

   // Create contents list
   m_contentsWidget = new QListWidget;
   m_contentsWidget -> setViewMode(QListView::ListMode);
   m_contentsWidget -> setMaximumWidth(200);
   m_contentsWidget -> setCurrentRow(0);

   // Create content items
   QListWidgetItem* pvButton = new QListWidgetItem(m_contentsWidget);
   pvButton -> setText(tr("Area Detector PV"));
   pvButton -> setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
   //QListWidgetItem* roiButton = new QListWidgetItem(m_contentsWidget);
   //roiButton -> setText(tr("ROI-PVs"));
   //roiButton -> setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


   // Create preference pages
   m_pagesWidget = new QStackedWidget;
   m_pvPage = new PreferencesPV();
   //m_roiPage = new PreferencesROI();
   m_pagesWidget -> addWidget(m_pvPage);
   //m_pagesWidget -> addWidget(m_roiPage);

   // Configuration layout
   QHBoxLayout* configLayout = new QHBoxLayout;
   configLayout -> addWidget(m_contentsWidget);
   configLayout -> addWidget(m_pagesWidget, 1);

   // Dialog buttons
   m_btnOK = new QPushButton(tr("OK"));
   m_btnCancel = new QPushButton(tr("Cancel"));

   // Button layout
   QHBoxLayout* btnLayout = new QHBoxLayout();
   btnLayout -> setContentsMargins(0, 0, 0, 0);
   btnLayout -> addStretch();
   btnLayout -> addWidget(m_btnOK);
   btnLayout -> addWidget(m_btnCancel);

   // Connect button signals/slots
   connect(m_btnOK, SIGNAL(clicked()), this, SLOT(accept()));
   connect(m_btnCancel, SIGNAL(clicked()), this, SLOT(reject()));

   // Main layout
   m_layout = new QVBoxLayout;
   m_layout -> addLayout(configLayout);
   m_layout -> addStretch(1);
   m_layout -> addSpacing(12);
   m_layout -> addLayout(btnLayout);
   setLayout(m_layout);

   // Set dialog title
   setWindowTitle(tr("Preferences"));

   // Change page signal/slot
   connect(m_contentsWidget,
           SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
           this,
           SLOT(changePage(QListWidgetItem*, QListWidgetItem*)));

   // Fix dialog size
   layout() -> setSizeConstraint(QLayout::SetFixedSize);

}

/*---------------------------------------------------------------------------*/

void PreferencesDialog::accept()
{

   // Accept changes in settings widget
   if (m_preferences != NULL) {
      m_preferences -> saveValueKey(Preferences::PVPrefixString,
                                    m_pvPage -> getPVPrefix());
      //m_preferences -> saveValueKey(Preferences::ROIPVString,
      //                              m_roiPage -> getROIPVs());
   }

   // Close with accept
   QDialog::accept();

}

/*---------------------------------------------------------------------------*/

void PreferencesDialog::changePage(QListWidgetItem* current,
                                   QListWidgetItem* previous)
{

   if (!current) {
      current = previous;
   }

   // Set visible page
   m_pagesWidget -> setCurrentIndex(m_contentsWidget -> row(current));

}

/*---------------------------------------------------------------------------*/

void PreferencesDialog::reject()
{

   // Close with reject
   QDialog::reject();

}

/*---------------------------------------------------------------------------*/

void PreferencesDialog::setPreferences(Preferences* preferences)
{

   // Assign preferences object
   m_preferences = preferences;

   // Assign preferences to pages
   if (m_preferences != NULL) {
      m_pvPage -> setPVPrefix(preferences -> readValueKey(
         Preferences::PVPrefixString).toString());
      //m_roiPage -> setROIPVs(preferences -> readValueKey(
      //  Preferences::ROIPVString).toList());
   }

}

/*---------------------------------------------------------------------------*/
