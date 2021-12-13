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

    for(i=1;i<=NBPIECEMAX;i++){
        Piece s;
        if(i <= NBPIECEBASE){
            s = makePiece(i);
        }else{
            s = (Piece) malloc(sizeof(struct piece));
            s->couleur = 0;
            s->type = 0;
            s->x = -1;
        }
        if(s == NULL){
            printf("problème de malloc\n");
            exit(EXIT_FAILURE);
        }
        if( 1 != fwrite(s, sizeof(struct piece), 1, fp)){
            fprintf(stderr, "probleme d'écriture de fichier\n");
        }
    }   
    rc = fclose(fp);
    if(rc == EOF){
        fprintf(stderr, "probleme de fermeture de fichier");
        exit(EXIT_FAILURE);
    }
}
void recuperePiece(Piece tab){

    int fr, rc;
    FILE * fp = fopen("./data/pieces", "r");

    if (fp == NULL){
        printf("Probleme d'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }

    fr = fread(tab, sizeof(struct piece), NBPIECEMAX, fp);
    if (fr != NBPIECEMAX){
        printf("Problème de lecture de fichier\n");
        exit(EXIT_FAILURE);
    }
    rc = fclose(fp);
    if(rc == EOF){
        fprintf(stderr, "probleme de fermeture de fichier");
        exit(EXIT_FAILURE);
    }
}
int comptePiece(Piece tab){
    int i, compte=0;

    for(i=0;i<NBPIECEMAX;i++){
        if(tab[i].x > 0 && tab[i].type != 0)compte++;
    }
    return compte;
}
void ajouterPiece(struct piece p, Piece tab){
    int i, j,k, test=1;
    
    
    for(i=0;i<NBPIECEMAX && test;i++){
        if(tab[i].x < 0 && tab[i].type == 0 && test){
            tab[i].type = NBPIECEBASE+i;
            tab[i].x = p.x;
            for(j=0;j<4;j++){
                for(k=0;k<4;k++){
                    tab[i].dessin[j][k] = p.dessin[j][k];
                }
            }
            test = 0;
        }
    }
    ecrireAllPiece(tab);
    free(tab);
}
void ecrireAllPiece(Piece tab){
    int i, rc;
    FILE * fp = fopen("./data/pieces", "w+");

    if (fp == NULL){
        printf("Probleme d'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }

    for(i=0;i<NBPIECEMAX;i++){
        struct piece * s = &tab[i];
        if( 1 != fwrite(s, sizeof(struct piece), 1, fp)){
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
Piece MakePiece(int choix){

    Piece tab = (Piece) malloc(NBPIECEMAX*sizeof(struct piece));
    recuperePiece(tab);
    int couleur, i, j;
    Piece p = &tab[choix-1];
    if(choix <= NBPIECEBASE){
        couleur = choixPiece(1,4);
        p->couleur = couleur;
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                if(p->dessin[i][j] > 0){
                    p->dessin[i][j] = couleur;
                }
            }
        }
    }
    

    free(tab);
    return p;
}