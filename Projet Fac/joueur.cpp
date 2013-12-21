#include "Joueur.h"
#include "Vaisseau.h"
#include <iostream>
#include "Log.h"
#include <sstream>


using namespace std;


Joueur::Joueur()//paramètres par defaut : 3 vies, score nul
{
	_pv = 3;
	_score = 0;
}

Joueur::~Joueur()
{
	//rien a faire;
}

//PV
int Joueur::Get_Pv() const
{
	return _pv;
}

void Joueur::Set_Pv(int pv)
{
	_pv = pv;
}

//Score
int Joueur::Get_Score() const
{
	return _score;
}

void Joueur::Set_Score(int score)
{
	_score = score;
}
