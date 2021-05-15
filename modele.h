/*  Authors Yassine El Aissaoui & Olivier Grima
 */
#pragma once

#include <libsx.h>

#define x 9
#define y 9

typedef enum {dead,alive} etat;

int  voisin[x][y];

extern int nombresdesvoi(const etat *, int, int);
extern void Voisins(const etat *, int *);
extern void Miseajournormal(etat *, int *);
extern void Miseajourday_night(etat *, int *);