#include "Objet.h"
#include "Obstacles.h"
#include <iostream>
#include "box.h"
using namespace std;



Obstacles::Obstacles():Objet() //constructeur, type d'obstacle par defaut : "Immobile", vitesse = 0, NbTicks = 0
{

	_typeobstacle = 1;
	_vitesse = 0;
	_nbticks = 0;
	_pv = 0;
	_points = 100;
}

Obstacles::Obstacles(char caractere, int x, int y, int typeobstacle, int vitesse, int points,bool tir):Objet(caractere, x, y,tir) //constructeur
{
	_typeobstacle = typeobstacle;
	_vitesse = vitesse;
	_nbticks = 0;
	_points = points;
	_pv = 0;
}

Obstacles::Obstacles(const Obstacles &obstacle):Objet(obstacle) //constructeur par recopie
{
	_typeobstacle = obstacle._typeobstacle;
	_vitesse = obstacle._vitesse;
	_nbticks = obstacle._nbticks;
	_points = obstacle._points;
	_pv = obstacle._pv;
}

Obstacles::~Obstacles()
{
	//rien a faire
}

//permet de faire monter l'obstacle tout en le laissant dans la zone de jeux
void Obstacles::Monte()
{
	if (this->Get_y() > 3)
	{
		this->Set_y(Get_y()-1);
	}
}
//permet de faire dessendre l'obstacle tout en le laissant dans la zone de jeu
void Obstacles::Descend()
{
	if (this->Get_y() < Box::Get_instance().Get_h()-1)
	{
		this->Set_y(Get_y()+1);
	}
}

void Obstacles::Set_TypeObstacle(int typeobstacle) //methode qui va permettre de modifier le type d'obstacle
{
	_typeobstacle = typeobstacle;
}

void Obstacles::Set_Vitesse(int vitesse) //methode qui va permettre de modifier la vitesse
{
	_vitesse = vitesse;
}

void Obstacles::Set_NbTicks(int nbticks) //methode qui va permettre de modifier le nombre de ticks
{
	_nbticks = nbticks;
}


int Obstacles::Get_TypeObstacle() //methode qui va permettre de recuperer le type de l'obstacle
{
	return _typeobstacle;
}

int Obstacles::Get_Vitesse() //methode qui va permettre de recuperer la valeur de la vitesse
{
	return _vitesse;
}

int Obstacles::Get_NbTicks() //methode qui va permettre de recuperer le nombre de ticks
{
	return _nbticks;
}

int Obstacles::Get_Points()
{
	return _points;
}

ostream & operator << (ostream & os, const Obstacles &obstacle) //surcharge de l'opérateur d'affichage
{
	os << obstacle.Get_char();
	return os;
}

//methode permettant le deplacement des obstacles
//les choix permetent de definir de choisir quelle direction vas etre prise par l'obstacle
//et donc de ne pas pouvoir prevoir le deplacement
void Obstacles::Deplacement (int x,int y)
{
	int temp1, temp2;
	switch (Get_TypeObstacle())
	{
	case IMMOBILE :
		break;

	case HORIZONTAL :
		this->Set_x(Get_x()-_vitesse);
		break;

	case VERTICAL :
		temp1 = rand() %3 +1;
		if (temp1 == 1)
		{
			Monte();
		}
		else 
		{
			if (temp1 == 2)
			{
				Descend();
			}
		}
		this->Set_x(Get_x()-1);
		break;

	case DIAGONAL :
		temp1 = rand() %3 +1;
		temp2 = rand() %2 +1;
		if (temp1 ==1)
		{
			Monte();
		}
		else 
		{
			if (temp1 ==2)
			{
				Descend();
			}
		}
		if (temp2 == 1)
		{
			this->Set_x(Get_x()-_vitesse);
		}
		break; 

	case BOSS :
		if (y < Get_y())
		{
			Monte();
		}
		else 
		{
			if (y > Get_y())
			{
				Descend();
			}
		}
		break;

	case BOSS_ANNEXE_SUP :
		if (y < Get_y()+1)
		{
			Monte();
		}
		else 
		{
			if (y > Get_y()+1)
			{
				Descend();
			}
		}
		break;
	case BOSS_ANNEXE_INF :
		if (y < Get_y()-1)
		{
			Monte();
		}
		else 
		{
			if (y > Get_y()-1)
			{
				Descend();
			}
		}
		break;
	case MISSILEV :
		this->Set_x(Get_x()+_vitesse);
		break;

	case MISSILEE :
		this->Set_x(Get_x()-_vitesse);
		break;
	}
}

void Obstacles::Set_Nb_Pv(int pv)
{
	_pv = pv;
}

int Obstacles::Get_Nb_Pv()
{
	return _pv;
}