// Copyright 2015 ESRI
//
// All rights reserved under the copyright laws of the United States
// and applicable international laws, treaties, and conventions.
//
// You may freely redistribute and use this sample code, with or
// without modification, provided you include the original copyright
// notice and use restrictions.
//
// See the Sample code usage restrictions document for further information.
//

#include "untitled3.h"
#include <QApplication>
#include <QMessageBox>
#include "ArcGISRuntime.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

#ifdef Q_OS_WIN
    // Force usage of OpenGL ES through ANGLE on Windows
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif

    // Before initializing ArcGIS Runtime, first set the
    // ArcGIS Runtime license setting required for your application.

    // EsriRuntimeQt::ArcGISRuntime::setClientId("Place client id here");
    // EsriRuntimeQt::ArcGISRuntime::License::setLicense("Place license string in here");

    // Set extensions license for local server extension
    // QStringList extensions;
    // EsriRuntimeQt::ArcGISRuntime::License::setExtensionLicenses(extensions);

    // Use this code to check for licensing errors
    //
    // if (EsriRuntimeQt::ArcGISRuntime::initialize() == false)
    // {
    //     QMessageBox msgBox;
    //     msgBox.setText(EsriRuntimeQt::ArcGISRuntime::error());
    //     msgBox.exec();
    //     application.quit();
    //     return 1;
    // }

    Untitled3 applicationWindow;
    applicationWindow.setMinimumWidth(800);
    applicationWindow.setMinimumHeight(600);
    applicationWindow.show();

    return application.exec();
}

