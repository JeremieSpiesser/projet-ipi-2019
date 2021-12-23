#include <stdio.h>
#include <math.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "grille.h"
#include "curseur.h"
#include "pile.h"

/*@requires un char* se finissant par un '\0'
@assigns rien
@ensures renvoie la longueur de ce mot
ex : strlen("bonjour") -> 7
*/
int mot_len(char* mot){
    int i = 0;
    //Car on suppose dans @requires que le char* se finit par un '\0'
    while ( mot[i]!='\0'){
        i = i+1;
    }
    return i;
}

int main(int argc, char** argv){
    srand(time(NULL));//Pour les directions aléatoires pour la suite
    pile lapile=NULL;

    //Ouverture du fichier dans fd
    if (argc <= 1){
        printf("Message d'usage : mettre un fichier\n");
        return 1;
    }
    

    char* file_location = argv[1];

    FILE* fd = fopen(file_location,"r");
    if (fd == NULL){
        printf("Erreur d'ouverture du fichier\n");
        return 2;
    }

    //Lecture des dimensions dans hauteur et largeur
    char buffer[256];
    int hauteur, largeur;
    fgets(buffer, 256, fd);
    sscanf(buffer, "%d %d", &largeur, &hauteur);

    if (hauteur <= 0 || largeur <=0){
        printf("Dimensions incorrectes \n");
        return 3;
    }

    // Création de la grille dans lagrille
    grille lagrille ;
    lagrille = creer_grille(hauteur, largeur);
    int i=0;

    for (i=0; i < lagrille.hauteur; i = i+1){
        fgets(lagrille.contenu[i], lagrille.largeur + 2, fd);
    }

    //Vérification que la grille soit carrée
    for (i=0; i < lagrille.hauteur; i = i+1){
        if (mot_len(lagrille.contenu[i]) != lagrille.largeur +1 ){
            printf("Erreur : la grille n'est pas carrée\n");
            return 4;
        }
    }

    // Exécution
    curseur lecurseur = init_curseur();
    //On suppose que le fichier est un programme correct donc qu'on atteint un '@'
    //Dans ce cas, etape_suivante fait passer la valeur lecurseur.end_programme = 1
    //et le programme s'arrête
    while (lecurseur.end_programme !=1){
        etape_suivante(&lagrille,&lecurseur,&lapile);
    }


    //Fin du programme on libère les cases mémoires utilisées
    free_grille(&lagrille);
    if (lapile != NULL){
        free_pile(&lapile);
    }

    fclose(fd);
}