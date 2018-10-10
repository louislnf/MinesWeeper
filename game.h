//
//  game.h
//  Minesweeper2
//
//  Created by Louis Lenief on 30/01/2016.
//  Copyright © 2016 Louis Lenief. All rights reserved.
//

#ifndef game_h
#define game_h

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void game(int *mode, int field_w, int field_h, int nb_mines);
void demine(int **mine_field, int **view_field, int w, int h, int i, int j);
void demine_except_flagged(int **mine_field, int **view_field, int w, int h, int i, int j);
void burrow_mines(int **mine_field, int nb_mines, int w, int h, int i0, int j0);
int count_close_mines(int **mine_field, int w, int h, int i, int j);
void display_mines(int **mine_field, int **view_field, int w, int h);

#endif /* game_h */
