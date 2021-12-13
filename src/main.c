#include "../MLV/MLV_all.h"
#include "../inc/Vue.h"
#include <math.h>
#include <time.h>


int main(void){

    int fenetre=1, height = 600, width = 700, k, i,ji, compteP;
    /*initScore(); pour initialiser le fichier de score, a lancer qu'une fois*/
    /*initPartie(); pour initialiser le fichier de sauvegarde de partie, a lancer qu'une fois*/
    Piece tab = (Piece) malloc(sizeof(struct piece));
    recuperePiece(tab);
    compteP = comptePiece(tab);
    free(tab);
    matriceJeu m;
    int ma[4][4];
    for(i=0;i<4;i++)
        for(ji=0;ji<4;ji++)
            ma[i][ji] = 0;
    Score monscore;
    monscore.score = 0;
    for(k=0;k<10;k++){
        monscore.nom[k] = 'n';
    }
    jeuVide(m);
    MLV_create_window("Tetris Magic", "tetris", width, height);
    Jeu * j = (Jeu*) malloc(3*sizeof(Jeu));
    chargerAllPartie(j);
    while(fenetre != 0){
        MLV_clear_window(MLV_COLOR_BLACK);
        if(fenetre >= 10){
            
            fenetre = jeu(height, width, j[fenetre-10].matrice, &j[fenetre-10].score, compteP);
        }
        switch(fenetre){

            case 1: /* Menu du début */
                fenetre = menu(height, width);
                break;
            case 2:
                fenetre = jeu(height, width, m, &monscore, compteP);
                break;
            case 3:
                fenetre = score(height, width);
                break;
            case 4:
                fenetre = creationPiece(height, width, ma, &compteP);
                break;
            case 5:
                fenetre = perdu(height, width, &monscore);
                break;
            case 6: 
                fenetre = charger(height, width);
                break;
            case 0:
                break;
        }
    }

    return 0;
}