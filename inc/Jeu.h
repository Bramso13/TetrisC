
#ifndef JEU_H
#define JEU_H
#include <MLV/MLV_all.h>
#include "../inc/Piece.h"
#define HAUTEUR 20
#define LARGEUR 10


typedef int matriceJeu[HAUTEUR][LARGEUR];

void jeuVide(matriceJeu mat);
int detectSoub(matriceJeu mat);
void soubstrait(matriceJeu mat, int a);
int finJeu(matriceJeu m);
int placePiece(Piece p, int * etape, matriceJeu m);
int finGravite(matriceJeu m, int x, int etape);
void recopieMatrice(matriceJeu m, matriceJeu c);
#endif