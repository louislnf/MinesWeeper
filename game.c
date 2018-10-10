//
//  game.c
//  Minesweeper2
//
//  Created by Louis Lenief on 30/01/2016.
//  Copyright © 2016 Louis Lenief. All rights reserved.
//

#include "game.h"
#include "graphic.h"
#include "basic.h"

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

/*
 mine_field = 
    -1 = mine
    0  = nothing
    n  = n mines adjacent to that cell
 view_field = 
    0 = not displayed
    1 = displayed
    2 = flagged
 */

void game(int *mode, int field_w, int field_h, int nb_mines) {
    int first_step_done = 0;
    int **mine_field, **view_field;
    view_field = generate_array(field_w, field_h);
    mine_field = generate_array(field_w, field_h);
    
    int gameover = 0;
    int c, i=0, j=0;
    int flags_left = nb_mines;
    
    draw_field(mine_field, view_field, field_w, field_h, flags_left);
    move_cursor(i, j, field_w, field_h);
    refresh();
    
    while (*mode == 2) {
        c = getch();
        switch (c) {
            case 'q':
                *mode = 0;
                break;
            case 'm':
                *mode = 1;
                break;
            case KEY_UP:
                if (i>0)
                    --i;
                break;
            case KEY_DOWN:
                if (i<field_h-1)
                    ++i;
                break;
            case KEY_LEFT:
                if (j>0)
                    --j;
                break;
            case KEY_RIGHT:
                if (j<field_w-1)
                    ++j;
                break;
            case ' ':
                if (first_step_done) {
                    if (mine_field[i][j] != -1 && view_field[i][j]==0) {
                        demine(mine_field, view_field, field_w, field_h, i, j);
                    }
                    else if (mine_field[i][j] == -1){
                        gameover = 1;
                    }
                    else if (mine_field[i][j]>0 && view_field[i][j]==1) {
                        //proceed to demine all the not displayed adjacent cells
                        if (i>0) {
                            if (view_field[i-1][j] != 2) {
                                if (mine_field[i-1][j] != -1) {
                                    demine(mine_field, view_field, field_w, field_h, i-1, j);
                                } else if (mine_field[i-1][j] == -1) {
                                    gameover = 1;
                                }
                            }
                        }
                        if (i>0 && j>0) {
                            if (view_field[i-1][j-1] != 2) {
                                if (mine_field[i-1][j-1] != -1) {
                                    demine(mine_field, view_field, field_w, field_h, i-1, j-1);
                                } else if (mine_field[i-1][j-1] == -1) {
                                    gameover = 1;
                                }
                            }
                        }
                        if (i>0 && j<field_w-1) {
                            if (view_field[i-1][j+1] != 2) {
                                if (mine_field[i-1][j+1] != -1) {
                                    demine(mine_field, view_field, field_w, field_h, i-1, j+1);
                                } else if (mine_field[i-1][j+1] == -1) {
                                    gameover = 1;
                                }
                            }
                        }
                        if (i<field_h-1) {
                            if (view_field[i+1][j] != 2) {
                                if (mine_field[i+1][j] != -1) {
                                    demine(mine_field, view_field, field_w, field_h, i+1, j);
                                } else if (mine_field[i+1][j] == -1) {
                                    gameover = 1;
                                }
                            }
                        }
                        if (i<field_h-1 && j>0) {
                            if (view_field[i+1][j-1] != 2) {
                                if (mine_field[i+1][j-1] != -1) {
                                    demine(mine_field, view_field, field_w, field_h, i+1, j-1);
                                } else if (mine_field[i+1][j-1] == -1) {
                                    gameover = 1;
                                }
                            }
                        }
                        if (i<field_h-1 && j<field_w-1) {
                            if (view_field[i+1][j+1] != 2) {
                                if (mine_field[i+1][j+1] != -1) {
                                    demine(mine_field, view_field, field_w, field_h, i+1, j+1);
                                } else if (mine_field[i+1][j+1] == -1) {
                                    gameover = 1;
                                }
                            }
                        }
                        if (j>0) {
                            if (view_field[i][j-1] != 2) {
                                if (mine_field[i][j-1] != -1) {
                                    demine(mine_field, view_field, field_w, field_h, i, j-1);
                                } else if (mine_field[i][j-1] == -1) {
                                    gameover = 1;
                                }
                            }
                        }
                        if (j<field_w-1) {
                            if (view_field[i][j+1] != 2) {
                                if (mine_field[i][j+1] != -1) {
                                    demine(mine_field, view_field, field_w, field_h, i, j+1);
                                } else if (mine_field[i][j+1] == -1) {
                                    gameover = 1;
                                }
                            }
                        }
                    }
                } else {
                    first_step_done=1;
                    burrow_mines(mine_field, nb_mines, field_w, field_h, i, j);
                    demine(mine_field, view_field, field_w, field_h, i, j);
                }
                break;
            case 'f':
                if (view_field[i][j] == 0 && flags_left > 0) {
                    view_field[i][j] = 2;
                    --flags_left;
                }
                else if (view_field[i][j] == 2) {
                    view_field[i][j] = 0;
                    ++flags_left;
                }
                break;
            default:
                break;
        }
        if (gameover) {
            display_mines(mine_field, view_field, field_w, field_h);
            *mode = 1;
        }
        draw_field(mine_field, view_field, field_w, field_h, flags_left);
        move_cursor(i, j, field_w, field_h);
        refresh();
    }
    if (gameover) {
        getch();
    }
    free(mine_field);
    free(view_field);
}

void demine(int **mine_field, int **view_field, int w, int h, int i, int j) {
    if (mine_field[i][j] == 0) {
        view_field[i][j] = 1;
        if (i>0) {
            if (mine_field[i-1][j] > 0) {
                view_field[i-1][j] = 1;
            }
            if (mine_field[i-1][j] == 0 && view_field[i-1][j] == 0) {
                demine(mine_field, view_field, w, h, i-1, j);
            }
            if (j>0) {
                if (mine_field[i-1][j-1] > 0) {
                    view_field[i-1][j-1] = 1;
                }
                if (mine_field[i-1][j-1] == 0 && view_field[i-1][j-1] == 0) {
                    demine(mine_field, view_field, w, h, i-1, j-1);
                }
            }
            if (j<w-1) {
                if (mine_field[i-1][j+1] > 0) {
                    view_field[i-1][j+1] = 1;
                }
                if (mine_field[i-1][j+1] == 0  && view_field[i-1][j+1] == 0) {
                    demine(mine_field, view_field, w, h, i-1, j+1);
                }
            }
        }
        if (j>0) {
            if (mine_field[i][j-1] > 0) {
                view_field[i][j-1] = 1;
            }
            if (mine_field[i][j-1] == 0  && view_field[i][j-1] == 0) {
                demine(mine_field, view_field, w, h, i, j-1);
            }
        }
        if (j<w-1) {
            if (mine_field[i][j+1] > 0) {
                view_field[i][j+1] = 1;
            }
            if (mine_field[i][j+1] == 0  && view_field[i][j+1] == 0) {
                demine(mine_field, view_field, w, h, i, j+1);
            }
        }
        if (i<h-1) {
            if (mine_field[i+1][j] > 0) {
                view_field[i+1][j] = 1;
            }
            if (mine_field[i+1][j] == 0  && view_field[i+1][j] == 0) {
                demine(mine_field, view_field, w, h, i+1, j);
            }
            if (j>0) {
                if (mine_field[i+1][j-1] > 0) {
                    view_field[i+1][j-1] = 1;
                }
                if (mine_field[i+1][j-1] == 0 && view_field[i+1][j-1] == 0) {
                    demine(mine_field, view_field, w, h, i+1, j-1);
                }
            }
            if (j<w-1) {
                if (mine_field[i+1][j+1] > 0) {
                    view_field[i+1][j+1] = 1;
                }
                if (mine_field[i+1][j+1] == 0 && view_field[i+1][j+1] == 0) {
                    demine(mine_field, view_field, w, h, i+1, j+1);
                }
            }
        }
    }
    if (mine_field[i][j] > 0) {
        view_field[i][j] = 1;
    }
}

void demine_except_flagged(int **mine_field, int **view_field, int w, int h, int i, int j) {
    if (mine_field[i][j] == 0) {
        view_field[i][j] = 1;
        if (i>0) {
            if (mine_field[i-1][j] > 0) {
                view_field[i-1][j] = 1;
            }
            if (mine_field[i-1][j] == 0 && view_field[i-1][j] == 0) {
                demine(mine_field, view_field, w, h, i-1, j);
            }
            if (j>0) {
                if (mine_field[i-1][j-1] > 0) {
                    view_field[i-1][j-1] = 1;
                }
                if (mine_field[i-1][j-1] == 0 && view_field[i-1][j-1] == 0) {
                    demine(mine_field, view_field, w, h, i-1, j-1);
                }
            }
            if (j<w-1) {
                if (mine_field[i-1][j+1] > 0) {
                    view_field[i-1][j+1] = 1;
                }
                if (mine_field[i-1][j+1] == 0  && view_field[i-1][j+1] == 0) {
                    demine(mine_field, view_field, w, h, i-1, j+1);
                }
            }
        }
        if (j>0) {
            if (mine_field[i][j-1] > 0) {
                view_field[i][j-1] = 1;
            }
            if (mine_field[i][j-1] == 0  && view_field[i][j-1] == 0) {
                demine(mine_field, view_field, w, h, i, j-1);
            }
        }
        if (j<w-1) {
            if (mine_field[i][j+1] > 0) {
                view_field[i][j+1] = 1;
            }
            if (mine_field[i][j+1] == 0  && view_field[i][j+1] == 0) {
                demine(mine_field, view_field, w, h, i, j+1);
            }
        }
        if (i<h-1) {
            if (mine_field[i+1][j] > 0) {
                view_field[i+1][j] = 1;
            }
            if (mine_field[i+1][j] == 0  && view_field[i+1][j] == 0) {
                demine(mine_field, view_field, w, h, i+1, j);
            }
            if (j>0) {
                if (mine_field[i+1][j-1] > 0) {
                    view_field[i+1][j-1] = 1;
                }
                if (mine_field[i+1][j-1] == 0 && view_field[i+1][j-1] == 0) {
                    demine(mine_field, view_field, w, h, i+1, j-1);
                }
            }
            if (j<w-1) {
                if (mine_field[i+1][j+1] > 0) {
                    view_field[i+1][j+1] = 1;
                }
                if (mine_field[i+1][j+1] == 0 && view_field[i+1][j+1] == 0) {
                    demine(mine_field, view_field, w, h, i+1, j+1);
                }
            }
        }
    }
    if (mine_field[i][j] > 0) {
        view_field[i][j] = 1;
    }
}

void burrow_mines(int **mine_field, int nb_mines, int w, int h, int i0, int j0) {
    int ri, rj;
    while (nb_mines > 0) {
        ri = rand_int(0, h-1);
        rj = rand_int(0, w-1);
        if (mine_field[ri][rj] != -1) {
            mine_field[ri][rj] = -1;
            if (count_close_mines(mine_field, w, h, i0, j0) > 0 || mine_field[i0][j0]==-1) { //avoiding to burrow a mine on the starting pick
                mine_field[ri][rj] = 0;
            } else {
                --nb_mines;
            }
        }
    }
    for (int i=0; i<h; ++i) {
        for (int j=0; j<w; ++j) {
            if (mine_field[i][j] != -1) {
                mine_field[i][j] = count_close_mines(mine_field, w, h, i, j);
            }
        }
    }
}

int count_close_mines(int **field, int w, int h, int i, int j) {
    int count = 0;
    if (i>0) {
        if (field[i-1][j] == -1) {
            ++count;
        }
    }
    if (i>0 && j>0) {
        if (field[i-1][j-1] == -1) {
            ++count;
        }
    }
    if (i>0 && j<w-1) {
        if (field[i-1][j+1] == -1) {
            ++count;
        }
    }
    if (j>0) {
        if (field[i][j-1] == -1) {
            ++count;
        }
    }
    if (j<w-1) {
        if (field[i][j+1] == -1) {
            ++count;
        }
    }
    if (i<h-1) {
        if (field[i+1][j] == -1) {
            ++count;
        }
    }
    if (i<h-1 && j>0) {
        if (field[i+1][j-1] == -1) {
            ++count;
        }
    }
    if (i<h-1 && j<w-1) {
        if (field[i+1][j+1] == -1) {
            ++count;
        }
    }
    return count;
}

void display_mines(int **mine_field, int **view_field, int w, int h) {
    for (int i=0; i<h; ++i) {
        for (int j=0; j<w; ++j) {
            if (mine_field[i][j] == -1) {
                view_field[i][j] = 1;
            }
        }
    }
}
