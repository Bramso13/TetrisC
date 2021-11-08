#ifndef VUE_H

#define VUE_H
#include "../MLV/MLV_all.h"
#include "../inc/Jeu.h"
#include "../inc/Piece.h"

int menu(int height, int width);
int jeu(int height, int width, matriceJeu m);
int afficheJeu(int height, int width, int x, int y, matriceJeu m);
int score(int height, int width);


#endif