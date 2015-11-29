#include "mainwindow.h"
#include <QApplication>

//***** MAP ******************************
#include <QMessageBox>
#include "ArcGISRuntime.h"
//****************************************


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

    MainWindow applicationWindow;
    applicationWindow.show();

    return application.exec();
}
