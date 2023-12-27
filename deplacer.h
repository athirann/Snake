#ifndef DEPLACER_H
#define DEPLACER_H

#define TAILLE_CASE 15
#define NBR_PASTILLE_INITIAL 5
#define LARGEUR_ECRAN_JEU 900
#define HAUTEUR_ECRAN_JEU 600
#include "affichage.h"



void gererEntreesClavier(int *direction, int *direction_avant, int *score, char *texte, int *minutes, int *secondes, int *jeu, Pastille *pomme, Obstacle *caisse, int nbr_obstacle);
void estManger(int *score, int *effacer, int *longueurSerpent, Pastille *pomme, Segment *serpent, Obstacle *caisse, int nbr_obstacle, char *texte);
void deplacerSerpent(int longueurSerpent, Segment serpent[],int effacer, int direction, char *texte, int score, int minutes, int secondes, int *jeu,int *recommencer);
void terrain(char *texte,Segment serpent[], int score, int minutes, int secondes, int *jeu,int *recommencer);
#endif