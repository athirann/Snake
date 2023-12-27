#include <stdlib.h>
#include <graph.h>
#include <stdio.h>
#include "affichage.h"
#include "deplacer.h"



void ReafficherObsPomme(Pastille *pomme,Obstacle *caisse,int nbr_obstacle){
            int i,deuxiemeRectangleX,deuxiemeRectangleY;
            
         for (i = 0; i < 5; i++)
            {
                dessin2couleurRond(pomme, "black", "red");
            }
            for (i = 0; i < nbr_obstacle; i++)
            {
                ChoisirCouleurDessin(CouleurParNom("dark"));
                RemplirRectangle(caisse[i].x, caisse[i].y, TAILLE_CASE, TAILLE_CASE);
                deuxiemeRectangleX = caisse[i].x + (TAILLE_CASE - 9) / 2;
                deuxiemeRectangleY = caisse[i].y + (TAILLE_CASE - 9) / 2;
                ChoisirCouleurDessin(CouleurParNom("gray"));
                RemplirRectangle(deuxiemeRectangleX, deuxiemeRectangleY, 9, 9);
                ChoisirCouleurDessin(CouleurParNom("black"));
                DessinerRectangle(caisse[i].x + 1, caisse[i].y + 1, 12, 12);
            }
        }

/*Fonction qui affiche l'interface 


/*Dessiner les pastilles*/
void dessin2couleurRond(Pastille *pomme, char *color1, char *color2)
{
    int i, deuxiemeRectangleX, deuxiemeRectangleY;
    for (i = 0; i < sizeof(pomme[i]) - 3; i++)
    {
        ChoisirCouleurDessin(CouleurParNom(color1));
        RemplirArc(pomme[i].x, pomme[i].y, TAILLE_CASE, TAILLE_CASE, 0, 360);
        deuxiemeRectangleX = pomme[i].x + (TAILLE_CASE - 10) / 2;
        deuxiemeRectangleY = pomme[i].y + (TAILLE_CASE - 10) / 2;
        ChoisirCouleurDessin(CouleurParNom(color2));
        RemplirArc(deuxiemeRectangleX, deuxiemeRectangleY, 10, 10, 0, 360);
    }
}
/*Le temps*/
void mettreAJourTemps(unsigned long *suivant, int *n, int *minutes, int *secondes, char *texte)
{
    if (Microsecondes() > *suivant)
    {
        *suivant = Microsecondes() + CYCLE;
        (*n)++;
        *minutes = *n / 60;
        *secondes = *n % 60;

        ChoisirCouleurDessin(CouleurParNom("black"));
        RemplirRectangle(75, 655, 250, 40);
        ChoisirCouleurDessin(CouleurParNom("white"));
        sprintf(texte, "Temps : %02d : %02d", *minutes, *secondes);
        EcrireTexte(85, 685, texte, 2);
    }
}
/*Affichage de l'image perdu avec le score et le timer*/
void perdu(char *texte, int score, int minutes, int secondes, int *recommencer, int *jeu)
{
    int i;
    ChargerImage("images/perdu.png", 300, 100, 0, 0, 900, 900);
    /*Afficher le score sur l'image*/
    ChoisirCouleurDessin(CouleurParNom("black"));
    sprintf(texte, "%3d", score);
    EcrireTexte(465, 355, texte, 2);
    /*affichage du timer au menu*/
    sprintf(texte, "%02d:%02d", minutes, secondes);
    EcrireTexte(710, 355, texte, 1);
    /*Relancer le jeu tant que la touche entre n'est pas rappuyer*/
    while (1)
    {
        switch (Touche())
        {
        case XK_Return:
            *recommencer = 1;
        case XK_Escape:
        for(i=0;i<40;i++){
            printf("Aurevoir !\n");
        }
        
            *jeu = 0;
            return;
            break;
        }
    }
}

/*Affichage du terrain de jeu a 2 couleurs*/
void EcranJeu()
{
    int i, j;
    for (i = 2; i < LIGNES + 2; i++)
    {
        for (j = 5; j < COLONNES + 5; j++)
        {
            if ((i + j) % 2 == 0)
            {
                ChoisirCouleurDessin(CouleurParComposante(126, 217, 87));
            }
            else
            {
                ChoisirCouleurDessin(CouleurParComposante(114, 190, 64));
            }
            RemplirRectangle(j * TAILLE_CASE, i * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
            ChoisirCouleurDessin(CouleurParNom("black"));
            DessinerRectangle(j * TAILLE_CASE, i * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
        }
    }
}
/*Effacer l'arriere du serpent avec la meme couleur du fond du jeu*/
void effacerSerpent(Segment *serpent, int longueurSerpent, int effacer)
{
    int i;
    for (i = 1; i < longueurSerpent; i++)
    {
        if ((serpent[longueurSerpent-1].x * TAILLE_CASE + serpent[longueurSerpent-1].y * TAILLE_CASE) % 2 == 0)
        {
            ChoisirCouleurDessin(CouleurParComposante(126, 217, 87));
        }
        else
        {
            ChoisirCouleurDessin(CouleurParComposante(114, 190, 64));
        }
        RemplirRectangle(serpent[longueurSerpent-1].x, serpent[longueurSerpent-1].y, TAILLE_CASE, TAILLE_CASE);
        ChoisirCouleurDessin(CouleurParNom("black"));
        DessinerRectangle(serpent[longueurSerpent-1].x, serpent[longueurSerpent-1].y, TAILLE_CASE, TAILLE_CASE);
    }
}


void afficherObstacle(Segment *serpent, Pastille *pomme, Obstacle *caisse, int z)
{
    int i;
    for (i = 0; i < z; i++)
    {

        caisse[i].x = rand() % (COLONNES)*TAILLE_CASE + 5 * TAILLE_CASE;
        caisse[i].y = rand() % (LIGNES)*TAILLE_CASE + (ESPACE_HAUT - 3 * TAILLE_CASE);

        /*Eviter que les caisse apparaisse devant le serpent au lancement*/
        while ((serpent[i].x == caisse[i].x && caisse[i].y == serpent[i].y) ||
               (caisse[i].y == 550 && caisse[i].x <= 420) ||
               (caisse[i].x >= 470 && caisse[i].x <= 650 && caisse[i].y >= 350 && caisse[i].y <= 440))
        {
            caisse[i].x = rand() % (COLONNES)*TAILLE_CASE + 5 * TAILLE_CASE;
            caisse[i].y = rand() % (LIGNES)*TAILLE_CASE + (ESPACE_HAUT - 3 * TAILLE_CASE);
        }

    }
}

void menu_accueil(int *jeu)
{
    InitialiserGraphique();
    ChargerImageFond("images/menu.png");

    while (1)
    {
        if (SourisCliquee())
        {
            SourisPosition();
            /*Quand la souris clique sur le bouton "Jouer" */
            if ((_X >= 90 && _X <= 350) && (_Y >= 575 && _Y <= 700))
            {
                break;
            }
            /*Quand la souris clique sur le bouton "Sortir"*/
            else if ((_X >= 715 && _X <= 970) && (_Y >= 575 && _Y <= 700))
            {
                *jeu = 0;
                break;
            }
        }
        /*Entre pour jouer et echape pour quitter*/
        if (ToucheEnAttente())
        {
            int touche = Touche();
            if (touche == XK_Return)
            {
                break;
            }

            if (touche == XK_Escape)
            {
                *jeu = 0;
                break;
            }
        }
    }
}

/*Fonction qui permet d'afficher le serpent au debut*/
void afficherSerpent(Segment *serpent, int taille)
{
    int i = 0;
    for (i = 0; i < taille; i++)
    {
        serpent[i].x = LARGEUR_FENETRE / 2 + i;
        serpent[i].y = HAUTEUR_FENETRE / 2;
    }
    for (i = 0; i < taille; i++)
    {
        RemplirRectangle(serpent[i].x, serpent[i].y, TAILLE_CASE, TAILLE_CASE);
    }
}

/*Afficher les pastielle de maniere aléoratoire*/
void afficherPastilleAleatoire(int z, Pastille *pomme, Obstacle *caisse, Segment *serpent, int nbr_obstacle, int longueurSerpent)
{
    int i = 0, j = 0;
    for (i = 0; i < z; i++)
    {

        pomme[i].x = rand() % COLONNES * TAILLE_CASE + 5 * TAILLE_CASE;
        pomme[i].y = rand() % LIGNES * TAILLE_CASE + (ESPACE_HAUT - 3 * TAILLE_CASE);
        /*Pour eviter que les pommes apparaisse dans le serpent*/
        for (j = 0; j < longueurSerpent; j++)
        {
            if (pomme[i].x == serpent[j].x && pomme[i].y == serpent[j].y)
            {
                pomme[i].x = rand() % COLONNES * TAILLE_CASE + 5 * TAILLE_CASE;
                pomme[i].y = rand() % LIGNES * TAILLE_CASE + (ESPACE_HAUT - 3 * TAILLE_CASE);
            }
        }
        /*Pour eviter que les pommes apparaisse dans les obstacle*/
        for (j = 0; j < nbr_obstacle; j++)
        {
            while ((pomme[i].x == caisse[j].x && pomme[i].y == caisse[j].y))
            {
                pomme[i].x = rand() % COLONNES * TAILLE_CASE + 5 * TAILLE_CASE;
                pomme[i].y = rand() % LIGNES * TAILLE_CASE + (ESPACE_HAUT - 3 * TAILLE_CASE);

                j = 0;
            }
        }

    }
}
