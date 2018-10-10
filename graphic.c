//
//  graphic.c
//  Minesweeper2
//
//  Created by Louis Lenief on 30/01/2016.
//  Copyright © 2016 Louis Lenief. All rights reserved.
//

#include "graphic.h"
#include "basic.h"

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void draw_field(int **mine_field, int **view_field, int w, int h, int flags_left) {
    int win_w, win_h;
    getmaxyx(stdscr, win_h, win_w);
    int win_w0 = (win_w-3*w)/2;
    int win_h0 = (win_h-h)/2;
    move(win_h0-2, win_w0-1);
    printw("Q: Quit M: Menu");
    move(win_h0-2, win_w0+3*w-15);
    printw("Flags left:     ");
    move(win_h0-2, win_w0+3*w-15);
    printw("Flags left: %d", flags_left);
    move(win_h0+h+1, win_w0-1);
    printw("Use arrows to move | SPACE: Demine | F: Flag");
    draw_box(win_h0-1, win_w0-1, h, 3*w);
    for (int i=0; i<h; ++i) {
        for (int j=0; j<w; ++j) {
            move(win_h0+i, win_w0+3*j+1);
            if (view_field[i][j] == 0) {
                printw("_");
            }
            if (view_field[i][j] == 2) {
                attron(A_BOLD);
                printw("F");
                attroff(A_BOLD);
            }
            if (view_field[i][j] == 1) {
                if (mine_field[i][j] == -1) {
                    printw("X");
                }
                else if (mine_field[i][j] == 0) {
                    printw(" ");
                }
                else {
                    printw("%d", mine_field[i][j]);
                }
            }
        }
    }
}

void draw_box(int l0, int c0, int l, int c) {
    int win_l, win_c;
    getmaxyx(stdscr, win_l, win_c);
    for (int i=0; i<l; i++) {
        move(l0+1+i, c0);
        printw("|");
        move(l0+1+i, c0+c+1);
        printw("|");
    }
    for (int j=0; j<c+2; j++) {
        move(l0, c0+j);
        if (j==0 || j==c+1) {
            printw("+");
        } else {
            printw("-");
        }
        move(l0+l+1, c0+j);
        if (j==0 || j==c+1) {
            printw("+");
        } else {
            printw("-");
        }
    }
}

void move_cursor(int i, int j, int w, int h) {
    int win_w, win_h;
    getmaxyx(stdscr, win_h, win_w);
    int win_w0 = (win_w-3*w)/2;
    int win_h0 = (win_h-h)/2;
    move(win_h0+i, win_w0+3*j+1);
}

void print_array(int **array, int w, int h) {
    move(0, 0);
    for(int i=0; i<h; ++i){
        move(i,0);
        for (int j=0; j<w; ++j) {
            printw("%d ", array[i][j]);
        }
    }
    refresh();
    printw("\n Press any key...");
    getch();
}

void draw_menu(int field_w, int field_h, int nb_mines) {
    int win_w, win_h;
    getmaxyx(stdscr, win_h, win_w);
    const int w=22, h=9;
    int l0, c0;
    l0 = (win_h-h)/2;
    c0 = (win_w-w)/2;
    draw_box(l0, c0, h, w);
    move(l0+1, c0+7);
    printw("MINESWEEPER");
    move(l0+3, c0+2);
    printw("Size:");
    move(l0+3, c0+15);
    printw("000x000");
    int pw=power_of_10(field_w), ph=power_of_10(field_h);
    move(l0+3, c0+18-pw);
    printw("%d", field_w);
    move(l0+3, c0+22-ph);
    printw("%d", field_h);
    move(l0+4, c0+2);
    printw("Mines:");
    move(l0+4, c0+18);
    printw("0000");
    int pn=power_of_10(nb_mines);
    move(l0+4, c0+22-pn);
    printw("%d", nb_mines);
    move(l0+6, c0+3);
    printw("Press S to start..");
    move(l0+8, c0+3);
    printw("arrows: size");
    move(l0+9, c0+3);
    printw("p/m: mines");
    move(0,0);
}