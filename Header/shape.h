//
// Created by valentin on 21/09/2019.
//

#ifndef MAPGENERATION_SHAPE_H
#define MAPGENERATION_SHAPE_H

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    unsigned int size;
    point_t *pool;
} line_t;

bool get_line(point_t start, point_t finish, line_t *diagonal);

#endif //MAPGENERATION_SHAPE_H
