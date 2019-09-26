//
// Created by Valentin on 9/25/2019.
//

#ifndef MAPGENERATION_CONTOURN_H
#define MAPGENERATION_CONTOURN_H

bool get_line(line_t *line);
point_t get_first_obst(const line_t* diagonal, const point_t start, const point_t finish, const room_t *room);
bool look_next_position(const room_t *room, const line_t *line, point_t start, point_t *tmp);
bool check_fallback(line_t *line, const point_t *to_check);
bool get_order_position(room_t *room, line_t *line, point_t *next);

#endif //MAPGENERATION_CONTOURN_H
