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
    char input_buffer[256];

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
        printf("Dimensions incorrectes (négatives) \n");
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

    // Création du backup pour restart
    grille lagrille_backup = copy_grille(lagrille);

    curseur lecurseur = init_curseur();

    int stop = 0; //Si 1, on sort du débuggueur
    int cmd_prec = 0 ;//Contient le code de la dernière commande lancée
    int go_prec=0; //Vaut 1 si l'utilisateur appuye sur entrée.
    //Permet de choisir la dernière commande dans le if ligne 98, en combinaison avec la variable cmd_prec

    while(stop!=1){
        afficher_grille(lagrille, lecurseur.x , lecurseur.y);
        afficher_pile(lapile);
        printf(">");
        fgets(input_buffer,256,stdin);
        char cmd[256];
        int arg=0;
        sscanf(input_buffer,"%s %i",cmd,&arg); //Récupération de la commande

        if (strcmp(cmd, "step") == 0 || ( go_prec == 1 && cmd_prec == 1) ){
            printf("Sortie :");
            if (lecurseur.end_programme != 1){
                //On exécute l'étape suivante au moins une fois
                etape_suivante(&lagrille,&lecurseur,&lapile);

                //S'il y a un argument non nul, on continue l'execution 
                for (i=1; i<arg; i = i+1){
                    if (lecurseur.end_programme != 1){
                        etape_suivante(&lagrille,&lecurseur,&lapile);
                    }
                }
            }

            go_prec = 0;
            cmd_prec = 1;
        } else if (strcmp(cmd, "run") == 0 || ( go_prec == 1 && cmd_prec == 3) ){
            printf("Sortie :");

            while (lecurseur.end_programme != 1){ 
                etape_suivante(&lagrille,&lecurseur,&lapile);
            }

            go_prec = 0;
            cmd_prec = 3;
        } else if (strcmp(cmd, "restart") == 0 || (go_prec == 1 && cmd_prec == 4) ){
            //restauration du backup de la grille
            free_grille(&lagrille);
            lagrille = copy_grille(lagrille_backup);
            lecurseur = init_curseur(); //On reset le curseur
            if (lapile != NULL){ //On reset/free la pile
                free_pile(&lapile);
            }
            lapile = NULL;

            go_prec = 0;
            cmd_prec = 4;
        } else if (strcmp(cmd, "quit") == 0 || ( go_prec == 1 && cmd_prec == 5) ){
            stop = 1;
            go_prec = 0;
            cmd_prec = 5;
        } else if (strcmp(cmd, " ") == 0 || ( go_prec == 1 && cmd_prec == 6) ){
            go_prec = 1;
        }
        else {
            printf("Erreur, veuillez réessayer\n");
        }
    }
    //Sortie du programme
    free_grille(&lagrille);
    free_grille(&lagrille_backup);
    if (lapile != NULL){
        free_pile(&lapile);
    }
    return 0;
}