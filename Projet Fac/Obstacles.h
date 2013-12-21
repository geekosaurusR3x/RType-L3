#ifndef _Obstacles
#define _Obstacles

#include "Objet.h"
#include <iostream>

using namespace std;

//types d'obstacle
#define IMMOBILE 1
#define HORIZONTAL 2
#define VERTICAL 3
#define DIAGONAL 4
#define BOSS 5
#define BOSS_ANNEXE_SUP 8
#define BOSS_ANNEXE_INF 9
#define MISSILEV 6
#define MISSILEE 7

class Obstacles:public Objet
{
private :
	int _typeobstacle; //type de l'obstacle "immobile, horizontal, ..."
	int _vitesse; //Vitesse de l'obstacle
	int _nbticks; //Nombre de ticks necessaires avant de faire avancer l'obstacle
	int _points; //Nombre de points raportés par l'ennemis
	int _pv; //Nombre de pv de l'ennemi
	void Monte(); 
	void Descend();

public :
	Obstacles(); //constructeur vide
	Obstacles(char, int, int, int, int, int,bool); //constructeur
	Obstacles(const Obstacles &); //constructeur par recopie
	virtual ~Obstacles(); //destructeur

	void Set_TypeObstacle(int); //methode qui va permettre de modifier le type d'obstacle
	void Set_Vitesse(int); //methode qui va permettre de modifier la vitesse
	void Set_NbTicks(int); //methode qui va permettre de modifier le nombre de ticks
	
	int Get_TypeObstacle(); //methode qui va permettre de recuperer le type de l'obstacle
	int Get_Vitesse(); //methode qui va permettre de recuperer la valeur de la vitesse
	int Get_NbTicks(); //methode qui va permettre de recuperer le nombre de ticks
	int Get_Points();  //recupere le nombre de points de score de l'obstacle

	void Set_Nb_Pv(int); //definit le nombre de pv
	int Get_Nb_Pv(); //recupere le nombre de pv
	friend ostream & operator << (ostream &, const Obstacles &); //surcharge de l'opérateur d'affichage
		
	void Deplacement (int x,int y); //methode permettant le deplacement des obstacles
};

extern ostream & operator << (ostream &,const Obstacles &);

#endif _Obstacles