#include "../MLV/MLV_all.h"
#include "../inc/Vue.h"

int main(void){

    int fenetre=1, height = 600, width = 500;

    MLV_create_window("Tetris Magic", "tetris", width, height);
    
    while(fenetre != 0){
        MLV_clear_window(MLV_COLOR_BLACK);

        switch(fenetre){

            case 1: /* Menu du début */
                fenetre = menu(height, width);
                break;
        }
    }

    return 0;
}