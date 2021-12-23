# Projet de programmation impérative

Voir le sujet (fichier pdf) pour plus de détails.

## Compilation

Pour compiler le projet : 
```
make clean ; make
```

## Interpréteur

L'interpréteur prend en argument un programme p2d valide.
Les fichiers d'essais sont disponibles dans le répertoire ```samples```.

Par exemple pour ```sieve.p2d```
``` 
./interpreter ./samples/sieve.p2d 
```
## Débogueur

Le débogueuer prend en argument un programme p2d valide.
Les fichiers d'essais sont disponibles dans le répertoire ```samples```.

Par exemple pour ```sieve.p2d```
``` 
./debugger ./samples/sieve.p2d 
```
Les fonctions disponibles dans le débogueur sont les suivantes : 

* step : avance d'une étape dans l'exécution du programme passé en argument.
* step n : avance de n étape(s) dans l'exécution du programme passé en argument. 
* run : continue dans l'exécution du programme jusqu'à atteindre le caractère '@'.
* restart : retourne à l'état initial.
* quit : quitte le débogueur.

