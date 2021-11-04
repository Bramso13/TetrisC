#include "../inc/Vue.h"

int menu(int height, int width){

    int xButton=50, i, yButton=70, hButton=150;

    /* Rectangle Menu */
    MLV_draw_filled_rectangle(10, 10, width-20, height-20, MLV_COLOR_GRAY);

    /* Titre */
    MLV_draw_text(((width-20)/2)-10, 20, "TETRIS", MLV_COLOR_BLACK);
    /* Boutons */
    char * nomB[3];
    nomB[0] = "Jouer"; nomB[1] = "Score"; nomB[2] = "Quitter";
    for(i=0;i<3;i++){
        MLV_draw_filled_rectangle(xButton, yButton+((hButton+20)*i), width-100, hButton, MLV_COLOR_WHITE);
        MLV_draw_text(((width-20)/2)-10, yButton+((hButton+20)*i)+(hButton/2),nomB[i], MLV_COLOR_BLACK);
    }
    /* Clique */
    int x, y;
    if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){
        MLV_get_mouse_position(&x, &y);
        for(i=0;i<3;i++){
            if(x > xButton && x < (width-100)+xButton && y > yButton+((hButton+20)*i) && y<yButton+((hButton+20)*i)+hButton){
                
                switch(i){
                    case 0:
                        return 2;
                        break;
                    case 1:
                        return 3;
                        break;
                    case 2:
                        return 0;
                        break;
                }
            }
        }
        return 1;
    }
    

    MLV_actualise_window();
    return 1;
}
int jeu(int height, int width, matriceJeu m){

    int taillePred = 150;

    MLV_clear_window(MLV_COLOR_BLACK);
    /*Grand rectangle blanc*/
    MLV_draw_filled_rectangle(20, 20, width-40, height-40, MLV_COLOR_WHITE);
    /* Rectangle Prediction */
    MLV_draw_filled_rectangle(width-40-taillePred, 20, taillePred+20, height-40, MLV_COLOR_GRAY);
    /* Ractangle de jeu */
    MLV_draw_rectangle(40, 40, width-80-taillePred-20, height-80, MLV_COLOR_BLACK);
    int i;
    
    for(i=0;i<LARGEUR;i++) m[0][i] = 1;
    while(!finJeu(m)){
        
        /* Affichage de la matrice du jeu */
        afficheJeu(height-80, width-80-taillePred-20, 40, 40, m);
        printf("detect = %d\n",detectSoub(m));
        
        MLV_wait_seconds(2);
        afficheJeu(height-80, width-80-taillePred-20, 40, 40, m);
    }
    
    MLV_actualise_window();
    return 2;
}
int score(int height, int width){

    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_actualise_window();
    return 2;
}
int afficheJeu(int h, int w, int x, int y, matriceJeu m){

    int hCarre, wCarre, i, j, k;
    hCarre = h/HAUTEUR;
    wCarre = w/LARGEUR;
    for(k=0;k<LARGEUR;k++) printf("ligne = %d\n", m[0][k]);
    for(i=0;i<LARGEUR;i++){
        for(j=0;j<HAUTEUR;j++){
            switch(m[j][i]){
                case 0:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_GRAY);
                    break;
                case 1:
                    MLV_draw_filled_rectangle(x+(i*wCarre), y+(j*hCarre), wCarre, hCarre, MLV_COLOR_BLUE);
                    break;
            }
        }
    }
    MLV_actualise_window();
}