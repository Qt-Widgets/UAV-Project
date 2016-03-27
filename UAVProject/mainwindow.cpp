#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebKitWidgets>
#include <QUrl>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include <math.h>
#include <windows.h>
#include <voce.h>

#define pi 3.14159265358979323846

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // VOCE Init
    voce::init("C:/Users/Ernest Curioso/Documents/Voce/voce-0.9.1/voce-0.9.1/lib", true, true,
               "file:/C:/Users/Ernest Curioso/Documents/GitHub/teamcayley/OldWork/VOCE/lib", "digits");

    // Map Setup
    ui->webView_4->hide();
    ui->webView_4->load(QUrl("file:/C:/Users/Ernest Curioso/Documents/Qt Projects/UAVProject/UAVProject/map.html"));
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    connect(ui->webView_4, SIGNAL(loadProgress(int)), ui->progressBar, SLOT(setValue(int)));
    connect(ui->webView_4, SIGNAL(loadFinished(bool)), this, SLOT(onMapLoaded()));

    //Hide UAV info
    ui->scrollArea->hide();

    ui->textBrowser->hide();
    ui->textBrowser_2->hide();
    ui->textBrowser_3->hide();
    ui->textBrowser_4->hide();
    ui->textBrowser_5->hide();
    ui->textBrowser_6->hide();
    ui->textBrowser_7->hide();
    ui->textBrowser_8->hide();
    ui->textBrowser_9->hide();
    ui->textBrowser_10->hide();

    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();

    ui->progressBar_1->hide();
    ui->progressBar_2->hide();
    ui->progressBar_3->hide();
    ui->progressBar_4->hide();
    ui->progressBar_5->hide();
    ui->progressBar_6->hide();
    ui->progressBar_7->hide();
    ui->progressBar_8->hide();
    ui->progressBar_9->hide();
    ui->progressBar_10->hide();

    ui->line_1->hide();
    ui->line_2->hide();
    ui->line_3->hide();
    ui->line_4->hide();
    ui->line_5->hide();
    ui->line_6->hide();
    ui->line_7->hide();
    ui->line_8->hide();
    ui->line_9->hide();

    ui->label_1->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label_9->hide();
    ui->label_10->hide();

    // User Interface Appearance
    ui->pushButton->setText("X");
    ui->pushButton_2->setText("X");
    ui->pushButton_3->setText("X");
    ui->pushButton_4->setText("X");
    ui->pushButton_5->setText("X");
    ui->pushButton_6->setText("X");
    ui->pushButton_7->setText("X");
    ui->pushButton_8->setText("X");
    ui->pushButton_9->setText("X");
    ui->pushButton_10->setText("X");

    ui->pushButton_11->setText("Talk");

    // Timer to update clock
    QTimer *timer = new QTimer(this);
    timer->start(1000);

    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));


    // BEGIN Arduino Pulse Sensor ==============================================================================

//    ui->lcdNumber_5->display(999);
    arduino = new QSerialPort(this);
//    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
//    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
//        qDebug() << "Description: " << serialPortInfo.description() << "\n";
//        qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
//        qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
//        qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
//        qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
//        }

    bool arduino_is_available = false;
    QString arduino_uno_port_name;
            //  For each available serial port
            foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
                //  check if the serialport has both a product identifier and a vendor identifier
                if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
                    //  check if the product ID and the vendor ID match those of the arduino uno
                    if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                            && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id)){
                        arduino_is_available = true; //    arduino uno is available on this port
                        arduino_uno_port_name = serialPortInfo.portName();
                    }
                }
            }
            if(arduino_is_available){
                    qDebug() << "Found the arduino port...\n";
                    arduino->setPortName(arduino_uno_port_name);
                    arduino->open(QSerialPort::ReadOnly);
                    arduino->setBaudRate(QSerialPort::Baud115200);
                    arduino->setDataBits(QSerialPort::Data8);
                    arduino->setFlowControl(QSerialPort::NoFlowControl);
                    arduino->setParity(QSerialPort::NoParity);
                    arduino->setStopBits(QSerialPort::OneStop);
                    QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
                }else{
                    qDebug() << "Couldn't find the correct port for the arduino.\n";
                    //QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
                }
  }

MainWindow::~MainWindow()
{   
    if(arduino->isOpen())
    {
        arduino->close(); //    Close the serial port if it's open.
    }

    delete ui;
}

void MainWindow::setLCD(int x)
{
    if(x>200)
        x=200;

    ui->lcdNumber_5->display(x);
}

void MainWindow::readSerial()
{
    QByteArray aData = arduino->readLine();
    QString bpm = QString::fromStdString(aData.toStdString());
    bpm.chop(1);

    if(bpm.at(0) == "B")
    {
       bpm.remove(0,1);
       bpm.chop(1);
       setLCD(bpm.toInt());
    }

    qDebug()<<bpm;
}

// END Arduino =======================================================================================================

// BEGIN VOCE Functions



// BEGIN UI Functions ================================================================================================

void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString timeString = time.toString("HH:mm");
    ui->lcdNumber_4->display(timeString);
}

QTimer *timer3 = new QTimer();

void MainWindow::onMapLoaded()
{
    ui->progressBar->hide();
    ui->webView_4->show();
    ui->webView_4->page()->mainFrame()->addToJavaScriptWindowObject("JSBridge", this);

    this->initialize();

    // Launch Initial UAVs (string name, string path, string speed in mph, int index number, int fuel level).
    addUAV("UAV1", "[[34.239, -118.529],[34.239, -118.554]]", 70, 1, 100);
    addUAV("UAV2", "[[34.239, -118.529],[34.183, -118.312]]", 700, 2, 100);
    addUAV("UAV3", "[[34.239, -118.529],[34.190, -118.603]]", 40, 3, 100);
    addUAV("UAV4", "[[34.239, -118.529],[34.156, -118.437]]", 30, 4, 100);

    // Timer for fuel simulator
    timer3->start(5000);
}

// Stores array of USPS locations, emergency mode
void MainWindow::initialize() {
    USPSArray[0] = "34.243689,-118.535640";
    USPSArray[1] = "34.210034,-118.571521";
    USPSArray[2] = "34.265814,-118.526196";
    USPSArray[3] = "34.273601,-118.554922";
    USPSArray[4] = "34.203311,-118.535677";
    USPSArray[5] = "34.256726,-118.600793";
    USPSArray[6] = "34.218416,-118.598400";
    USPSArray[7] = "34.236373,-118.466520";
    USPSArray[8] = "34.172675,-118.541652";
    USPSArray[9] = "34.176279,-118.519337";
    USPSArray[10] = "34.200541,-118.630173";
    USPSArray[11] = "34.268628,-118.468120";
    USPSArray[12] = "34.202057,-118.476116";
    USPSArray[13] = "34.170057,-118.608636";
    USPSArray[14] = "34.224525,-118.447225";
    USPSArray[15] = "34.160040,-118.500507";
    USPSArray[16] = "34.189540,-118.448980";
    USPSArray[17] = "34.282136,-118.442553";
    USPSArray[18] = "34.154324,-118.641864";
    USPSArray[19] = "34.164363,-118.458005";
    USPSArray[20] = "34.164719,-118.404642";
    USPSArray[21] = "34.187314,-118.398483";
    USPSArray[22] = "34.198664,-118.397087";
    USPSArray[23] = "34.241801,-118.425418";
    USPSArray[24] = "34.262476,-118.427655";
    USPSArray[25] = "34.142350,-118.394123";
    USPSArray[26] = "34.152470,-118.350381";
    USPSArray[27] = "34.167841,-118.377927";
    USPSArray[28] = "34.187958,-118.348218";
    USPSArray[29] = "34.217020,-118.368881";
    USPSArray[30] = "34.180514,-118.309706";

    USPSNames[0] = "Northridge";
    USPSNames[1] = "Winnetka";
    USPSNames[2] = "Granada Hills";
    USPSNames[3] = "Porter Ranch";
    USPSNames[4] = "Reseda";
    USPSNames[5] = "Chatsworth";
    USPSNames[6] = "Canoga Park";
    USPSNames[7] = "North Hills";
    USPSNames[8] = "Tarzana";
    USPSNames[9] = "Encino";
    USPSNames[10] = "West Hills";
    USPSNames[11] = "Mission Hills";
    USPSNames[12] = "Van Nuys";
    USPSNames[13] = "Woodland Hills";
    USPSNames[14] = "Panorama City";
    USPSNames[15] = "Balboa Van Nuys";
    USPSNames[16] = "Civic Center Van Nuys";
    USPSNames[17] = "San Fernando";
    USPSNames[18] = "Calabasas";
    USPSNames[19] = "Sherman Oaks";
    USPSNames[20] = "Valley Village";
    USPSNames[21] = "Valley Plaza";
    USPSNames[22] = "North Hollywood";
    USPSNames[23] = "Arleta";
    USPSNames[24] = "Pacoima";
    USPSNames[25] = "Studio City";
    USPSNames[26] = "Toluca Lake";
    USPSNames[27] = "Chandler";
    USPSNames[28] = "Burbank";
    USPSNames[29] = "Sun Valley";
    USPSNames[30] = "Downtown Burbank";

    emerg[1] = false;
    emerg[2] = false;
    emerg[3] = false;
    emerg[4] = false;
    emerg[5] = false;
    emerg[6] = false;
    emerg[7] = false;
    emerg[8] = false;
    emerg[9] = false;
    emerg[10] = false;
}

void MainWindow::addUAV(QString name, QString path, int speed, int index, int fuelLevel) {
    int timeInterval = calcTimeInterval(speed, path);

    ui->webView_4->page()->mainFrame()->evaluateJavaScript("addUAV('" + name + "', " + path + ", " + QString::number(timeInterval) + ");");
    fuel[index] = fuelLevel;
    connect(timer3, &QTimer::timeout, this, [=]{ fuelSim(name, index); });
}

// Simulates constant fuel decrementation
void MainWindow::fuelSim(QString name, int index)
{
    //for (int i = 1; i < 4; i++) {
    //    ui->webView_4->page()->mainFrame()->evaluateJavaScript("popup(" + QString::number(i) + ");");
    //}

    QMessageBox* msgBox = new QMessageBox();
    msgBox->setWindowTitle("ALERT");

    QVariant stopped = ui->webView_4->page()->mainFrame()->evaluateJavaScript("isStopped('" + name + "');");

    if (stopped == false) {
        fuel[index]--;
    }

    if (index == 1) {
       ui->progressBar_1->setValue(fuel[index]);
    }
    else if (index == 2) {
        ui->progressBar_2->setValue(fuel[index]);
    }
    else if (index == 3) {
        ui->progressBar_3->setValue(fuel[index]);
    }
    else if (index == 4) {
        ui->progressBar_4->setValue(fuel[index]);
    }
    else if (index == 5) {
        ui->progressBar_5->setValue(fuel[index]);
    }
    else if (index == 6) {
        ui->progressBar_6->setValue(fuel[index]);
    }
    else if (index == 7) {
        ui->progressBar_7->setValue(fuel[index]);
    }
    else if (index == 8) {
        ui->progressBar_8->setValue(fuel[index]);
    }
    else if (index == 9) {
        ui->progressBar_9->setValue(fuel[index]);
    }
    else if (index == 10) {
        ui->progressBar_10->setValue(fuel[index]);
    }

    QString temp;
    int i;

    // Alerts for low fuel levels
    if (fuel[index] == 20){
        showUAVWindow(name, index);
        ui->webView_4->page()->mainFrame()->evaluateJavaScript("popup('" + QString::number(index) + "', 'Battery at 20%');");

        msgBox->setText(name + "\n Low Battery at 20%. \n Will emergency land at nearest USPS at 10%.");
        msgBox->show();
        voce::synthesize("U A V" + QString::number(index).toStdString() + "Low Battery at 20%");

        fuel[index]--;
    }
    else if (fuel[index] == 10){
        showUAVWindow(name, index);
        ui->webView_4->page()->mainFrame()->evaluateJavaScript("popup('" + QString::number(index) + "', 'Emergency Landing!');");

        temp = getLatLng(name);
        i = closestUSPS(temp);

        emerg[index] = true;

        msgBox->setText(name +
                        "\nLow Battery at 10% \n"
                        "Emergency landing at " + USPSNames[i] + " post office.");
        msgBox->show();
        voce::synthesize("U A V" + QString::number(index).toStdString() + "Low Battery at 10%. Emergency landing at" + USPSNames[i].toStdString() + "post office.");

        ui->webView_4->page()->mainFrame()->evaluateJavaScript("reroute('" + name + "', [" + USPSArray[i] + "], 7000);");

        fuel[index]--;
    }
    else if (fuel[index] == 2) {
        showUAVWindow(name, index);
        ui->webView_4->page()->mainFrame()->evaluateJavaScript("popup('" + QString::number(index) + "', 'Unexpected landing.');");

        emerg[index] = true;

        msgBox->setText(name +
                        "\nDid not make it to nearest USPS. \n" +
                        "Landed at current location.");
        msgBox->show();

        voce::synthesize("U A V" + QString::number(index).toStdString() + "did not make it to the nearest U S P S. Landed at current location.");


        ui->webView_4->page()->mainFrame()->evaluateJavaScript("stopFlight('" + name + "');");

        fuel[index]--;
    }
}

// Getter for latlng
QString MainWindow::getLatLng(QString name) {
    QVariant a = ui->webView_4->page()->mainFrame()->evaluateJavaScript("getLatLng('" + name +  "');");
    return a.toString();
}

// Determines closest USPS for given latlng
int MainWindow::closestUSPS(QString latlng) {

    QRegExp rx ("[(),]");
    QStringList list = latlng.split(rx, QString::SkipEmptyParts);
    QString lat = list.at(1);
    QString lng = list.at(2);

    QString lat2;
    QString lng2;
    QStringList list2;

    double r = 3961;
    double dist = 1000000;
    double dlat;
    double dlon;
    double a;
    double c;
    double temp;
    int position = 0;

    for (int i=0; i<=30; i++) {
        list2 = USPSArray[i].split(rx, QString::SkipEmptyParts);
        lat2 = list2.at(0);
        lng2 = list2.at(1);

        // Formula for determing distance between to latlng values
        dlat = lat2.toDouble() - lat.toDouble();
        dlat = (dlat * pi)/180;
        dlon = lng2.toDouble() - lng.toDouble();
        dlon = (dlon * pi)/180;
        a = ((sin(dlat/2))*(sin(dlat/2))) + cos(lat.toDouble()) * cos(lat2.toDouble()) * ((sin(dlon/2))*(sin(dlon/2)));
        c = 2 * atan2(sqrt(a), sqrt(1-a));
        temp = r * c;

        if (temp < dist) {
            dist = temp;
            position = i;
        }
    }

    return position;
}

QTimer *timer2 = new QTimer();

// Shows UAV Window
void MainWindow::showUAVWindow(QString name, int index)
{
    // Timer for live update of UAV info ie latlong values
    connect(timer2, &QTimer::timeout, this, [=]{ showInfo(name); });
    timer2->start(100);

    // Shows/hides UAV box UI elements    
    if (index == 1){
        //ui->textBrowser->setStyleSheet("background-color: #33ff00;");

        ui->scrollArea->show();
        ui->scrollArea->ensureWidgetVisible(ui->label_1);
        ui->scrollArea->ensureWidgetVisible(ui->progressBar_1);
        ui->textBrowser->show();
        ui->pushButton->show();
        ui->progressBar_1->show();
        ui->line_1->show();
        ui->label_1->show();
        ui->label_1->setText(name);
        connect(ui->pushButton, SIGNAL(pressed()), ui->textBrowser, SLOT(hide()));
        connect(ui->pushButton, SIGNAL(pressed()), ui->pushButton, SLOT(hide()));
        connect(ui->pushButton, SIGNAL(pressed()), ui->progressBar_1, SLOT(hide()));
        connect(ui->pushButton, SIGNAL(pressed()), ui->line_1, SLOT(hide()));
        connect(ui->pushButton, SIGNAL(pressed()), ui->label_1, SLOT(hide()));
    }
    else if (index == 2){
        ui->scrollArea->show();
        ui->scrollArea->ensureWidgetVisible(ui->label_2);
        ui->scrollArea->ensureWidgetVisible(ui->progressBar_2);
        ui->textBrowser_2->show();
        ui->pushButton_2->show();
        ui->progressBar_2->show();
        ui->line_2->show();
        ui->label_2->show();
        ui->label_2->setText(name);
        connect(ui->pushButton_2, SIGNAL(pressed()), ui->textBrowser_2, SLOT(hide()));
        connect(ui->pushButton_2, SIGNAL(pressed()), ui->pushButton_2, SLOT(hide()));
        connect(ui->pushButton_2, SIGNAL(pressed()), ui->progressBar_2, SLOT(hide()));
        connect(ui->pushButton_2, SIGNAL(pressed()), ui->line_2, SLOT(hide()));
        connect(ui->pushButton_2, SIGNAL(pressed()), ui->label_2, SLOT(hide()));
    }
    else if (index == 3){
        ui->scrollArea->show();
        ui->scrollArea->ensureWidgetVisible(ui->label_3);
        ui->scrollArea->ensureWidgetVisible(ui->progressBar_3);
        ui->textBrowser_3->show();
        ui->pushButton_3->show();
        ui->progressBar_3->show();
        ui->line_3->show();
        ui->label_3->show();
        ui->label_3->setText(name);
        connect(ui->pushButton_3, SIGNAL(pressed()), ui->textBrowser_3, SLOT(hide()));
        connect(ui->pushButton_3, SIGNAL(pressed()), ui->pushButton_3, SLOT(hide()));
        connect(ui->pushButton_3, SIGNAL(pressed()), ui->progressBar_3, SLOT(hide()));
        connect(ui->pushButton_3, SIGNAL(pressed()), ui->line_3, SLOT(hide()));
        connect(ui->pushButton_3, SIGNAL(pressed()), ui->label_3, SLOT(hide()));
    }
    else if (index == 4){
        ui->scrollArea->show();
        ui->scrollArea->ensureWidgetVisible(ui->label_4);
        ui->scrollArea->ensureWidgetVisible(ui->progressBar_4);
        ui->textBrowser_4->show();
        ui->pushButton_4->show();
        ui->progressBar_4->show();
        ui->line_4->show();
        ui->label_4->show();
        ui->label_4->setText(name);
        connect(ui->pushButton_4, SIGNAL(pressed()), ui->textBrowser_4, SLOT(hide()));
        connect(ui->pushButton_4, SIGNAL(pressed()), ui->pushButton_4, SLOT(hide()));
        connect(ui->pushButton_4, SIGNAL(pressed()), ui->progressBar_4, SLOT(hide()));
        connect(ui->pushButton_4, SIGNAL(pressed()), ui->line_4, SLOT(hide()));
        connect(ui->pushButton_4, SIGNAL(pressed()), ui->label_4, SLOT(hide()));
    }
    else if (index == 5){
        ui->scrollArea->show();
        ui->scrollArea->ensureWidgetVisible(ui->label_5);
        ui->scrollArea->ensureWidgetVisible(ui->progressBar_5);
        ui->textBrowser_5->show();
        ui->pushButton_5->show();
        ui->progressBar_5->show();
        ui->line_5->show();
        ui->label_5->show();
        ui->label_5->setText(name);
        connect(ui->pushButton_5, SIGNAL(pressed()), ui->textBrowser_5, SLOT(hide()));
        connect(ui->pushButton_5, SIGNAL(pressed()), ui->pushButton_5, SLOT(hide()));
        connect(ui->pushButton_5, SIGNAL(pressed()), ui->progressBar_5, SLOT(hide()));
        connect(ui->pushButton_5, SIGNAL(pressed()), ui->line_5, SLOT(hide()));
        connect(ui->pushButton_5, SIGNAL(pressed()), ui->label_5, SLOT(hide()));
    }
    else if (index == 6){
        ui->scrollArea->show();
        ui->scrollArea->ensureWidgetVisible(ui->label_6);
        ui->scrollArea->ensureWidgetVisible(ui->progressBar_6);
        ui->textBrowser_6->show();
        ui->pushButton_6->show();
        ui->progressBar_6->show();
        ui->line_6->show();
        ui->label_6->show();
        ui->label_6->setText(name);
        connect(ui->pushButton_6, SIGNAL(pressed()), ui->textBrowser_6, SLOT(hide()));
        connect(ui->pushButton_6, SIGNAL(pressed()), ui->pushButton_6, SLOT(hide()));
        connect(ui->pushButton_6, SIGNAL(pressed()), ui->progressBar_6, SLOT(hide()));
        connect(ui->pushButton_6, SIGNAL(pressed()), ui->line_6, SLOT(hide()));
        connect(ui->pushButton_6, SIGNAL(pressed()), ui->label_6, SLOT(hide()));
    }
    else if (index == 7){
        ui->scrollArea->show();
        ui->scrollArea->ensureWidgetVisible(ui->label_7);
        ui->scrollArea->ensureWidgetVisible(ui->progressBar_7);
        ui->textBrowser_7->show();
        ui->pushButton_7->show();
        ui->progressBar_7->show();
        ui->line_7->show();
        ui->label_7->show();
        ui->label_7->setText(name);
        connect(ui->pushButton_7, SIGNAL(pressed()), ui->textBrowser_7, SLOT(hide()));
        connect(ui->pushButton_7, SIGNAL(pressed()), ui->pushButton_7, SLOT(hide()));
        connect(ui->pushButton_7, SIGNAL(pressed()), ui->progressBar_7, SLOT(hide()));
        connect(ui->pushButton_7, SIGNAL(pressed()), ui->line_7, SLOT(hide()));
        connect(ui->pushButton_7, SIGNAL(pressed()), ui->label_7, SLOT(hide()));
    }
    else if (index == 8){
        ui->scrollArea->show();
        ui->scrollArea->ensureWidgetVisible(ui->label_8);
        ui->scrollArea->ensureWidgetVisible(ui->progressBar_8);
        ui->textBrowser_8->show();
        ui->pushButton_8->show();
        ui->progressBar_8->show();
        ui->line_8->show();
        ui->label_8->show();
        ui->label_8->setText(name);
        connect(ui->pushButton_8, SIGNAL(pressed()), ui->textBrowser_8, SLOT(hide()));
        connect(ui->pushButton_8, SIGNAL(pressed()), ui->pushButton_8, SLOT(hide()));
        connect(ui->pushButton_8, SIGNAL(pressed()), ui->progressBar_8, SLOT(hide()));
        connect(ui->pushButton_8, SIGNAL(pressed()), ui->line_8, SLOT(hide()));
        connect(ui->pushButton_8, SIGNAL(pressed()), ui->label_8, SLOT(hide()));
    }
    else if (index == 9){
        ui->scrollArea->show();
        ui->scrollArea->ensureWidgetVisible(ui->label_9);
        ui->scrollArea->ensureWidgetVisible(ui->progressBar_9);
        ui->textBrowser_9->show();
        ui->pushButton_9->show();
        ui->progressBar_9->show();
        ui->line_9->show();
        ui->label_9->show();
        ui->label_9->setText(name);
        connect(ui->pushButton_9, SIGNAL(pressed()), ui->textBrowser_9, SLOT(hide()));
        connect(ui->pushButton_9, SIGNAL(pressed()), ui->pushButton_9, SLOT(hide()));
        connect(ui->pushButton_9, SIGNAL(pressed()), ui->progressBar_9, SLOT(hide()));
        connect(ui->pushButton_9, SIGNAL(pressed()), ui->line_9, SLOT(hide()));
        connect(ui->pushButton_9, SIGNAL(pressed()), ui->label_9, SLOT(hide()));
    }
    else if (index == 10){
        ui->scrollArea->show();
        ui->scrollArea->ensureWidgetVisible(ui->label_10);
        ui->scrollArea->ensureWidgetVisible(ui->progressBar_10);
        ui->textBrowser_10->show();
        ui->pushButton_10->show();
        ui->progressBar_10->show();
        //ui->line_10->show();
        ui->label_10->show();
        ui->label_10->setText(name);
        connect(ui->pushButton_10, SIGNAL(pressed()), ui->textBrowser_10, SLOT(hide()));
        connect(ui->pushButton_10, SIGNAL(pressed()), ui->pushButton_10, SLOT(hide()));
        connect(ui->pushButton_10, SIGNAL(pressed()), ui->progressBar_10, SLOT(hide()));
        //connect(ui->pushButton_10, SIGNAL(pressed()), ui->line_10, SLOT(hide()));
        connect(ui->pushButton_10, SIGNAL(pressed()), ui->label_10, SLOT(hide()));
    }
}

// Live update of information within UAV Window.
void MainWindow::showInfo(QString name)
{
    QVariant a = ui->webView_4->page()->mainFrame()->evaluateJavaScript("getLatLng('" + name +  "');");
    QVariant started = ui->webView_4->page()->mainFrame()->evaluateJavaScript("isStarted('" + name +  "');");
    QVariant running = ui->webView_4->page()->mainFrame()->evaluateJavaScript("isRunning('" + name +  "');");
    QVariant paused = ui->webView_4->page()->mainFrame()->evaluateJavaScript("isPaused('" + name +  "');");
    QVariant stopped = ui->webView_4->page()->mainFrame()->evaluateJavaScript("isStopped('" + name +  "');");
    QVariant f = ui->webView_4->page()->mainFrame()->evaluateJavaScript("getUAVIndexFromName('" + name + "');");
    int g = f.toInt();

    // Mission and status levels
    if (running == true && emerg[g] == false){
        status[g] = "En Route.";
        mission[g] = "In Progress.";
    }
    else if (paused == true && emerg[g] == false) {
        status[g] = "En Route. Hovering in place.";
        mission[g] = "In progress.";
    }
    else if (stopped == true && emerg[g] == false) {
        status[g] = "Landed at destination.";
        mission[g] = "Complete.";
    }
    else if (emerg[g] == true && running == true) {
        status[g] = "Emergency landing in progress.";
        mission[g] = "Aborting.";
    }
    else if (emerg[g] == true && stopped == true) {
        status[g] = "Emergency landed.";
        mission[g] = "Incomplete. Aborted.";
    }

    //Displays live update.
    if (name == "UAV1") {        
        ui->textBrowser->setText("MISSION STATUS: " + mission[g] + "\n\n" +
                                 "UAV STATUS: " + status[g] + "\n\n" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV2") {
        ui->textBrowser_2->setText("MISSION STATUS: " + mission[g] + "\n\n" +
                                 "UAV STATUS: " + status[g] + "\n\n" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV3") {
        ui->textBrowser_3->setText("MISSION STATUS: " + mission[g] + "\n\n" +
                                 "UAV STATUS: " + status[g] + "\n\n" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV4") {
        ui->textBrowser_4->setText("MISSION STATUS: " + mission[g] + "\n\n" +
                                 "UAV STATUS: " + status[g] + "\n\n" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV5") {
        ui->textBrowser_5->setText("MISSION STATUS: " + mission[g] + "\n\n" +
                                 "UAV STATUS: " + status[g] + "\n\n" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV6") {
        ui->textBrowser_6->setText("MISSION STATUS: " + mission[g] + "\n\n" +
                                 "UAV STATUS: " + status[g] + "\n\n" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV7") {
        ui->textBrowser_7->setText("MISSION STATUS: " + mission[g] + "\n\n" +
                                 "UAV STATUS: " + status[g] + "\n\n" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV8") {
        ui->textBrowser_8->setText("MISSION STATUS: " + mission[g] + "\n\n" +
                                 "UAV STATUS: " + status[g] + "\n\n" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV9") {
        ui->textBrowser_9->setText("MISSION STATUS: " + mission[g] + "\n\n" +
                                 "UAV STATUS: " + status[g] + "\n\n" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV10") {
        ui->textBrowser_10->setText("MISSION STATUS: " + mission[g] + "\n\n" +
                                 "UAV STATUS: " + status[g] + "\n\n" +
                                 "LOCATION: " + a.toString());
    }

    if (ui->textBrowser->isHidden() &&
            ui->textBrowser_2->isHidden() &&
            ui->textBrowser_3->isHidden() &&
            ui->textBrowser_4->isHidden() &&
            ui->textBrowser_5->isHidden() &&
            ui->textBrowser_6->isHidden() &&
            ui->textBrowser_7->isHidden() &&
            ui->textBrowser_8->isHidden() &&
            ui->textBrowser_9->isHidden() &&
            ui->textBrowser_10->isHidden()
            ) {
        ui->scrollArea->hide();
    }
}

//Calculates distance between two latlong values (path [[lat,long],[lat,long]])
 double MainWindow::calcDistance(QString path) {
    QRegExp rx ("[][,]");
    QStringList list = path.split(rx, QString::SkipEmptyParts);
    QString lat = list.at(0);
    QString lng = list.at(1);
    QString lat2 = list.at(2);
    QString lng2 = list.at(3);

    double r = 3961;
    double dist;
    double dlat;
    double dlon;
    double a;
    double c;

    dlat = lat2.toDouble() - lat.toDouble();
    dlat = (dlat * pi)/180;
    dlon = lng2.toDouble() - lng.toDouble();
    dlon = (dlon * pi)/180;
    a = ((sin(dlat/2))*(sin(dlat/2))) + cos(lat.toDouble()) * cos(lat2.toDouble()) * ((sin(dlon/2))*(sin(dlon/2)));
    c = 2 * atan2(sqrt(a), sqrt(1-a));
    dist = r * c;

    return dist;
}

int MainWindow::calcTimeInterval(int speed, QString path) {
    double distance = calcDistance(path);
    double time = distance/speed;

    QRegExp rx ("[.]");
    QStringList list = QString::number(time).split(rx, QString::SkipEmptyParts);
    QString hour = list.at(0);
    QString minute = "0." + list.at(1);

    double hourToMs = hour.toDouble() * 60 * 60 * 1000;
    double minToMs = minute.toDouble() * 60 * 60 * 1000;
    double ms = hourToMs + minToMs;

    return ms;
}

// END UI Functions =====================================================================================================

