//
// Created by Valentin on 10/6/2019.
//

#ifndef MAPGENERATION_CHARACTER_H
#define MAPGENERATION_CHARACTER_H

#include "core_game.h"

/// MOVEMENT.C
point_t verify_player_position(const point_t p_cursor, const room_t room);
void input_treat(const int key, point_t *p_cursor);

/// PLAYER.C
charac_t initialize_player(void);

/// MONSTER.C
void move_monster(core_game_t *core);

#endif //MAPGENERATION_CHARACTER_H
