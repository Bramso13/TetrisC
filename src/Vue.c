#include "../inc/Vue.h"

int menu(int height, int width){

    int xButton=50, i, yButton=70, hButton=150;

    MLV_draw_filled_rectangle(10, 10, width-20, height-20, MLV_COLOR_GRAY);

    /* Boutons */
    
    for(i=0;i<3;i++){
        MLV_draw_filled_rectangle(xButton, yButton+((hButton+20)*i), width-100, hButton, MLV_COLOR_WHITE);
        MLV_draw_text(xButton+((width-100)/2), yButton+((hButton+20)*i)+(hButton/2),nomB[i], MLV_COLOR_BLACK);
    }

    MLV_actualise_window();
    return 1;
}