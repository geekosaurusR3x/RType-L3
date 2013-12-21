//La box est la boite represantant tous le jeux et contenant tous le reste.
#ifndef _Box
#define _Box

#include <vector>
#include <string>

#include "joueur.h"
#include "Obstacles.h"
#include "Vaisseau.h"

class Box
{
private:
	int _largeur; //largeur de la fenetre
	int _hauteur; //hauteur de la fenetre
	float _pos_decors; //position dans les X du decor pour l'affichage
	bool _pause; //pause du jeu
	bool _boss_tue; //boss mort ou pas
	int _lvl; //difficulte du jeu
	Joueur _joueur; //joueur
	Vaisseau _vaisseau; //vaiseau
	vector<Obstacles> _decors, _missiles,_missiles_enemis, _enemis; 
	static Box* _self; //pointeur du la box pour n'avoir qu'une seule instance de la boite dans le jeu
	Box(); //constructeur vide
	~Box();

public:
	static Box& Get_instance();
	static void Kill();
	Joueur & Get_Joueur();
	Vaisseau & Get_Vaisseau();
	int Get_h();
	int Get_l();
	void Set_h(int);
	void Set_l(int);
	float Get_pos_decors();
	void Set_pos_decors(float);
	bool Get_Pause();
	void Set_Pause();
	int Get_diff();
	void Set_diff(int);
	vector<Obstacles> & Get_Decors();
	vector<Obstacles> & Get_Chaine_Missile();
	vector<Obstacles> & Get_Chaine_Missile_Enemis();
	vector<Obstacles> & Get_Chaine_Enemis();
	void Add_Missille();
	void Add_Missille_Enemis(int,int);
	void Supp_Missille(int);
	void Supp_Missille_Enemis(int);
	void Add_Enemis();
	void Supp_Enemis(int);
	void Add_Boss();
	void Supp_Boss();
	bool Get_Boss_tue();

	void Charger_Decors(char *);
};

#endif _Box
