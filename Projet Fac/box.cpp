#include <vector>
#include <fstream>
#include "joueur.h"
#include "Obstacles.h"
#include "Vaisseau.h"
#include "box.h"
#include <iostream>
#include "fonction.h"



//initalisation du pointeur
Box* Box::_self = NULL;

Box::Box() //constructeur vide
{
	_joueur;
	_vaisseau;
	_largeur = 80;
	_hauteur = 25;
	_pause = false;
	_boss_tue = false;
	_pos_decors = 0;
	_lvl = 1;
	
}

Box::~Box()
{
	//rien a faire
}

//methode qui renvoi l'instance de la box et qui l'initalise la premiere fois
//assure de n'avoir qu'une seule instance de la box
Box& Box::Get_instance()
{
	if( _self == NULL)
	{
		_self = new Box();
	}
	return *_self;
}

//remplace le destructeur
void Box::Kill()
{
	if( _self != NULL)
	{
		delete _self;
		_self = NULL;
	}
	
}

Joueur & Box::Get_Joueur()
{
	return _joueur;
}
Vaisseau & Box::Get_Vaisseau()
{
	return _vaisseau;
}
int Box::Get_h()
{
	return _hauteur;
}

int Box::Get_l()
{
	return _largeur;
}

void Box::Set_l(int l)
{
	_largeur = l;
}

void Box::Set_h(int h)
{
	_hauteur = h;
}

float Box::Get_pos_decors()
{
	return _pos_decors;
}

void Box::Set_pos_decors(float pos)
{
	_pos_decors = pos;
}

bool Box::Get_Pause()
{
	return _pause;
}

void Box::Set_Pause()
{
	_pause = !_pause;

}

int Box::Get_diff()
{
	return _lvl;
}

void Box::Set_diff(int lvl)
{
	_lvl = lvl;
}

vector<Obstacles> & Box::Get_Chaine_Missile()
{
	return _missiles;
}

vector<Obstacles> & Box::Get_Decors()
{
	return _decors;
}


vector<Obstacles> & Box::Get_Chaine_Missile_Enemis()
{
	return _missiles_enemis;
}

vector<Obstacles> & Box::Get_Chaine_Enemis()
{
	return _enemis;
}
//les methodes suivantes sont toutes sur le meme modele
//creation d'un obstacle temporaire
//ajout de celui-ci dans le vector corespondant
void Box::Add_Missille()
{
	Obstacles temp('-', 2, _vaisseau.Get_y(),6,1,0,false);
	_missiles.push_back (temp);
}

void Box::Add_Missille_Enemis(int x,int y)
{
	Obstacles temp('-', x, y,7,1*_lvl,0,false);
	_missiles_enemis.push_back (temp);
}

void Box::Supp_Missille(int i)
{
	_missiles.erase(_missiles.begin()+i);
}

void Box::Supp_Missille_Enemis(int i)
{
	_missiles_enemis.erase(_missiles_enemis.begin()+i);
}

void Box::Add_Enemis()
{
	int type =  rand()%(5-2)+2;
	int y = rand()%(_hauteur-4)+3;
	int vitesse = rand()%(3-1)+1;
	bool tir = false;
	if ((rand()%(3-1)+1)== 2)
	{
		tir = true;
	}
	Obstacles temp('3',(_largeur-1),y,type, vitesse*_lvl, 50*_lvl,tir);
	temp.Set_Nb_Pv(0+_lvl);
	_enemis.push_back (temp);
}
void Box::Supp_Enemis(int i)
{
	_enemis.erase(_enemis.begin()+i);
}

void Box::Add_Boss()
{
	Obstacles temp('@',(_largeur-2),_vaisseau.Get_y(),5, 0, 4000*_lvl,true);
	temp.Set_Nb_Pv(3+2*_lvl);
	_enemis.push_back(temp);
	//aile 1
	Obstacles temp2('/',(_largeur-2),(_vaisseau.Get_y()-1),8, 0, 500*_lvl,true);
	temp2.Set_Nb_Pv(3+_lvl);
	_enemis.push_back(temp2);
	//aile 2
	Obstacles temp3('\\',(_largeur-2),(_vaisseau.Get_y()+1),9, 0, 500*_lvl,true);
	temp3.Set_Nb_Pv(3+_lvl);
	_enemis.push_back(temp3);
}

void Box::Supp_Boss()
{
	_enemis.clear();
	_boss_tue = true;
}

bool Box::Get_Boss_tue()
{
	return _boss_tue;
}
//chargement du decor:
//lit le fichier passer en parametre caractere par caractere.
//Et pour chaque caractere different de " " et "\n" rajoute un obstacle dans le vector du decor avec des coordonées X et Y
void Box::Charger_Decors(char * nom)
{
	cout<<"Chargement"<<endl;
	int x = 0;
	int y = 3;
	ifstream OpenFile(nom);
	char ch;
	while(!OpenFile.eof())
	{
		OpenFile.get(ch);
        switch (ch)
        {
			case '\n':
			{
				x = 0;
				y++;
				break;
			}
			case ' ':
			{
				x++;
				break;
			}
			default :
			{
				Obstacles temp(ch,x,y,1, 0, 0,false);
				_decors.push_back (temp);
				x++;
				break;
			}
		}
		cout<<".";
	}
	OpenFile.close();
}
