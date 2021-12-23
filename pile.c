#include <stdio.h>
#include <math.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "grille.h"
#include "pile.h"

/*Pour les piles simples*/

struct maillon{
    int head;
    struct maillon * tail;
};

typedef struct maillon maillon;

/* Pour les piles2piles */

struct maillon2{
    pile val;
    struct maillon2* next;
};

typedef struct maillon2 maillon2;

/*@requires rien
@assigns rien
@ensures retourne 1 si l est vide, 0 sinon 
*/
int est_vide(pile l){
    return (NULL==l);
}

/*@requires rien
@assigns rien
@ensures retourne une pile vide
*/
pile init_pile(){
    return (NULL);
}

/*
pile copy_pile(pile p){
    pile p2 = init_pile();
    cons()
}
*/

/*@requires rien
@assigns alloue une case mémoire 
@ensures crée une nouvelle pile avec le maillon de tête c, 
puis p ensuite
*/
pile cons( int c, pile p){
    pile res;
    res = malloc(sizeof(maillon));
    res->head = c;
    res->tail = p;
    return(res);
}

/*@requires rien
@assigns modifie la liste à l'adresse pp 
@ensures ajoute un élément en tête de &pp
*/
void empiler(int c, pile* pp){
    *pp = cons(c, *pp);
}

/*@requires rien
@assigns rien
@ensures affiche les éléments de p les uns après les autres
*/
void afficher_pile(pile p){
    while (p!=NULL){      
        printf(" %d (%c) |",p->head, p->head);
        p = p->tail;
    }
    printf("|\n");
}

/*@requires rien(fonctionne sur une pile vide)
@assigns supprime l'élément de tete de &pp
@ensures renvoie l'élément de tête de &pp (0 si &pp est vide) puis 
le supprime de &pp 
*/
int pop(pile* pp){
    if (est_vide(*pp)){
        return 0;
    }
    else{
        pile p = *pp;
        int res = p->head;
        pile p2 = p->tail;
        *pp = p2;
        free(p);
        return res;
    }
}

/*@requires rien
@assigns détruit &pp
@ensures détruit la pile &pp
*/
void free_pile(pile* pp){
    while (*pp != NULL){
        if ( ! est_vide(*pp))
        {
            pile p = *pp;
            pile p2 = p->tail;
            *pp = p2;
            free(p);
        }
    }
}

/*@requires rien
@assigns les 2 elts de tete de &pp
@ensures dépile 2 elts de &pp et empile leur somme
*/
void addition(pile* pp){
    int a,b;
    a=pop(pp);
    b=pop(pp);
    empiler(a+b, pp);
}

/*@requires rien
@assigns les 2 elts de tete de &pp
@ensures dépile 2 elts a puis b de &pp et empile leur différence b-a
*/
void soustraction(pile* pp){
    int a,b;
    a=pop(pp);
    b=pop(pp);
    empiler(b-a, pp);
}

/*@requires rien
@assigns les 2 elts de tete de &pp
@ensures dépile 2 elts de &pp et empile leur produit
*/
void multiplication(pile* pp){
    int a,b;
    a=pop(pp);
    b=pop(pp);
    empiler(a*b, pp);
}

/*@requires rien
@assigns &pp modifiée
@ensures On dépile deux entiers a puis b, et on empile la division euclidienne 
de b par a. Si a vaut 0, on empile 42.
*/
void div_entiere(pile* pp){
    int a,b;
    a=pop(pp);
    b=pop(pp);
    if (a==0){
        empiler(42, pp);
    }
    else{
        empiler(b/a, pp);
    }
}

/*@requires rien
@assigns &pp modifiée
@ensures On dépile deux entiers a puis b, et on empile le reste de la division 
euclidienne de b par a. Si a vaut 0, on empile 0xbadc0de.
*/
void reste(pile* pp){
    int a,b;
    a=pop(pp);
    b=pop(pp);
    if (a==0){
        empiler(0xbadc0de, pp);
    }
    else{
        empiler(b%a, pp);
    }
}

/*@requires rien
@assigns &pp modifiée
@ensures On dépile un entier. Si c'est 0 on empile 1, sinon on empile 0.
*/
void non_logique(pile* pp){
    int a=pop(pp);
    if (a==0){
        empiler(1, pp);
    }
    else{
        empiler(0,pp);
    }
}

/*@requires rien
@assigns &pp modifiée
@ensures On dépile deux entiers a et b, et on empile 1 si b>a, 0 sinon.
*/
void plus_grand_que(pile* pp){
    int a=pop(pp);
    int b=pop(pp);
    if (b>a){
        empiler(1, pp);
    }
    else{
        empiler(0,pp);
    }
}

/*@requires rien
@assigns &pp a un nouvel element de tete
@ensures le sommet de &pp est dupliqué 
*/
void duplique_sommet_pile(pile* pp){
    int a = pop(pp);
    empiler(a,pp);
    empiler(a,pp);
}

/*@requires rien
@assigns 2 elts de tete de &pp modifiés
@ensures on dépile a puis b puis on empile b puis a. 
*/
void echange_sommet_pile(pile* pp){
    int a = pop(pp);
    if (est_vide(*pp)){
        empiler(a,pp);
        empiler(0,pp);
    }else{
        int b = pop(pp);
        empiler(a,pp);
        empiler(b,pp);
    }
}

/*@requires rien
@assigns sommet de &pp supprimé
@ensures on retire le sommet de &pp
*/
void retire_sommet(pile* pp){
    if (!est_vide(*pp)){
        pop(pp);
    }
}

/*@requires rien
@assigns sommet de &pp supprimé
@ensures dépile puis affiche le sommet de &pp 
*/
void depile_affiche(pile* pp){
    int a = pop(pp);
    printf("%d", a);
}

/*@requires rien
@assigns &pp modifiée
@ensures dépile un entier puis affiche le caractere correspondant au code ascii de sa valeur
tronquée à l'intervalle [0;255]
*/
void depile_affiche_ascii(pile* pp){
    int a = pop(pp);
    a = a % 255;
    char c = a; //Conversion implicite
    printf("%c",c);
}

/*@requires rien
@assigns on ajoute un elt a &pp
@ensures demande un entier à l'utilisateur et l'empile sur &pp
*/
void demande_entier(pile* pp){
    int a;
    printf("Entrez un entier : ");
    scanf("%d",&a);
    empiler(a,pp);
}

/*@requires rien
@assigns on ajoute un elt a &pp
@ensures demande un char à l'utilisateur et empile la valeur ascii tronquée à [0;255] sur &pp
*/
void demande_char(pile* pp){
    char c;
    int a;
    printf("Entrez un caractère : ");
    scanf("%c",&c);
    a = c;
    empiler(a,pp);
}

/*@requires grille g non vide (initialisée correctement)
@assigns 2 elts de tete de &pp
@ensures dépile x puis y et empile la valeur (code ASCII) de la grille à la position (x,y). 
Si la position est en dehors de la grille, empile 0.
*/
void get(pile* pp, grille g){
    int x = pop(pp);
    int y = pop(pp);
    if (x >= g.hauteur || x<0 || y >= g.largeur || y<0){
        empiler(0,pp);
    } else {
        int tmp = g.contenu[x][y];
        empiler(tmp, pp);
    }
}

/*@requires grille g non vide (initialisée correctement)
@assigns 3 elts de tete de &pp
@ensures dépile trois entiers x, y et z, et écrit z (code ASCII de la valeur tronquée entre 0 
et 255) dans la grille à la position (x,y). Si la position est en dehors de la grille, ne fait
rien.
*/
void put(pile* pp, grille* g){
    int x = pop(pp);
    int y = pop(pp);
    int z = pop(pp);
    if ( x < g->hauteur && x>=0 && y < g->largeur && y>=0){
        z = z % 255;
        char t = z;
        (g->contenu)[x][y] = t;
    } 
}


/*@requires nothing
@assigns crée un nouvelle pile en mémoire
@ensures crée une copie par valeur de la pile p
*/
pile copy_pile(pile p){
    if (p != NULL){
        pile p2;
        pile a,b;
        b = NULL;
        a = (pile) malloc(sizeof(maillon));
        p2 = a;
        while (p->tail != NULL){
            a->head = p->head;
            p = p->tail;
            b = a;
            a = (pile) malloc(sizeof(maillon));
            b->tail = a;
        }
        a->head = p->head;
        a->tail = NULL;
        return p2;
    }else{
        return NULL;
    }
}