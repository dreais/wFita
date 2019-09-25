//
// Created by Valentin on 9/25/2019.
//

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../Header/shape.h"

static bool append_point(point_t *pool, unsigned int size, point_t to_append)
{
    pool = realloc(pool, sizeof(point_t) * size);
    pool[size] = to_append;
    return true;
}

static bool get_diagonal(line_t *line, int x, int y)
{
    int dx = line->finish.x - line->start.x;
    int dy = line->finish.y - line->start.y;
    bool success = false;
    unsigned int counter = 0;

    while (!success) {
        if (counter % 2)
            x = x + (1 * (int)copysign(1, dx));
        else
            y = y + (1 * (int)copysign(1, dy));
        counter++;
        line->size++;
        append_point(line->pool, line->size, (point_t) {.x = x, .y = y});
        if (x == line->finish.x && y == line->finish.y) {
            line->size++;
            append_point(line->pool, line->size, (point_t) {.x = x, .y = y});
            success = true;
        }
    }
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
    if (!get_diagonal(line, x, y)) {
        return false;
    }
    return true;
}