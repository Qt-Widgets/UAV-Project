#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebKitWidgets/QWebView>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->webView->load(QUrl("file:///C:/Users/Aaron Cho/Desktop/UAVwebMap/map.html"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
