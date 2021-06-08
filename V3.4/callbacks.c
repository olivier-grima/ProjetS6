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



static int toggleon_off=0;// variable qui correspond au niveau de toggle (activé ou pas). Valeur impaire => activée/Valeur paire => déclenchée
static float valDelay = 1000;//variable qui va controler la vitesse d'execution automatique

/* 
 * Rôle : procédure qui termine l'éxécution du jeu si le jeu est en cours 
 * Quitte le jeu si l'utilisateur est sur la page d'accueil
 */
void quit(Widget w,void *d) {
  int yn = GetYesNo("Voulez vous quitter ?"); //Demande à l'utilisateur s'il souhaite quitter la fenêtre où il se trouve
  if (yn!=0)        //ferme la fenêtre si l'utilisateur clique sur "yes"
    CloseWindow();
}

/* 
 *Rôle : procédure qui permet l'initialisation de la structure sélectionnée
 */
void initStruct(Donnes *d, FILE *in){
  fileToGrid(d,in);//importer la structure lue dans le fichier sur la grille
  initNbIteration(d);// initialisation du nombre d'iterations
  fclose(in);//fermeture du fichier lu
  newDisplay(d);//affiche la grille
}

/*
 *Role: procédure qui réinitialise la grille à partir d'une structure lue sur le fichier 'oscillateur'
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
 *Role: procédure qui réinitialise la grille à partir d'une structure lue sur le fichier 'stable'
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
 *Role: procédure qui réinitialise la grille à partir d'une structure lue sur le fichier 'Vaisseau'
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
 *Role: procédure qui réinitialise la grille à partir d'une structure lue sur le fichier 'mathusalhem'
 */ 
void structMathusalem(Widget w,void *d){
  FILE *in;
  if((in =fopen("mathusalhem","r")) == NULL) {
    perror("mathusalhem");
    exit(errno);
  }// fichier lu sans problème
  initStruct(d,in);//appel de la procédure qui initialise la structure
}

/*
 *Role: procédure qui réinitialise la grille aléatoirement
 */ 
void randomStruct(Widget w,void *d){
  randomPopulation(d);//procédure qui initialise la grille aléatoirement
  initNbIteration(d);//initialisation du nombre d'iterations
  newDisplay(d);//affiche l'état initial 
}
        
/*
 *Role: procédure qui refait l'affichage à chaque tour de jeu+ incrementaion du nombre d'iterations
 */         
void newDisplay(Donnes *d){
	ClearDrawArea();
	char nbr[10];//chaine de caracteres qui va contenir le nombre d'iterations
	etat *grille=d->grille[0];//grille va contenir l'adresse de la grille
  d->nbriteration=(d->nbriteration)+1;//on incremente le nombre d'iterations pour chaque nouvel affichage
	sprintf(nbr,"%d",d->nbriteration);//on affiche le nombre d'iterations sur la chaine de caractères
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
 *Role: procédure qui modifie le temps de pause du mode automatique en fonction de la position de la scrollBar 
 */
void scrollCallback(Widget w, float new_val, void *data){
  valDelay = 10000/new_val;// Valdelay (variable static) correspond à la durée entre chaque itération pour le mode automatique qui depend de la valeur reçue par la scrollbar
}

/*
 *Role: procédure qui enchaine les itérations normales dans le cas où le bouton toggle est activé
 */
void autoModeNormal(void *d, XtIntervalId *id){
  //si le nombre d'appui est pair alors on a desactivé le toggle==> on ne fait pas la mise à jour
  //sinon quand le nombre d'appui est impair alors on vient de lancer l'enchainement=> on fait la mise à jour normale
  if(toggleon_off%2!=0){
    Voisins(d);//on calcule le nombre de voisins de chaque cellule
    updateNormal(d);// on fait la mise à jour du mode normal de la grille 
    newDisplay(d);//on affiche les individus actuels de la grille
    AddTimeOut(valDelay, (GeneralCB)autoModeNormal, d);//on refait la procédure après un délai (valDelay)
  }
}

/*
 *Role: procédure callback de toggle qui enchaine les itérations normales.
 */
void nbToggleNormal(Widget w,void *d){
  toggleon_off++;//incrémentation de la variable qui correspond à chaque appui au niveau du bouton  (impair=>toggle activé / pair=>toggle désactivé) 
  AddTimeOut(valDelay, (GeneralCB)autoModeNormal, d);
}

/*
 *Role: procédure qui enchaine les itérations de style day and night dans le cas où le bouton toggle est activé
 */
void autoModeVariant(void *d, XtIntervalId *id){
  //si le nombre d'appui est pair alors on a desactivé le toggle==> on ne fait pas la mise à jour
  //sinon quand le nombre d'appui est impair alors on vient de lancer l'enchainement=> on fait la mise à jour day and night
  if(toggleon_off%2!=0){
    Voisins(d);//on calcule le nombre de voisins de chaque cellule
    updateDayNight(d);// on fait la mise à jour du mode day & night de la grille
    newDisplay(d);//on affiche les individus actuels de la grille
    AddTimeOut(valDelay, (GeneralCB)autoModeVariant, d);//on refait la procédure après un délai (valDelay)
  }
}

/*
 *Role: procédure callback de toggle qui enchaine les itérations day and night.
 */
void nbToggleVariant(Widget w,void *d){
  toggleon_off++;
  AddTimeOut(valDelay, (GeneralCB)autoModeVariant, d);
}

/*
 *Rôle : procédure qui met à jour l'affichage après le clic sur le bouton play dans la fenêtre de jeu standard ou lors de l'éxécution automatique avec le bouton Auto
 */
void playNormal(Widget w,void *d){
	Voisins(d);//on calcule le nombre de voisins de chaque cellule
	updateNormal(d);// on fait la mise à jour du mode normal de la grille
  newDisplay(d);//on affiche les individus actuels de la grille
}


/*
 *  Rôle : procédure qui met à jour l'affichage après le clic sur le bouton play dans la fenêtre du variant day & night ou lors de l'éxécution automatique avec le bouton Auto
 */
void playVariant(Widget w,void *d){	
	Voisins(d);//on calcule le nombre de voisins de chaque cellule
	updateDayNight(d);// on fait la mise à jour du mode day and night de la grille
  newDisplay(d);//on affiche les individus actuels de la grille
}

/*
 *  Rôle : procédure qui affiche la grille de taille M x N vide et initialise les itérations et la grille à chaque affichage (pour éviter d'avoir les memes individus quand on change de style de jeu)
 */
void traceDeBase(Widget w, int width, int height, void *d){
  initNbIteration(d);// initialiser le nombre d'iterations à chaque fois qu'on change la fenetre de style de jeu
  initGrid(d);//initialiser la grille à chaque fois qu'on change de fenetre
  int i,j;
  for(i=0;i<x;i++)
    for(j=0;j<y;j++)
      DrawBox(i*19,j*19,19,19);
 }


