#include "Point.h"
#include <iostream>

using namespace std;

Point::Point() //constructeur, coordonnées par défaut : x=0 et y=0
{
	_x = 0;
	_y = 0;
}

Point::Point(int x, int y) //constructeur
{
	_x = x;
	_y = y;
}

Point::Point(const Point &point) //constructeur par recopie
{

	_x = point._x;
	_y = point._y;
}

Point::~Point() //destructeur
{
	//rien a faire
}

int Point::Get_x() const
{
	return _x;
}

void Point::Set_x(int x)
{
	_x = x;
}

int Point::Get_y() const
{
	return _y;
}

void Point::Set_y(int y)
{
	_y = y;
}



