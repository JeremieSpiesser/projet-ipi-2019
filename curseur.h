#ifndef CURSEUR_H
#define CURSEUR_H

#include "pile.h"
#include "grille.h"

/* On définit dans ce module le type curseur et ses fonctions associées
Un curseur est un type explicite contenant 
- les coordonnées x et y (entières positives)
- une "boussole" indiquant la direction du curseur
- un champ n_ignore qui représente le nombre de cases à ignorer
- un champ end_programme qui quitte l'exécution s'il vaut 1
*/

//On choisit la correspondance entier <-> direction
//pour faciliter le traitement du caractère '  
enum direction {nord=0 , ouest=6 , sud=4 , est=2, nord_ouest=7 , nord_est=1 , sud_ouest=5 , sud_est=3 };
typedef enum direction direction;

struct curseur {
    int x;
    int y;
    direction direct;
    int n_ignore;//Nombre de cases suivantes à ignorer, si -1, 
    //on ignore toutes les cases suivantes (jusqu'a rencontrer un " selon l'énoncé)
    int end_programme;//Si passe à 1, on arrête le programme
};

typedef struct curseur curseur;

/*@requires rien
@assigns crée un curseur
@ensures crée un curseur vide (initialisé selon l'énoncé)
*/
curseur init_curseur();

/*@requires rien
@assigns rien
@ensures affiche les coordonnées du curseur*/
void print_position_curseur(curseur c);


/*@requires rien
@assigns enleve l'elt de tête de &pp, direction de &c
@ensures modifie la direction de c
*/
void reste_div_eucl(pile* pp, curseur* c);

/*@requires rien
@assigns direction de &c
@ensures fait tourner c à droite de 45°
*/
void tourner_droite(curseur* c);

/*@requires rien
@assigns direction de &c
@ensures fait tourner c à gauche de 45°
*/
void tourner_gauche(curseur* c);

/*@requires rien
@assigns c->n_ignore
@ensures toggle entre mode chaine de caractère (n_ignore == -1)
et mode "normal" (n_ignore != -1)
*/
void toggle_mode_chaine_caractere(curseur* c);

//h et l représentent hauteur et largeur de la grille
/*@requires h et l hauteur et largeur de la grille (donc positifs et correspondant à 
la grille utilisée par la suite)
@assigns coordonnées de &c
@ensures fait évoluer le curseur de la position (x,y) à (x',y') en suivant la direction c->direct
On prend en compte le fait que la grille est torique
*/
void curseur_update(curseur* c, int h, int l);

/*on initialise rand avec srand(time(NULL)) dans main
Puis on demande un nombre aléatoire entre 0 et 7 pour choisir une parmis
les 7 directions possibles
@requires rien
@assigns direction
@ensures c actualisé, avec une direction aléatoire
*/
void direction_hasard(curseur* c);

/*@require rien
@assigns tête de la pile et direction du curseur
@ensures modifie la direction du curseur en fonction de la tête de la pile (voir énoncé)
*/
void conditionnelle_horizontale(pile* pp, curseur* c);

/*@require rien
@assigns tête de la pile et direction du curseur
@ensures modifie la direction du curseur en fonction de la tête de la pile (voir énoncé)
*/
void conditionnelle_verticale(pile* pp, curseur* c);

/*@require rien
@assigns tête de la pile et direction du curseur
@ensures modifie la direction du curseur en fonction de la tête de la pile (voir énoncé)
*/
void conditionnelle_diagonale_droite(pile* pp, curseur* c);

/*@require rien
@assigns tête de la pile et direction du curseur
@ensures modifie la direction du curseur en fonction de la tête de la pile (voir énoncé)
*/
void conditionnelle_diagonale_gauche(pile* pp, curseur* c);

/*@requires rien
@assigns c->n_ignore, tête de la pile dépilée
@ensures démarre le mode pont
*/
void pont(pile* pp, curseur* c);

//Lancée quand on rencontre un '@'
/*@requires rien
@assigns c->end_programme
@ensures met le champ end_programme de c à 1 pour finir l'exécution
*/
void end_programme(curseur* c);


/*L'algo dans le cas général est le suivant

1 : on regarde le caractère à (c.x,c.y)
2 : on actualise la direction du curseur
3 : on actualise les coordonnées (appel à curseur_update)

2 et 3 se font par l'appel à curseur_update(c)

Si on est dans le cas d'un pont on fait n_ignore <- n_ignore - 1 au lieu de 
regarder le caractère sous le curseur et on fait l'étape 3

Si on est dans le cas du mode chaîne de caractère, on fait de même sans changer n_ignore

*/

/*@requires un pointeur sur une grille initialisée, valide
@assigns contenu de la grille, tous les champs du curseur, pile
@ensures itère le processus à l
*/
void etape_suivante(grille* gp, curseur* cp,pile* pp);

#endif