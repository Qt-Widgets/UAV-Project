#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QtCore>
#include <QTimer>
#include "uav.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QDesktopWidget dw;

    int x=dw.width()*0.95;
    int y=dw.height()*0.8;
    w.setFixedSize(x,y);

    w.show();

    Uav uav1;

    return a.exec();
}
