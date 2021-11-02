#include <MLV/MLV_all.h>
#ifndef JEU_H
#define JEU_H

#define HAUTEUR 10
#define LARGEUR 6


typedef int matriceJeu[HAUTEUR][LARGEUR];

void jeuVide(matriceJeu mat);
int detectSoub(matriceJeu mat);
void soubstrait(matriceJeu mat, int a);

#endif