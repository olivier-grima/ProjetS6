/* Ce fichier contient les callbacks du jeu
 * Authors Yassine El Aissaoui & Olivier Grima
 */

#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include <errno.h>
#include "modele.h"
#include "vue.h"
#include "callbacks.h"

/* 
 * Rôle : termine l'éxécution du jeu si le jeu est en cours 
 * Quitte le jeu si l'utilisateur est sur la page d'accueil
 */
void quit(Widget w,void *d) {
  int yn = GetYesNo("Voulez vous quitter ?"); //Demande à l'utilisateur s'il souhaite quitter la fenêtre où il se trouve
  if (yn!=0)        //ferme la fenêtre si l'utilisateur clique sur "yes"
    CloseWindow();
}

 
/*
 Role: fonction qui réinitialise la grille à partir d'une structure lu sur le fichier 'oscillateur'
 */
void structOscillateur(Widget w,void *d){
  FILE *in;
  if((in =fopen("oscillateur","r")) == NULL) {
    perror("oscillateur");
    exit(errno);
  }
  fichiertogrille(d,in);
  fclose(in);}
/*
 Role: fonction qui réinitialise la grille à partir d'une structure lu sur le fichier 'stable'
 */
void structStable(Widget w,void *d){
  FILE *in;
  if((in =fopen("stable","r")) == NULL) {
    perror("stable");
    exit(errno);
  }
  fichiertogrille(d,in);
  fclose(in);}
/*
 Role: fonction qui réinitialise la grille à partir d'une structure lu sur le fichier 'Vaisseau'
 */ 
void structVaisseau(Widget w,void *d){
  FILE *in;
  if((in =fopen("Vaisseau","r")) == NULL) {
    perror("Vaisseau");
    exit(errno);
  }
  fichiertogrille(d,in);
  fclose(in);
}
/*
 Role: fonction qui réinitialise la grille à partir d'une structure lu sur le fichier 'mathusalhem'
 */ 
void structMathusalhem(Widget w,void *d){
  FILE *in;
  if((in =fopen("mathusalhem","r")) == NULL) {
    perror("mathusalhem");
    exit(errno);
  }
  fichiertogrille(d,in);
  fclose(in);
}
   
        
        

void newDisplay(void *d){
	ClearDrawArea();
	etat *data= (etat *)d;
	int i,j;
	for(i=0; i<x; i++){
		for(j=0; j<y;j++){
			if((*(data+i*x+j))==dead){
				DrawBox(j*20,i*20,20,20);		//affiche une case vide si la cellule est morte
			}
			else{
				DrawFilledBox(j*20,i*20,20,20);	//affiche une case pleine si la cellule est vivante
			}
		}
	}
}

/*
 *  Rôle : update l'affichage après le clic sur le bouton play sur la fenêtre de jeu standard
 */
void playNormal(Widget w,void *d){	
	newDisplay(d);
	Voisins(d,&voisin[0][0]);
	updateNormal(d,&voisin[0][0]);
}


/*
 *  Rôle : update l'affichage après le clic sur le bouton play sur la fenêtre du variant day & night
 */
void playVariant(Widget w,void *d){	
	newDisplay(d);
	Voisins(d,&voisin[0][0]);
	updateDayNight(d,&voisin[0][0]);
}

/*
 *  Rôle : affiche la grille de taille M x N vide
 */
void color(Widget w, int width, int height, void *d){
  int i,j;
  for(i=0;i<x;i++)
    for(j=0;j<y;j++)
      DrawBox(i*20,j*20,20,20);
 }

