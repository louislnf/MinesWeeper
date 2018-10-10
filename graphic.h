//
//  graphic.h
//  Minesweeper2
//
//  Created by Louis Lenief on 30/01/2016.
//  Copyright © 2016 Louis Lenief. All rights reserved.
//

#ifndef graphic_h
#define graphic_h

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void draw_field(int **mine_field, int **view_field, int w, int h, int flags_left);
void draw_box(int l0, int c0, int l, int c);
void move_cursor(int i, int j, int w, int h);
void draw_menu(int field_w, int field_h, int nb_mines);

void print_array(int **array, int w, int h);


#endif /* graphic_h */
