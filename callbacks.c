/* Ce fichier contient les callbacks du jeu
 * Authors Yassine El Aissaoui & Olivier Grima
 */

#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
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
 *  Rôle : update l'affichage après le clic sur le bouton play sur la fenêtre de jeu standard
 */
void playnormal(Widget w,void *d){	
ClearDrawArea();
etat *data= (etat *)d;
int i,j;
for(i=0; i<x; i++){
  for(j=0; j<y;j++){
 	if((*(data+i*x+j))==dead){
 	DrawBox(j*20,i*20,20,20);
    	
    	}
 	else{
 	DrawFilledBox(j*20,i*20,20,20);
    	 
    	  }}}
	
Voisins(d,&voisin[0][0]);
Miseajournormal(d,&voisin[0][0]);	    
}


/*
 *  Rôle : update l'affichage après le clic sur le bouton play sur la fenêtre du variant day & night
 */
void playvariant(Widget w,void *d){	
ClearDrawArea();
etat *data= (etat *)d;
int i,j;
for(i=0; i<x; i++){
  for(j=0; j<y;j++){
 	if((*(data+i*x+j))==dead){
 	DrawBox(j*20,i*20,20,20);
    	
    	}
 	else{
 	DrawFilledBox(j*20,i*20,20,20);
    	 
    	  }}}
	
Voisins(d,&voisin[0][0]);
Miseajourday_night(d,&voisin[0][0]);	    
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

