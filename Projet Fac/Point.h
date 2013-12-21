#ifndef _Point
#define _Point

class Point
{
private :
	int _x; //coordonn�e sur l'axe des abscisses
	int _y; //coordonn�e sur l'axe des ordonn�es
		
public : 
	Point(); //constructeur vide
	Point(int,int); //constructeur
	Point (const Point&); //constructeur par recopie	
	~Point(); //destructeur

	int Get_x() const; //methode qui va permettre de recuperer la coordonn�e x
	void Set_x(int); //methode qui va permettre de modifier la coordonn�e x
	int Get_y() const; //methode qui va permettre de recuperer la coordonn�e y
	void Set_y(int); //methode qui va permettre de modifier la coordonn�e y
};

#endif _Point