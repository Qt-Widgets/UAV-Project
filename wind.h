#ifndef WIND_H
#define WIND_H

#include <QtCore>

using namespace std;

class Wind : public QObject
{
	Q_OBJECT
private:
	int degree;
	float speed;

public:
	Wind();

public slots: 
	int getDegree(wind); 
	int getSpeed(wind); 
	int triggerGale(wind); 
	int updateWind(wind);

};

#endif // WIND_H