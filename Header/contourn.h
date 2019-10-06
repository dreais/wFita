//
// Created by Valentin on 9/25/2019.
//

#ifndef MAPGENERATION_CONTOURN_H
#define MAPGENERATION_CONTOURN_H

#include <stdbool.h>
#include "room.h"
#include "shape.h"

bool get_line(line_t *line);
point_t get_first_obst(const line_t* diagonal, const point_t start, const point_t finish, const room_t *room);
bool look_next_position(const room_t *room, const line_t *line, point_t start, point_t *tmp); // deprecated
bool check_fallback(line_t *line, point_t *to_check);
bool get_order_position(const room_t room, line_t *line, point_t *next);

line_t create_path(const point_t start, const point_t finish, const room_t room);

// static point_t *append_point(point_t *pool, const unsigned int size, const point_t to_append)

#endif //MAPGENERATION_CONTOURN_H
