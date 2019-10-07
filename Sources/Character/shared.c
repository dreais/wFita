//
// Created by Valentin on 10/8/2019.
//

/// THIS FILE CONTAINS SHARED FUNCTION BETWEEN CHARAC_T AS PLAYER AND CHARAC_T AS MONSTER
/// EX.: ATTACKING BASED ON STATS, TAKING DAMAGES,...

#include "../../Header/core_game.h"

void set_attack(charac_t *attacker, charac_t *defender)
{
    defender->stat.health--;
    if (defender->stat.health <= 0) {
        defender->stat.state = false;
        defender->p_cursor.x = -1;
        defender->p_cursor.y = -1;
    }
}
