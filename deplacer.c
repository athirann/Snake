#include <stdlib.h>
#include <graph.h>
#include <stdio.h>
#include "deplacer.h"
#include "affichage.h"

/*Actions des touche du clavier*/
void gererEntreesClavier(int *direction, int *direction_avant, int *score, char *texte, int *minutes, int *secondes, int *jeu, Pastille *pomme, Obstacle *caisse, int nbr_obstacle)
{
    int i, deuxiemeRectangleX, deuxiemeRectangleY;
    if (ToucheEnAttente())
    {
        switch (Touche())
        {
        case XK_Right:
            *direction = 1;

            break;
        case XK_Left:
            *direction = -1;

            break;
        case XK_Up:
            *direction = 2;

            break;
        case XK_Down:
            *direction = -2;

            break;
        case XK_space:
            ChargerImage("images/pause.png", 300, 100, 0, 0, 900, 900);
            ChoisirCouleurDessin(CouleurParNom("black"));
            sprintf(texte, "%3d", *score);
            EcrireTexte(465, 355, texte, 2);
            sprintf(texte, "%02d:%02d", *minutes, *secondes);
            EcrireTexte(710, 355, texte, 1);
            while (1)
            {
                 if (Touche() == XK_space)
            {

                EcranJeu();
                break;
            }
            else if (Touche() == XK_Escape)
            {
                jeu = 0;
                FermerGraphique();
                for(i=0;i<40;i++){
                    printf("Aurevoir !\n");
                }
                break;
            } 
            }

            for (i = 0; i < NBR_PASTILLE_INITIAL; i++)
            {
                /*Fonction permettant de dessiner un rond avec deux couleur*/
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

            break;
        }

        if (*direction == (*direction_avant * (-1)))
        {
            *direction = *direction_avant;
        }
        else
        {
            *direction_avant = *direction;
        }
    }
}
/*Lorsque que le serpent mange une pomme*/
void estManger(int *score, int *effacer, int *longueurSerpent, Pastille *pomme, Segment *serpent, Obstacle *caisse, int nbr_obstacle, char *texte)
{
    int i, j;
    /*Eviter que les pommes apparaisse sur le serpent*/
    for (i = 0; i < NBR_PASTILLE_INITIAL; i++)
    {
        if (serpent[0].x == pomme[i].x && serpent[0].y == pomme[i].y)
        {
            /*+2 a la longeur du serpents quand il mange une pomme*/
            *longueurSerpent += 2;

            pomme[i].x = rand() % COLONNES * TAILLE_CASE + 5 * TAILLE_CASE;
            pomme[i].y = rand() % LIGNES * TAILLE_CASE + (ESPACE_HAUT - 3 * TAILLE_CASE);
    
            for (j = 0; j < *longueurSerpent; j++)
            {
                if (pomme[i].x == serpent[j].x && pomme[i].y == serpent[j].y)
                {
                    pomme[i].x = rand() % COLONNES * TAILLE_CASE + 5 * TAILLE_CASE;
                    pomme[i].y = rand() % LIGNES * TAILLE_CASE + (ESPACE_HAUT - 3 * TAILLE_CASE);
                }
            }
        /*Eviter que les pommes apparaise sur les obstacles*/
            for (j = 0; j < nbr_obstacle; j++)
            {
                while ((pomme[i].x == caisse[j].x && pomme[i].y == caisse[j].y))
                {
                    pomme[i].x = rand() % COLONNES * TAILLE_CASE + 5 * TAILLE_CASE;
                    pomme[i].y = rand() % LIGNES * TAILLE_CASE + (ESPACE_HAUT - 3 * TAILLE_CASE);

                    j = 0;
                }
            }
    /*Pour dessiner les pommes*/
            dessin2couleurRond(pomme, "black", "red");
    /*Pour ajouter +5 a chaque pastilles manger*/
            *score += 5;
            *effacer += 2;
    /*Afficher le score*/
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(825, 655, 150, 40);
            ChoisirCouleurDessin(CouleurParNom("white"));
            sprintf(texte, "Score : %3d", *score);
            EcrireTexte(825, 685, texte, 2);
        }
    }
}
/*Fonction qui permet de deplacer le serpent*/
void deplacerSerpent(int longueurSerpent, Segment *serpent, int effacer, int direction, char *texte, int score, int minutes, int secondes, int *jeu,int *recommencer)
{
    int i;
    int deuxiemeRectangleY, deuxiemeRectangleX;
    effacerSerpent(serpent, longueurSerpent, effacer);
    for (i = longueurSerpent; i > 0; i--)
    {

        serpent[i] = serpent[i - 1];
    }
    switch (direction)
    {
    case 1:
        serpent[0].x += TAILLE_CASE;
        break;
    case -1:
        serpent[0].x -= TAILLE_CASE;
        break;
    case 2:
        serpent[0].y -= TAILLE_CASE;
        break;
    case -2:
        serpent[0].y += TAILLE_CASE;
        break;
    }
    /*Eviter que le serpent puisse se retourner sur lui meme*/

    for (i = 1; i < longueurSerpent; i++)
    {
        if (serpent[0].x == serpent[i].x && serpent[0].y == serpent[i].y)
        {
        perdu(texte, score, minutes, secondes, recommencer, jeu);

        }
    }


/*Dessiner le serpent*/
    for (i = 1; i < longueurSerpent; i++)
    {

        ChoisirCouleurDessin(CouleurParNom("black"));
        RemplirRectangle(serpent[0].x + 2, serpent[0].y + 5, 3, 3);
        RemplirRectangle(serpent[0].x + 5, serpent[0].y + 5, 3, 3);
        ChoisirCouleurDessin(CouleurParNom("darkgreen"));
        RemplirRectangle(serpent[0].x, serpent[0].y, TAILLE_CASE, TAILLE_CASE);

        deuxiemeRectangleX = serpent[0].x + (TAILLE_CASE - 10) / 2;
        deuxiemeRectangleY = serpent[0].y + (TAILLE_CASE - 10) / 2;

        ChoisirCouleurDessin(CouleurParNom("orange"));
        RemplirRectangle(deuxiemeRectangleX, deuxiemeRectangleY, 10, 10);

        ChoisirCouleurDessin(CouleurParNom("darkgreen"));
        RemplirRectangle(serpent[i].x, serpent[i].y, TAILLE_CASE, TAILLE_CASE);

        deuxiemeRectangleX = serpent[i].x + (TAILLE_CASE - 10) / 2;
        deuxiemeRectangleY = serpent[i].y + (TAILLE_CASE - 10) / 2;

        ChoisirCouleurDessin(CouleurParNom("orange"));
        RemplirRectangle(deuxiemeRectangleX, deuxiemeRectangleY, 10, 10);
    }
}
/*Limite du terrain*/
void terrain(char *texte, Segment *serpent, int score, int minutes, int secondes, int *jeu, int *recommencer)
{
    int i,j;
    if (serpent[0].x < 5 * TAILLE_CASE || serpent[0].x >= LARGEUR_ECRAN_JEU + 5 * TAILLE_CASE || serpent[0].y < ESPACE_HAUT - 3 * TAILLE_CASE || serpent[0].y >= HAUTEUR_ECRAN_JEU + 2 * TAILLE_CASE)
    {
        ChoisirCouleurDessin(CouleurParNom("black"));
        RemplirRectangle(serpent[0].x, serpent[0].y, TAILLE_CASE, TAILLE_CASE);
        /*Execution de la fontion perdu si il sort du terrain*/
        perdu(texte, score, minutes, secondes,recommencer, jeu);
        
  

    }
    if(score > 85 && score < 95){
        for(i=0;i<2;i++){
            for(j=30;j<40;j++){
                ChoisirCouleurDessin(CouleurParNom("black"));
                RemplirRectangle(i*TAILLE_CASE,j*TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
            }
        }

        
    }

}