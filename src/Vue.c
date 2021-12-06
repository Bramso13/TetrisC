#include "../inc/Vue.h"
#include <math.h>
#include <time.h>
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
                        return 2;
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

int jeu(int height, int width, matriceJeu m){

    int taillePred = 150, choixP, etape=1, i, fin=0, vit, rotation=0;
    const int vitesse=400;
    MLV_Keyboard_button touche;
    MLV_Button_state state;
    srand(time(NULL));
    int **x = (int**) malloc(16*sizeof(int));
    if (x == NULL) exit(EXIT_FAILURE);
    for(i=0;i<16;i++)
        x[i] = (int*) malloc(2*sizeof(int));
    Piece p; 
    Score monscore;
    matriceJeu base;
    recopieMatrice(m, base);
    MLV_clear_window(MLV_COLOR_BLACK);
    /*Grand rectangle blanc*/
    MLV_draw_filled_rectangle(20, 20, width-40, height-40, MLV_COLOR_WHITE);
    /* Rectangle Prediction */
    
    MLV_draw_filled_rectangle(width-40-taillePred, 20, taillePred+20, height-40, MLV_COLOR_GRAY);
    //MLV_draw_text(width-20-taillePred, 30, "SUIVANT :", MLV_COLOR_BLACK);
    /* Ractangle de jeu */
    MLV_draw_rectangle(40, 40, width-80-taillePred-20, height-80, MLV_COLOR_BLACK);
    
    choixP = choixPiece(1,2);
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
            choixP = choixPiece(1,2);
            p = makePiece(choixP);
            etape = 0;
            fin = finJeu(m);
            rotation = 0;
        }
        

        /* Affichage de la matrice du jeu */
        afficheJeu(height-80, width-80-taillePred-20, 40, 40, m);
        
        etape++;
        MLV_wait_milliseconds(vit);
    }
    free(x);
    
    MLV_actualise_window();
    return 1;
}
int score(int height, int width){

    MLV_clear_window(MLV_COLOR_WHITE);


    Score * tab = (Score *) malloc(3*sizeof(struct score));
    recupereScore(tab);

    

    MLV_actualise_window();
    return 3;
}
int creationPiece(int height, int width){

    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_actualise_window();
    return 4;    
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