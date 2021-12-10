#include "../inc/Vue.h"
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int menu(int height, int width){

    int xButton=50, i, yButton=70, hButton=70;

    /* Rectangle Menu */
    MLV_draw_filled_rectangle(10, 10, width-20, height-20, MLV_COLOR_GRAY);

    /* Titre */
    MLV_draw_text(((width-20)/2)-10, 20, "TETRIS", MLV_COLOR_BLACK);
    /* Boutons */
    char * nomB[5];
    nomB[0] = "Jouer"; nomB[1] = "Charger"; nomB[2] = "Score";nomB[3] = "Creation de piece";nomB[4] = "Quitter";
    for(i=0;i<5;i++){
        MLV_draw_filled_rectangle(xButton, yButton+((hButton+20)*i), width-100, hButton, MLV_COLOR_WHITE);
        MLV_draw_text(((width-20)/2)-10, yButton+((hButton+20)*i)+(hButton/2),nomB[i], MLV_COLOR_BLACK);
    }
    /* Clique */
    int x, y;
    if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){
        MLV_get_mouse_position(&x, &y);
        for(i=0;i<5;i++){
            if(x > xButton && x < (width-100)+xButton && y > yButton+((hButton+20)*i) && y<yButton+((hButton+20)*i)+hButton){
                
                switch(i){
                    case 0:
                        return 2;
                        break;
                    case 1:
                        return 6;
                        break;
                    case 2:
                        return 3;
                        break;
                    case 4:
                        return 0;
                        break;
                    case 3:
                        return 4;
                }
            }
        }
        return 1;
    }
    

    MLV_actualise_window();
    return 1;
}

int jeu(int height, int width, matriceJeu m, Score * monscore){

    int taillePred = 150, choixP, choixPP, etape=1, i, fin=0, vit, rotation=0;
    const int vitesse=400;
    MLV_Keyboard_button touche;
    MLV_Button_state state;
    srand(time(NULL));
    int **x = (int**) malloc(16*sizeof(int));
    if (x == NULL) {
        printf("bug malloc sur x\n");
        exit(EXIT_FAILURE);
    }
    for(i=0;i<16;i++){
        x[i] = (int*) malloc(2*sizeof(int));
        if(x[i] == NULL){
            printf("bug malloc sur x\n");
            exit(EXIT_FAILURE);
        }    
    }
    Piece p, pp; 
    matriceJeu base;
    recopieMatrice(m, base);
    MLV_clear_window(MLV_COLOR_BLACK);

    
    /*Grand rectangle blanc*/
    MLV_draw_filled_rectangle(20, 20, width-40, height-40, MLV_COLOR_WHITE);
    /* Rectangle Prediction */
    
    MLV_draw_filled_rectangle(width-40-taillePred, 20, taillePred+20, height-40, MLV_COLOR_GRAY);
    
    /* Ractangle de jeu */
    MLV_draw_rectangle(40, 40, width-80-taillePred-20, height-80, MLV_COLOR_BLACK);
    
    MLV_draw_filled_rectangle(width-30-taillePred, 150, taillePred, 30, MLV_COLOR_WHITE);
    
    choixP = choixPiece(1,2);
    choixPP = choixPiece(1,2);
    pp = makePiece(choixPP);
    p = makePiece(choixP);
    while(!fin){
        
        recopieMatrice(base, m);
        MLV_get_event (
                        &touche, NULL, NULL,
                        NULL, NULL,
                        NULL, NULL, NULL,
                        &state
                );
        
        if(touche == MLV_KEYBOARD_RIGHT && state == MLV_PRESSED){
            movePiece(p, 1);
        }
        if(touche == MLV_KEYBOARD_LEFT && state == MLV_PRESSED){
            movePiece(p, 0);
        }
        if(touche == MLV_KEYBOARD_DOWN && state == MLV_PRESSED){
            vit = 100;
        }else vit = vitesse;
        if(touche == MLV_KEYBOARD_UP && state == MLV_PRESSED){
            if(rotation == 1){
                rotate90HorlogeInv(p->dessin);
                rotation=0;
            }else{
                rotate90Horloge(p->dessin);
                rotation=1;
            }
        }
        
        
        placePiece(p, &etape, m, x);
        if(finGravite(m, x, etape)){
            detectSoub(m);
            recopieMatrice(m, base);
            choixP = choixPP;
            p = pp;
            etape = 0;
            fin = finJeu(m);
            rotation = 0;
            choixPP = choixPiece(1, 2);
            pp = makePiece(choixPP);
        }
        
        MLV_draw_text(570, 155, "Retour", MLV_COLOR_BLACK);
        MLV_draw_text(570, 200, "Score", MLV_COLOR_BLACK);
        
        
        /* Affichage de la matrice du jeu */
        afficheJeu(height-80, width-80-taillePred-20, 40, 40, m);
        affichePred(100, taillePred, width-taillePred-30, 40, pp->dessin);
        char sc[10];
        sprintf(sc, "%d", monscore->score);
        MLV_draw_text(570, 220, sc, MLV_COLOR_BLACK);
        etape++;
        monscore->score = monscore->score+1;
        MLV_wait_milliseconds(vit);
    }
    Jeu j;
    j.score.score = monscore->score;
    j.score.classement = monscore->classement;
    int k;
    for(k=0;k<10;k++) j.score.nom[k] = monscore->nom[k];
    recopieMatrice(base, j.matrice);
    savePartie(j);
    MLV_actualise_window();
    return 5;
}
int score(int height, int width){

    MLV_clear_window(MLV_COLOR_GRAY10);
    int i, base=100, x, y;
    char clas[10];

    Score * tab = (Score *) malloc(3*sizeof(struct score));
    recupereScore(tab);

    MLV_draw_filled_rectangle(20, 20, width-40, height-40, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(40, 40, 60, 20, MLV_COLOR_GRAY);
    
    if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){
        MLV_get_mouse_position(&x, &y);
        if(x > 40 && x < 100 && y > 40 && y < 60){
            return 1;
        }
    }
    MLV_draw_text(width/2 - 30, 40, "Top Score", MLV_COLOR_BLACK);
    
    for(i=0;i<3;i++){
        
        if(tab[i].score != 0 && tab[i].classement != 0){
            sprintf(clas, "%d", tab[i].classement);
            MLV_draw_text(width/2 - 50, base+(i*20), clas, MLV_COLOR_BLACK);
            MLV_draw_text(width/2 - 20, base+(i*20), tab[i].nom, MLV_COLOR_BLACK);
            sprintf(clas, "%d", tab[i].score);
            MLV_draw_text(width/2 + 80, base+(i*20), clas, MLV_COLOR_BLACK);

        }else{
            /* Afficher "Vide" */
            MLV_draw_text(width/2 - 15, base+(i*20), "Vide", MLV_COLOR_BLACK);
        }
    }

    free(tab);

    MLV_actualise_window();
    return 3;
}
int creationPiece(int height, int width, int m[][4]){

    MLV_clear_window(MLV_COLOR_WHITE);
    int hCarre, wCarre, i, j;
    int h=500,w=600,x=50,y=50, xu, yu;
    hCarre = h/4;
    wCarre = w/4;

    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){
                    MLV_get_mouse_position(&xu, &yu);
                    if(xu > x+(i*wCarre) && xu < x+(i*wCarre)+wCarre && yu > y+(j*hCarre) && yu < y+(j*hCarre)+hCarre){
                        
                        m[j][i]++;
                        if(m[j][i] == 5) m[j][i]=0;
                        xu=-1;
                        yu=-1;
                    } 
            }

        }
    }
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            
            switch(m[j][i]){
                case 0:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_GRAY);
                    break;
                case 1:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_BLUE);
                    break;
                case 2:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_RED);
                    break;
                case 3:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_GREEN);
                    break;
                case 4:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_YELLOW);
                    break;
            }
        }
    }
    MLV_actualise_window();
    return 4;    
}
int perdu(int height, int width, Score * score){

    MLV_clear_window(MLV_COLOR_GRAY10);
    int i, base=100, x, y;
    
    char clas[4];
    char * text;

    MLV_wait_input_box(300, 50, 350, 80,
        MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_WHITE, "Votre nom :", &text);

    for(i=0;i<10;i++){
        score->nom[i] = text[i];
    }
    score->nom[i] = '\0';
    ajouterScore(*score);
    printf("je suis la\n");
    // MLV_draw_filled_rectangle(20, 20, width-40, height-40, MLV_COLOR_WHITE);
    
    // MLV_draw_text(320, 40, "Game Over", MLV_COLOR_BLACK);
    // MLV_draw_text(350, 40, "Game Over", MLV_COLOR_BLACK);
    // printf("je suis la mint\n");
    // sprintf(clas, "%d", score->score);

    // MLV_draw_text(width/2 - 30, 100, "Votre Score :", MLV_COLOR_BLACK);
    // MLV_draw_text(350, 100, clas, MLV_COLOR_BLACK);
    MLV_actualise_window();
    return 1;
}
void ecrireChar(char * result, char * base){

    int i;
    for(i=0;base[i]!='\n';i++){
        result[i] = base[i];
    }
}
int affichePred(int h, int w, int x, int y, int m[4][4]){

    int hCarre, wCarre, i, j;
    hCarre = h/4;
    wCarre = w/4;
    
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            switch(m[j][i]){
                case 0:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_WHITE);
                    break;
                case 1:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_BLUE);
                    break;
                case 2:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_RED);
                    break;
                case 3:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_GREEN);
                    break;
                case 4:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_YELLOW);
                    break;
            }
        }
    }
    MLV_actualise_window();
    return 1;
}
int afficheJeu(int h, int w, int x, int y, matriceJeu m){

    int hCarre, wCarre, i, j;
    hCarre = h/HAUTEUR;
    wCarre = w/LARGEUR;
    
    for(i=0;i<LARGEUR;i++){
        for(j=0;j<HAUTEUR;j++){
            switch(m[j][i]){
                case 0:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_GRAY);
                    break;
                case 1:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_BLUE);
                    break;
                case 2:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_RED);
                    break;
                case 3:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_GREEN);
                    break;
                case 4:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_YELLOW);
                    break;
            }
        }
    }
    MLV_actualise_window();
    return 1;
}

int charger(int height, int width){

    MLV_clear_window(MLV_COLOR_WHITE);

    MLV_draw_text(300, 50, "Charger une partie", MLV_COLOR_BLACK);

    int i, base=100, x, y, xu, yu;
    char clas[10];

    Jeu * tab = (Jeu *) malloc(3*sizeof(struct jeu));
    chargerAllPartie(tab);

    MLV_draw_filled_rectangle(20, 20, width-40, height-40, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(40, 40, 60, 20, MLV_COLOR_GRAY);
    
    if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){
        MLV_get_mouse_position(&x, &y);
        if(x > 40 && x < 100 && y > 40 && y < 60){
            return 1;
        }
    }
    MLV_draw_text(width/2 - 30, 40, "Charger une Partie", MLV_COLOR_BLACK);
    
    for(i=0;i<3;i++){
        
        if(tab[i].score.score != 0 && tab[i].score.classement != 0){
            sprintf(clas, "%d", tab[i].score.score);
            MLV_draw_text(width/2 + 10, base+(i*20), clas, MLV_COLOR_BLACK);
            MLV_draw_rectangle(width/2 + 50, base+(i*20), 70, 20, MLV_COLOR_GRAY0);
            MLV_draw_text(width/2 + 54, base+(i*20)+3, "Charger", MLV_COLOR_BLACK);
            if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){
                MLV_get_mouse_position(&xu, &yu);
                
                if(xu > width/2 + 50 && xu < (width/2 + 50+70) && yu > base+(i*20) && yu < base+(i*20)+20){
                    return 10 + i;
                }
            }
        }else{
            /* Afficher "Vide" */
            MLV_draw_text(width/2 - 15, base+(i*20)+10, "Sauvegarde Vide", MLV_COLOR_BLACK);
        }
    }
    
    free(tab);
    MLV_actualise_window();
    return 6;
}