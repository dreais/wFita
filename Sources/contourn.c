//
// Created by Valentin on 9/25/2019.
//

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../Header/shape.h"

bool append_point(point_t *pool, unsigned int size, point_t to_append)
{
    pool = realloc(pool, sizeof(point_t) * size);
    pool[size] = to_append;
    return true;
}

bool get_line(line_t *line)
{
    int dx = line->finish.x - line->start.x;
    int dy = line->finish.y - line->start.y;
    int x = line->start.x;
    int y = line->start.y;

    line->size = 0;
    line->pool = malloc(sizeof(point_t) * 1);
    line->pool[0] = line->start;

    // printf("dx=%d\tdy=%d\n", dx, dy);
    // printf("start=\nx=%d\ty=%d\n", x, y);
    // printf("finish=\nx=%d\ty=%d\n", line->finish.x, line->finish.y);

    while (abs(dx) != abs(dy)) {
        if (abs(dx) > abs(dy)) {
            x = x + (1 * (int)copysign(1, dx));
            dx = line->finish.x - x;
            line->size++;
            append_point(line->pool, line->size, (point_t) { .x = x, .y = y });
        } else {
            y = y + (1 * (int)copysign(1, dy));
            dy = line->finish.y - y;
            line->size++;
            append_point(line->pool, line->size, (point_t) { .x = x, .y = y });
        }
    }
    return true;
}