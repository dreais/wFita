//
// Created by Valentin on 9/25/2019.
//

#ifndef MAPGENERATION_CONTOURN_H
#define MAPGENERATION_CONTOURN_H

bool get_line(line_t *line);
point_t get_first_obst(line_t* diagonal, point_t start, point_t finish, room_t *room);

#endif //MAPGENERATION_CONTOURN_H
