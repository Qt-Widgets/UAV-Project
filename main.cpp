#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QtCore>
#include <QTimer>
#include "uav.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Uav uav1;

    return a.exec();
}
