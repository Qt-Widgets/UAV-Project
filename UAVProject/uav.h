#ifndef UAV_H
#define UAV_H

#include <QObject>

class UAV
{ 
public:
    UAV(QString name, QString origin, QString destination, int speed, int mainIndex, int battery);
    QString getName();
    void setName(QString name);
    QString getOrigin();
    void setOrigin(QString origin);
    QString getDestination();
    void setDestination(QString destination);
    int getSpeed();
    void setSpeed(int speed);
    int getMainIndex();
    void setMainIndex(int mainIndex);
    int getBattery();
    void setBattery(int battery);

private:
    QString UAVname;
    QString UAVorigin;
    QString UAVdestination;
    int UAVspeed;
    int UAVmainIndex;
    int UAVbattery;
};

#endif // UAV_H
