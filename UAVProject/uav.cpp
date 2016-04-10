#include "uav.h"

UAV::UAV(QString name, QString origin, QString destination, int speed, int mainIndex, int battery)
{
    UAVname = name;
    UAVorigin = origin;
    UAVdestination = destination;
    UAVspeed = speed;
    UAVmainIndex = mainIndex;
    UAVbattery = battery;
}

QString UAV::getName()
{
    return UAVname;
}

void UAV::setName(QString name)
{
    UAVname = name;
}

QString UAV::getOrigin()
{
    return UAVorigin;
}

void UAV::setOrigin(QString origin)
{
    UAVorigin = origin;
}

QString UAV::getDestination()
{
    return UAVdestination;
}

void UAV::setDestination(QString destination)
{
    UAVdestination = destination;
}

int UAV::getSpeed()
{
    return UAVspeed;
}

void UAV::setSpeed(int speed)
{
    UAVspeed = speed;
}

int UAV::getMainIndex()
{
    return UAVmainIndex;
}

void UAV::setMainIndex(int mainIndex)
{
    UAVmainIndex = mainIndex;
}

int UAV::getBattery()
{
    return UAVbattery;
}

void UAV::setBattery(int battery)
{
    UAVbattery = battery;
}

