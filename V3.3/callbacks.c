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



static int toggleon_off=0;// variable qui correspond au niveau de toggle (activé ou pas). Valeur impaire => activé/Valeur paire => déclenché
static float valDelay = 1000;//variable qui va controler la vitesse d'execution automatique

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
 *Rôle : permet l'initialisation de la structure sélectionnée
 */
void initStruct(Donnes *d, FILE *in){
  fileToGrid(d,in);//importer la structure lu dans le fichier sur la grille
  initNbIteration(d);// initialisation de nombre d'iteration
  fclose(in);//fermeture de fichier lu
  newDisplay(d);//affiche la grille
}

/*
 *Role: fonction qui réinitialise la grille à partir d'une structure lu sur le fichier 'oscillateur'
 */
void structOscillateur(Widget w,void *d){
  FILE *in;
  if((in =fopen("oscillateur","r")) == NULL) {
    perror("oscillateur");
    exit(errno);
  }// fichier lu sans problème
  initStruct(d,in); //appel de la procédure qui initialise la structure
}

/*
 *Role: fonction qui réinitialise la grille à partir d'une structure lu sur le fichier 'stable'
 */
void structStable(Widget w,void *d){
  FILE *in;
  if((in =fopen("stable","r")) == NULL) {
    perror("stable");
    exit(errno);
  }// fichier lu sans problème
  initStruct(d,in);//appel de la procédure qui initialise la structure
}

/*
 *Role: fonction qui réinitialise la grille à partir d'une structure lu sur le fichier 'Vaisseau'
 */ 
void structVaisseau(Widget w,void *d){
  FILE *in;
  if((in =fopen("Vaisseau","r")) == NULL) {
    perror("Vaisseau");
    exit(errno);
  }// fichier lu sans problème
  initStruct(d,in);//appel de la procédure qui initialise la structure
}

/*
 *Role: fonction qui réinitialise la grille à partir d'une structure lu sur le fichier 'mathusalhem'
 */ 
void structMathusalhem(Widget w,void *d){
  FILE *in;
  if((in =fopen("mathusalhem","r")) == NULL) {
    perror("mathusalhem");
    exit(errno);
  }// fichier lu sans problème
  initStruct(d,in);//appel de la procédure qui initialise la structure
}

/*
 *Role: fonction qui réinitialise la grille aléatoirement
 */ 
void randomStruct(Widget w,void *d){
  randomPopulation(d);//fonction qui initialise la grille aléatoirement
  initNbIteration(d);//initialisation de nombre d'iteration
  newDisplay(d);//affiche l'etat initial 
}
        
/*
 *Role: Refait l'affichage à chaque tour de jeu+ incrementaion de nombre d'iteration
 */         
void newDisplay(Donnes *d){
	ClearDrawArea();
	char nbr[10];//chaine de caracteres qui va contenir le nombre d'iteration
	etat *grille=d->grille[0];//grille va contenir l'adresse de la grille
  d->nbriteration=(d->nbriteration)+1;//on increment le nombre d'iteration pour chaque nouveau affichage
	sprintf(nbr,"%d",d->nbriteration);//on print le nombre d'iteration sur la chaine de caractères
	SetLabel(iteration,nbr);//on change le contenu du widget déclaré comme variable globale par le contenu de la chaine de caractères
	int i,j;
	for(i=0; i<x; i++){
		for(j=0; j<y;j++){
			if((*(grille+i*y+j))==dead){
				DrawBox(j*19,i*19,19,19);		//affiche une case vide si la cellule est morte
			}
			else{
				DrawFilledBox(j*19,i*19,19,19);	//affiche une case pleine si la cellule est vivante
			}
		}
	}
}

/*
 *Antécédant : récupère la valeur de la scrollBar
 *Role: modifie le temps de pause du mode automatique en fonction de la position de la scrollBar 
 */
void scrollCallback(Widget w, float new_val, void *data){
  valDelay = 10000/new_val;// Valdelay (variable static) correspond à la durée entre chaque itération pour le mode automatique qui depend de la valeur reçu par la scrollbar
}

/*
 *Role: Fonction qui enchaine les itération normal dans le cas où le bouton toggle est activé
 */
void autoModeNormal(void *d, XtIntervalId *id){
  //si le nombre d'appui est paire alors on a desactiver le toggle==> on fait pas la mise à jour
  //sinon quand le nombre d'appui est impaire alors on vient de lancer l'enchainement=> on fait la mise à jour normal
  if(toggleon_off%2!=0){
    Voisins(d);//on calcule les nombres de voisins de chaque cellule
    updateNormal(d);// on fait la mise à jour du mode normal de la grille 
    newDisplay(d);//on affiche les individu actuel de la grille
    AddTimeOut(valDelay, (GeneralCB)autoModeNormal, d);//on refait la fonction apres un delai (valDelay)
  }
}

/*
 *Role: Fonction callback de toggle qui enchaine les itération normal.
 */
void CBtogglenormal(Widget w,void *d){
  toggleon_off++;//incrémentation de variable qui correspond au niveau de bouton à chaque appui (impaire=>toggle activé/paire=>toggle declanché) 
  AddTimeOut(valDelay, (GeneralCB)autoModeNormal, d);
}

/*
 *Role: Fonction qui enchaine les itération de style day and night dans le cas où le bouton toggle est activé
 */
void autoModeVariant(void *d, XtIntervalId *id){
  //si le nombre d'appui est paire alors on a desactiver le toggle==> on fait pas la mise à jour
  //sinon quand le nombre d'appui est impaire alors on vient de lancer l'enchainement=> on fait la mise à jour day and night
  if(toggleon_off%2!=0){
    Voisins(d);//on calcule les nombres des voisins de chaque cellule
    updateDayNight(d);// on fait la mise à jour du mode day & night de la grille
    newDisplay(d);//on affiche les individu actuel de la grille
    AddTimeOut(valDelay, (GeneralCB)autoModeVariant, d);//on refait la fonction apres un delai (valDelay)
  }
}

/*
 *Role: Fonction callback de toggle qui enchaine les itération day and night.
 */
void CBtogglevariant(Widget w,void *d){
  toggleon_off++;
  AddTimeOut(valDelay, (GeneralCB)autoModeVariant, d);
}

/*
 *Rôle : update l'affichage après le clic sur le bouton play dans la fenêtre de jeu standard ou lors de l'éxécution automatique avec le bouton Auto
 */
void playNormal(Widget w,void *d){
	Voisins(d);//on calcule le nombre de voisins de chaque cellule
	updateNormal(d);// on fait la mise à jour du mode normal de la grille
  newDisplay(d);//on affiche les individu actuel de la grille
}


/*
 *  Rôle : update l'affichage après le clic sur le bouton play dans la fenêtre du variant day & night ou lors de l'éxécution automatique avec le bouton Auto
 */
void playVariant(Widget w,void *d){	
	Voisins(d);//on calcule les nombres des voisins de chaque cellule
	updateDayNight(d);// on fait la mise à jour du mode day and night de la grille
  newDisplay(d);//on affiche les individu actuel de la grille
}

/*
 *  Rôle : affiche la grille de taille M x N vide et inistilise les itérations et la grille à chaque affichage (pour éviter d'avoir les meme individus quand on change de style de jeu)
 */
void traceDeBase(Widget w, int width, int height, void *d){
  initNbIteration(d);// initialiser le nombre d'iteration à chaque fois on change la fenetre de style de jeu
  initGrid(d);//initialiser la grille à chaque fois on change de fenetre
  int i,j;
  for(i=0;i<x;i++)
    for(j=0;j<y;j++)
      DrawBox(i*19,j*19,19,19);
 }


