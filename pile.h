#ifndef PILE_H
#define PILE_H

#include "grille.h"


typedef struct maillon* pile;

/* Ce module pile gère la création et l'interaction avec
la pile.*/

/* Les piles sont un d'un type abstrait, et les fonctions disponibles
sont les suivantes */

/*@requires rien
@assigns rien
@ensures retourne 1 si l est vide, 0 sinon 
*/
int est_vide(pile l);

/*@requires rien
@assigns rien
@ensures retourne une pile vide
*/
pile init_pile();

/*@requires rien
@assigns détruit &pp
@ensures détruit la pile &pp
*/
void free_pile(pile* pp);

/*@requires rien
@assigns alloue une case mémoire 
@ensures crée une nouvelle pile avec le maillon de tête c, 
puis p ensuite
*/
pile cons( int c, pile p);

//Version procédure de cons
/*@requires rien
@assigns modifie la liste à l'adresse pp 
@ensures ajoute un élément en tête de &pp
*/
void empiler(int c, pile* pp);

/*@requires rien
@assigns rien
@ensures affiche les éléments de p les uns après les autres
*/
void afficher_pile(pile p);

/*@requires rien(fonctionne sur une pile vide)
@assigns supprime l'élément de tete de &pp
@ensures renvoie l'élément de tête de &pp (0 si &pp est vide) puis 
le supprime de &pp 
*/
int pop(pile* pp);

/*@requires rien
@assigns les 2 elts de tete de &pp
@ensures dépile 2 elts de &pp et empile leur somme
*/
void addition(pile* pp);

/*@requires rien
@assigns les 2 elts de tete de &pp
@ensures dépile 2 elts a puis b de &pp et empile leur différence b-a
*/
void soustraction(pile* pp);

/*@requires rien
@assigns les 2 elts de tete de &pp
@ensures dépile 2 elts de &pp et empile leur produit
*/
void multiplication(pile* pp);

/*@requires rien
@assigns &pp modifiée
@ensures On dépile deux entiers a puis b, et on empile la division euclidienne 
de b par a. Si a vaut 0, on empile 42.
*/
void div_entiere(pile* pp);

/*@requires rien
@assigns &pp modifiée
@ensures On dépile deux entiers a puis b, et on empile le reste de la division 
euclidienne de b par a. Si a vaut 0, on empile 0xbadc0de.
*/
void reste(pile* pp);

/*@requires rien
@assigns &pp modifiée
@ensures On dépile un entier. Si c'est 0 on empile 1, sinon on empile 0.
*/
void non_logique(pile* pp);

/*@requires rien
@assigns &pp modifiée
@ensures On dépile deux entiers a et b, et on empile 1 si b>a, 0 sinon.
*/
void plus_grand_que(pile* pp);

/*@requires rien
@assigns &pp a un nouvel element de tete
@ensures le sommet de &pp est dupliqué 
*/
void duplique_sommet_pile(pile* pp);

/*@requires rien
@assigns 2 elts de tete de &pp modifiés
@ensures on dépile a puis b puis on empile b puis a. 
*/
void echange_sommet_pile(pile* pp);

/*@requires rien
@assigns sommet de &pp supprimé
@ensures on retire le sommet de &pp
*/
void retire_sommet(pile* pp);

/*@requires rien
@assigns sommet de &pp supprimé
@ensures dépile puis affiche le sommet de &pp 
*/
void depile_affiche(pile* pp);

/*@requires rien
@assigns &pp modifiée
@ensures dépile un entier puis affiche le caractere correspondant au code ascii de sa valeur
tronquée à l'intervalle [0;255]
*/
void depile_affiche_ascii(pile* pp);

/*@requires rien
@assigns on ajoute un elt a &pp
@ensures demande un entier à l'utilisateur et l'empile sur &pp
*/
void demande_entier(pile* pp);

/*@requires rien
@assigns on ajoute un elt a &pp
@ensures demande un char à l'utilisateur et empile la valeur ascii tronquée à [0;255] sur &pp
*/
void demande_char(pile* pp);

/*@requires grille g non vide (initialisée correctement)
@assigns 2 elts de tete de &pp
@ensures dépile x puis y et empile la valeur (code ASCII) de la grille à la position (x,y). 
Si la position est en dehors de la grille, empile 0.
*/
void get(pile* pp, grille g);

/*@requires grille g non vide (initialisée correctement)
@assigns 3 elts de tete de &pp
@ensures dépile trois entiers x, y et z, et écrit z (code ASCII de la valeur tronquée entre 0 
et 255) dans la grille à la position (x,y). Si la position est en dehors de la grille, ne fait
rien.
*/
void put(pile* pp, grille* g);

/*@requires nothing
@assigns crée un nouvelle pile en mémoire
@ensures crée une copie par valeur de la pile p
*/
pile copy_pile(pile p);
#endif