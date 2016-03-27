#ifndef UAV_H
#define UAV_H

#include <QtCore>

using namespace std;

class Uav : public QObject
{
    Q_OBJECT
private:
    int simtime;

    double latitude;
    double longitude;
    int altitude;

    double destinationLatitude;
    double destinationLongitude;
    int destinationAltitude;
public:
    Uav();
    Uav(string, string);
    QTimer *timer;

public slots:
    void update();
    void elp();
    void setSimtime(int);
    int getSimtime();
    void setLatitude(int);
    int getLatitude();
    void setLongitude(int);
    int getLongitude();
    void setAltitude(int);
    int getAltitude();
    void setDestinationLatitude(string);
    double getDestinationLatitude();
    void setDestinationLongitude(string);
    double getDestinationLongitude();
    void setDestinationAltitude(string);
    int getDestinationAltitude();

};

#endif // UAV_H

