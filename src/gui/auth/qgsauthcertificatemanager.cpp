/***************************************************************************
    qgsauthcertificatemanager.cpp
    ---------------------
    begin                : September, 2015
    copyright            : (C) 2015 by Boundless Spatial, Inc. USA
    author               : Larry Shaffer
    email                : lshaffer at boundlessgeo dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgsauthcertificatemanager.h"
#include "qgssettings.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>

QgsAuthCertEditors::QgsAuthCertEditors( QWidget *parent )
  : QWidget( parent )
{
  setupUi( this );
  const QgsSettings settings;
  tabWidget->setCurrentIndex( ::settingsAuthCertEditorsSelectedTab.value() );
}

QgsAuthCertEditors::~QgsAuthCertEditors()
{
  QgsSettings settings;
  ::settingsAuthCertEditorsSelectedTab.setValue( tabWidget->currentIndex() );
}


QgsAuthCertManager::QgsAuthCertManager( QWidget *parent )
  : QDialog( parent )
{
  setWindowTitle( tr( "Certificate Manager" ) );
  QVBoxLayout *layout = new QVBoxLayout( this );
  layout->setContentsMargins( 6, 6, 6, 6 );

  mCertEditors = new QgsAuthCertEditors( this );
  layout->addWidget( mCertEditors );

  QDialogButtonBox *buttonBox = new QDialogButtonBox( QDialogButtonBox::Close,
      Qt::Horizontal, this );
  buttonBox->button( QDialogButtonBox::Close )->setDefault( true );
  connect( buttonBox, &QDialogButtonBox::rejected, this, &QWidget::close );
  layout->addWidget( buttonBox );

  setLayout( layout );
}
