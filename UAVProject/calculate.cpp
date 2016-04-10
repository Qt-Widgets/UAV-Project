#include "calculate.h"
#include "mainwindow.h"
#include <QString>
#include <QStringList>
#include <QRegExp>

#define pi 3.14159265358979323846

//converts speed in mph given in adduav parameter to time interval for adding marker parameter in movingmarker.js
int calculate::speedToTimeInterval(int speed, QString path)
{
    double distance = distanceInMiles(path);
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

// Calculates distance to each USPS
double calculate::distanceInMiles(QString path)
{
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
