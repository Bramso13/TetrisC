#include "../inc/Jeu.h"

void jeuVide(matriceJeu m){

    int i,j;
    for(i=0;i<HAUTEUR;i++){
        for(j=0;j<LARGEUR;j++)
            m[i][j] = 0;
    }
}
int detectSoub(matriceJeu mat){

    int compte=0, i, j, nb=0;
    for(i=0;i<HAUTEUR;i++){
        for(j=0;j<LARGEUR;j++){
            if(mat[i][j] > 0) compte++;
        }
        if(compte == LARGEUR){
            soubstrait(mat, i);
            detectSoub(mat);
            compte = 0;
            nb++;
        }
    }
    return nb;
}
void soubstrait(matriceJeu mat, int ligne){

    int i, j;
    for(j=0;j<LARGEUR;j++) mat[ligne][j]=0;
    for(i=ligne;i>0;i--){
        for(j=0;j<LARGEUR;j++){
            if(mat[i][j] == 0 && mat[i-1][j] > 0) mat[i][j] = mat[i-1][j];
        }
    }
}