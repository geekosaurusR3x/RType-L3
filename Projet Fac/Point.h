#ifndef _Point
#define _Point

class Point
{
private :
	int _x; //coordonnée sur l'axe des abscisses
	int _y; //coordonnée sur l'axe des ordonnées
		
public : 
	Point(); //constructeur vide
	Point(int,int); //constructeur
	Point (const Point&); //constructeur par recopie	
	~Point(); //destructeur

	int Get_x() const; //methode qui va permettre de recuperer la coordonnée x
	void Set_x(int); //methode qui va permettre de modifier la coordonnée x
	int Get_y() const; //methode qui va permettre de recuperer la coordonnée y
	void Set_y(int); //methode qui va permettre de modifier la coordonnée y
};

#endif _Point