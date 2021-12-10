#ifndef VUE_H

#define VUE_H
#include "../MLV/MLV_all.h"
#include "../inc/Jeu.h"
#include "../inc/Piece.h"

int menu(int height, int width);
int jeu(int height, int width, matriceJeu m, Score * score);
int afficheJeu(int height, int width, int x, int y, matriceJeu m);
int score(int height, int width);
int creationPiece(int height, int width, int ma[][4]);
int affichePred(int h, int w, int x, int y, int m[4][4]);
int perdu(int height, int width, Score * score);
void ecrireChar(char * result, char * base);
int charger(int height, int width);

#endif