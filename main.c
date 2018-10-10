//
//  main.c
//  Minesweeper2
//
//  Created by Louis Lenief on 30/01/2016.
//  Copyright © 2016 Louis Lenief. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "menu.h"
#include "game.h"

int main(int argc, const char *argv[]) {
    srand((unsigned int)time(NULL));
    initscr();
    noecho();
    keypad(stdscr, true);
    int mode = 1;
    int field_w = 20, field_h = 20, nb_mines = 80;
    
    clear();
    
    while (mode) {
        switch(mode) {
            case 1:
                //menu
                clear();
                menu(&mode, &field_w, &field_h, &nb_mines);
                break;
            case 2:
                // game
                clear();
                game(&mode, field_w, field_h, nb_mines);
                break;
            default:
                mode = 1;
                break;
        }
    }
    
    endwin();
    return 0;
}
