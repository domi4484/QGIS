/***************************************************************************
  qgssettingsregistrygui.cpp
  --------------------------------------
  Date                 : July 2021
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

#include "qgssettingsregistrygui.h"

#include "qgsapplication.h"
#include "qgssettingsregistrycore.h"
#include "qgsstylemanagerdialog.h"
#include "qgscompoundcolorwidget.h"
#include "qgserrordialog.h"
#include "qgspointcloudlayersaveasdialog.h"
#include "qgscodeeditor.h"
#include "qgscodeeditorpython.h"
#include "qgsauthcertificatemanager.h"
#include "qgsdualview.h"
#include "qgshighlight.h"
#include "qgsmaptool.h"
#include "qgsmodeldesignerdialog.h"
#include "qgscolorwidgets.h"
#include "qgsmaptoolidentify.h"
#include "qgsmapcanvas.h"

QgsSettingsRegistryGui::QgsSettingsRegistryGui()
  : QgsSettingsRegistry()
{
  addSettingsEntry( &QgsCodeEditor::settingsCodeEditorFontsize );
  addSettingsEntry( &QgsCodeEditorPython::settingsPythonConsoleAutoCompThreshold );
  addSettingsEntry( &QgsModelDesignerDialog::settingsZoomFavor );
  addSettingsEntry( &::settingsAuthCertEditorsSelectedTab );
  addSettingsEntry( &settingsZoomFactor );
  addSettingsEntry( &QgsDualView::settingsAttributeTableRowCache );
  addSettingsEntry( &settingsMessageTimeout );
  addSettingsEntry( &QgsMapCanvas::settingsSegmentationTolerance );
  addSettingsEntry( &QgsHighlight::settingsMapHighlightMinWidth );
  addSettingsEntry( &settingsRespectScreenDPI );
  addSettingsEntry( &QgsHighlight::settingsMapHighlightBuffer );
  addSettingsEntry( &::settingsColorWidgetsTextWidgetFormat );
  addSettingsEntry( &QgsMapTool::settingsMapSearchRadiusMM );
  addSettingsEntry( &settingsAutomaticallyCheckForPluginUpdates );
  addSettingsEntry( &QgsMapToolIdentify::settingsMapIdentifyMode );
  addSettingsEntry( &QgsStyleManagerDialog::settingLastStyleDatabaseFolder );
  addSettingsEntry( &QgsMapCanvas::settingsSegmentationToleranceType );
  addSettingsEntry( &QgsCompoundColorWidget::settingsWindowsColorDialogActiveScheme );
  addSettingsEntry( &settingsPromptForSublayers );
  addSettingsEntry( &QgsErrorDialog::settingsErrorDialogDetail );
  addSettingsEntry( &settingsLayoutDesignerLastSizeUnit );
  addSettingsEntry( &QgsPointCloudLayerSaveAsDialog::settingsLastPointCloudFormat );
  addSettingsEntry( &settingsStyleLastStyleCategories );

  QgsApplication::settingsRegistryCore()->addSubRegistry( this );
}

QgsSettingsRegistryGui::~QgsSettingsRegistryGui()
{
  QgsApplication::settingsRegistryCore()->removeSubRegistry( this );
}

