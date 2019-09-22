//
// Created by valentin on 22/09/2019.
//

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "../../Header/shape.h"

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