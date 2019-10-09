//
// Created by Valentin on 10/6/2019.
//

#ifndef MAPGENERATION_PRINT_H
#define MAPGENERATION_PRINT_H

#include "core_game.h"

/// PRINT_ROOM.C
void print_stairs(core_game_t *core);
void print_room(core_game_t *core);
void init_colors(void);

/// PRINT_STATS.C
void print_stats(WINDOW *main_game, const charac_t player);

void print_logs(core_game_t *core);

#endif //MAPGENERATION_PRINT_H
