/*
 *  Les fonctions du modèle qui assurent le calcul de l'état des cases (mortes ou vivantes) et
 *  actualise leur valeurs à chaque tour.
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
    if(b>=0 && b< x ){/*au cas on est dans les bord ==> on peut pas acceder à certain espace de la matrice grille*/
      for(a=j-1;a<j+2;a++){
      //matrice 3*3 de centre i,j 
        if(a>=0 && a<y){
          if(*(grille+(x*b)+a)==alive) nbv++;//cellule vivant sur la matrice 3*3 de centre i,j => nombre des voisins +1
        }
      }
    }
  }
  if(*(grille+(x*i)+j)==alive) nbv--;// au cas où la cellule d'indice i,j est aussi vivant,on soustri 1 de nbv 
  return nbv;// la fonction renvoi le nombre des voisins de la cellule i,j
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
      *(voisin+(x*i)+j)=nbDeVoisins(grille,i,j);//voisin[i][j]=nombre des voisins de la cellule i,j
    }
  }
}

// Rôle : procédure qui fait la mise a jour normal de jeu de la vie
void updateNormal(Donnes *d){
  etat *grille=d->grille[0];
  int *voisin=d->voisin[0];
  int i,j;
  for(i=0; i< x; i++){
    for(j=0;j<y;j++){
      if(*(grille+(i*x)+j)==alive){
        if(*(voisin+(i*x)+j)==2||*(voisin+(i*x)+j)==3) *(grille+(i*x)+j)=alive;/*2 voisins ou 3 voisin => l'individu est vivant*/  
        else *(grille+(i*x)+j)=dead;// sinon il meurt
      }
      else {
        if(*(voisin+(i*x)+j)==3) *(grille+(i*x)+j)=alive;/*si il etait mort et il a 3 voisin ==> rendre vivant*/   
      }
    }
  }
}

// Rôle : procédure qui fait la mise a jour day and night de jeu de la vie
void updateDayNight(Donnes *d){
  etat *grille=d->grille[0];
  int *voisin=d->voisin[0];
  int i,j;
  for(i=0; i< x; i++){
    for(j=0;j<y;j++){
      if(*(grille+(i*x)+j)==alive){
        if(*(voisin+(i*x)+j)==3||*(voisin+(i*x)+j)==4||*(voisin+(i*x)+j)==6||*(voisin+(i*x)+j)==7||*(voisin+(i*x)+j)==8) *(grille+(i*x)+j)=alive;//3,4,6,7,8 voisins => l'individu reste vivant  
        else *(grille+(i*x)+j)=dead; //sinon il meurt
      }
      else {
      //si l'individu est mort
        if(*(voisin+(i*x)+j)==3||*(voisin+(i*x)+j)==6||*(voisin+(i*x)+j)==7||*(voisin+(i*x)+j)==8) *(grille+(i*x)+j)=alive;/*si il etait mort et il a 3,6,7,8 voisins ==> rendre vivant*/            
      }
    }
  }
}

/*
 Role: remplie la grille avec des population aleatoire
*/
void randomPopulation(Donnes *d){
  etat *population=d->grille[0];
  srand(time(NULL));
  for(int i=0;i<x;i++){
    for(int j=0;j<y;j++){
      *(population+i*x+j)=rand()&1; //on prend un bit d'un nombre random qui peut etre 1 ou 0 ==> remplissage aleatoire de la grille
      }}}
  
/*
 Role: implimentation de la grille à partir d'un fichier deja lu par la fonction "fopen"
*/
void fileToGrid(Donnes *d,FILE *in){
  etat *population=d->grille[0];
  int i=0;
  char Tab[x][y]={};
  while(i<x){
    fgets(&Tab[i][0],255,in);//copie une ligne des caractères lu sur le fichier dans le tableau des caractères 'Tab' (on a pris 255 aleatoirement car on est bien loin de ce nombre de caractére par ligne) 
    i++;
  }
  
  for(int i=0;i<x;i++){
    for(int j=0;j<y;j++){
      if(Tab[i][j]=='0') *(population+i*x+j)=dead;// si le caractère lu à l'indice i,j est '0'==> cellule est meurt
      if(Tab[i][j]=='1') *(population+i*x+j)=alive;//  si le caractère lu à l'indice i,j est '1'==> cellule vivant
    }
  }
}
/*
 Role: initialisation de la grille à 0
*/
void initGrid(Donnes *d){
  etat *population=d->grille[0];
  for(int i=0;i<x;i++){
    for(int j=0;j<y;j++){
      *(population+i*x+j)=dead;//grille[i][j]=dead
      }
   }
}
/*
 Role: initialisation de nombre d'itération (utiliser à chaque fois on change de structure ou de fenetre de style)
*/ 
void initNbIteration(Donnes *d){
  d->nbriteration=-1;
 }