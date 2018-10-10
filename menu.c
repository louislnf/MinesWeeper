//
//  menu.c
//  Minesweeper2
//
//  Created by Louis Lenief on 30/01/2016.
//  Copyright © 2016 Louis Lenief. All rights reserved.
//

#include "menu.h"
#include "graphic.h"

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void menu(int *mode, int *field_w, int *field_h, int *nb_mines) {
    int win_w, win_h;
    getmaxyx(stdscr, win_h, win_w);
    int c;
    while (*mode == 1) {
        draw_menu(*field_w, *field_h, *nb_mines);
        c = getch();
        switch(c) {
            case 'q':
                *mode = 0;
                break;
            case 's':
                *mode = 2;
                break;
            case KEY_UP:
                if (*field_h+2 < win_h-2) {
                    *field_h = *field_h+1;
                }
                break;
            case KEY_DOWN:
                if (*field_h > 4) {
                    *field_h = *field_h-1;
                }
                if (*nb_mines+9 > *field_w**field_h) {
                    *nb_mines = (*field_w**field_h-9)/5*5;
                }
                break;
            case KEY_RIGHT:
                if (3*(*field_w)+4 < win_w) {
                    *field_w = *field_w+1;
                }
                break;
            case KEY_LEFT:
                if (*field_w > 14) {
                    *field_w = *field_w-1;
                }
                if (*nb_mines+9 > *field_w**field_h) {
                    *nb_mines = (*field_w**field_h-9)/5*5;
                }
                break;
            case 'p':
                if (*nb_mines+9 < *field_h*(*field_w)) {
                    *nb_mines = *nb_mines+5;
                }
                break;
            case 'm':
                if (*nb_mines > 0) {
                    *nb_mines = *nb_mines-5;
                }
                break;
            default:
                break;
        }
    }
    
}