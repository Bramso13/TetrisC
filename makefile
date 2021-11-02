gcc = gcc

p1 = -Wall `pkg-config --cflags MLV`
p2 = `pkg-config --libs-only-other --libs-only-L MLV`
p3 = `pkg-config --libs-only-l MLV`

Tetris : Vue.o Jeu.o main.o
	$(gcc) $(p2) Vue.o Jeu.o main.o $(p3) -o Tetris

Jeu.o : ./inc/Jeu.h ./src/Jeu.c
	$(gcc) $(p1) -c ./src/Jeu.c

Vue.o : ./inc/Vue.h ./src/Vue.c
	$(gcc) $(p1) -c ./src/Vue.c

main.o : ./inc/Jeu.h ./src/main.c
	$(gcc) $(p1) -c ./src/main.c

clean:
	rm -f *.o *~ Space