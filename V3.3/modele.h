/*  Authors Yassine El Aissaoui & Olivier Grima
 */
#pragma once

#include <libsx.h>

#define x 25
#define y 25
typedef enum {dead,alive} etat;

typedef struct {
etat grille[x][y];// la grille qui contient la population
int  voisin[x][y];// matrice avec meme taille x,y que grille,qui contient le nombre des voisins de chaque cellule
int nbriteration;// le nombre d'iteration effectué
}Donnes;

extern int nbDeVoisins(const etat *, int, int);
extern void Voisins(Donnes *);
extern void updateNormal(Donnes *);
extern void updateDayNight(Donnes *);
extern void randomPopulation(Donnes *);
extern void fileToGrid(Donnes *,FILE *);
extern void initNbIteration(Donnes *);
extern void initGrid(Donnes *);
