#include <stdio.h>
#include <math.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pile.h"
#include "curseur.h"
#include "grille.h"

/*@requires rien
@assigns crée un curseur
@ensures crée un curseur vide (initialisé selon l'énoncé)
*/
curseur init_curseur(){
    curseur c;
    c.x = 0;
    c.y = 0;
    c.direct = est;
    c.n_ignore=0;
    c.end_programme=0;
    return c;
}

/*@requires rien
@assigns rien
@ensures affiche les coordonnées du curseur*/
void print_position_curseur(curseur c){
    printf("x: %d, y: %d \n",c.x, c.y);
}


/*@requires rien
@assigns enleve l'elt de tête de &pp, direction de &c
@ensures modifie la direction de c
*/
void reste_div_eucl(pile* pp, curseur* c){
    int a;
    a = pop(pp)%8;
    c->direct = a;
}

/*@requires rien
@assigns direction de &c
@ensures fait tourner c à droite de 45°
*/
void tourner_droite(curseur* c){
    c->direct = (c->direct +1)%8 ;
}

/*@requires rien
@assigns direction de &c
@ensures fait tourner c à gauche de 45°
*/
void tourner_gauche(curseur* c){
    c->direct = (c->direct -1)%8;
}

/*@requires rien
@assigns c->n_ignore
@ensures toggle entre mode chaine de caractère (n_ignore == -1)
et mode "normal" (n_ignore != -1)
*/
void toggle_mode_chaine_caractere(curseur* c){
    if (c->n_ignore == -1){
        c->n_ignore = 0;
    }else{
        c->n_ignore = -1;
    }
}

//h et l représentent hauteur et largeur de la grille
/*@requires h et l hauteur et largeur de la grille (donc positifs et correspondant à 
la grille utilisée par la suite)
@assigns coordonnées de &c
@ensures fait évoluer le curseur de la position (x,y) à (x',y') en suivant la direction c->direct
On prend en compte le fait que la grille est torique
*/
void curseur_update(curseur* c, int h, int l){
    direction d = c->direct;
    switch (d){
        //Nord
        case nord : 
            //Grille torique : cas dépassement vers le haut
            //Si on est à la bordure en haut, on gère
            //les coordonnées manuellement
            if (c->x == 0){
                     c->x = h-1;
                 }else{
                     c->x = c->x -1;
                 }
            break;
        //Est
        case est :
            //Si on est à la bordure à droite, on gère
            //les coordonnées manuellement
            if ( c->y == l-1){
                c->y = 0;
            }else{
                c->y = c->y +1;
            }
            break;
        //Sud
        case sud : 
            if (c->x == h-1){
                c->x = 0;
            }else{
                c->x = c->x +1;
            }
            break;
        //Ouest
        case ouest : 
            if (c->y == 0){
                c->y = l-1;
            }else{
                c->y = c->y -1;
            }
            break;

        //Nord Ouest
        case nord_ouest :
            //Nord
            if (c->x == 0){
                     c->x = h-1;
                 }else{
                     c->x = c->x -1;
                 }
            //Puis ouest
            if (c->y == 0){
                c->y = l-1;
            }else{
                c->y = c->y -1;
            }
            break;
        //Nord Est
        case nord_est:
            if (c->x == 0){
                     c->x = h-1;
                 }else{
                     c->x = c->x -1;
                 }
            if ( c->y == l-1){
                c->y = 0;
            }else{
                c->y = c->y +1;
            }
            break;
        //Sud Est
        case sud_est:

            if (c->x == h-1){
                c->x = 0;
            }else{
                c->x = c->x +1;
            }

            if ( c->y == l-1){
                c->y = 0;
            }else{
                c->y = c->y +1;
            }
            break;

        //Sud Ouest
        case sud_ouest:

            if (c->x == h-1){
                c->x = 0;
            }else{
                c->x = c->x +1;
            }

            if (c->y == 0){
                c->y = l-1;
            }else{
                c->y = c->y -1;
            }
            break;

        //Défaut : jamais rencontré
        default:
            break;
    }
}

/*on initialise rand avec srand(time(NULL)) dans main
Puis on demande un nombre aléatoire entre 0 et 7 pour choisir une parmis
les 7 directions possibles
@requires rien
@assigns direction
@ensures c actualisé, avec une direction aléatoire
*/
void direction_hasard(curseur* c){
    int direction = rand() % (7+1) ;
    c->direct = direction;
}

/*@require rien
@assigns tête de la pile et direction du curseur
@ensures modifie la direction du curseur en fonction de la tête de la pile (voir énoncé)
*/
void conditionnelle_horizontale(pile* pp, curseur* c){
    int a = pop(pp);
    if (a==0){
        c->direct = est;
    }else{
        c->direct = ouest;
    }
}

/*@require rien
@assigns tête de la pile et direction du curseur
@ensures modifie la direction du curseur en fonction de la tête de la pile (voir énoncé)
*/
void conditionnelle_verticale(pile* pp, curseur* c){
    int a = pop(pp);
    if (a==0){
        c->direct = sud;
    }else{
        c->direct = nord;
    }
}

/*@require rien
@assigns tête de la pile et direction du curseur
@ensures modifie la direction du curseur en fonction de la tête de la pile (voir énoncé)
*/
void conditionnelle_diagonale_droite(pile* pp, curseur* c){
    int a = pop(pp);
    if (a==0){
        c->direct = nord_est;
    }else{
        c->direct = sud_ouest;
    }
}

/*@require rien
@assigns tête de la pile et direction du curseur
@ensures modifie la direction du curseur en fonction de la tête de la pile (voir énoncé)
*/
void conditionnelle_diagonale_gauche(pile* pp, curseur* c){
    int a = pop(pp);
    if (a==0){
        c->direct = sud_est;
    }else{
        c->direct = nord_ouest;
    }
}

/*@requires rien
@assigns c->n_ignore, tête de la pile dépilée
@ensures démarre le mode pont
*/
void pont(pile* pp, curseur* c){
    int n = pop(pp);
    c->n_ignore = n;
}

//Lancée quand on rencontre un '@'
/*@requires rien
@assigns c->end_programme
@ensures met le champ end_programme de c à 1 pour finir l'exécution
*/
void end_programme(curseur* c){
    c->end_programme=1;    
}

/*L'algo dans le cas général est le suivant

1 : on regarde le caractère à (c.x,c.y)
2 : on actualise la direction du curseur
3 : on actualise les coordonnées (appel à curseur_update)

4 : GOTO 1

2 et 3 se font par l'appel à curseur_update(c)

Si on est dans le cas d'un pont on fait n_ignore <- n_ignore - 1 au lieu de 
regarder le caractère sous le curseur (étape 2) et on fait l'étape 3

Si on est dans le cas du mode chaîne de caractère, on fait de même sans changer n_ignore

*/

/*@requires un pointeur sur une grille initialisée, valide
@assigns contenu de la grille, tous les champs du curseur, pile
@ensures itère le processus à l'étape suivante
*/
void etape_suivante(grille* gp, curseur* cp,pile* pp){
    char car = gp->contenu[cp->x][cp->y];
    //Premier cas : lors d'un pont
    if (cp->n_ignore > 0){
        cp->n_ignore = cp->n_ignore -1;
    }else if (cp->n_ignore < 0){ //Deuxieme cas : mode chaine de caractère
        if (car == '"'){ //On vérifie si on doit quitter le mode chaine de caractere
            toggle_mode_chaine_caractere(cp);
        }else{
            int val = car;
            empiler(val, pp);
        }
    }else{ // Cas général
    switch (car){
        case '+' : addition(pp); break;
        case '-' : soustraction(pp); break;
        case '*' : multiplication(pp); break;
        case ':' : div_entiere(pp); break;
        case '%' : reste(pp); break;
        case '!' : non_logique(pp); break;
        case '`' : plus_grand_que(pp); break;
        case '>' : cp->direct = est; break;
        case '<' : cp->direct = ouest; break;
        case '^' : cp->direct = nord; break;
        case 'v' : cp->direct = sud; break;
        case '?' : direction_hasard(cp); break;
        case '\'' : reste_div_eucl(pp,cp); break;
        case ']' : tourner_gauche(cp); break;
        case '[' : tourner_droite(cp); break;
        case '_' : conditionnelle_horizontale(pp, cp); break;
        case '|' : conditionnelle_verticale(pp, cp); break;
        case '/' : conditionnelle_diagonale_droite(pp, cp); break;
        case '\\': conditionnelle_diagonale_gauche(pp, cp); break;
        case '"': toggle_mode_chaine_caractere(cp); break;
        case '=' : duplique_sommet_pile(pp); break;
        case '$' : echange_sommet_pile(pp); break;
        case ';' : retire_sommet(pp); break;
        case '.' : depile_affiche(pp); break;
        case ',' : depile_affiche_ascii(pp); break;

        case '#' : pont(pp,cp); break;
        case 'g' : get(pp,*gp); break;
        case 'p' : put(pp,gp); break;
        case '&' : demande_entier(pp); break;
        case '~' : demande_char(pp); break;

        case '@' : cp->end_programme = 1; break;

        case '0' : empiler(0,pp); break;
        case '1' : empiler(1,pp); break;
        case '2' : empiler(2,pp); break;
        case '3' : empiler(3,pp); break;
        case '4' : empiler(4,pp); break;
        case '5' : empiler(5,pp); break;
        case '6' : empiler(6,pp); break;
        case '7' : empiler(7,pp); break;
        case '8' : empiler(8,pp); break;
        case '9' : empiler(9,pp); break;
        case ' ' : break;
        default : break;
    }

}
    curseur_update(cp, gp->hauteur, gp->largeur);
}


