/*
 *  Les fonctions du modèle qui assurent le calcul de l'état des cases (mortes ou vivantes) et
 *  actualise leur valeurs à chaque tour.
 *  Authors Yassine El Aissaoui & Olivier Grima
 */

#include <stdlib.h>
#include <stdio.h>
#include "modele.h"



// Rôle : cette fonction calcule les voisins d'une cellule d'indice i et j donnée pour déterminer son état
int nombresdesvoi(const etat *grille,int i,int j){
  int nbv=0;
  int b,a;
  for(b=i-1;b<i+2;b++){
    if(b>=0 && b< x ){/*au cas on est dans les bord ==> on peut pas acceder à certain espace de la matrice grille*/
      for(a=j-1;a<j+2;a++){
	if(a>=0 && a<y){
	  if(*(grille+(x*b)+a)==alive)
	    nbv++;}
      }
    }
  }
  if(*(grille+(x*i)+j)==alive)
    nbv--;
  return nbv;
}

/* Rôle : matrice qui enregistre le nombre de voisins de chaque case dans la grille 
 * Cette matrice a la même taille que la grille
 */
void Voisins(const etat *grille,int  *voisin){
  int i,j;
  for(i=0;i<x;i++){
    for(j=0;j<y;j++){
      *(voisin+(x*i)+j)=nombresdesvoi(grille,i,j);
    }
  }
}

// Rôle : procédure qui fait la mise a jour normal de jeu de la vie
void Miseajournormal(etat *grille, int *voisin){
  int i,j;
  for(i=0; i< x; i++){
    for(j=0;j<y;j++){
      if(*(grille+(i*x)+j)==alive){
	if(*(voisin+(i*x)+j)==2||*(voisin+(i*x)+j)==3)/*2 voisins ou 3 voisin => l'individu est vivant*/
	  *(grille+(i*x)+j)=alive;
	else
	  *(grille+(i*x)+j)=dead;
      }
      else {
	if(*(voisin+(i*x)+j)==3)/*si il etait mort est il a 3 voisin ==> rendre vivant*/
	  *(grille+(i*x)+j)=alive;}}}}

// Rôle : procédure qui fait la mise a jour day and night de jeu de la vie
void Miseajourday_night(etat *grille, int *voisin){
  int i,j;
  for(i=0; i< x; i++){
    for(j=0;j<y;j++){
      if(*(grille+(i*x)+j)==alive){
	if(*(voisin+(i*x)+j)==3||*(voisin+(i*x)+j)==4||*(voisin+(i*x)+j)==6||*(voisin+(i*x)+j)==7||*(voisin+(i*x)+j)==8)/*3,4,6,7,8 voisins => l'individu rest vivant*/
	  *(grille+(i*x)+j)=alive;
	else
	/*sinon il morts*/
	  *(grille+(i*x)+j)=dead;
      }
      else {
      /* si la cellule est mort*/
	if(*(voisin+(i*x)+j)==3||*(voisin+(i*x)+j)==6||*(voisin+(i*x)+j)==7||*(voisin+(i*x)+j)==8)/*si il etait mort et il a 3,6,7,8 voisins ==> rendre vivant*/
	  *(grille+(i*x)+j)=alive;}}}}