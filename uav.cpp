#include "uav.h"
#include <QtCore>
#include <QDebug>
#include <QTimer>

using namespace std;

Uav::Uav()
{
    simtime = 0;

    latitude = 0;
    longitude = 0;
    altitude = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
}

Uav::Uav(string destLat, string destLong) //overloaded constructor
{
    simtime = 0;

    latitude = 0;
    longitude = 0;
    altitude = 0;

    destinationLatitude = stod(destLat); //stod converts string to double.  Error check all stod and stoi
    destinationLongitude = stod(destLong);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
}

void Uav::update()
{
    simtime++;//very basic, will be more realistic
    latitude += 10;
    longitude += 20;
    altitude += 100;

    /*qDebug() << "Sim Time: " << simtime;
    qDebug() << "Latitude: " << latitude;
    qDebug() << "Longitude: " << longitude;
    qDebug() << "Altitude: " << altitude;*/
}

void Uav::elp()
{
    //add elp code here

}

//setters and getters:
void Uav::setSimtime(int simtime)
{
    this->simtime = simtime;
}

int Uav::getSimtime()
{
    return simtime;
}

void Uav::setLatitude(int latitude)
{
    this->latitude = latitude;
}

int Uav::getLatitude()
{
    return latitude;
}

void Uav::setLongitude(int longitude)
{
    this->longitude = longitude;
}

int Uav::getLongitude()
{
    return longitude;
}

void Uav::setAltitude(int altitude)
{
    this->altitude = altitude;
}

int Uav::getAltitude()
{
    return altitude;
}

void Uav::setDestinationLatitude(string destinationLatitude)
{
    this->destinationLatitude = stod(destinationLatitude); //should error check
}

double Uav::getDestinationLatitude()
{
    return destinationLatitude;
}

void Uav::setDestinationLongitude(string destinationLongitude)
{
    this->destinationLongitude = stod(destinationLongitude);
}

double Uav::getDestinationLongitude()
{
    return destinationLongitude;
}

void Uav::setDestinationAltitude(string destinationAltitude)
{
    this->destinationAltitude = stoi(destinationAltitude);
}

int Uav::getDestinationAltitude()
{
    return destinationAltitude;
}

