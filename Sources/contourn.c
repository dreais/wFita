//
// Created by Valentin on 9/25/2019.
//

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
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

point_t get_first_obst(line_t* diagonal, point_t start, point_t finish, room_t *room)
{
    int sign_x = (start.x < finish.x) ? 1 : -1;
    int sign_y = (start.y < finish.y) ? 1 : -1;
    unsigned int width = room->width;
    unsigned int height = room->height;

    for (unsigned int i = 0, x, y; i < diagonal->size; i++) {
        x = diagonal->pool[i].x;
        y = diagonal->pool[i].y;
        if (room->room[diagonal->pool[i].y][diagonal->pool[i].x] == OBST) {
            return (point_t) { .x = diagonal->pool[i].x, .y = diagonal->pool[i].y };
        }
        else if (diagonal->pool[i].x > 0 && diagonal->pool[i].y > 0) {
            if (sign_x == 1) {
                if (sign_y == 1) {
                    if (x < width && y < height) {
                        if (room->room[y + 1][x] == OBST && room->room[y][x + 1] == OBST) {
                            return (point_t) { .x = x, .y = y };
                        }
                    }
                }
                else {
                    if (x < width && y > 0) {
                        if (room->room[y - 1][x] == OBST && room->room[y][x + 1] == OBST) {
                            return (point_t) { .x = x, .y = y };
                        }
                    }
                }
            }
            else {
                if (sign_y == 1) {
                    if (x > 0 && y < height) {
                        if (room->room[y + 1][x] == OBST && room->room[y][x - 1] == OBST) {
                            return (point_t) { .x = x, .y = y };
                        }
                    }
                }
                else {
                    if (x > 0 && y > 0) {
                        if (room->room[y - 1][x] == OBST && room->room[y][x - 1] == OBST) {
                            return (point_t) { .x = x, .y = y };
                        }
                    }
                }
            }
        }
    }
    return (point_t) { .x = -1, .y = -1 };
}