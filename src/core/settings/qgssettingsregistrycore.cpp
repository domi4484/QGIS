/***************************************************************************
  qgssettingsregistrycore.cpp
  --------------------------------------
  Date                 : February 2021
  Copyright            : (C) 2021 by Damiano Lombardi
  Email                : damiano at opengis dot ch
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgssettingsregistrycore.h"

#include "qgslayout.h"
#include "qgslocator.h"

QgsSettingsRegistryCore::QgsSettingsRegistryCore()
  : mSettingsEntries()
{
  mSettingsEntries.append( new QgsLayout::Settings::SearchPathForTemplates() );

  mSettingsEntries.append( new QgsLocator::Settings::LocatorFilterEnabled() );
  mSettingsEntries.append( new QgsLocator::Settings::LocatorFilterDefault() );
  mSettingsEntries.append( new QgsLocator::Settings::LocatorFilterPrefix() );
}

QgsSettingsRegistryCore::~QgsSettingsRegistryCore()
{
  qDeleteAll( mSettingsEntries );
}


