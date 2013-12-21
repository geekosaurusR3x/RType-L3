#ifndef __Fonction
#define __Fonction

#include "box.h"
//fonctions données pour l'affichage
void gotoxy(int x, int y);
void Clear();

void draw_screen(Box &); //méthode qui va permettre la gestion de l'affichage
void Deplacement(Box &);
void Set_haut_lageur(Box &);//méthode pour definir la largeur et la hauteur de la console dans la box
void Tir_Enemis(Box &);
bool Collision(int, int, int, int,int,int,int); //méthode qui va permettre la gestion des collisions
void Game_Over(Box &);
void End_Lvl(Box &);
int Menu(Box &);
int Menu_Diff(Box &);

#endif
