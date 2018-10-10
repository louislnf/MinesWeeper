//
//  basic.c
//  Minesweeper2
//
//  Created by Louis Lenief on 31/01/2016.
//  Copyright © 2016 Louis Lenief. All rights reserved.
//

#include "basic.h"

#include <stdio.h>
#include <stdlib.h>


int rand_int(const int MIN, const int MAX) {
    return MIN + rand()%(MAX-MIN+1);
}

int **generate_array(int w, int h) {
    int **array = NULL;
    array = malloc(h*sizeof(int*));
    for(int i=0; i<h; ++i){
        array[i] = malloc(w*sizeof(int));
        for (int j=0; j<w; ++j) {
            array[i][j] = 0;
        }
    }
    return array;
}

int power_of_10(int a) {
    int p = 0;
    while (a/power(10, p) > 0) {
        ++p;
    }
    return p;
}

int power(int a, int p) {
    if (p == 0) {
        return 1;
    }
    else {
        return a*power(a,p-1);
    }
}