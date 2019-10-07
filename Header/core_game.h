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

typedef struct {
    room_t c_room; // current
    charac_t player;
    point_t *camera;
    charac_t *monster_arr;
    unsigned int size_monster_arr;
    WINDOW *game_screen;
    WINDOW *stat_screen;
} core_game_t;

void main_loop(WINDOW *win, const room_t room, charac_t *player, const int key, point_t *camera, core_game_t *core);

#endif //MAPGENERATION_CORE_GAME_H
