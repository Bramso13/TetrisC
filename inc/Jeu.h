
#ifndef JEU_H
#define JEU_H
#include <MLV/MLV_all.h>
#include "../inc/Piece.h"
#define HAUTEUR 20
#define LARGEUR 10


typedef int matriceJeu[HAUTEUR][LARGEUR];
typedef struct jeu Jeu;
typedef struct score Score;

struct score{

    char nom[10];
    int score;
    int classement;
};

struct jeu{

    matriceJeu matrice;
    Score score;
};

void jeuVide(matriceJeu mat);
int estVide(matriceJeu mat);
int detectSoub(matriceJeu mat);
void soubstrait(matriceJeu mat, int a);
int finJeu(matriceJeu m);
void placePiece(Piece p, int * etape, matriceJeu m, int ** x);
int finGravite(matriceJeu m, int ** x, int etape);
void recopieMatrice(matriceJeu m, matriceJeu c);
int movePiece(Piece p, int direction);
void rotate90Horloge(int a[4][4]);
void rotate90HorlogeInv(int a[4][4]);
void recopieMat(int m[4][4], int c[4][4]);
void attribueScore(int scoreFinal, char nom[10]);
void recupereScore(Score * tab);
void initScore();
void chargerAllPartie(Jeu * j);
void initPartie();

#endif