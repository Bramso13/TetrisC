#include "../inc/Piece.h"


int choixPiece(int min, int max){

    return rand()%(max - min + 1)+min;
}

Piece makePiece(int type){

    Piece p = (Piece) malloc(sizeof(struct piece));
    int couleur = choixPiece(1,4);
    p->couleur = couleur;
    p->type = type;
    p->x = 10/2;
    int i,j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            p->dessin[i][j] = 0;

    switch(type){
        case 1: /* S */
            p->dessin[1][3]=couleur;p->dessin[1][2]=couleur;
            p->dessin[2][2] = couleur;p->dessin[2][1]=couleur;
            break;

    }
}