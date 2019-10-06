//
// Created by Valentin on 10/6/2019.
//

#ifndef MAPGENERATION_PRINT_H
#define MAPGENERATION_PRINT_H

#include "room.h"
#include "curses.h"
#include "shape.h"

#define GREEN 1
#define YELLOW 2
#define WHITE 3

void print_room(const room_t room, WINDOW *main_game, const point_t player_position);

#endif //MAPGENERATION_PRINT_H
