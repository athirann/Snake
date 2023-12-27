#include <stdlib.h>
#include <graph.h>
#include <stdio.h>
#include "vitesse.h"


void Attendre(unsigned int millisecondes)
{
    unsigned long debut = Microsecondes();
    unsigned long attente = millisecondes * 1000;
    while (Microsecondes() - debut < attente)
    {
    }
}

void ajusterVitesse(int *vitesse, int *score, int *scoretemp)
{
    if (*score > *scoretemp && *score < 500)
    {
        *vitesse -= 7;
        *scoretemp += *scoretemp;
    }
}