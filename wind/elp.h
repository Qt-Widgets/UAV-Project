#ifndef ELP_H
#define ELP_H

#include <QtCore>

class ELP : public QObject
{
	Q_OBJECT
public:
	bool emergency; 
	int severity;

public slots:
	double getdestXcord();
	double getdestYcord();
	double getuavXcord();
	double getuavYcord();
};

#endif //ELP_H