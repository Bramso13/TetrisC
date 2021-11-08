#ifndef PIECE_H

#define PIECE_H
#include "../MLV/MLV_all.h"

#define BASEX 2
#define BASEY 1

typedef struct piece * Piece;

struct piece{

    int dessin[4][4];
    short x;
    short type;
    short couleur;
};

int choixPiece(int min, int max);
Piece makePiece(int type);

#endif