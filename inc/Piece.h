#ifndef PIECE_H

#define PIECE_H
#include "../MLV/MLV_all.h"

#define BASEX 2
#define BASEY 1
#define NBPIECEBASE 2
#define NBPIECEMAX 10

typedef struct piece * Piece;

struct piece{

    int dessin[4][4];
    short x;
    short type;
    short couleur;
};

int choixPiece(int min, int max);
Piece makePiece(int type);
void recuperePiece(Piece tab);
void ecrireAllPiece(Piece tab);
void ajouterPiece(struct piece p, Piece tab);
Piece MakePiece(int choix);
int comptePiece(Piece tab);
void initPiece();

#endif