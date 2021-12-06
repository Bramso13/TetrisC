#include "../MLV/MLV_all.h"
#include "../inc/Vue.h"
#include <math.h>
#include <time.h>

int main(void){

    int fenetre=1, height = 600, width = 700;
    /*initScore(); pour initialiser le fichier de score, a lancer qu'une fois*/
    /*initPartie(); pour initialiser le fichier de sauvegarde de partie, a lancer qu'une fois*/
    matriceJeu m;
    jeuVide(m);
    MLV_create_window("Tetris Magic", "tetris", width, height);
    
    while(fenetre != 0){
        MLV_clear_window(MLV_COLOR_BLACK);

        switch(fenetre){

            case 1: /* Menu du début */
                fenetre = menu(height, width);
                break;
            case 2:
                fenetre = jeu(height, width, m);
                break;
            case 3:
                fenetre = score(height, width);
                break;
            case 4:
                fenetre = creationPiece(height, width);
            case 0:
                break;
        }
    }

    return 0;
}