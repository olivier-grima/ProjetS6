/*  Authors Yassine El Aissaoui & Olivier Grima
 */
#pragma once

#include <libsx.h>

#define x 16
#define y 16
typedef enum {dead,alive} etat;

typedef struct {
etat grille[x][y];
int  voisin[x][y];
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
