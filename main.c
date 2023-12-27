#include <stdlib.h>
#include <graph.h>
#include <time.h>
#include <stdio.h>
#include "vitesse.h"
#include "deplacer.h"
#include "affichage.h"

#define MAX_LONGUEUR 100

int main()
{

    int recommencer = 1;
    int jeu = 1;
    InitialiserGraphique();
    CreerFenetre(350, 100, LARGEUR_FENETRE, HAUTEUR_FENETRE);
    menu_accueil(&jeu);
    
    if (jeu == 0)
    {
        recommencer = 0;
        jeu = 0;
    }

    /*Boucle qui permet de recommencer*/
    while (recommencer)
    {

        unsigned long suivant = 0;
        int n = 0, nbr_obstacle = 20, minutes = 0, secondes = 0, score = 0, effacer = 0, scoretemp = 20, vitesse = 80;
        char texte[50];
        int jeu = 1, i, direction = 1, direction_avant = 1, longueurSerpent = 10;

        Obstacle *caisse = (Obstacle *)malloc(nbr_obstacle * sizeof(Obstacle));
        Pastille *pomme = (Pastille *)malloc(NBR_PASTILLE_INITIAL * sizeof(Pastille));
        Segment *serpent = (Segment *)malloc(MAX_LONGUEUR * sizeof(Segment));

        srand(time(NULL));
        afficherPastilleAleatoire(5, pomme, caisse, serpent, nbr_obstacle, longueurSerpent);
        afficherObstacle(serpent, pomme, caisse, nbr_obstacle);
        EffacerEcran(CouleurParNom("black"));
        EcranJeu();
        afficherSerpent(serpent, longueurSerpent);
        ReafficherObsPomme(pomme,caisse,nbr_obstacle);
    
        /*Boucle de jeu principale*/
        while (jeu)
        {

            recommencer = 0;

            if (longueurSerpent == MAX_LONGUEUR)
            {
                serpent = (Segment *)realloc(serpent, (MAX_LONGUEUR + MAX_LONGUEUR) * sizeof(Segment));
            }

            mettreAJourTemps(&suivant, &n, &minutes, &secondes, texte);

            gererEntreesClavier(&direction, &direction_avant, &score, texte, &minutes, &secondes, &jeu, pomme, caisse, nbr_obstacle);
            for (i = 0; i < nbr_obstacle; i++)
            {
                if (serpent[0].x == caisse[i].x && serpent[0].y == caisse[i].y)
                {
                    perdu(texte, score, minutes, secondes, &recommencer, &jeu);
                }
            }

            deplacerSerpent(longueurSerpent, serpent, effacer, direction, texte, score, minutes, secondes, &jeu, &recommencer);

            estManger(&score, &effacer, &longueurSerpent, pomme, serpent, caisse, nbr_obstacle, texte);

            terrain(texte, serpent, score, minutes, secondes, &jeu, &recommencer);

            ajusterVitesse(&vitesse, &score, &scoretemp);

            Attendre(vitesse);
        }
        
        free(pomme);
        free(serpent);
    }


    FermerGraphique();
    return EXIT_SUCCESS;
}
