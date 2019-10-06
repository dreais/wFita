//
// Created by Valentin on 10/7/2019.
//

#include <math.h>
#include <stdlib.h>
#include "../../Header/shape.h"
#include "../../Header/path.h"

static const int directions[4][2] = {
        {0, -1}, // TOP
        {1, 0}, // RIGHT
        {0, 1}, // BOTTOM
        {-1, 0}}; // LEFT

point_t search_next_cell(const point_t start, const point_t finish, const room_t room)
{
    int rand_dir = rand() % 2;
    point_t new = {.x = 0, .y = 0};
    int dx = finish.x - start.x;
    int dy = finish.y - start.y;
    int current_direction[2] = { // TODO: make define with these conditions (how dirty!)
            ((int)copysign(1, dx) == 1 && (int)copysign(1, dy) == 1) ? 1 :
            ((int)copysign(1, dx) == -1 && (int)copysign(1, dy) == -1) ? -1 : 0,
            ((int)copysign(1, dx) == -1 && (int)copysign(1, dy) == 1) ? 1 :
            ((int)copysign(1, dx) == 1 && (int)copysign(1, dy) == -1) ? -1 : 0
    };
    dir_name directions_path[4];

    directions_path[0] = get_position_direction_array(current_direction);
    if (directions_path[0] > 3)
        directions_path[0] = 0;
    for (int i = 1; i < 4; i++) {
        directions_path[i] = directions_path[i - 1] + 1;
        if (directions_path[i] > 3)
            directions_path[i] = 0;
    }
    new.x = start.x + directions[directions_path[rand_dir]][0];
    new.y = start.y + directions[directions_path[rand_dir]][1];
    return new;
}