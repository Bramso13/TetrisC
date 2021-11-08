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

    int i=0,j, compte=0;
    for(j=0;j<LARGEUR;j++)
        if(m[i][j] > 0) return 1;
    return 0;
}
void placePiece(Piece p, int * etape, matriceJeu m, int ** x){

    int i,j, compte=0, test=1;
    
    for(i=3;i!=0;i--){
        compte = *etape - (3-i);
        if(compte >= 0){
            for(j=0;j<4;j++){
                if(p->dessin[i][j] > 0){
                    if(p->dessin[i+1][j] == 0){
                        x[test][0] = compte;
                        x[test][1] = p->x+j;
                        test++;
                    }
                    m[compte][p->x+j] = p->dessin[i][j];
                }
            }
        }
    }
    x[0][0] = test;
    x[0][1] = test;
    
}
int finGravite(matriceJeu m, int ** x, int etape){

    int ma = x[0][0], i;
    for(i=0;i<ma;i++){
        if(m[x[i][0]+1][x[i][1]] > 0 || x[i][0]+1 == HAUTEUR) return 1;
    }
    return 0;
}
void recopieMatrice(matriceJeu m, matriceJeu c){

    int i, j;
    for(i=0;i<HAUTEUR;i++)
        for(j=0;j<LARGEUR;j++)
            c[i][j] = m[i][j];
}
void recopieMat(int m[4][4], int c[4][4]){
    int i, j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            c[i][j] = m[i][j];
}
int movePiece(Piece p, int direction){

    int i,j, compte=0, max=0;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(p->dessin[i][j]>0) compte++;
        }
        if(compte > max) max = compte;
        compte=0;
    }
    if(direction){ /* DROITE */
        if(p->x+max < LARGEUR-max && p->x+1 > 0){
            p->x = p->x+1;
            return 1;
        }else return 0;
    }else{
        if(p->x >= 0 && p->x < LARGEUR-max){
            p->x = p->x-1;
            return 1;
        }else return 0;
    }
    return 0;
}
void rotate90Horloge(int a[4][4]){
    int N=4, i, j;
    for (i = 0; i < N / 2; i++) {
        for (j = i; j < N - i - 1; j++) {

            int temp = a[i][j];
            a[i][j] = a[N - 1 - j][i];
            a[N - 1 - j][i] = a[N - 1 - i][N - 1 - j];
            a[N - 1 - i][N - 1 - j] = a[j][N - 1 - i];
            a[j][N - 1 - i] = temp;
        }
    }
}
void rotate90HorlogeInv(int a[4][4]){
    int temp[4][4];
    int i,j, n=4;

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            temp[n-j-1][i] = a[i][j];
        }
    }
    recopieMat(temp, a);

}