#include "Objet.h"
#include "Point.h"
#include <iostream>

using namespace std;

Objet::Objet():_point() //constructeur, caractère par défaut : >
{
	Set_char('>');
	_tir = false;
	
}

Objet::Objet(char caractere, int x, int y,bool tir):_point(x,y) //constructeur
{
	Set_char(caractere);
	_tir = tir;
}

Objet::Objet(const Objet &objet):_point(objet._point) //constructeur par recopie
{
	Set_char(objet._caractere);
	_tir = objet._tir;
}

Objet::~Objet() //destructeur
{
	//rien a faire
}

void Objet::Set_char(char caractere)
{
	_caractere = caractere;
}

char Objet::Get_char() const
{
	return _caractere;
}

int Objet::Get_x() const
{
	return _point.Get_x();
}

void Objet::Set_x(int x)
{
	_point.Set_x(x);
}

int Objet::Get_y() const
{
	return _point.Get_y();
}

void Objet::Set_y(int y)
{
	_point.Set_y(y);
}

bool Objet::Get_tir() const
{
	return _tir;
}

void Objet::Set_tir(bool tir)
{
	_tir = tir;
}




	  



