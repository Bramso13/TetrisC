#include "../inc/Jeu.h"

void jeuVide(matriceJeu m){

    int i,j;
    for(i=0;i<HAUTEUR;i++){
        for(j=0;j<LARGEUR;j++)
            m[i][j] = 0;
    }
}
int detectSoub(matriceJeu mat){

    int compte=0, i, j, nb=0, k;
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
    
    for(j=0;j<LARGEUR;j++) {
        mat[ligne][j]=0;
        
    }
    for(i=ligne;i>0;i--){
        for(j=0;j<LARGEUR;j++){
            if(mat[i][j] == 0 && mat[i-1][j] > 0) mat[i][j] = mat[i-1][j];
        }
    }
}
int finJeu(matriceJeu m){

    int i,j, compte=0;
    for(i=0;i<LARGEUR;i++){
        for(j=0;j<HAUTEUR;j++){
            if(m[i][j] > 0) compte++;
        }
    }
    if(compte == LARGEUR*HAUTEUR) return 1;
    return 0;
}
int placePiece(Piece p, int * etape, matriceJeu m){

    int i,j, compte=0, x, test=0;
    
    for(i=3;i!=0;i--){
        compte = *etape - (3-i);
        if(compte >= 0){
            for(j=0;j<4;j++){
                if(p->dessin[i][j] > 0){
                    if(!test) {
                        x = p->x+j;
                        test = 1;
                    }
                    m[compte][p->x+j] = p->dessin[i][j];
                }
            }
        }
    }
    return x;
}
int finGravite(matriceJeu m, int x, int etape){

    if(m[etape+1][x] > 0 || etape+1 == HAUTEUR) return 1;
    return 0;
}
void recopieMatrice(matriceJeu m, matriceJeu c){

    int i, j;
    for(i=0;i<HAUTEUR;i++)
        for(j=0;j<LARGEUR;j++)
            c[i][j] = m[i][j];
}