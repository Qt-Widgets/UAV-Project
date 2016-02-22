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
	bool gale;

public:
	Wind();

public slots: 
	int getDegree(); 
	int getSpeed(); 
	int triggerGale(); 
	int updateWind();

};

#endif // WIND_H