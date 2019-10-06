//
// Created by Valentin on 10/6/2019.
//

#ifndef MAPGENERATION_CORE_GAME_H
#define MAPGENERATION_CORE_GAME_H

#ifdef _WIN32
#include "curses.h"
#else
#include <ncurses.h>
#endif

#include "room.h"
#include "character.h"

void main_loop(WINDOW *win, const room_t room, charac_t *player, const int key, point_t *camera);

#endif //MAPGENERATION_CORE_GAME_H
