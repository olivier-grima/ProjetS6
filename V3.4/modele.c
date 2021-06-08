/*
 *  Les fonctions du modèle qui assurent le calcul de l'état des cases (mortes ou vivantes) et
 *  actualisent leurs valeurs à chaque tour.
 *  Authors Yassine El Aissaoui & Olivier Grima
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "modele.h"



// Rôle : cette fonction calcule les voisins d'une cellule d'indice i et j donnée pour déterminer son état
int nbDeVoisins(const etat *grille,int i,int j){
  int nbv=0;
  int b,a;
  for(b=i-1;b<i+2;b++){
    if(b>=0 && b< x ){/*au cas où on est dans les bords ==> on ne peut pas acceder à certains espaces de la matrice grille*/
      for(a=j-1;a<j+2;a++){
      //matrice 3*3 de centre i,j 
        if(a>=0 && a<y){
          if(*(grille+(y*b)+a)==alive) nbv++;//cellule vivante sur la matrice 3*3 de centre i,j => nombre de voisins +1
        }
      }
    }
  }
  if(*(grille+(y*i)+j)==alive) nbv--;// au cas où la cellule d'indice i,j est aussi vivante,on soustrait 1 à nbv 
  return nbv;// la fonction renvoie le nombre de voisins de la cellule i,j
}

/* Rôle : matrice qui enregistre le nombre de voisins de chaque case dans la grille 
 * Cette matrice a la même taille que la grille
 */
void Voisins(Donnes *d){
  int *voisin=d->voisin[0];
  etat *grille=d->grille[0];
  int i,j;
  for(i=0;i<x;i++){
    for(j=0;j<y;j++){
      *(voisin+(y*i)+j)=nbDeVoisins(grille,i,j);//voisin[i][j]=nombre de voisins de la cellule i,j
    }
  }
}

// Rôle : procédure qui fait la mise à jour normale du jeu de la vie
void updateNormal(Donnes *d){
  etat *grille=d->grille[0];
  int *voisin=d->voisin[0];
  int i,j;
  for(i=0; i< x; i++){
    for(j=0;j<y;j++){
      if(*(grille+(i*y)+j)==alive){
        if(*(voisin+(i*y)+j)==2||*(voisin+(i*y)+j)==3) *(grille+(i*y)+j)=alive;/*2 voisins ou 3 voisins => l'individu est vivant*/  
        else *(grille+(i*y)+j)=dead;// sinon il meurt
      }
      else {
        if(*(voisin+(i*y)+j)==3) *(grille+(i*y)+j)=alive;/*s'il est mort et a 3 voisins ==> rendre vivant*/   
      }
    }
  }
}

// Rôle : procédure qui fait la mise à jour day and night du jeu de la vie
void updateDayNight(Donnes *d){
  etat *grille=d->grille[0];
  int *voisin=d->voisin[0];
  int i,j;
  for(i=0; i< x; i++){
    for(j=0;j<y;j++){
      if(*(grille+(i*y)+j)==alive){
        if(*(voisin+(i*y)+j)==3||*(voisin+(i*y)+j)==4||*(voisin+(i*y)+j)==6||*(voisin+(i*y)+j)==7||*(voisin+(i*y)+j)==8) *(grille+(i*y)+j)=alive;//3,4,6,7,8 voisins => l'individu reste vivant  
        else *(grille+(i*y)+j)=dead; //sinon il meurt
      }
      else {
      //si l'individu est mort
        if(*(voisin+(i*y)+j)==3||*(voisin+(i*y)+j)==6||*(voisin+(i*y)+j)==7||*(voisin+(i*y)+j)==8) *(grille+(i*y)+j)=alive;/*s'il est mort et a 3,6,7,8 voisins ==> rendre vivant*/            
      }
    }
  }
}

/*
 Role: procédure qui remplit la grille avec des populations aleatoires
*/
void randomPopulation(Donnes *d){
  etat *population=d->grille[0];
  srand(time(NULL));
  for(int i=0;i<x;i++){
    for(int j=0;j<y;j++){
      *(population+i*y+j)=rand()&1; //on prend un bit d'un nombre random qui peut etre 1 ou 0 ==> remplissage aleatoire de la grille
      }}}
  
/*
 Role: procédure qui implémente la grille à partir d'un fichier déjà lu par la fonction "fopen"
*/
void fileToGrid(Donnes *d,FILE *in){
  etat *population=d->grille[0];
  int i=0;
  char Tab[x][y]={};
  while(i<x){
    fgets(&Tab[i][0],255,in);//copie une ligne de caractères lus sur le fichier dans le tableau des caractères 'Tab' (on a pris 255 aleatoirement car on est bien loin de ce nombre de caractéres par ligne) 
    i++;
  }
  
  for(int i=0;i<x;i++){
    for(int j=0;j<y;j++){
      if(Tab[i][j]=='0') *(population+i*y+j)=dead;// si le caractère lu à l'indice i,j est '0'==> la cellule est morte
      if(Tab[i][j]=='1') *(population+i*y+j)=alive;//  si le caractère lu à l'indice i,j est '1'==> la cellule est vivante
    }
  }
}
/*
 Role: procédure qui initialise la grille à 0
*/
void initGrid(Donnes *d){
  etat *population=d->grille[0];
  for(int i=0;i<x;i++){
    for(int j=0;j<y;j++){
      *(population+i*y+j)=dead;//grille[i][j]=dead
      }
   }
}
/*
 Role: procédure qui initialise le nombre d'itérations (utilisée à chaque fois qu'on change de structure ou de fenetre de style)
*/ 
void initNbIteration(Donnes *d){
  d->nbriteration=-1;
 }
