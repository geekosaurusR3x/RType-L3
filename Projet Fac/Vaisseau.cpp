#include "Objet.h"
#include "box.h"
#include "Vaisseau.h"
#include <iostream>
#include <sstream>
using namespace std;

Vaisseau::Vaisseau():Objet('>',0,14,true) //contructeur vide
{
}

Vaisseau::Vaisseau(const Vaisseau &vaisseau):Objet(vaisseau) //constructeur par recopie
{
}

Vaisseau::~Vaisseau() //destructeur
{
	//rien a faire
}

void Vaisseau::Monte() //methode qui va permettre de faire monter le vaisseau
{
	
	if (Get_y() > 3) //pour eviter que le vaisseau reste dans la zone de jeu
	{
		Set_y(Get_y()-1); //hauteur exprimee en lignes de caracteres
	}
}

void Vaisseau::Descend() //methode qui va permettre de faire descendre le vaisseau
{
	if (Get_y() < Box::Get_instance().Get_h()-1) //le vaisseau ne pourra pas descendre plus bas 
	{
		Set_y(Get_y()+1);
	}
}

ostream & operator << (ostream & os, const Vaisseau &vaisseau) 
{
	os << vaisseau.Get_char();
	return os;
}