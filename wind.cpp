#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

Wind::Wind()
{
	int degree;
	float speed;
	bool gale;
}


Wind::initWind(wind a)
{
	a.degree = rand() % 360 + 1;
	a.speed = rand() % 10 + 1;
	a.gale = false;
	
}

Wind::triggerGale(wind a)
{
	a.speed = 30;
	a.gale = true;
}

Wind::updateWind(wind a)
{
	int hold = rand() % 100;
	cout << hold;
	cout << "\n";
	bool pos;
	int change;
	if(hold % 2 == 0)
	{//determin if wind is changeing or not
		pos = true;
	}
	else
	{
		pos = false;
	}
	
	if(hold < 50)
	{//determin speed of change in wind
		cout << "50 speed";
		cout << "\n";
		change = 1;
	}
	else if(hold < 75)
	{
		cout << "75 speed";
		cout << "\n";
		change = 2;
	}
	else if(hold < 90)
	{
		cout << "90 speed";
		cout << "\n";
		change = 3;
	}
	else if(hold < 95)
	{
		cout << "95 speed";
		cout << "\n";
		change = 4;
	}
	else
	{
		cout << hold;
		cout << "\n";
		change = 5;
	}

	if(pos == true)
	{//applies change to wind speed
		a.speed = a.speed + change;
	}
	else
	{
		a.speed = a.speed - change;
	}
	a.speed = abs(a.speed);
	if(a.speed > 20)
	{
		fast = true;
	}
//for change in direction
	hold = rand() %  100;
	if(hold % 2 == 0)
		{pos = true;}
	else
		{pos = false;}
	if(hold < 40)
	{
		if(pos == true)
		{
			a.degree = a.degree + 2;
		} 
		else
		{
			a.degree = a.degree - 2;
		}
	}
	else if(hold < 60)
	{
		if(pos == true)
		{
			a.degree = a.degree + 5;
		} 
		else
		{
			a.degree = a.degree - 5;
		}
	}
	else if(hold < 80)
	{
		if(pos == true)
		{
			a.degree = a.degree + 10;
		} 
		else
		{
			a.degree = a.degree - 10;
		}
	}
	else if(hold < 95)
	{
		if(pos == true)
		{
			a.degree = a.degree + 15;
		} 
		else
		{
			a.degree = a.degree - 15;
		}
	}
	else if(hold < 98)
	{
		if(pos == true)
		{
			a.degree = a.degree + 30;
		} 
		else
		{
			a.degree = a.degree - 30;
		}
	}
	else 
	{
		if(pos == true)
		{
			a.degree = a.degree + 45;
		} 
		else
		{
			a.degree = a.degree - 45;
		}
	}
	a.degree = a.degree % 360;
}

Wind::printWind(Wind a)
{
	cout << a.speed;
	cout << "\n";
	cout << a.degree;
	cout << "\n";
}



