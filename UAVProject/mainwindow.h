#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QSerialPort *arduino;
    void setLCD(int x);
    ~MainWindow();

    Q_INVOKABLE void showUAVWindow(QString name, int index);

private slots:
    void readSerial();

    void showTime();
    void onMapLoaded();
    void showInfo(QString name, int index);
    void fuelSim(QString name, int fuel);
    QString getLatLng(int index);
    void addUAV(QString name, QString origin, QString destinatino, int speed, int fuel, int fuelLevel);
    void setDefaultColor(int index);
    void focus(int index);
    int closestUSPS(QString latlng);
    void avoidCheck(int index);
    void avoidVanNuysAirport (double lat, double lng, int index);
    void atVNACorner(int index);

    void onTalkPressed();
    void onTalkReleased();

    void manipString(QString heard);
    int numStringToInt(QString num);
    void lag();

private:
    Ui::MainWindow *ui;
    static const quint16 arduino_uno_vendor_id = 6790;
    static const quint16 arduino_uno_product_id = 29987;
    QString USPSArray[40];
    QString USPSNames[40];
    QString status[11];
    QString mission[11];
    bool emerg[11];
    int fuel[11];
    QString destinationArray[11];
    int speedArray[11];
    int mainIndex = 1;
    std::string s;
    QTimer *timer2 = new QTimer(); // timer for uav info
    QTimer *timer3 = new QTimer(); // timer for fuel simulation
    QTimer *timer4 = new QTimer(); // timer for avoidCheck;
    QTimer *timer5 = new QTimer;

};

#endif // MAINWINDOW_H
