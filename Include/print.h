//
// Created by Valentin on 3/19/2021.
//

#ifndef WFITA_REMASTER_PRINT_H
#define WFITA_REMASTER_PRINT_H

#include "core_game.h"

void print_map(core_game_t *core, int zoom_value);

void display_textures(core_game_t *core, int zoom);
void print_player(core_game_t *core, int zoom, unsigned int screen_h, unsigned int screen_w);

#endif //WFITA_REMASTER_PRINT_H
