gcc = gcc

p1 = -Wall `pkg-config --cflags MLV`
p2 = `pkg-config --libs-only-other --libs-only-L MLV`
p3 = `pkg-config --libs-only-l MLV`

Tetris : Jeu.o Piece.o Vue.o main.o
	$(gcc) $(p2) Jeu.o Piece.o Vue.o main.o $(p3) -o Tetris

Jeu.o : ./inc/Piece.h ./inc/Jeu.h ./src/Jeu.c
	$(gcc) $(p1) -c ./src/Jeu.c

Vue.o : ./inc/Jeu.h ./inc/Piece.h ./inc/Vue.h ./src/Vue.c
	$(gcc) $(p1) -c ./src/Vue.c

Piece.o : ./inc/Vue.h ./inc/Piece.h ./src/Piece.c
	$(gcc) $(p1) -c ./src/Piece.c

main.o : ./inc/Jeu.h ./src/main.c
	$(gcc) $(p1) -c ./src/main.c

clean:
	rm -f *.o *~ Tetris