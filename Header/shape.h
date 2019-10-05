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
    int dx, dy;
} line_t;

#endif //MAPGENERATION_SHAPE_H
