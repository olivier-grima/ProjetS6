/*
 *  Rôle : cette vue fabrique l'interface graphique à l'aide de la bibliothèque libsx
 *  
 *  Authors Yassine El Aissaoui & Olivier Grima
 */

#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "modele.h"
#include "callbacks.h"

etat grille[x][y]={{0,0,0,1,0,0,0,1,0},
				   {0,0,0,1,0,0,0,1,0},
				   {0,1,0,1,0,0,0,1,0},
				   {0,0,0,1,0,1,0,1,0},
				   {0,1,0,1,0,1,0,1,0},
				   {0,0,0,1,0,0,1,1,0},
				   {0,1,0,1,1,0,1,1,0},
				   {0,0,0,1,0,0,1,1,0},
				   {0,1,0,1,0,1,0,1,0}};

/* Rôle : affichage de la nouvelle fenetre de l'interface graphique quand t-on choisi le fonctionnement normal 
 *        de jeu de la vie 
 */
void createNormalGrid(Widget w,void *d){
  	MakeWindow("Jeu Standard", NULL, 1);
  	Widget Draw_grille=MakeDrawArea(20*x,20*y, color, d);
 	Widget quitter=MakeButton("quitter",quit,NULL);
	Widget start=MakeButton("play",playNormal,&grille[0][0]);
 	SetWidgetPos(quitter,PLACE_UNDER,Draw_grille,NO_CARE,NULL);
	SetWidgetPos(start,PLACE_RIGHT,quitter,PLACE_UNDER,Draw_grille);

	GetStandardColors();
	ShowDisplay();
}

/* 
 * Rôle : affiche la nouvelle fenetre de l'interface graphique quand on selectionne la variant day and night
 */
void createVariantGrid(Widget w,void *d){
  	MakeWindow("Day & Night", NULL, 1);
  	Widget Draw_grille=MakeDrawArea(20*x,20*y, color, d);
 	Widget quitter=MakeButton("quitter",quit,NULL);
	Widget start=MakeButton("play",playVariant,&grille[0][0]);
 	SetWidgetPos(quitter,PLACE_UNDER,Draw_grille,NO_CARE,NULL);
	SetWidgetPos(start,PLACE_RIGHT,quitter,PLACE_UNDER,Draw_grille);

	GetStandardColors();
	ShowDisplay();
}


	
/*
 * Rôle : Creation de la fenêtre d'accueil qui va nous diriger vers la grille pour visualiser le fonctionnement du
 *        jeu de la vie ou sa variant day and night
 */
void init_display(int argc, char *argv[], void *d){

    //On crée les widget, les ecritures et titres de notre premier fenetre*/
    GetStandardColors();
    XFont policeTitre = GetFont("-bitstream-courier 10 pitch-bold-r-normal--0-0-0-0-m-0-adobe-standard"); 
    XFont policeText = GetFont("-bitstream-bitstream charter-bold-i-normal--0-0-0-0-p-0-adobe-standard");


 /************		MISE EN PAGE		***************/

    // Les Labels et consigne       
		Widget titre = MakeLabel("Jeu de la vie\n\n ");
		Widget consigne = MakeLabel("Le jeu de la vie est un jeu de simulation au sens mathematique plutot que ludique.\nBien que n'etant pas decrit par la theorie des jeux, certains le decrivent comme un\n\"jeu a zero joueur\"\n\nDeux styles de jeu s'offrent à vous :\n\n        Premier style: le jeu standard de la vie\n        Deuxieme style: la variant Day & Night\n\n\nVous pouvez choisir parmis différents presets le positionnement initial des cellules\nvivantes sur la grille.");

		SetWidgetPos(consigne, PLACE_UNDER, titre, NO_CARE, NULL);
		SetWidgetFont(titre, policeTitre);
		SetWidgetFont(consigne, policeText);


    // Les 2 buttons de syle
		        
		Widget textJouer = MakeLabel("\nPour jouer,veuillez choisir un style de jeu ainsi qu'un preset\n\n");

		Widget jeunormal = MakeButton("\n  Jeu standard \n ", createNormalGrid, NULL);
		SetBgColor(jeunormal, GetRGBColor(0, 255, 0));
		Widget jeuvariant = MakeButton("\n  Day & Night  \n ", createVariantGrid, NULL);
		SetBgColor(jeuvariant, GetRGBColor(244, 102, 27));


		SetWidgetPos(textJouer, PLACE_UNDER, consigne, NO_CARE, NULL);
		SetWidgetPos(jeunormal, PLACE_UNDER, textJouer, NO_CARE, NULL);
		SetWidgetPos(jeuvariant, PLACE_RIGHT, jeunormal, PLACE_UNDER, textJouer);
		SetWidgetFont(textJouer, policeText);

    // the quit button
		Widget bQuitter = MakeButton(  "\n      QUIT       \n ", quit, NULL);

		SetWidgetPos(bQuitter, PLACE_UNDER, jeunormal, NO_CARE, NULL);

	
// affichage du fenetre
ShowDisplay();
}