//
// Created by valentin on 21/09/2019.
//

#ifndef MAPGENERATION_SHAPE_H
#define MAPGENERATION_SHAPE_H

#include "room.h"

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    unsigned int size;
    point_t start;
    point_t finish;
    point_t *pool;
} line_t;

bool get_line(line_t *diagonal);
point_t get_first_obst(line_t* diagonal, point_t start, point_t finish, room_t *room);
bool set_diag(line_t *diagonal, point_t obst, room_t *room);

#endif //MAPGENERATION_SHAPE_H
