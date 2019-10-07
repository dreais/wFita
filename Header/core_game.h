//
// Created by Valentin on 10/6/2019.
//

#ifndef MAPGENERATION_CORE_GAME_H
#define MAPGENERATION_CORE_GAME_H

#pragma once

#ifdef _WIN32
#include "curses.h"
#else
#include <ncurses.h>
#endif


/// ENUM TYPEDEFs
typedef enum {TOP, RIGHT, BOTTOM, LEFT} dir_name;


/// SHAPE TYPES
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

/// CHARACTER TYPES
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

/// ROOM TYPES
typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
    char** room;
} room_t;

/// CORE_GAME TYPES
typedef struct {
    room_t c_room; // current
    charac_t player;
    point_t *camera;
    charac_t *monster_arr;
    unsigned int size_monster_arr;
    WINDOW *game_screen;
    WINDOW *stat_screen;
} core_game_t;

/**
 * COLORS DEFINITION
 * first define is the COLOR_PAIR key
 * second define is the index from the converted table (see "Sources" in the README)
 */
#define GREEN 1
#define YELLOW 2
#define WHITE 3
#define DARK_GREEN 4
#define LIGHT_GREEN 5
#define GREY 6

#define COLOR_DARK_GREEN 22
#define COLOR_LIGHT_GREEN 119
#define COLOR_GREY 253
/**
 * END OF COLORS DEFINITION
 */

#include "character.h"
#include "path.h"
#include "print.h"
#include "room.h"

void main_loop(core_game_t *core, const int key);

#endif //MAPGENERATION_CORE_GAME_H