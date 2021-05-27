/*  Authors Yassine El Aissaoui & Olivier Grima
 */
#pragma once

#include <libsx.h>

#define x 16
#define y 16

typedef enum {dead,alive} etat;

int  voisin[x][y];

extern int nbDeVoisins(const etat *, int, int);
extern void Voisins(const etat *, int *);
extern void updateNormal(etat *, int *);
extern void updateDayNight(etat *, int *);
extern void randomPopulation(etat *);
extern void fileToGrid(etat *,FILE *);
