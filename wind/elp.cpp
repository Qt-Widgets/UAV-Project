#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
//#include <wind.h>

using namespace std;

double batteryPercent;//this will be replaced with a UAV call

double destXcord;//destination coodinates
double destYcord;//destination coodinates

double uavXcord; //current UAV coodinates
double uavYcord; //current UAV coodinates
/*We are going to need a list of the coodinates of safe landing locations*/


ELP::distance(double x1, double y1, double x2, double y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

double getdestXcord()
{
	return getdestXcord;
}
double getdestYcord()
{
	return getdestYcord;
}
double getuavXcord()
{
	return getuavXcord;
}
double getuavYcord()
{
	return getuavYcord;
}

ELP::enoughPower()
{
	int mpp;//this is the amount of distance we can expect per percent of battery remaining.
	//stands for miles per percent	
	if(distance(destXcord, destYcord, uavXcord, uavYcord) > batteryPercent * mpp)
	{
		return false;
	}
	else
	{
		return true;
	}
}

ELP::droneDamage()
{//need timer
	bool damage = false;
	int severity = 0;
	int per = rand() % 100;
	if(per < 99)
	{
		damage = true;
		severity = rand() % 5 + 1;
	}
	return damage;
}


ELP::emergency()
{
	if(enoughPower() == false)
	{
		return true;
	}
	//else if(w.gale)
	//{
	//	return true;
	//}
	else if(droneDamage())
	{
		return true;
	}
	else
	{
		return false;
	}
}

