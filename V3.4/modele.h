/*  Authors Yassine El Aissaoui & Olivier Grima
 */
#pragma once

#include <libsx.h>

// taille de la matrice grille/voisin
#define x 25 
#define y 25
typedef enum {dead,alive} etat;

typedef struct {
etat grille[x][y];// la grille qui contient la population
int  voisin[x][y];// matrice avec la meme taille x,y que la grille,qui contient le nombre de voisins de chaque cellule
int nbriteration;// le nombre d'iterations effectuées
}Donnes;

extern int nbDeVoisins(const etat *, int, int);
extern void Voisins(Donnes *);
extern void updateNormal(Donnes *);
extern void updateDayNight(Donnes *);
extern void randomPopulation(Donnes *);
extern void fileToGrid(Donnes *,FILE *);
extern void initNbIteration(Donnes *);
extern void initGrid(Donnes *);
