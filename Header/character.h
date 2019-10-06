//
// Created by Valentin on 10/6/2019.
//

#ifndef MAPGENERATION_CHARACTER_H
#define MAPGENERATION_CHARACTER_H

#ifdef _WIN32
#include "curses.h"
#else
#include <ncurses.h>
#endif

#include "room.h"
#include "shape.h"
#include "path.h"

typedef struct {
    unsigned int level;
    unsigned int experience;
    int health;
} stat_t;

typedef struct {
    stat_t stat;
    point_t p_cursor;
    char repr;
    line_t path; // ONLY USED IF MONSTER
} charac_t;

/// MOVEMENT.C
point_t verify_player_position(const point_t p_cursor, const room_t room);
void input_treat(const int key, point_t *p_cursor);

/// PLAYER.C

charac_t initialize_player(void);

/// MONSTER.C

void move_monster(charac_t *monster, const int arr_size, WINDOW* win);

#endif //MAPGENERATION_CHARACTER_H
