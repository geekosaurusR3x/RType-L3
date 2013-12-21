/* 
 * File:   main.cpp
 * Author: skad
 *
 * Created on 7 octobre 2010, 14:21
 */
//include lib standar
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <time.h>

//include class perso
#include "Joueur.h"
#include "Vaisseau.h"
#include "fonction.h"
#include "box.h"

#define TIME 20 //temps en ms d'un tick
#define TIME_BOSS 50000//temps en ms de l'apparition du boss
using namespace std;


int main(int argc, char** argv)
{
	
	bool run = true;
	Set_haut_lageur(Box::Get_instance());
	while (run)
	{

		int choix = Menu(Box::Get_instance());
		switch (choix)
		{
		case 1:
		{
			//initialisation du jeu
			
			Clear();
			Box::Get_instance().Charger_Decors("lvl.txt");
			int touche;
			bool end_game = false;
			int seconds = clock();
			int seconds_boss = clock();
			bool boss = false;
			int tick = 0;
			int nb_tick = 50/Box::Get_instance().Get_diff(); //nombre de ticks pour l'apparition d'un nouvel ennemi
			int tick_tir = 0;
			int nb_tick_tir = 75/Box::Get_instance().Get_diff(); //nombre de ticks pour l'apprition d'un nouveau tir d'ennemi
			int tick_aff = 0;
			int nb_tick_aff = 20; //nombre de ticks pour l'affichage
			int tick_dep = 0;
			int nb_tick_dep = 3; //bombre de ticks pour la gestion des deplacements
			//boucle principale
			while(!end_game)
			{
				//recuperation des touches du claviers
				if(_kbhit())
				{
					touche = _getch();
					if ((touche == 0 || touche == 224)&&(!Box::Get_instance().Get_Pause()))
					{
						touche = _getch();
						if(touche == 72) //touche du haut
						{
							Box::Get_instance().Get_Vaisseau().Monte();
						}
						else if (touche == 80) //touche du bas
						{
							Box::Get_instance().Get_Vaisseau().Descend();
						}
					}
					else
					{
						if (touche == 112 || touche == 80)
						{
							//gestion de la pause (touche p ou P)
							Box::Get_instance().Set_Pause();		
						}
						else if ((touche == 32)&&(!Box::Get_instance().Get_Pause()))
						{
							//gestion du tir
							Box::Get_instance().Add_Missille();
						}
						if (touche == 113 || touche == 81)
						{
							//gestion du quitter (touche Q)
							break;
						}
					}
				}
				//gestion du tick
				if (clock() - seconds >= TIME) //calcul du temps : temps depuis le lancement - temps depuis le dernier traitement des infos
				{
					
					if (!Box::Get_instance().Get_Pause()) //verification de la pause
					{
						if (clock() - seconds_boss >= TIME_BOSS) //si c'est le temps du boss
						{
							if (!boss)
							{
								Box::Get_instance().Add_Boss();
								boss = true;
							}
						}
						else
						{
							if (tick >= nb_tick ) //sinon les enemis
							{
								Box::Get_instance().Add_Enemis();
								tick = 0;
							}
						}
						if (tick_tir >= nb_tick_tir ) // si c'est le temps de tirer
						{
							Tir_Enemis (Box::Get_instance());
							tick_tir = 0;
						}
						if (tick_dep >= nb_tick_dep)//si c'est le temps de deplacer tous le monde
						{
							Deplacement(Box::Get_instance());
							tick_dep =0;
						}
					}			
					if (tick_aff >= nb_tick_aff )//si c'est le temps d'afficher le jeux
					{
						draw_screen(Box::Get_instance());	
						tick_aff = 0;
					}
							
					//incrementation des differents ticks
					tick++;
					tick_tir++;
					tick_aff++;
					tick_dep++;
					seconds = clock();
				}
				
				if (Box::Get_instance().Get_Joueur().Get_Pv() <= 0)
				{
					end_game = true;
				}

				if (Box::Get_instance().Get_Boss_tue())
				{
					end_game = true;
				}
			}
			
			//gestion du GAME OVER
			if (end_game == true && !Box::Get_instance().Get_Boss_tue())
			{
				Game_Over(Box::Get_instance());
			}

			//Gestion de la fin du jeu
			if (Box::Get_instance().Get_Boss_tue())
			{
				End_Lvl(Box::Get_instance());
			}

			//fermeture du jeu
			Box::Kill();			
			break;
		}
		case 2:
		{
			Box::Get_instance().Set_diff(Menu_Diff(Box::Get_instance()));
			break;
		}
		default :
		{
			run = false;
			Box::Get_instance();
			break;
		}
	}
	}
	

    return 0; 
}