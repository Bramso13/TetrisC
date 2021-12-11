#include "../inc/Piece.h"


int choixPiece(int min, int max){

    return rand()%(max - min + 1)+min;
}

void initPiece(){

    int i, rc;
    FILE * fp = fopen("./data/pieces", "w+");

    if (fp == NULL){
        printf("Probleme d'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }

    for(i=1;i<=NBPIECEBASE;i++){
        Piece s = makePiece(i);

        if(s == NULL){
            printf("problème de malloc\n");
            exit(EXIT_FAILURE);
        }
        if( 1 != fwrite(s, sizeof(Piece), 1, fp)){
            fprintf(stderr, "probleme d'écriture de fichier\n");
        }
    }   
    rc = fclose(fp);
    if(rc == EOF){
        fprintf(stderr, "probleme de fermeture de fichier");
        exit(EXIT_FAILURE);
    }
}

Piece makePiece(int type){

    Piece p = (Piece) malloc(sizeof(struct piece));
    if(p == NULL) exit(EXIT_FAILURE);
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
        case 2:
            p->dessin[1][1]=couleur;p->dessin[1][2]=couleur;
            p->dessin[1][3] = couleur;p->dessin[2][2]=couleur;
            break;

    }
    return p;
}