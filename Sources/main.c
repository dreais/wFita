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

bool get_line(point_t start, point_t finish, line_t *diagonal)
{
    int dx = finish.x - start.x;
    int dy = finish.y - start.y;
    float step = 0;
    float m, b;
    float* steps;
    point_t tmp_pt[2];
    unsigned int counter = 0;

    diagonal->pool = malloc(sizeof(point_t) * 1);
    diagonal->pool[0] = (point_t) { .x = -1, .y = -1 };

    if (dx == 0) {
        step = (float) copysign(1, dy);
        for (int i = 0; i != dy; i += (int) step);
        // TODO: return the pt_pool
        return true;
    }
    m = (float)dy / ((float)dx);
    b = (float)(start.y + 1) - m * (float)(start.x + 1);
    step = 1.0f / ((float)fmax(abs(dx), abs(dy)));

    float tmp = (float)(finish.x + 1) / step;
    tmp++;
    float x = ((float)start.x + 1.0f) / step;
    steps = (float*) malloc(sizeof(float) * fabsf(fabsf(x) - fabsf(tmp)) + 2); // last is -1.0
    for (unsigned int i = 0; round((double)x) != round((double)tmp); x = x + copysign(1, dx)) {
        steps[counter] = x * step;

        float y = m * steps[counter] + b;
        if (counter > 0) {
            tmp_pt[1].x = tmp_pt[0].x;
            tmp_pt[1].y = tmp_pt[0].y;
            tmp_pt[0].x = (int)steps[counter];
            tmp_pt[0].y = (int)y;
            if (tmp_pt[0].x != tmp_pt[1].x) {
                diagonal->pool = realloc(diagonal->pool, sizeof(point_t) * (i  + 1));
                if (!diagonal->pool)
                    return false;
                diagonal->pool[i++] = tmp_pt[0];
                diagonal->size = i;
            }
            else if (tmp_pt[0].y != tmp_pt[1].y) {
                diagonal->pool = realloc(diagonal->pool, sizeof(point_t) * (i  + 1));
                if (!diagonal->pool)
                    return false;
                diagonal->pool[i++] = tmp_pt[0];
                diagonal->size = i;
            }
        }
        else {
            tmp_pt[0].x = (int)steps[counter];
            tmp_pt[0].y = (int)y;
            diagonal->pool = realloc(diagonal->pool, sizeof(point_t) * (i  + 1));
            if (!diagonal->pool)
                return false;
            diagonal->pool[i++] = tmp_pt[0];
            diagonal->size = i;
        }
        counter++;
    }
    return true;
}

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
    for (int i = 0; i < diagonal.size; i++) {
        printf("---------------\nx=%d    y=%d\n", diagonal.pool[i].x, diagonal.pool[i].y);
    }
    return 0;
}