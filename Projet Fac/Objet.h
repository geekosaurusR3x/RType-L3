#ifndef _Objet
#define _Objet

#include "Point.h"
class Objet
{
private :
	char _caractere; //caract�re qui va representer l'obstacle
	Point _point; //object point
	bool _tir; //possibilit� de tir ou pas
public :
	Objet(); //constructeur vide
	Objet(char, int, int,bool); //constructeur
	Objet(const Objet&); //constructeur par recopie
	virtual ~Objet(); //destructeur

	char Get_char() const; //methode qui va permettre de recuperer le char
	void Set_char(char); //methode qui va permettre de modifier le caractere

	int Get_x() const; //methode qui va permettre de recuperer la coordonn�e x
	void Set_x(int); //methode qui va permettre de modifier la coordonn�e x
	int Get_y() const; //methode qui va permettre de recuperer la coordonn�e y
	void Set_y(int); //methode qui va permettre de modifier la coordonn�e y
	bool Get_tir() const; //methode qui va permettre de recuperer la coordonn�e y
	void Set_tir(bool); //methode qui va permettre de modifier la coordonn�e y

};

#endif _Objet