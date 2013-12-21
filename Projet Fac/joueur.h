#ifndef __Joueur
#define __Joueur

#include <iostream>

using namespace std;
class Joueur
{
	private:
		int _pv; //nombre de vies
		int _score; //score
	
	public:
		Joueur (); //constructeur vide
		~Joueur(); //destructeur

		int Get_Pv() const; //methode qui va permettre de recuperer le nombre de vies
		void Set_Pv(int); //methode qui va permettre la modification du nombre de vies
		int Get_Score() const; //methode qui va permettre de recuperer le score 
		void Set_Score(int); //methode qui va permettre la modification du score 
};

#endif _Joueur