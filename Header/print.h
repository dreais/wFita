//
// Created by Valentin on 10/6/2019.
//

#ifndef MAPGENERATION_PRINT_H
#define MAPGENERATION_PRINT_H

#include "room.h"
#include "shape.h"
#include "character.h"

#ifdef _WIN32
#include "curses.h"
#else
#include <ncurses.h>
#endif

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

/// PRINT_ROOM.C
void print_room(const room_t room, WINDOW *main_game, const point_t player_position, point_t *camera);
void init_colors(void);

/// PRINT_STATS.C
void print_stats(WINDOW *main_game, const charac_t player);

#endif //MAPGENERATION_PRINT_H
