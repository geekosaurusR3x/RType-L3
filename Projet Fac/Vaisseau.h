#ifndef _Vaisseau
#define _Vaisseau

#include "Objet.h"
#include <iostream>

using namespace std;

class Vaisseau:public Objet
{

private : //pas d'attributs propres a la classe Vaisseau

public :
	Vaisseau(); //constructeur vide
	Vaisseau(const Vaisseau&); //constructeur par recopie
	virtual ~Vaisseau(); //destructeur

	void Monte(); //methode qui va permettre de faire monter le vaisseau
	void Descend(); //methode qui va permettre de faire descendre le vaisseau
	friend ostream & operator << (ostream &, const Vaisseau &); //surcharge de l'opérateur d'affichage
};

extern ostream & operator << (ostream &,const Vaisseau &);

#endif _Vaisseau