#pragma once

#include <libsx.h>

#define x 9
#define y 9

typedef enum {dead,alive} etat;

etat grille[x][y]={{0,0,0,1,0,0,0,1,0},
				   {0,0,0,1,0,0,0,1,0},
				   {0,1,0,1,0,0,0,1,0},
				   {0,0,0,1,0,1,0,1,0},
				   {0,1,0,1,0,1,0,1,0},
				   {0,0,0,1,0,0,1,1,0},
				   {0,1,0,1,1,0,1,1,0},
				   {0,0,0,1,0,0,1,1,0},
				   {0,1,0,1,0,1,0,1,0}};
int  voisin[x][y];

extern int nombresdesvoi(const etat *, int, int);
extern void Voisins(const etat *, int *);
extern void Miseajournormal(etat *, int *);
extern void Miseajourday_night(etat *, int *);