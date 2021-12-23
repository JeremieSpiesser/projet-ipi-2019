#ifndef GRILLE_H
#define GRILLE_H

/*On définit dans ce module les types et fonctions liées
aux manipulations de la grille*/

/* Une grille est la donnée de ses dimensions et un tableau de char*,
 avec chaque char* représentant une ligne du fichier  */
struct grille{
    int hauteur;
    int largeur;
    char** contenu;
};
typedef struct grille grille;

/*Crée une grille vide de taille h*l
 * @requires h>0 et l>0
 * @assigns rien
 * @ensures retourne une grille de char nuls
 */
grille creer_grille(int h, int l);

/*@requires un entier positif
@assigns rien
@ensures retourne le nombre de chiffres de l'entier
ex : int_length(10) -> 2 ; int_length(666) -> 3
*/
int int_length(int k);

/* Affiche une grille, en mettant en rouge le point de coordonnées (x,y)
 * @requires x et y coordonnées valides pour la grille g, g correcte
 * @assigns rien
 * @ensures affiche la grille
*/
void afficher_grille(grille g, int x, int y);


/*Copie (par valeur) une grille
@requires une grille initialisée
@assigns nouvelle grille
@ensures retourne une nouvelle grille clonée (par valeur) depuis la grille initiale
*/
grille copy_grille(grille g);


/* Libère la case mémoire précédemment occupée par une grille
 * @requires un pointeur vers une grille correcte
 * @assigns supprime la grille à l'adresse g
 * @ensures supprime la grille à l'adresse g
*/
void free_grille(grille* g);

#endif