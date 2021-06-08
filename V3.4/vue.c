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
#include "vue.h"



/* Rôle : procédure qui affiche la nouvelle fenetre de l'interface graphique quand on choisit le fonctionnement normal 
 *        du jeu de la vie 
 */
void createNormalGrid(Widget w,void *d){
  	MakeWindow("Jeu Standard", NULL, 1);// création de la fenetre
  	/*------création des widgets-------*/
	//Widget MenuButton=MakeMenu("Structures");
	//Widget MenuItems = MakeMenuItem(MenuButton,"menuItems",structDef,structList[0]);

  	Widget Draw_grille=MakeDrawArea(19*x,19*y,traceDeBase,d);//Drawarea où on va dessiner la grille
	Widget scrollBar = MakeHorizScrollbar(150, scrollCallback, NULL);//scrollbar pour varier la vitesse

 	Widget quitter=MakeButton("Quitter",quit,NULL);// bouton pour quitter
	Widget start=MakeButton("Step-by-step",playNormal,d);//pas-à-pas bouton
	Widget oscillateur=MakeButton("Oscillateur",structOscillateur,d);//bouton pour fixer la structure on oscillateur
	Widget stable=MakeButton("Stable",structStable,d);//bouton pour fixer la structure stable
	Widget vaisseau=MakeButton("Vaisseau",structVaisseau,d);//bouton pour la structure vaisseau
	Widget mathusalem=MakeButton("Mathusalem",structMathusalem,d);//bouton pour la structure mathusalem
	Widget aleatoire=MakeButton("Aleatoire",randomStruct,d);//bouton pour une structure aleatoire
	Widget starttoggle=MakeToggle("Automatique",FALSE,NULL,nbToggleNormal,d);//bouton pour l'enchainement des iterations
	iteration=MakeLabel("Choissez une structure dans le menu");//label pour afficher le nombre d'iterations déclarées comme variable globale afin de manipuler son contenu sur callacks.c
	Widget scrollTxt = MakeLabel("Vitesse d'execution");
	Widget structure=MakeLabel("Structure:");
	Widget txtiteration=MakeLabel("Nombre d'iterations");

	SetScrollbar(scrollBar,50.0,100.0,1.0);//taille de scrollbar
  	/*------assemblage et positionnement des widgets-------*/
	//SetWidgetPos(MenuButton,PLACE_UNDER,quitter,PLACE_RIGHT,structure);

 	SetWidgetPos(quitter,PLACE_UNDER,Draw_grille,NO_CARE,NULL);
	SetWidgetPos(start,PLACE_RIGHT,quitter,PLACE_UNDER,Draw_grille);
	SetWidgetPos(starttoggle,PLACE_RIGHT,start,PLACE_UNDER,Draw_grille);
	SetWidgetPos(structure,PLACE_UNDER,quitter,NO_CARE,NULL);
	SetWidgetPos(aleatoire,PLACE_UNDER,structure,NO_CARE,NULL);
	SetWidgetPos(oscillateur,PLACE_UNDER,structure,PLACE_RIGHT,aleatoire);
	SetWidgetPos(stable,PLACE_UNDER,structure,PLACE_RIGHT,oscillateur);
	SetWidgetPos(vaisseau,PLACE_UNDER,structure,PLACE_RIGHT,stable);
	SetWidgetPos(mathusalem,PLACE_UNDER,structure,PLACE_RIGHT,vaisseau);
	SetWidgetPos(txtiteration,PLACE_UNDER,mathusalem,NO_CARE,NULL);
	SetWidgetPos(iteration,PLACE_RIGHT,txtiteration,PLACE_UNDER,mathusalem);
	SetWidgetPos(scrollTxt,PLACE_UNDER,txtiteration,NO_CARE,NULL);
	SetWidgetPos(scrollBar,PLACE_RIGHT,scrollTxt,PLACE_UNDER,txtiteration);

	GetStandardColors();
	ShowDisplay();// pour afficher l'interface
}

/* 
 * Rôle : procédure qui affiche la nouvelle fenetre de l'interface graphique quand on selectionne le variant day and night
 */
void createVariantGrid(Widget w,void *d){
  	MakeWindow("Day & Night", NULL, 1);// création de la  fenetre
  	/*------création des widgets-------*/
  	Widget Draw_grille=MakeDrawArea(19*x,19*y,traceDeBase,d);//Drawarea où on va dessiner la grille
	Widget scrollBar = MakeHorizScrollbar(150, scrollCallback, NULL);//scrollbar pour varier la vitesse
 	Widget quitter=MakeButton("Quitter",quit,NULL);// bouton pour quitter
	Widget start=MakeButton("Step-by-step",playVariant,d);//pas-à-pas bouton
	Widget oscillateur=MakeButton("Oscillateur",structOscillateur,d);//bouton pour fixer la structure on oscillateur
	Widget stable=MakeButton("Stable",structStable,d);//bouton pour fixer la structure stable
	Widget vaisseau=MakeButton("Vaisseau",structVaisseau,d);//bouton pour fixer la structure vaisseau
	Widget mathusalem=MakeButton("Mathusalem",structMathusalem,d);//bouton pour fixer la structure mathusalem
	Widget aleatoire=MakeButton("Aleatoire",randomStruct,d);//bouton pour fixer une structure aleatoire
	Widget starttoggle=MakeToggle("Automatique",FALSE,NULL,nbToggleVariant,d);//bouton pour l'enchainement des iterations
	iteration=MakeLabel("Choissez une structure dans le menu");//label pour afficher le nombre d'iterations déclarées comme variable globale afin de manipuler son contenu sur callacks.c
	Widget scrollTxt = MakeLabel("Vitesse d'execution");
	Widget structure=MakeLabel("Structure:");
	Widget txtiteration=MakeLabel("Nombre d'iterations");
	SetScrollbar(scrollBar,50.0,100.0,1.0);//taille de scrollbar
	/*------assemblage et positionnement des widgets-------*/
 	SetWidgetPos(quitter,PLACE_UNDER,Draw_grille,NO_CARE,NULL);
	SetWidgetPos(start,PLACE_RIGHT,quitter,PLACE_UNDER,Draw_grille);
	SetWidgetPos(starttoggle,PLACE_RIGHT,start,PLACE_UNDER,Draw_grille);
	SetWidgetPos(structure,PLACE_UNDER,quitter,NO_CARE,NULL);
	SetWidgetPos(aleatoire,PLACE_UNDER,structure,NO_CARE,NULL);
	SetWidgetPos(oscillateur,PLACE_UNDER,structure,PLACE_RIGHT,aleatoire);
	SetWidgetPos(stable,PLACE_UNDER,structure,PLACE_RIGHT,oscillateur);
	SetWidgetPos(vaisseau,PLACE_UNDER,structure,PLACE_RIGHT,stable);
	SetWidgetPos(mathusalem,PLACE_UNDER,structure,PLACE_RIGHT,vaisseau);
	SetWidgetPos(txtiteration,PLACE_UNDER,mathusalem,NO_CARE,NULL);
	SetWidgetPos(iteration,PLACE_RIGHT,txtiteration,PLACE_UNDER,mathusalem);
	SetWidgetPos(scrollTxt,PLACE_UNDER,txtiteration,NO_CARE,NULL);
	SetWidgetPos(scrollBar,PLACE_RIGHT,scrollTxt,PLACE_UNDER,txtiteration);
	GetStandardColors();
	ShowDisplay();// pour afficher l'interface					
}


	
/*
 * Rôle : procédure qui crée la fenêtre d'accueil qui va nous diriger vers la grille pour visualiser le fonctionnement du
 *        jeu de la vie ou sa variant day and night
 */
void init_display(int argc, char *argv[], void *d){

    /*On crée les widgets, les écritures et titres de notre première fenetre*/
    GetStandardColors();
    XFont styleTitre = GetFont("-bitstream-courier 10 pitch-bold-r-normal--0-0-0-0-m-0-adobe-standard"); 
    XFont styleText = GetFont("-bitstream-bitstream charter-bold-i-normal--0-0-0-0-p-0-adobe-standard");

    /*------création et positionnement des widgets-------*/
    // Les Labels et consignes       
	Widget titre = MakeLabel("                        Jeu de la vie\n\n ");
	Widget consigne = MakeLabel("\t Le jeu de la vie est un jeu de simulation au sens mathematique plutot que ludique.\nBien que n'etant pas decrit par la theorie des jeux, certains le decrivent comme un\n\"jeu a zero joueur\"\n\nDeux styles de jeu s'offrent pour vous :\n\n        Premier style: le jeu standard de la vie\n        Deuxieme style: la variant Day & Night\n\n\n");
	SetWidgetPos(consigne, PLACE_UNDER, titre, NO_CARE, NULL);
	SetWidgetFont(titre, styleTitre);
	SetWidgetFont(consigne, styleText);


    // Les 2 boutons de style
		        
	Widget textJouer = MakeLabel("\nPour jouer, veuillez choisir un style de jeu, puis choisISsez une structure sur \nla nouvelle fenetre qui s'ouvre\n\n");
	Widget jeunormal = MakeButton("\n  Jeu standard \n ", createNormalGrid, d);
	SetBgColor(jeunormal, GetRGBColor(0, 255, 0));
	Widget jeuvariant = MakeButton("\n  Day & Night  \n ", createVariantGrid, d);
	SetBgColor(jeuvariant, GetRGBColor(244, 102, 27));

	SetWidgetPos(textJouer, PLACE_UNDER, consigne, NO_CARE, NULL);
	SetWidgetPos(jeunormal, PLACE_UNDER, textJouer, NO_CARE, NULL);
	SetWidgetPos(jeuvariant, PLACE_RIGHT, jeunormal, PLACE_UNDER, textJouer);
	SetWidgetFont(textJouer, styleText);

    // Le bouton quitter
	Widget quitter = MakeButton(  "\n      QUIT       \n ", quit, NULL);

	SetWidgetPos(quitter, PLACE_UNDER, jeunormal, NO_CARE, NULL);

	
    // affichage de la fenetre
	ShowDisplay();
}
