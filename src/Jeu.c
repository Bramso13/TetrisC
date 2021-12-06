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
        compte = 0;
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

    int i=0,j;
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
                    if(p->dessin[i+1][j] == 0 || i==3){
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
    for(i=1;i<ma;i++){
        
        if(m[x[i][0]+1][x[i][1]] > 0 || x[i][1]+1 == HAUTEUR){
            return 1;
        }
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
        compte = 0;
        for(j=0;j<4;j++){
            if(p->dessin[i][j]>0) compte++;
        }
        if(compte > max) max = compte;
        compte=0;
    }
    if(direction){ /* DROITE */
        if(p->x+max <= LARGEUR-max && p->x+1 > 0){
            p->x = p->x+1;
            return 1;
        }else return 0;
    }else{ /* GAUCHE */
        if(p->x >= 0 && p->x <= LARGEUR-max){
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

void recupereScore(Score * tab){

    int fr, rc;
    FILE * fp = fopen("./data/score", "r");

    if (fp == NULL){
        printf("Probleme d'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }

    fr = fread(tab, sizeof(Score), 3, fp);
    if (fr != 3){
        printf("Problème de lecture de fichier\n");
        exit(EXIT_FAILURE);
    }
    rc = fclose(fp);
    if(rc == EOF){
        fprintf(stderr, "probleme de fermeture de fichier");
        exit(EXIT_FAILURE);
    }
}

void initScore(){

    int i, rc;
    FILE * fp = fopen("./data/score", "w+");

    if (fp == NULL){
        printf("Probleme d'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }

    for(i=0;i<3;i++){
        Score * s = (Score *) malloc(sizeof(struct score));

        if(s == NULL){
            printf("problème de malloc\n");
            exit(EXIT_FAILURE);
        }
        s->classement = 0;
        s->score = 0;
        if( 1 != fwrite(s, sizeof(struct score), 1, fp)){
            fprintf(stderr, "probleme d'écriture de fichier\n");
        }
    }   
    rc = fclose(fp);
    if(rc == EOF){
        fprintf(stderr, "probleme de fermeture de fichier");
        exit(EXIT_FAILURE);
    }

}
void initPartie(){

    int i, rc;
    FILE * fp = fopen("./data/partieSauvegarde", "w+");

    if (fp == NULL){
        printf("Probleme d'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }

    for(i=0;i<3;i++){
        Jeu * s = (Jeu *) malloc(sizeof(struct jeu));

        if(s == NULL){
            printf("problème de malloc\n");
            exit(EXIT_FAILURE);
        }
        jeuVide(s->matrice);
        s->score.classement = 0;
        s->score.score = 0;
        if( 1 != fwrite(s, sizeof(struct jeu), 1, fp)){
            fprintf(stderr, "probleme d'écriture de fichier\n");
        }
    }   
    rc = fclose(fp);
    if(rc == EOF){
        fprintf(stderr, "probleme de fermeture de fichier");
        exit(EXIT_FAILURE);
    }

}
int estVide(matriceJeu mat){

    int i,j, compte=0;
    for(i=0;i<HAUTEUR;i++){
        for(j=0;j<LARGEUR;j++)
            if(mat[i][j] == 0) compte++;
    }
    if(compte == LARGEUR*HAUTEUR) return 1;
    return 0;
}