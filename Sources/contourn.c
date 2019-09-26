//
// Created by Valentin on 9/25/2019.
//

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h> // will leave it, i often use printf here
#include "../Header/shape.h"

static const int directions[4][2] = {
        {0, -1}, // TOP
        {1, 0}, // RIGHT
        {0, 1}, // BOTTOM
        {-1, 0}}; // LEFT

typedef enum {TOP, RIGHT, BOTTOM, LEFT} dir_name;

static void insert_enum(dir_name *order, const dir_name to_insert[4])
{
    order[0] = to_insert[0];
    order[1] = to_insert[1];
    order[2] = to_insert[2];
    order[3] = to_insert[3];
}

static bool append_point(point_t *pool, const unsigned int size, const point_t to_append)
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

//////////////////////////////////
/** NON STATIC FUNCTION BELOW **/
/////////////////////////////////

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

point_t get_first_obst(const line_t* diagonal, const point_t start, const point_t finish, const room_t *room)
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

/////////////////////////
/////////////////////////

bool look_next_position(const room_t *room, const line_t *line, point_t start, point_t *tmp)
{
    int dx = line->finish.x - line->start.x;
    int dy = line->finish.y - line->start.y;
    dir_name order[4] = {-1};

    if (dx > 0) {
        if (dy > 0) {
            insert_enum(order, (dir_name[4]) {RIGHT, BOTTOM, LEFT, TOP});
        } else {
            insert_enum(order, (dir_name[4]) {TOP, RIGHT, BOTTOM, LEFT});
        }
    } else { //if dx < 0
        if (dy > 0) {
            insert_enum(order, (dir_name[4]) {BOTTOM, LEFT, TOP, RIGHT});
        } else { // if dx < 0 && if dy < 0
            insert_enum(order, (dir_name[4]) {LEFT, TOP, RIGHT, BOTTOM});
        }
    }
    for (int i = 0; i < 4; i++) {
        // we're testing all 4 positions around one given (which is the start)
        if (room->room[start.y + directions[order[i]][1]][start.x + directions[order[i]][0]] != OBST) {
            tmp->x = start.x + directions[order[i]][0];
            tmp->y = start.y + directions[order[i]][1];
            return true;
        }
    }
    return false;
}

static dir_name get_position_direction_array(const int current_direction[2])
{
    dir_name direction = -1;

    for (int i = 0; i < 4; i++) {
        if (current_direction[0] == directions[i][0] && current_direction[1] == directions[i][1]) {
            direction = i;
            return direction;
        }
    }
    return direction;
}

static void set_next_pos(room_t *room, point_t *next, dir_name directions_path[4])
{
    for (int i = 0; i < 4; i++) {
        if (room->room[next->y + directions[directions_path[i]][1]][next->x + directions[directions_path[i]][0]] != OBST) {
            next->x = next->x + directions[directions_path[i]][0];
            next->y = next->y + directions[directions_path[i]][1];
            return;
        }
    }
}

void get_order_position(room_t *room, line_t *line, point_t *next)
{
    int dx = line->finish.x - line->start.x;
    int dy = line->finish.y - line->start.y;
    int current_direction[2] = { // TODO: make define with these conditions (how dirty!)
            ((int)copysign(1, dx) == 1 && (int)copysign(1, dy) == 1) ? 1 :
            ((int)copysign(1, dx) == -1 && (int)copysign(1, dy) == -1) ? -1 : 0,
            ((int)copysign(1, dx) == -1 && (int)copysign(1, dy) == 1) ? 1 :
            ((int)copysign(1, dx) == 1 && (int)copysign(1, dy) == -1) ? -1 : 0
    };
    dir_name directions_path[4];

    directions_path[0] = get_position_direction_array(current_direction) + 1;
    if (directions_path[0] > 3)
        directions_path[0] = 0;
    for (int i = 1; i < 4; i++) {
        directions_path[i] = directions_path[i - 1] + 1;
        if (directions_path[i] > 3)
            directions_path[i] = 0;
    }
    set_next_pos(room, next, directions_path);
}

bool check_fallback(line_t *line, const point_t *to_check)
{
    int dx = line->finish.x - line->start.x;
    int dy = line->finish.y - line->start.y;
    bool result = false;

    for (unsigned int i = 0; i < line->size; i++) {
        if (line->pool[i].x == to_check->x && line->pool[i].y == to_check->y) {
            line->size = i + 1;
            result = true;
            return result;
        }
    }
    return result;
}