#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../Header/room.h"
#include "../Header/shape.h"

#define FLOR '0'
#define OBST '1'
#define FINI '2'
#define STAR '3'

int main(void)
{
    // constructing map - this is a pre-made for test purpose!
    char map_base[8][10] = {
            {FLOR, FLOR, FLOR, OBST, FLOR, FLOR, FLOR, FLOR, FINI, FLOR},
            {FLOR, FLOR, FLOR, OBST, FLOR, FLOR, FLOR, OBST, FLOR, FLOR},
            {FLOR, FLOR, FLOR, FLOR, OBST, OBST, FLOR, FLOR, FLOR, FLOR},
            {FLOR, FLOR, FLOR, FLOR, FLOR, OBST, OBST, FLOR, FLOR, FLOR},
            {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, OBST, FLOR, FLOR, FLOR},
            {FLOR, FLOR, FLOR, FLOR, FLOR, OBST, FLOR, FLOR, FLOR, FLOR},
            {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR},
            {STAR, FLOR, FLOR, FLOR, OBST, FLOR, FLOR, FLOR, FLOR, FLOR} };
    point_t start = { .x = 0, .y = 8 };
    point_t finish = { .x = 7, .y = 0 };
    line_t diagonal;

    if (!get_line(start, finish, &diagonal))
        printf("something went wrong\n");
    for (unsigned int i = 0; i < diagonal.size; i++) {
        printf("---------------\nx=%d    y=%d\n", diagonal.pool[i].x, diagonal.pool[i].y);
    }
    return 0;
}