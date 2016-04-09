#ifndef CALCULATE_H
#define CALCULATE_H

#include <QObject>

class calculate
{
public:
    static int speedToTimeInterval(int speed, QString path);
    static double distToUSPS(QString path);
};

#endif // CALCULATE_H
