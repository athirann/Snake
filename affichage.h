#ifndef AFFICHAGE_H
#define AFFICHAGE_H

typedef struct
{
    int x;
    int y;
} Pastille;

typedef struct
{
    int x;
    int y;
} Segment;

typedef struct
{
    int x;
    int y;
} Obstacle;

#define LARGEUR_FENETRE 1050
#define HAUTEUR_FENETRE 750
#define COLONNES 60
#define LIGNES 40
#define ESPACE_HAUT 75
#define CYCLE 1000000L

void ReafficherObsPomme(Pastille pomme[],Obstacle caisse[],int nbr_obstacle);
void dessin2couleurRond(Pastille pomme[], char* color1, char* color2);
void mettreAJourTemps(unsigned long *suivant, int *n, int *minutes, int *secondes, char *texte);
void terrain(char *texte, Segment serpent[], int score, int minutes, int secondes, int *jeu, int *recommencer);
void perdu(char *texte, int score, int minutes, int secondes,int *recommencer, int *jeu);
void EcranJeu();
void effacerSerpent(Segment serpent[], int longueurSerpent,int effacer);
void afficherObstacle(Segment serpent[], Pastille pomme[], Obstacle caisse[], int z);
void menu_accueil(int *jeu);
void afficherSerpent(Segment serpent[], int taille);
void afficherPastilleAleatoire(int z, Pastille pomme[], Obstacle caisse[], Segment serpent[], int nbr_obstacle, int longueurSerpent);




#endif