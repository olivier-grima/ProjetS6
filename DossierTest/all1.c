#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
typedef enum {dead,alive} etat;

#define x 9
#define y 9
etat grille[x][y]={{0,0,0,1,0,0,0,1,0},
		     {0,0,0,1,0,0,0,1,0},
		     {0,1,0,1,0,0,0,1,0},
		     {0,0,0,1,0,1,0,1,0},
		     {0,1,0,1,0,1,0,1,0},
		     {0,0,0,1,0,0,1,1,0},
		     {0,1,0,1,1,0,1,1,0},
		     {0,0,0,1,0,0,1,1,0},
		     {0,1,0,1,0,1,0,1,0}};
int  voisin[x][y];
int normalouvariant;
// fonction qui calcule les voisin d'une cellule d'indice i et j donnée
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

/*matrice qui enregistre le nombre des voisins de chaque case dans la grille (il a la meme taille que la grille)*/
void Voisins(const etat *grille,int  *voisin){
  int i,j;
  for(i=0;i<x;i++){
    for(j=0;j<y;j++){
      *(voisin+(x*i)+j)=nombresdesvoi(grille,i,j);
    }
  }
}

   

/*fonction qui fait la mise a jour normal de jeu de la vie*/
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
/* fonction qui fait la mise a jour day and night de jeu de la vie*/
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



//callback de draw area qui trace la grille vide
void color(Widget w, int width, int height, void *d){
  int i,j;
  for(i=0;i<x;i++)
    for(j=0;j<y;j++)
      DrawBox(i*20,j*20,20,20);
 }

// callback du botton quite
void quit(Widget w,void *d) {
  int yn = GetYesNo("Voulez vous quitter ?");
  if (yn!=0)
    CloseWindow();
}
// callback du bouton play sur la fenetre du jeu standard
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
// call back du bouton play sur la fenetre du variant day & night 
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
/*affichage de la nouvelle fenetre de l'interface graphique quand t-on choisi le fonctionnement normal de jeu de la vie */

void creelagrillenormal(Widget w,void *d){
  	MakeWindow("Jeu Standard", NULL, 1);
  	Widget Draw_grille=MakeDrawArea(20*x,20*y, color, d);
 	Widget quitter=MakeButton("quitter",quit,NULL);
	Widget start=MakeButton("play",playnormal,&grille[0][0]);
 	SetWidgetPos(quitter,PLACE_UNDER,Draw_grille,NO_CARE,NULL);
	SetWidgetPos(start,PLACE_RIGHT,quitter,PLACE_UNDER,Draw_grille);

	GetStandardColors();
	ShowDisplay();}
void creelagrillevariant(Widget w,void *d){
  	MakeWindow("Day & Night", NULL, 1);
  	Widget Draw_grille=MakeDrawArea(20*x,20*y, color, d);
 	Widget quitter=MakeButton("quitter",quit,NULL);
	Widget start=MakeButton("play",playvariant,&grille[0][0]);
 	SetWidgetPos(quitter,PLACE_UNDER,Draw_grille,NO_CARE,NULL);
	SetWidgetPos(start,PLACE_RIGHT,quitter,PLACE_UNDER,Draw_grille);

	GetStandardColors();
	ShowDisplay();}
// la nouvelle fenetre de l'interface graphique quand on selectionne la variant day and night

	
/* Creation de la premier fenetre qui va nous diriger vers la grille pour visualiser le fonctionnement de jeu de la vie ou sa variant day and night*/
void init_display(int argc, char *argv[], void *d){


/*On crée les widget, les ecritures et titres de notre premier fenetre*/



GetStandardColors();
XFont policeTitre = GetFont("-bitstream-courier 10 pitch-bold-r-normal--0-0-0-0-m-0-adobe-standard"); 
XFont policeText = GetFont("-bitstream-bitstream charter-bold-i-normal--0-0-0-0-p-0-adobe-standard");

// la mise en page



 
// Les Labels et consigne       
			Widget titre = MakeLabel("                  Jeu de la vie            \n\n ");
			Widget consigne = MakeLabel("	    Le jeu de la vie est un jeu de simulation au sens mathematique \n plutot que ludique. Bien que n'etant pas decrit par la theorie des jeux,\n certains le decrivent comme un « jeu a zero joueur »\n\n On vous fourni 2 style de jeu , qui sont :\n Premier style: le jeu standard de la vie \n Deuxieme style: la variant Day & night\n\n");

		SetWidgetPos(consigne, PLACE_UNDER, titre, NO_CARE, NULL);
		SetWidgetFont(titre, policeTitre);
		SetWidgetFont(consigne, policeText);



		

// Les 2 buttons de syle
		    
		   
		    
			Widget textJouer = MakeLabel("\nPour jouer,veuillez choisir un style de jeu\n\n");

			Widget jeunormal = MakeButton("\n  Jeu standard \n ", creelagrillenormal, NULL);
			SetBgColor(jeunormal, GetRGBColor(0, 255, 0));
			Widget jeuvariant = MakeButton("\n  Day & Night  \n ", creelagrillevariant, NULL);
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

int main (int argc ,char **argv){
  if(OpenDisplay(argc , argv) == 0) {
    fprintf(stderr ,"Can’t open  display\n");
    return EXIT_FAILURE;}
  init_display(argc,argv,NULL);
  MainLoop ();
  return EXIT_SUCCESS;
}
