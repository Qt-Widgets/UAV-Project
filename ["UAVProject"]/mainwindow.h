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

    Q_INVOKABLE void showUAVWindow(QString name);


private slots:
    void readSerial();
    void showTime();
    void onMapLoaded();
    void showInfo(QString name);
    void fuelSim(QString name, int fuel);
    //void test(QString name, int fuel);
    int closestUSPS(QString latlng);
    void initialize();
    QString getLatLng(QString name);
    void addUAV(QString name, QString path, QString speed, int fuel, int fuelLevel);

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
};

#endif // MAINWINDOW_H
