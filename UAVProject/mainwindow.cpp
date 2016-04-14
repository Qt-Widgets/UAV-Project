#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebKitWidgets>
#include <QUrl>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QtMultimedia/QMediaPlayer>
#include <math.h>
#include <windows.h>
#include <voce.h>
#include "calculate.h"
#include "uav.h"

#define pi 3.14159265358979323846

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // VOCE Init
    voce::init("C:/Users/Ernest Curioso/Documents/Voce/voce-0.9.1/voce-0.9.1/lib", true, true,
               "file:/C:/Users/Ernest Curioso/Documents/Qt Projects/UAVProject/UAVProject/gram", "digits");
    voce::setRecognizerEnabled(false);

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

    ui->focusButton_1->hide();
    ui->focusButton_2->hide();
    ui->focusButton_3->hide();
    ui->focusButton_4->hide();
    ui->focusButton_5->hide();
    ui->focusButton_6->hide();
    ui->focusButton_7->hide();
    ui->focusButton_8->hide();
    ui->focusButton_9->hide();
    ui->focusButton_10->hide();

    ui->closeAllButton->hide();

    // User Interface Appearance

    ui->pushButton->setStyleSheet("background-color: #FA5858; color: #000000 ");
    ui->pushButton_2->setStyleSheet("background-color: #FA5858; color: #000000 ");
    ui->pushButton_3->setStyleSheet("background-color: #FA5858; color: #000000 ");
    ui->pushButton_4->setStyleSheet("background-color: #FA5858; color: #000000 ");
    ui->pushButton_5->setStyleSheet("background-color: #FA5858; color: #000000 ");
    ui->pushButton_6->setStyleSheet("background-color: #FA5858; color: #000000 ");
    ui->pushButton_7->setStyleSheet("background-color: #FA5858; color: #000000 ");
    ui->pushButton_8->setStyleSheet("background-color: #FA5858; color: #000000 ");
    ui->pushButton_9->setStyleSheet("background-color: #FA5858; color: #000000 ");
    ui->pushButton_10->setStyleSheet("background-color: #FA5858; color: #000000 ");

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
    ui->pushButton_11->setStyleSheet("background-color: #9FF781;");

    ui->closeAllButton->setText("Hide All");
    ui->closeAllButton->setStyleSheet("background-color: #FA5858; color: #000000;");

    ui->focusButton_1->setStyleSheet("background-color: #E6E6E6; color: #000000;");
    ui->focusButton_2->setStyleSheet("background-color: #E6E6E6; color: #000000;");
    ui->focusButton_3->setStyleSheet("background-color: #E6E6E6; color: #000000;");
    ui->focusButton_4->setStyleSheet("background-color: #E6E6E6; color: #000000;");
    ui->focusButton_5->setStyleSheet("background-color: #E6E6E6; color: #000000;");
    ui->focusButton_6->setStyleSheet("background-color: #E6E6E6; color: #000000;");
    ui->focusButton_7->setStyleSheet("background-color: #E6E6E6; color: #000000;");
    ui->focusButton_8->setStyleSheet("background-color: #E6E6E6; color: #000000;");
    ui->focusButton_9->setStyleSheet("background-color: #E6E6E6; color: #000000;");
    ui->focusButton_10->setStyleSheet("background-color: #E6E6E6; color: #000000;");

    ui->focusButton_1->setText("Focus");
    ui->focusButton_2->setText("Focus");
    ui->focusButton_3->setText("Focus");
    ui->focusButton_4->setText("Focus");
    ui->focusButton_5->setText("Focus");
    ui->focusButton_6->setText("Focus");
    ui->focusButton_7->setText("Focus");
    ui->focusButton_8->setText("Focus");
    ui->focusButton_9->setText("Focus");
    ui->focusButton_10->setText("Focus");

    ui->centralWidget->setStyleSheet("color: #848484;");

    ui->textBrowser_11->setStyleSheet("color: #9FF781;"
                                      "background-color: #585858;"
                                      "font-size: 16px;"
                                      "font-weight: bold;");

    this->setStyleSheet("background-color: #112E34;");

    ui->scrollAreaWidgetContents_6->setStyleSheet("background-color: #585858;");

    // Timer to update clock
    QTimer *timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));

/*USPSName[0] = "Northridge";
USPSName[1] = "Winnetka";
USPSName[2] = "Granada Hills";
USPSName[3] = "Porter Ranch";
USPSName[4] = "Reseda";
USPSName[5] = "Chatsworth";
USPSName[6] = "Canoga Park";
USPSName[7] = "North Hills";
USPSName[8] = "Tarzana";
USPSName[9] = "Encino";
USPSName[10] = "West Hills";
USPSName[11] = "Mission Hills";
USPSName[12] = "Van Nuys";
USPSName[13] = "Woodland Hills";
USPSName[14] = "Panorama City";
USPSName[15] = "Balboa Van Nuys";
USPSName[16] = "Civic Center Van Nuys";
USPSName[17] = "San Fernando";
USPSName[18] = "Calabasas";
USPSName[19] = "Sherman Oaks";
USPSName[20] = "Valley Village";
USPSName[21] = "Valley Plaza";
USPSName[22] = "North Hollywood";
USPSName[23] = "Arleta";
USPSName[24] = "Pacoima";
USPSName[25] = "Studio City";
USPSName[26] = "Toluca Lake";
USPSName[27] = "Chandler";
USPSName[28] = "Burbank";
USPSName[29] = "Sun Valley";
USPSName[30] = "Downtown Burbank";

Northridge
Winnetka
Granada Hills
Porter Ranch
Reseda
Chatsworth
Canoga Park
North Hills

Encino
West Hills
Mission Hills
Van Nuys
Woodland Hills
Panorama City
Balboa Van Nuys
Civic Center Van Nuys
San Fernando
Calabasas
Sherman Oaks
Valley Village
Valley Plaza
North Hollywood


Studio City

Chandler
Burbank
Sun Valley
Downtown Burbank

USPSLatLng[0] = "34.243689,-118.535640";
USPSLatLng[1] = "34.210034,-118.571521";
USPSLatLng[2] = "34.265814,-118.526196";
USPSLatLng[3] = "34.273601,-118.554922";
USPSLatLng[4] = "34.203311,-118.535677";
USPSLatLng[5] = "34.256726,-118.600793";
USPSLatLng[6] = "34.218416,-118.598400";
USPSLatLng[7] = "34.236373,-118.466520";
USPSLatLng[8] = "34.172675,-118.541652";
USPSLatLng[9] = "34.176279,-118.519337";
USPSLatLng[10] = "34.200541,-118.630173";
USPSLatLng[11] = "34.268628,-118.468120";
USPSLatLng[12] = "34.202057,-118.476116";
USPSLatLng[13] = "34.170057,-118.608636";
USPSLatLng[14] = "34.224525,-118.447225";
USPSLatLng[15] = "34.160040,-118.500507";
USPSLatLng[16] = "34.189540,-118.448980";
USPSLatLng[17] = "34.282136,-118.442553";
USPSLatLng[18] = "34.154324,-118.641864";
USPSLatLng[19] = "34.164363,-118.458005";
USPSLatLng[20] = "34.164719,-118.404642";
USPSLatLng[21] = "34.187314,-118.398483";
USPSLatLng[22] = "34.198664,-118.397087";
USPSLatLng[23] = "34.241801,-118.425418";
USPSLatLng[24] = "34.262476,-118.427655";
USPSLatLng[25] = "34.142350,-118.394123";
USPSLatLng[26] = "34.152470,-118.350381";
USPSLatLng[27] = "34.167841,-118.377927";
USPSLatLng[28] = "34.187958,-118.348218";
USPSLatLng[29] = "34.217020,-118.368881";
USPSLatLng[30] = "34.180514,-118.309706";*/


    // Reads text file containing usps locations and stores them in array
    QFile inputFile("C:/Users/Ernest Curioso/Documents/Qt Projects/UAVProject/UAVProject/SFVUSPS.txt");
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        int i = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList pair = line.split(":");
            //USPSNames[i] = pair[0];
            USPSName[i]  = pair[0];
            USPSLatLng[i] = pair[1];
            i++;
        }
        inputFile.close();
    }

    //for (int i =0; i<=30; i++) {
    //    ui->textBrowser_11->append(USPSName[i]);
    //}

    //for (int i =0; i<=30; i++) {
    //    ui->textBrowser_11->append(USPSLatLng[i]);
    //}

    //for (int i =0; i<=30; i++) {
    //    ui->textBrowser_11->append(USPSName[i]);
    //}


    // Initalizes emergency flag for each UAV to false
    for (int i=1; i<=10; i++) {
        emerg[i] = false;
    }

    timer4->start(250);

    // BEGIN Arduino Pulse Sensor  ==============================================================================

//    ui->lcdNumber_5->display(999);
    arduino = new QSerialPort(this);
//    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "/n";
//    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
//        qDebug() << "Description: " << serialPortInfo.description() << "/n";
//        qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "/n";
//        qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "/n";
//        qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "/n";
//        qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "/n";
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
                    qDebug() << "Found the arduino port.../n";
                    arduino->setPortName(arduino_uno_port_name);
                    arduino->open(QSerialPort::ReadOnly);
                    arduino->setBaudRate(QSerialPort::Baud115200);
                    arduino->setDataBits(QSerialPort::Data8);
                    arduino->setFlowControl(QSerialPort::NoFlowControl);
                    arduino->setParity(QSerialPort::NoParity);
                    arduino->setStopBits(QSerialPort::OneStop);
                    QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
                }else{
                    qDebug() << "Couldn't find the correct port for the arduino./n";
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

// BEGIN VOCE Functions ==============================================================================================

void MainWindow::manipString(QString heard)
{
    QStringList heardList = heard.split(" ", QString::SkipEmptyParts);
    int temp = -1;
    int temp2 = -1;
    QString temp3;

    if (responseName == true) {
        if (heard == "ernest" || heard == "daniel" || heard == "blake" || heard == "tariq" || heard == "eric" || heard == "aaron") {
            atcName = heard;
            voce::synthesize("Hello" + atcName.toStdString());
            ui->textBrowser_11->append("Cayley: Hello " + atcName + ".");
            responseName = false;
        }
        else {
            voce::synthesize("A T C name not recognized. Please restate your name");
            ui->textBrowser_11->append("Cayley: ATC name not recognized. Please restate your name.");
        }
    }
    else if (responseName == false) {
    if (heardList[0] == "change") {
        atcName = heardList[5];
        voce::synthesize("Hello" + atcName.toStdString());
        ui->textBrowser_11->append("Hello " + atcName + ".");
    }
    else if (heard == "launch all u a v") {
        ui->webView_4->page()->mainFrame()->evaluateJavaScript("start();");

        // Timer for fuel simulator
        timer3->start(5000);
    }
    else if (heardList[0] == "report") {

        temp = numStringToInt(heardList[6]);

        if (heardList[1] == "speed") {
            temp2 = speedArray[temp];
            voce::synthesize(QString::number(temp2).toStdString() + "miles per hour.");
            ui->textBrowser_11->append("Cayley: " + QString::number(temp2) + " mph.");
        }
        else if (heardList[1] == "destination") {
            temp3 = destinationArray[temp];
            voce::synthesize(temp3.toStdString());
            ui->textBrowser_11->append("Cayley: " + temp3);
        }
        else if (heardList[1] == "battery") {
            temp2 = fuel[temp];
            voce::synthesize(QString::number(temp2).toStdString() + "percent" );
            ui->textBrowser_11->append("Cayley: " + QString::number(temp2) + "%.");
        }
        else if (heardList[1] == "u") {
            temp = numStringToInt(heardList[9]);
            temp3 = status[temp];
            voce::synthesize(temp3.toStdString());
            ui->textBrowser_11->append("Cayley: " + temp3 + ".");
        }
        else if (heardList[1] == "mission") {
            temp = numStringToInt(heardList[7]);
            temp3 = mission[temp];
            voce::synthesize(temp3.toStdString());
            ui->textBrowser_11->append("Cayley: " + temp3 + ".");
        }
        else if (heardList[1] == "closest") {
            temp = numStringToInt(heardList[8]);
            temp3 = getLatLng(temp);
            temp2 = closestUSPS(temp3);
            voce::synthesize(USPSName[temp2].toStdString());
            ui->textBrowser_11->append("Cayley: " + USPSName[temp2] + ".");
        }
    }
    else if (heardList [0] == "hover") {
        temp = numStringToInt(heardList[4]);
        ui->webView_4->page()->mainFrame()->evaluateJavaScript("pauseFlight('" + QString::number(temp) + "');");
    }
    else if (heardList[0] == "resume") {
        temp = numStringToInt(heardList[6]);
        ui->webView_4->page()->mainFrame()->evaluateJavaScript("resumeFlight('" + QString::number(temp) + "');");
    }
    else if (heardList[0] == "return") {
        temp = numStringToInt(heardList[6]);
        if (destinationArray[temp] == originArray[temp]) {
        }
        else {
            destinationArray[temp] = originArray[temp];
            reroute(temp, originArray[temp]);
            start(temp, originArray[temp]);
        }
    }
    else if (heardList[0] == "emergency") {
        temp = numStringToInt(heardList[5]);
        temp3 = getLatLng(temp);
        int i = closestUSPS(temp3);
        if (destinationArray[temp] == USPSName[i]) {
        }
        else {
            destinationArray[temp] = USPSName[i];
            emerg[temp] = true;
            reroute(temp, USPSName[i]);\
        }
    }
    else if (heardList[0] == "code") {
        if (heardList[1] == "red") {
            responseRed = true;
            voce::synthesize("Landing all U A V. Are you sure?");
            ui->textBrowser_11->append("Cayley: Landing all UAV. Are you sure?");
        }
        else if (heardList[1] == "yellow") {
            responseYellow = true;
            voce::synthesize("Returning all U A V to origin. Are you sure?");
            ui->textBrowser_11->append("Cayley: Returning all UAV to origin. Are you sure?");
        }
    }
    else if (heardList[0] == "yes") {
        if (responseRed == true) {
            voce::synthesize("Landing all U A V to closest post office.");
            ui->textBrowser_11->append("Cayley: Landing all UAV to closest post office.");
            for (int i=1; i<=mainIndex-1; i++) {
                temp3 = getLatLng(i);
                int j = closestUSPS(temp3);
                if (destinationArray[i] == USPSName[j]) {
                }
                else {
                    destinationArray[i] = USPSName[j];
                    emerg[i] = true;
                    reroute(i, USPSName[j]);
                }
            }
        }
        else if (responseYellow == true) {
            voce::synthesize("Returning all U A V to origin.");
            ui->textBrowser_11->append("Cayley: Returning all UAV to origin.");
            for (int i=1; i<=mainIndex-1; i++) {
                if (destinationArray[i] == originArray[i]) {
                }
                else {
                    destinationArray[i] = originArray[i];
                    emerg[i] = true;
                    reroute(i, originArray[i]);
                    start(i, originArray[i]);
                }
            }
        }
    }
    else if (heardList[0] == "no") {
        if (responseRed == true) {
            voce::synthesize("Code red aborted.");
            ui->textBrowser_11->append("Cayley: Code red aborted.");
        }
        else if (responseYellow == true) {
            voce::synthesize("Code yellow aborted.");
            ui->textBrowser_11->append("Cayley: Code yellow aborted.");
        }
    }
    }

    if (heardList[0] != "code") {
        responseRed = false;
        responseYellow = false;
    }
}

int MainWindow::numStringToInt(QString num)
{
    if (num == "one") {
        return 1;
    }
    else if (num == "two") {
        return 2;
    }
    else if (num == "three") {
        return 3;
    }
    else if (num == "four") {
        return 4;
    }
    else if (num == "five") {
        return 5;
    }
    else if (num == "six") {
        return 6;
    }
    else if (num == "seven") {
        return 7;
    }
    else if (num == "eight") {
        return 8;
    }
    else if (num == "nine") {
        return 9;
    }
    else
        return 0;
}

// END VOCE Functions ================================================================================================

// BEGIN UI Functions ================================================================================================

void MainWindow::onTalkPressed()
{
    ui->pushButton_11->setStyleSheet("background-color: #33ff00;");
    voce::stopSynthesizing();
    if (voce::isRecognizerEnabled() == false) {
        voce::setRecognizerEnabled(true);
    }
}

void MainWindow::lag() // makes up for VOCE lag in recognizing what you said.
{
    QTimer::singleShot(1500, this, SLOT(onTalkReleased()));
}

void MainWindow::onTalkReleased()
{
    ui->pushButton_11->setStyleSheet("background-color: #9FF781;");
    s = voce::popRecognizedString();
    if (voce::isRecognizerEnabled() == true) {
        voce::setRecognizerEnabled(false);
    }
    voce::stopSynthesizing();

    if (s.empty() == false)
    {
        ui->textBrowser_11->append("<span style = 'color: #FAFAFA'>ATC: " + QString::fromStdString(s) + "</span>");
        manipString(QString::fromStdString(s));
    }
    else
    {
        voce::synthesize("Command not heard.");
    }
}

void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString timeString = time.toString("HH:mm");
    ui->lcdNumber_4->display(timeString);
}

void MainWindow::onMapLoaded()
{
    ui->progressBar->hide();
    ui->webView_4->show();
    ui->webView_4->page()->mainFrame()->addToJavaScriptWindowObject("JSBridge", this);
    connect(ui->pushButton_11, SIGNAL(pressed()), this, SLOT(onTalkPressed()));
    connect(ui->pushButton_11, SIGNAL(released()), this, SLOT(lag()));
    voce::synthesize("Welcome aboard. Please state your name.");

    // Launch Initial UAVs (string name, string origin, string destination, string speed in mph, int index number, int fuel level).
    addUAV("UAV1", "Van Nuys", "Porter Ranch", 900, mainIndex, 12);
    addUAV("UAV2", "Van Nuys", "West Hills", 700, mainIndex, 49);
    addUAV("UAV3", "Van Nuys", "Calabasas", 700, mainIndex, 95);
    addUAV("UAV4", "Van Nuys", "Studio City", 700, mainIndex, 63);
    addUAV("UAV5", "Van Nuys", "Downtown Burbank", 1500, mainIndex, 60);
    addUAV("UAV6", "Van Nuys", "San Fernando", 1200, mainIndex, 60);

    player->setMedia(QUrl::fromLocalFile("C:/Users/Ernest Curioso/Documents/Qt Projects/UAVProject/UAVProject/sounds/Alert.mp3"));

    //UAV UAV1 ("UAV1", "Van Nuys", "Canoga Park", 700, mainIndex, 12);
    //addUAV(UAV1.getName(), UAV1.getOrigin(), UAV1.getDestination(), UAV1.getSpeed(), UAV1.getMainIndex(), UAV1.getBattery());
}

void MainWindow::addUAV(QString name, QString origin, QString destination, int speed, int index, int fuelLevel)
{
    QString path;

    for (int i=0; i<=30; i++) {
        if (origin == USPSName[i]) {
            for (int j=0; j<=30; j++) {
                if (destination == USPSName[j]) {
                    path = "[[" + USPSLatLng[i] + "],[" + USPSLatLng[j] + "]]";
                }
            }
        }
    }

    int timeInterval = calculate::speedToTimeInterval(speed, path);
    originArray[index] = origin;
    speedArray[index] = speed;
    destinationArray[index] = destination;

    ui->webView_4->page()->mainFrame()->evaluateJavaScript("addUAV('" + name + "', " + path + ", " + QString::number(timeInterval) + ");");

    fuel[index] = fuelLevel;
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

    connect(timer4, &QTimer::timeout, this, [=]{ avoidCheck(index); });
    connect(timer3, &QTimer::timeout, this, [=]{ fuelSim(name, index); });

    // Timer for live update of UAV info ie latlong values
    connect(timer2, &QTimer::timeout, this, [=]{ showInfo(name, index); });
    timer2->start(250);

    mainIndex++;
}

// Simulates constant fuel decrementation
void MainWindow::fuelSim(QString name, int index)
{
    bool stopped = isStopped(index);
;
    if (stopped == false) {
        fuel[index]--;
    }
    else {
        emerg[index] = false;
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
        player->play();
        ui->webView_4->page()->mainFrame()->evaluateJavaScript("popup('" + QString::number(index) + "', 'Battery at 20%');");

        ui->textBrowser_11->append("<br><span style= 'color: #FA5858'>" + name + " ALERT!<br>Low Battery at 20%. <br>Will emergency land at nearest USPS at 10%.</span><br>");
        voce::synthesize("U A V" + QString::number(index).toStdString() + "Low Battery at 20%");

        fuel[index]--;
    }
    else if (fuel[index] == 10){
        showUAVWindow(name, index);
        player->play();
        ui->webView_4->page()->mainFrame()->evaluateJavaScript("popup('" + QString::number(index) + "', 'Emergency Landing!');");

        temp = getLatLng(index);
        i = closestUSPS(temp);
        destinationArray[index] = USPSName[i];

        emerg[index] = true;

        ui->textBrowser_11->append("<br><span style= 'color: #FA5858'>" + name + " ALERT!" +
                        "<br>Low Battery at 10% <br>"
                        "Emergency landing at " + USPSName[i] + " post office.</span><br>");
        voce::synthesize("U A V" + QString::number(index).toStdString() + "Low Battery at 10%. Emergency landing at" + USPSName[i].toStdString() + "post office.");

        reroute(index, USPSName[i]);

        fuel[index]--;
    }
    else if (fuel[index] == 2) {
        showUAVWindow(name, index);
        player->play();
        ui->webView_4->page()->mainFrame()->evaluateJavaScript("popup('" + QString::number(index) + "', 'Unexpected landing.');");

        emerg[index] = true;

        ui->textBrowser_11->append("<span style= 'color: #FA5858'><br>" + name + " ALERT!" +
                        "<br>Did not make it to nearest USPS. <br>" +
                        "Landed at current location.</span><br>");

        voce::synthesize("U A V" + QString::number(index).toStdString() + "did not make it to the nearest U S P S. Landed at current location.");


        ui->webView_4->page()->mainFrame()->evaluateJavaScript("stopFlight('" + name + "');");

        fuel[index]--;
    }
}

// Determines closest USPS for given latlng
int MainWindow::closestUSPS(QString latlng)
{

    QRegExp rx ("[(),]");
    QStringList list = latlng.split(rx, QString::SkipEmptyParts);
    QString lat = list.at(1);
    QString lng = list.at(2);

    QString lat2;
    QString lng2;
    QStringList list2;

    QString path;

    double dist = 1000000;
    double temp;
    int position = 0;

    for (int i=0; i<=30; i++) {
        list2 = USPSLatLng[i].split(rx, QString::SkipEmptyParts);
        lat2 = list2.at(0);
        lng2 = list2.at(1);

        path = "[[" + lat + "," + lng + "],[" + lat2 + "," + lng2 + "]]";
        temp = calculate::distanceInMiles(path);

        if (temp < dist) {
            dist = temp;
            position = i;
        }
    }

    return position;
}

// Getter for latlng. Returns string "LatLng([latValue],[longValue])
QString MainWindow::getLatLng(int index)
{
    QVariant a = ui->webView_4->page()->mainFrame()->evaluateJavaScript("getLatLng('" + QString::number(index) +  "');");
    return a.toString();
}

// Shows UAV Window
void MainWindow::showUAVWindow(QString name, int index)
{
    // Turns uav window original after half a second of being red.
    QTimer::singleShot(500, this, [=]{ setDefaultColor(index); });

    ui->closeAllButton->show();
    connect(ui->closeAllButton, SIGNAL(pressed()), ui->scrollArea, SLOT(hide()));
    connect(ui->closeAllButton, SIGNAL(pressed()), ui->closeAllButton, SLOT(hide()));

    // Shows/hides UAV box UI elements    
    if (index == 1){
        ui->scrollArea->show();
        ui->scrollArea->ensureWidgetVisible(ui->label_1);
        ui->scrollArea->ensureWidgetVisible(ui->progressBar_1);
        ui->textBrowser->show();
        ui->pushButton->show();
        ui->progressBar_1->show();
        ui->line_1->show();
        ui->label_1->show();
        ui->label_1->setText(name);
        ui->label_1->setStyleSheet("color: #FF0000;");
        ui->textBrowser->setStyleSheet("background-color: #FF0000;");
        connect(ui->pushButton, SIGNAL(pressed()), ui->textBrowser, SLOT(hide()));
        connect(ui->pushButton, SIGNAL(pressed()), ui->pushButton, SLOT(hide()));
        connect(ui->pushButton, SIGNAL(pressed()), ui->progressBar_1, SLOT(hide()));
        connect(ui->pushButton, SIGNAL(pressed()), ui->line_1, SLOT(hide()));
        connect(ui->pushButton, SIGNAL(pressed()), ui->label_1, SLOT(hide()));

        ui->focusButton_1->show();
        connect(ui->pushButton, SIGNAL(pressed()), ui->focusButton_1, SLOT(hide()));
        connect(ui->focusButton_1, &QPushButton::pressed, this, [=]{ focus(index); });
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
        ui->label_2->setStyleSheet("color: #FF0000;");
        ui->textBrowser_2->setStyleSheet("background-color: #FF0000;");
        connect(ui->pushButton_2, SIGNAL(pressed()), ui->textBrowser_2, SLOT(hide()));
        connect(ui->pushButton_2, SIGNAL(pressed()), ui->pushButton_2, SLOT(hide()));
        connect(ui->pushButton_2, SIGNAL(pressed()), ui->progressBar_2, SLOT(hide()));
        connect(ui->pushButton_2, SIGNAL(pressed()), ui->line_2, SLOT(hide()));
        connect(ui->pushButton_2, SIGNAL(pressed()), ui->label_2, SLOT(hide()));

        ui->focusButton_2->show();
        connect(ui->pushButton_2, SIGNAL(pressed()), ui->focusButton_2, SLOT(hide()));
        connect(ui->focusButton_2, &QPushButton::pressed, this, [=]{ focus(index); });
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
        ui->label_3->setStyleSheet("color: #FF0000;");
        ui->textBrowser_3->setStyleSheet("background-color: #FF0000;");
        connect(ui->pushButton_3, SIGNAL(pressed()), ui->textBrowser_3, SLOT(hide()));
        connect(ui->pushButton_3, SIGNAL(pressed()), ui->pushButton_3, SLOT(hide()));
        connect(ui->pushButton_3, SIGNAL(pressed()), ui->progressBar_3, SLOT(hide()));
        connect(ui->pushButton_3, SIGNAL(pressed()), ui->line_3, SLOT(hide()));
        connect(ui->pushButton_3, SIGNAL(pressed()), ui->label_3, SLOT(hide()));

        ui->focusButton_3->show();
        connect(ui->pushButton_3, SIGNAL(pressed()), ui->focusButton_3, SLOT(hide()));
        connect(ui->focusButton_3, &QPushButton::pressed, this, [=]{ focus(index); });
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
        ui->label_4->setStyleSheet("color: #FF0000;");
        ui->textBrowser_4->setStyleSheet("background-color: #FF0000;");
        connect(ui->pushButton_4, SIGNAL(pressed()), ui->textBrowser_4, SLOT(hide()));
        connect(ui->pushButton_4, SIGNAL(pressed()), ui->pushButton_4, SLOT(hide()));
        connect(ui->pushButton_4, SIGNAL(pressed()), ui->progressBar_4, SLOT(hide()));
        connect(ui->pushButton_4, SIGNAL(pressed()), ui->line_4, SLOT(hide()));
        connect(ui->pushButton_4, SIGNAL(pressed()), ui->label_4, SLOT(hide()));

        ui->focusButton_4->show();
        connect(ui->pushButton_4, SIGNAL(pressed()), ui->focusButton_4, SLOT(hide()));
        connect(ui->focusButton_4, &QPushButton::pressed, this, [=]{ focus(index); });
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
        ui->label_5->setStyleSheet("color: #FF0000;");
        ui->textBrowser_5->setStyleSheet("background-color: #FF0000;");
        connect(ui->pushButton_5, SIGNAL(pressed()), ui->textBrowser_5, SLOT(hide()));
        connect(ui->pushButton_5, SIGNAL(pressed()), ui->pushButton_5, SLOT(hide()));
        connect(ui->pushButton_5, SIGNAL(pressed()), ui->progressBar_5, SLOT(hide()));
        connect(ui->pushButton_5, SIGNAL(pressed()), ui->line_5, SLOT(hide()));
        connect(ui->pushButton_5, SIGNAL(pressed()), ui->label_5, SLOT(hide()));

        ui->focusButton_5->show();
        connect(ui->pushButton_5, SIGNAL(pressed()), ui->focusButton_5, SLOT(hide()));
        connect(ui->focusButton_5, &QPushButton::pressed, this, [=]{ focus(index); });
    }
    else if (index == 6){
        ui->scrollArea->ensureWidgetVisible(ui->label_6);
        ui->scrollArea->ensureWidgetVisible(ui->progressBar_6);
        ui->scrollArea->show();
        ui->textBrowser_6->show();
        ui->pushButton_6->show();
        ui->progressBar_6->show();
        ui->line_6->show();
        ui->label_6->show();
        ui->label_6->setText(name);
        ui->label_6->setStyleSheet("color: #FF0000;");
        ui->textBrowser_6->setStyleSheet("background-color: #FF0000;");
        connect(ui->pushButton_6, SIGNAL(pressed()), ui->textBrowser_6, SLOT(hide()));
        connect(ui->pushButton_6, SIGNAL(pressed()), ui->pushButton_6, SLOT(hide()));
        connect(ui->pushButton_6, SIGNAL(pressed()), ui->progressBar_6, SLOT(hide()));
        connect(ui->pushButton_6, SIGNAL(pressed()), ui->line_6, SLOT(hide()));
        connect(ui->pushButton_6, SIGNAL(pressed()), ui->label_6, SLOT(hide()));

        ui->focusButton_6->show();
        connect(ui->pushButton_6, SIGNAL(pressed()), ui->focusButton_6, SLOT(hide()));
        connect(ui->focusButton_6, &QPushButton::pressed, this, [=]{ focus(index); });
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
        ui->label_7->setStyleSheet("color: #FF0000;");
        ui->textBrowser_7->setStyleSheet("background-color: #FF0000;");
        connect(ui->pushButton_7, SIGNAL(pressed()), ui->textBrowser_7, SLOT(hide()));
        connect(ui->pushButton_7, SIGNAL(pressed()), ui->pushButton_7, SLOT(hide()));
        connect(ui->pushButton_7, SIGNAL(pressed()), ui->progressBar_7, SLOT(hide()));
        connect(ui->pushButton_7, SIGNAL(pressed()), ui->line_7, SLOT(hide()));
        connect(ui->pushButton_7, SIGNAL(pressed()), ui->label_7, SLOT(hide()));

        ui->focusButton_7->show();
        connect(ui->pushButton_7, SIGNAL(pressed()), ui->focusButton_7, SLOT(hide()));
        connect(ui->focusButton_7, &QPushButton::pressed, this, [=]{ focus(index); });
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
        ui->label_8->setStyleSheet("color: #FF0000;");
        ui->textBrowser_8->setStyleSheet("background-color: #FF0000;");
        connect(ui->pushButton_8, SIGNAL(pressed()), ui->textBrowser_8, SLOT(hide()));
        connect(ui->pushButton_8, SIGNAL(pressed()), ui->pushButton_8, SLOT(hide()));
        connect(ui->pushButton_8, SIGNAL(pressed()), ui->progressBar_8, SLOT(hide()));
        connect(ui->pushButton_8, SIGNAL(pressed()), ui->line_8, SLOT(hide()));
        connect(ui->pushButton_8, SIGNAL(pressed()), ui->label_8, SLOT(hide()));

        ui->focusButton_8->show();
        connect(ui->pushButton_8, SIGNAL(pressed()), ui->focusButton_8, SLOT(hide()));
        connect(ui->focusButton_8, &QPushButton::pressed, this, [=]{ focus(index); });
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
        ui->label_9->setStyleSheet("color: #FF0000;");
        ui->textBrowser_9->setStyleSheet("background-color: #FF0000;");
        connect(ui->pushButton_9, SIGNAL(pressed()), ui->textBrowser_9, SLOT(hide()));
        connect(ui->pushButton_9, SIGNAL(pressed()), ui->pushButton_9, SLOT(hide()));
        connect(ui->pushButton_9, SIGNAL(pressed()), ui->progressBar_9, SLOT(hide()));
        connect(ui->pushButton_9, SIGNAL(pressed()), ui->line_9, SLOT(hide()));
        connect(ui->pushButton_9, SIGNAL(pressed()), ui->label_9, SLOT(hide()));

        ui->focusButton_9->show();
        connect(ui->pushButton_9, SIGNAL(pressed()), ui->focusButton_9, SLOT(hide()));
        connect(ui->focusButton_9, &QPushButton::pressed, this, [=]{ focus(index); });
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
        ui->label_10->setStyleSheet("color: #FF0000;");
        ui->textBrowser_10->setStyleSheet("background-color: #FF0000;");
        connect(ui->pushButton_10, SIGNAL(pressed()), ui->textBrowser_10, SLOT(hide()));
        connect(ui->pushButton_10, SIGNAL(pressed()), ui->pushButton_10, SLOT(hide()));
        connect(ui->pushButton_10, SIGNAL(pressed()), ui->progressBar_10, SLOT(hide()));
        //connect(ui->pushButton_10, SIGNAL(pressed()), ui->line_10, SLOT(hide()));
        connect(ui->pushButton_10, SIGNAL(pressed()), ui->label_10, SLOT(hide()));

        ui->focusButton_10->show();
        connect(ui->pushButton_10, SIGNAL(pressed()), ui->focusButton_10, SLOT(hide()));
        connect(ui->focusButton_10, &QPushButton::pressed, this, [=]{ focus(index); });
    }
}

// Live update of information within UAV Window.
void MainWindow::showInfo(QString name, int index)
{
    //ui->textBrowser_11->append(USPSName[0]);
    QVariant a = ui->webView_4->page()->mainFrame()->evaluateJavaScript("getLatLng('" + QString::number(index) +  "');");
    QVariant started = ui->webView_4->page()->mainFrame()->evaluateJavaScript("isStarted('" + name +  "');");
    QVariant running = ui->webView_4->page()->mainFrame()->evaluateJavaScript("isRunning('" + name +  "');");
    QVariant paused = ui->webView_4->page()->mainFrame()->evaluateJavaScript("isPaused('" + name +  "');");
    bool stopped = isStopped(index);
    QVariant f = ui->webView_4->page()->mainFrame()->evaluateJavaScript("getUAVIndexFromName('" + name + "');");
    int g = f.toInt();

    // Mission and status levels
    if (running == true && emerg[g] == false){
        status[g] = "En Route";
        mission[g] = "In Progress";
    }
    else if (paused == true && emerg[g] == false) {
        status[g] = "En Route - Hovering in place";
        mission[g] = "In progress";
    }
    else if (stopped == true && emerg[g] == false) {
        status[g] = "Landed at destination";
        mission[g] = "Complete";
    }
    else if (emerg[g] == true && running == true) {
        status[g] = "Emergency landing in progress";
        mission[g] = "Aborting";
    }
    else if (emerg[g] == true && stopped == true) {
        status[g] = "Emergency landed";
        mission[g] = "Incomplete - Aborted";
    }

    //Displays live update.
    if (name == "UAV1") {
        ui->textBrowser->setText("MISSION STATUS: " + mission[g] + "<br><br>" +
                                 "UAV STATUS: " + status[g] + "<br><br>" +
                                 "DESTINATION: " + destinationArray[index] + "<br><br>" +
                                 "SPEED: " + QString::number(speedArray[index]) + " MPH<br><br>" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV2") {
        ui->textBrowser_2->setText("MISSION STATUS: " + mission[g] + "<br><br>" +
                                 "UAV STATUS: " + status[g] + "<br><br>" +
                                   "DESTINATION: " + destinationArray[index] + "<br><br>" +
                                 "SPEED: " + QString::number(speedArray[index]) + " MPH<br><br>" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV3") {
        ui->textBrowser_3->setText("MISSION STATUS: " + mission[g] + "<br><br>" +
                                 "UAV STATUS: " + status[g] + "<br><br>" +
                                   "DESTINATION: " + destinationArray[index] + "<br><br>" +
                                   "SPEED: " + QString::number(speedArray[index]) + " MPH<br><br>" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV4") {
        ui->textBrowser_4->setText("MISSION STATUS: " + mission[g] + "<br><br>" +
                                 "UAV STATUS: " + status[g] + "<br><br>" +
                                   "DESTINATION: " + destinationArray[index] + "<br><br>" +
                                   "SPEED: " + QString::number(speedArray[index]) + " MPH<br><br>" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV5") {
        ui->textBrowser_5->setText("MISSION STATUS: " + mission[g] + "<br><br>" +
                                 "UAV STATUS: " + status[g] + "<br><br>" +
                                   "DESTINATION: " + destinationArray[index] + "<br><br>" +
                                   "SPEED: " + QString::number(speedArray[index]) + " MPH<br><br>" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV6") {
        ui->textBrowser_6->setText("MISSION STATUS: " + mission[g] + "<br><br>" +
                                 "UAV STATUS: " + status[g] + "<br><br>" +
                                   "DESTINATION: " + destinationArray[index] + "<br><br>" +
                                   "SPEED: " + QString::number(speedArray[index]) + " MPH<br><br>" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV7") {
        ui->textBrowser_7->setText("MISSION STATUS: " + mission[g] + "<br><br>" +
                                 "UAV STATUS: " + status[g] + "<br><br>" +
                                   "DESTINATION: " + destinationArray[index] + "<br><br>" +
                                   "SPEED: " + QString::number(speedArray[index]) + " MPH<br><br>" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV8") {
        ui->textBrowser_8->setText("MISSION STATUS: " + mission[g] + "<br><br>" +
                                 "UAV STATUS: " + status[g] + "<br><br>" +
                                   "DESTINATION: " + destinationArray[index] + "<br><br>" +
                                   "SPEED: " + QString::number(speedArray[index]) + " MPH<br><br>" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV9") {
        ui->textBrowser_9->setText("MISSION STATUS: " + mission[g] + "<br><br>" +
                                 "UAV STATUS: " + status[g] + "<br><br>" +
                                   "DESTINATION: " + destinationArray[index] + "<br><br>" +
                                   "SPEED: " + QString::number(speedArray[index]) + " MPH<br><br>" +
                                 "LOCATION: " + a.toString());
    }
    else if (name == "UAV10") {
        ui->textBrowser_10->setText("MISSION STATUS: " + mission[g] + "<br><br>" +
                                 "UAV STATUS: " + status[g] + "<br><br>" +
                                    "DESTINATION: " + destinationArray[index] + "<br><br>" +
                                    "SPEED: " + QString::number(speedArray[index]) + " MPH<br><br>" +
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
        ui->closeAllButton->hide();
    }
}

void MainWindow::avoidCheck(int index)
{
    QString temp = getLatLng(index);

    QRegExp rx ("[(),]");
    QStringList list = temp.split(rx, QString::SkipEmptyParts);
    QString latString = list.at(1);
    QString lngString = list.at(2);
    double lat = latString.toDouble();
    double lng = lngString.toDouble();

    if (lat < 34.224 && lat > 34.190 && lng < -118.479 && lng > -118.501) {
        avoidVanNuysAirport(lat, lng, index);
        timer4->stop();
        QTimer::singleShot(1000, this, [=]{ timer4->start(100); });
    }
}

void MainWindow::avoidVanNuysAirport(double lat, double lng, int index)
{
    QString path1;
    QString path2;
    double dist1;
    double dist2;

    connect(timer5, &QTimer::timeout, this, [=]{ atVNACorner(index); });
    timer5->start(250);

    if (lat < 34.224 && lat > 34.222) {
        for (int i = 0; i<=30; i++) {
            if (destinationArray[index] == USPSName[i]) {
                path1 = "[[34.226,-118.477],[" + USPSLatLng[i] + "]]";
                path2 = "[[34.226,-118.503],[" + USPSLatLng[i] + "]]";
            }
        }

        dist1 = calculate::distanceInMiles(path1);
        dist2 = calculate::distanceInMiles(path2);

        if (dist1 < dist2) {
            reroute(index, "34.226,-118.477");
        }
        else {
            reroute(index, "34.226,-118.503");
        }
    }

    else if (lat > 34.190 && lat < 34.192) {
        for (int i = 0; i<=30; i++) {
            if (destinationArray[index] == USPSName[i]) {
                path1 = "[[34.188,-118.477],[" + USPSLatLng[i] + "]]";
                path2 = "[[34.188,-118.503],[" + USPSLatLng[i] + "]]";
            }
        }

        dist1 = calculate::distanceInMiles(path1);
        dist2 = calculate::distanceInMiles(path2);

        if (dist1 < dist2) {
            reroute(index, "34.188,-118.477");
        }
        else {
            reroute(index, "34.188,-118.503");
        }
    }
    else if (lng > -118.501 && lng < -118.499) {
        for (int i = 0; i<=30; i++) {
            if (destinationArray[index] == USPSName[i]) {
                path1 = "[[34.226,-118.503],[" + USPSLatLng[i] + "]]";
                path2 = "[[34.188,-118.503],[" + USPSLatLng[i] + "]]";
            }
        }

        dist1 = calculate::distanceInMiles(path1);
        dist2 = calculate::distanceInMiles(path2);

        if (dist1 < dist2) {
            reroute(index, "34.226,-118.503");
        }
        else {
            reroute(index, "34.188,-118.503");
        }
    }
    else if (lng < -118.479 && lng > -118.481) {
        for (int i = 0; i<=30; i++) {
            if (destinationArray[index] == USPSName[i]) {
                path1 = "[[34.226,-118.477],[" + USPSLatLng[i] + "]]";
                path2 = "[[34.188,-118.477],[" + USPSLatLng[i] + "]]";
            }
        }

        dist1 = calculate::distanceInMiles(path1);
        dist2 = calculate::distanceInMiles(path2);

        if (dist1 < dist2) {
            reroute(index, "34.226,-118.477");
        }
        else {
            reroute(index, "34.188,-118.477");
        }
    }
}

void MainWindow::atVNACorner(int index)
{
    double currentLat;
    double currentLng;
    QString currentLatLng;

    currentLatLng = getLatLng(index);
    QRegExp rx ("[(),]");
    QStringList list = currentLatLng.split(rx, QString::SkipEmptyParts);
    QString latString = list.at(1);
    QString lngString = list.at(2);
    currentLat = latString.toDouble();
    currentLng = lngString.toDouble();

    if ((currentLat > 34.224 && currentLat < 34.228 && currentLng < -118.501 && currentLng > -118.505) ||
        (currentLat > 34.224 && currentLat < 34.228 && currentLng > -118.479 && currentLng < -118.475) ||
        (currentLat < 34.190 && currentLat > 34.186 && currentLng > -118.479 && currentLng < -118.475) ||
        (currentLat < 34.190 && currentLat > 34.186 && currentLng < -118.501 && currentLng > -118.505)) {

        if (emerg[index] == false) {
            for (int i = 0; i<=30; i++) {
                if (destinationArray[index] == USPSName[i]) {
                    reroute(index, USPSLatLng[i]);
                    //ui->webView_4->page()->mainFrame()->evaluateJavaScript("reroute(" + QString::number(index) + ", [" + USPSLatLng[i] + "], 7000);");
                }
            }
        }
        else {
            for (int i = 0; i<=30; i++) {
                if (destinationArray[index] == USPSName[i]) {
                    reroute(index, USPSLatLng[i]);
                    //ui->webView_4->page()->mainFrame()->evaluateJavaScript("reroute(" + QString::number(index) + ", [" + USPSLatLng[i] + "], 7000);");
                }
            }
        }
    }
}

void MainWindow::setDefaultColor(int index)
{
    if (index == 1) {
        ui->textBrowser->setStyleSheet("background-color: #E6E6E6;");
        ui->label_1->setStyleSheet("color: #E6E6E6;");
    }
    else if (index == 2) {
        ui->textBrowser_2->setStyleSheet("background-color: #E6E6E6;");
        ui->label_2->setStyleSheet("color: #E6E6E6;");
    }
    else if (index == 3) {
        ui->textBrowser_3->setStyleSheet("background-color: #E6E6E6;");
        ui->label_3->setStyleSheet("color: #E6E6E6;");
    }
    else if (index == 4) {
        ui->textBrowser_4->setStyleSheet("background-color: #E6E6E6;");
        ui->label_4->setStyleSheet("color: #E6E6E6;");
    }
    else if (index == 5) {
        ui->textBrowser_5->setStyleSheet("background-color: #E6E6E6;");
        ui->label_5->setStyleSheet("color: #E6E6E6;");
    }
    else if (index == 6) {
        ui->textBrowser_6->setStyleSheet("background-color: #E6E6E6;");
        ui->label_6->setStyleSheet("color: #E6E6E6;");
    }
    else if (index == 7) {
        ui->textBrowser_7->setStyleSheet("background-color: #E6E6E6;");
        ui->label_7->setStyleSheet("color: #E6E6E6;");
    }
    else if (index == 8) {
        ui->textBrowser_8->setStyleSheet("background-color: #E6E6E6;");
        ui->label_8->setStyleSheet("color: #E6E6E6;");
    }
    else if (index == 9) {
        ui->textBrowser_9->setStyleSheet("background-color: #E6E6E6;");
        ui->label_9->setStyleSheet("color: #E6E6E6;");
    }
    else if (index == 10) {
        ui->textBrowser_10->setStyleSheet("background-color: #E6E6E6;");
        ui->label_10->setStyleSheet("color: #E6E6E6;");
    }
}

void MainWindow::focus(int index)
{
    QString temp = getLatLng(index);

    QRegExp rx ("[(),]");
    QStringList list = temp.split(rx, QString::SkipEmptyParts);
    QString lat = list.at(1);
    QString lng = list.at(2);

    ui->webView_4->page()->mainFrame()->evaluateJavaScript("focus('" + lat + "','" + lng + "');");
}

void MainWindow::reroute(int index, QString newDestination)
{
    QString latlng = getLatLng(index);
    QRegExp rx ("[(),]");
    QStringList list = latlng.split(rx, QString::SkipEmptyParts);
    QString lat = list.at(1);
    QString lng = list.at(2);

    for (int i=0; i<=30; i++) {
        if (newDestination == USPSName[i]) {
            newDestination = USPSLatLng[i];
        }
    }

    QString path = "[[" + lat + "," + lng + "],[" + newDestination + "]]";
    int speed = speedArray[index];
    int timeInterval = calculate::speedToTimeInterval(speed, path);
    ui->webView_4->page()->mainFrame()->evaluateJavaScript("reroute(" + QString::number(index) + ", [" + newDestination + "], " + QString::number(timeInterval) + ");");
}

void MainWindow::start(int index, QString destination) {
    QString current = getLatLng(index);
    QRegExp rx ("[(),]");
    QStringList list = current.split(rx, QString::SkipEmptyParts);
    QString lat = list.at(1);
    QString lng = list.at(2);

    QString path;

    for (int i=0; i<=30; i++) {

        if (destination == USPSName[i]) {
            path = "[[" + lat + "," + lng + "],[" + USPSLatLng[i] + "]]";
        }
    }

    ui->webView_4->page()->mainFrame()->evaluateJavaScript("startFlight(" + QString::number(index) + ");");
}

bool MainWindow::isStopped(int index)
{
    QVariant stopped = ui->webView_4->page()->mainFrame()->evaluateJavaScript("isStopped(" + QString::number(index) +  ");");
    if (stopped == true) {
        return true;
    }
    else {
        return false;
    }
}

// END UI Functions =====================================================================================================
