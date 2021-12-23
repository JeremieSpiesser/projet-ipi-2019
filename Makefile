all: interpreter debugger

interpreter: curseur.o pile.o grille.o interpreter.o
	gcc -o interpreter -Wall -Wextra -lm curseur.o pile.o grille.o interpreter.o

interpreter.o: interpreter.c curseur.h pile.h grille.h
	gcc -o interpreter.o -c interpreter.c -Wall -Wextra -lm

debugger: curseur.o pile.o grille.o debugger.o
	gcc -o debugger -Wall -Wextra -lm curseur.o pile.o grille.o debugger.o

debugger.o: debugger.c curseur.h pile.h grille.h
	gcc -o debugger.o -c debugger.c -Wall -Wextra -lm

curseur.o: curseur.c pile.h grille.h
	gcc -o curseur.o -c curseur.c -Wall -Wextra -lm

pile.o: pile.c grille.h
	gcc -o pile.o -c pile.c -Wall -Wextra -lm

grille.o: grille.c
	gcc -o grille.o -c grille.c -Wall -Wextra -lm

clean:
	rm *.o