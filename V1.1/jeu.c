/* Rôle : ce programme est le jeu de la vie
 * l'interface graphique est programmée à l'aide de la biblothèque libsx
 *
 * Authors Yassine El Aissaoui & Olivier Grima
 */

#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "modele.h"
#include "vue.h"

int main (int argc ,char **argv){
  if(OpenDisplay(argc , argv) == 0) {
    fprintf(stderr ,"Can’t open  display\n");
    return EXIT_FAILURE;
  }
  init_display(argc,argv,NULL);
  MainLoop ();
  return EXIT_SUCCESS;
}