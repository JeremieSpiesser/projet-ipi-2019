#include <stdio.h>
#include <math.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "grille.h"

/*Crée une grille vide de taille h*l
 * @requires h>0 et l>0
 * @assigns rien
 * @ensures retourne une grille de char nuls
 */
grille creer_grille(int h, int l){
    grille tmp;
    tmp.hauteur = h;
    tmp.largeur = l;
    tmp.contenu = (char **) malloc(h*sizeof(char*));
    int i;
    for (i=0; i<h ; i = i+1 ) {
        tmp.contenu[i] = (char *) calloc(l,sizeof(char));
    }
    return tmp;
};

//ANCIENNE VERSION NON UTILISEE
/* Affiche une grille, en mettant en rouge le point de coordonnées (x,y)
 * @requires x et y coordonnées valides pour la grille g, g correcte
 * @assigns rien
 * @ensures affiche la grille
void afficher_grille(grille g, int x, int y){
    int i;
    int j;
    for (i=0; i< g.hauteur; i = i+1){
        for (j=0; j< g.largeur; j = j+1){
            if (i == x && j == y){
                printf("\033[1;31m");
                printf("%c",g.contenu[i][j]);
                printf("\033[0m");
            }else{
                printf("%c",g.contenu[i][j]);
            }
        }
        printf("\n");
    }
}

*/

/*@requires un entier positif
@assigns rien
@ensures retourne le nombre de chiffres de l'entier
ex : int_length(10) -> 2 ; int_length(666) -> 3
*/
int int_length(int k){
    int n = 1;
    while (k/10 > 0){
        k = k/10;
        n = n +1;
    }
    return n;
}


/*@requires grille bien initialisée (dimensions correctes, contenu correct)
@assigns rien
@ensures affiche la grille selon le schéma de l'énoncé
*/
void afficher_grille(grille g, int x, int y){
    printf("\n");
    int i=5;
    int j=0;
    int k=0;
    int n,p;

    //1 ère étape : Ligne 1

    //Pour prendre en compte le décalage du à la colonne de gauche
    for (k=0; k < int_length(g.hauteur)+1;k=k+1){
        printf(" ");
    }

    //Affichage de la ligne de chiffres
    i=5;
    printf("0    ");
    while(i <= g.largeur){
        n = int_length(i);
        if (n<=5){
            p = 5;
        }else if (n <= 10){
            p = 10;
        }
        printf("%d",i);
        for (j=0; j < p-n; j = j +1){
            printf(" ");
        }
        i = i + p;
    }
    printf("\n");

    //2è étape : Ligne 2

    //Pour prendre en compte le décalage du à la colonne de gauche
    for (k=0; k < int_length(g.hauteur)+1;k=k+1){
        printf(" ");
    }

    i=0;
    for (i=0; i<=g.largeur; i = i+1){
        if (i==y){
            printf("v");
        }else if (i==0){
            printf("|");
        }else if ( (i%5==0) && (i < 10000) ){
            printf("|");
        }else if ( (i%10 == 0) && (i >= 10000)){
            printf("|");
        }else{
            printf(" ");
        }
    }
    printf("\n");

    //3ème étape : reste de la grille
    n = int_length(g.hauteur);
    for (i=0; i< g.hauteur; i = i+1){

        if (i==x){
            for (k=0; k<n-1; k = k+1){
                printf(" ");
            }
            printf("%d",i);
            printf(">");
        }else if (i%5 == 0){
            for (k=int_length(i); k < n ; k = k+1 ){
                printf(" ");
            }
            printf("%d",i);
            printf("-");

        }else{
            for (k=0; k<n+1; k = k+1){
                printf(" ");
            }
        }



        for (j=0; j< g.largeur; j = j+1){
            printf("%c",g.contenu[i][j]);
            }
        printf("\n");
    }
    printf("\n");
}

/*Copie (par valeur) une grille
@requires une grille initialisée
@assigns nouvelle grille
@ensures retourne une nouvelle grille clonée (par valeur) depuis la grille initiale
*/
grille copy_grille(grille g){
    grille g2 = creer_grille(g.hauteur, g.largeur);
    int i;
    for (i=0;i<g2.hauteur;i = i+1){
        strcpy(g2.contenu[i], g.contenu[i]);
    }
    return g2;
}

/* Libère la case mémoire précédemment occupée par une grille
 * @requires un pointeur vers une grille correcte
 * @assigns supprime la grille à l'adresse g
 * @ensures supprime la grille à l'adresse g
*/
void free_grille(grille* g){
    int i;
    for (i = 0; i <g->hauteur; i = i+1 ){
        free(g->contenu[i]);
    }
    free(g->contenu);
    g->contenu = NULL;
}