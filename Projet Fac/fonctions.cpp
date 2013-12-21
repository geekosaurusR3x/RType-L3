#include <windows.h>
#include <iostream>
#include <conio.h>

#include "fonction.h"
#include "Vaisseau.h"
#include "Joueur.h"
#include "box.h"
#include "Obstacles.h"

void gotoxy(int x, int y)//fonction qui va permettre de gérer la position du curseur de la console
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;

	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void Clear() //fonction qui va permettre d'effacer tout ce qui affiché sur la console
{

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {0, 0};
	DWORD count;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//This fills the buffer with a given character (in this case 32=space).
		FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
		//This will set our cursor position for the next print statement.
		SetConsoleCursorPosition(hStdOut, coord);
	}
}

//gestion ecran
void draw_screen(Box & box)
{
	Clear();
	HANDLE  HCmd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (box.Get_Pause())
	{
		gotoxy((box.Get_l()/2)-5,box.Get_h()/2);
		cout<<"Pause"<<endl;
		gotoxy((box.Get_l()/2)-15,(box.Get_h()/2)+2);
		cout<<"Appuyer sur p pour reprendre";
	}
	//taile de l'ecran definie dans la boite
	gotoxy(0,0);
	//affichage de la zone d'infos
	cout<<"Vie : ";
	for(int i=1;i<=box.Get_Joueur().Get_Pv();i++)
	{
		cout<<" <3 ";
	}
	gotoxy(0,1);
	cout<<"Score : "<<box.Get_Joueur().Get_Score()<<" pts";
	gotoxy(0,2);
	for(int i=0;i < box.Get_l()-1;i++)
	{
		cout<<"-";
	}
	//affichage de la zone de jeu
	//decor
	int start = box.Get_pos_decors();
	int end = start+box.Get_l()-2;
	int x_max = -1;
	int x,y = 0;

	//affiche les elements du vecteur decor qui ont un X compris entre start et end
	for (int i=0; i < box.Get_Decors().size(); i++)
	{
		x = box.Get_Decors().at(i).Get_x();
		y = box.Get_Decors().at(i).Get_y();
		
		if (x > x_max)
		{
			x_max = x;
		}
		
		if( x >= start && x <= end)
		{
			gotoxy(x-start,y);
			cout<<box.Get_Decors().at(i);
		}
	}

	//vaisseau
	gotoxy(1,box.Get_Vaisseau().Get_y());
	cout<<box.Get_Vaisseau();
	//les missiles
	//passe tous les elements du vector des missiles et les affiche en vert
	for (int i=0; i < box.Get_Chaine_Missile().size(); i++)
	{
		gotoxy(box.Get_Chaine_Missile().at(i).Get_x(),box.Get_Chaine_Missile().at(i).Get_y());
		SetConsoleTextAttribute(HCmd, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		cout<<box.Get_Chaine_Missile().at(i);
	}
	SetConsoleTextAttribute(HCmd, FOREGROUND_INTENSITY);
	//les ennemis
	//meme methode pour les ennemis
	for (int i=0; i<box.Get_Chaine_Enemis().size(); i++)
	{
		gotoxy(box.Get_Chaine_Enemis().at(i).Get_x(),box.Get_Chaine_Enemis().at(i).Get_y());
		cout<<box.Get_Chaine_Enemis().at(i);
	}

	//les missiles ennemis
	//et pour les missiles ennemis mais les affiche en rouge
	for (int i=0; i<box.Get_Chaine_Missile_Enemis().size(); i++)
	{
		gotoxy(box.Get_Chaine_Missile_Enemis().at(i).Get_x(),box.Get_Chaine_Missile_Enemis().at(i).Get_y());
		SetConsoleTextAttribute(HCmd, FOREGROUND_RED|FOREGROUND_INTENSITY);
		cout<<box.Get_Chaine_Missile_Enemis().at(i);

	}
	SetConsoleTextAttribute(HCmd, FOREGROUND_INTENSITY);
}

void Deplacement(Box & box)
{
	//deplacement du decor
	float start = box.Get_pos_decors();
	int end = start+box.Get_l()-2;
	int x;
	int x_max = -1;
	float temp = start+2; //avance le decor de 3 
	//Recupere le x_max dans les x du decor
	for (int i=0; i < box.Get_Decors().size(); i++)
	{
		x = box.Get_Decors().at(i).Get_x();
		if (x > x_max)
		{
			x_max = x;
		}
	}
	//si la fin de la zone d'affichage est > au x max alors choisi un point aleatoire dans tout le decor pour repeter
	if (end+3 > x_max)
	{
		temp = rand()%(x_max);
	}
	//stockage de la position
	box.Set_pos_decors(temp);

	int i=0;
	int j=0;
	
	//tous les deplacements sont sur le meme modele :
	//parcours du vector
	//	appel de la methode de deplacement
	//	si l'element sort de la zone de jeu
	//		on le supprime
	//	sinon
	//		verification de collision et gestion de la collision en cas de besoin
	//
	//gestion des missiles
	while( i<box.Get_Chaine_Missile().size())
	{
		box.Get_Chaine_Missile().at(i).Deplacement(box.Get_Vaisseau().Get_x(), box.Get_Vaisseau().Get_y());
		if (box.Get_Chaine_Missile().at(i).Get_x() >= box.Get_l()-1)
		{
			box.Supp_Missille(i);
		}
		else
		{
			while (j<box.Get_Chaine_Enemis().size())
			{
				if (Collision(box.Get_Chaine_Missile().at(i).Get_x(), box.Get_Chaine_Missile().at(i).Get_y(), 
					box.Get_Chaine_Enemis().at(j).Get_x(), box.Get_Chaine_Enemis().at(j).Get_y(),
					box.Get_Chaine_Missile().at(i).Get_Vitesse(),
					1,box.Get_Chaine_Enemis().at(j).Get_TypeObstacle()))
				{
					box.Supp_Missille(i);
					Obstacles temp45 = box.Get_Chaine_Enemis().at(j);
					temp45.Set_Nb_Pv(temp45.Get_Nb_Pv()-1);
					if (temp45.Get_Nb_Pv() <= 0)
					{
						box.Get_Joueur().Set_Score(box.Get_Joueur().Get_Score()+box.Get_Chaine_Enemis().at(j).Get_Points());
						if (temp45.Get_TypeObstacle() == 5)
						{
							box.Supp_Boss();
						}
						else
						{
							box.Supp_Enemis(j);
						}
					}
				}
				j++;
			}
			j=0;
		}
	i++;
	}

	//gestion des ennemis
	for (int i=0; i<box.Get_Chaine_Enemis().size(); i++)
	{
		box.Get_Chaine_Enemis().at(i).Deplacement(box.Get_Vaisseau().Get_x(), box.Get_Vaisseau().Get_y());
		if (Collision(box.Get_Chaine_Enemis().at(i).Get_x(), box.Get_Chaine_Enemis().at(i).Get_y(),
			box.Get_Vaisseau().Get_x(),box.Get_Vaisseau().Get_y(),box.Get_Chaine_Enemis().at(i).Get_Vitesse(),box.Get_Chaine_Enemis().at(i).Get_TypeObstacle(),1))
			{
				box.Get_Joueur().Set_Pv(box.Get_Joueur().Get_Pv()-1);
				box.Supp_Enemis(i);
			}
		else if (box.Get_Chaine_Enemis().at(i).Get_x() <= 0)
		{
			box.Supp_Enemis(i);
		}
	}

	//gestion des tirs ennemis
	for (int i=0; i<box.Get_Chaine_Missile_Enemis().size(); i++)
	{
		box.Get_Chaine_Missile_Enemis().at(i).Deplacement(box.Get_Vaisseau().Get_x(), box.Get_Vaisseau().Get_y());
		if (box.Get_Chaine_Missile_Enemis().at(i).Get_x() <= 0)
		{
			box.Supp_Missille_Enemis(i);
		}
		else
		{
			if (Collision( box.Get_Chaine_Missile_Enemis().at(i).Get_x(), box.Get_Chaine_Missile_Enemis().at(i).Get_y(),
				box.Get_Vaisseau().Get_x(), box.Get_Vaisseau().Get_y(),box.Get_Chaine_Missile_Enemis().at(i).Get_Vitesse(),1,1))
			{
				box.Get_Joueur().Set_Pv(box.Get_Joueur().Get_Pv()-1);
				box.Supp_Missille_Enemis(i);
			}
		}
	}
}

//definiton de la largeur et la hauteur de la fenetre de la console dans la box
void Set_haut_lageur(Box & box)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);
	box.Set_l(csbi.dwSize.X);
	box.Set_h(csbi.dwSize.Y);
}

//parcours le vector d'enemis et verifie a chaque element si l'ennemi peut tirer
//si oui alors ajout d'un tir
void Tir_Enemis (Box & box)
{
	for (int i=0; i<box.Get_Chaine_Enemis().size(); i++)
	{
		if (box.Get_Chaine_Enemis().at(i).Get_tir())
		{
			box.Add_Missille_Enemis(box.Get_Chaine_Enemis().at(i).Get_x(), box.Get_Chaine_Enemis().at(i).Get_y());
		}
	}
}

//boite de collision
//si les 2 types d'objets sont 1 alors on doit verifier sur le meme Y mais avec une zone de X+/- la vitesse(v1)
//sinon on doit avoir une boite de collision Y+/- 1 et X+/- vitesse (v1)
bool Collision(int x1, int y1, int x2, int y2, int v1,int type1, int type2)
{
	bool retour;
	if ((type1 == 1)&&(type2 == 1))
	{
		if ((x1+v1 >= x2) && (x1-v1 <= x2) && (y1 == y2))
		{
			retour = true;
		}
		else 
		{
			retour = false;
		}
	}
	else
	{
		if ((x1+v1 >= x2) && (x1-v1 <= x2) && (y1+1 >= y2) && (y1-1 <= y2))
		{
			retour = true;
		}
		else 
		{
			retour = false;
		}
	}
	return retour;
}

void Game_Over(Box & box)
{
		Clear();
		gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)-3);
		cout<<"  __   __        __        __        __   __"<<endl;
		gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)-2);
		cout<<" /    /  | /|/| /         /  | /  | /    /  |"<<endl;
		gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)-1);
		cout<<"( __ (___|( / |(___      (   |(   |(___ (___|"<<endl;
		gotoxy((box.Get_l()/2)-25,(box.Get_h()/2));
		cout<<"|   )|   )|   )|         |   ) \\  )|    |\\   "<<endl;
		gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)+1);
		cout<<"|__/ |  / |  / |__       |__/   \\/ |__  | \\  "<<endl;
		gotoxy((box.Get_l()/2)-10,(box.Get_h()/2)+3);
		cout<<"Score : "<<box.Get_Joueur().Get_Score()<<" points";
		gotoxy((box.Get_l()/2)-18,(box.Get_h()/2)+5);
		cout<<"Appuyer sur une touche pour continuer";
		system ("pause >0");
}

void End_Lvl(Box & box)
{
	Clear();
	gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)-7);
	cout<<" __       ___________    ____  _______  __      "<<endl;
	gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)-6);
	cout<<"|  |     |   ____\\   \\  /   / |   ____||  |     "<<endl;
	gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)-5);
	cout<<"|  |     |  |__   \\   \\/   /  |  |__   |  |     "<<endl;
	gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)-4);
	cout<<"|  |     |   __|   \\      /   |   __|  |  |     "<<endl;
	gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)-3);
	cout<<"|  `----.|  |____   \\    /    |  |____ |  `----."<<endl;
	gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)-2);
	cout<<"|_______||_______|   \\__/     |_______||_______|"<<endl;
	gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)-1);
	cout<<"                                                "<<endl;
	gotoxy((box.Get_l()/2)-25,(box.Get_h()/2));
	cout<<"  ______  __       _______     ___      .______      "<<endl;
	gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)+1);
	cout<<" /      ||  |     |   ____|   /   \\     |   _  \\     "<<endl;
	gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)+2);
	cout<<"|  ,----'|  |     |  |__     /  ^  \\    |  |_)  |    "<<endl;
	gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)+3);
	cout<<"|  |     |  |     |   __|   /  /_\\  \\   |      /     "<<endl;
	gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)+4);
	cout<<"|  `----.|  `----.|  |____ /  _____  \\  |  |\\  \\----."<<endl;
	gotoxy((box.Get_l()/2)-25,(box.Get_h()/2)+5);
	cout<<" \\______||_______||_______/__/     \\__\\ | _| `._____|"<<endl;
	gotoxy((box.Get_l()/2)-10,(box.Get_h()/2)+7);
	cout<<"Score : "<<box.Get_Joueur().Get_Score()<<" points";
	gotoxy((box.Get_l()/2)-18,(box.Get_h()/2)+9);
	cout<<"Appuyer sur une touche pour continuer";
	system ("pause >0");
}

//menu d'affichage du jeu
int Menu(Box & box)
{
	Clear();
	gotoxy((box.Get_l()/2)-7,(box.Get_h()/2)-6);
	cout<<"1 : Jouer"<<endl;
	gotoxy((box.Get_l()/2)-7,(box.Get_h()/2)-4);
	cout<<"2 : Difficulte"<<endl;
	gotoxy((box.Get_l()/2)-7,(box.Get_h()/2)-2);
	cout<<"3 : Sortir"<<endl;
	gotoxy((box.Get_l()/2)-7,(box.Get_h()/2));
	cout<<"Choix: ";
    int i;
	cin>>i;
	return int(i);
}

//menu de difficulte
int Menu_Diff(Box & box)
{
	Clear();
	gotoxy((box.Get_l()/2)-7,(box.Get_h()/2)-6);
	cout<<"1 : Facile"<<endl;
	gotoxy((box.Get_l()/2)-7,(box.Get_h()/2)-4);
	cout<<"2 : Difficile"<<endl;
	gotoxy((box.Get_l()/2)-7,(box.Get_h()/2)-2);
	cout<<"3 : Insane"<<endl;
	gotoxy((box.Get_l()/2)-7,(box.Get_h()/2));	
	cout<<"Choix: ";
    int i;
	cin>>i;
	return int(i);
}