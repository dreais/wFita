//
// Created by Valentin on 10/8/2019.
//

#include "../../../Header/core_game.h"

/**
 * IF YOU WANT TO DEFINE A NEW WEAPON, FOLLOW THIS EXAMPLE:
 * .priv_key = number of existing weapon + 1
 * .name = name of the variable followed by the UID
 * .dmg = ALWAYS set to -1 to claim as a non-offensive item. else, your value
 * .def = ALWAYS set to -1 to claim as a non-defensive item. else, your value
 * .crit =  for a shield: chance of blocking
 *          for a weapon: chance of critique
 */

const weapon_t bare_hand = (weapon_t) {
    .slot = LEFT_RIGHT_HAND,
    .piv_key = 0,
    .name = "bare_hand_0",
    .dmg = 1,
    .def = 1,
    .crit = 0.1
};

const weapon_t short_sword = (weapon_t) {
    .slot = RIGHT_HAND,
    .piv_key = 1,
    .name = "short_sword_1",
    .dmg = 2,
    .def = -1,
    .crit = 0.4
};

const weapon_t leather_shield = (weapon_t) {
    .slot = LEFT_HAND,
    .piv_key = 2,
    .name = "leather_shield_2",
    .dmg = -1,
    .def = 2,
    .crit = 0.2
};

const weapon_t creative_sword = (weapon_t) {
    .slot = LEFT_RIGHT_HAND,
    .piv_key = 9999,
    .name = "creative_sword_9999",
    .dmg = 7500,
    .def = 7500,
    .crit = 5
};

#define UID_MAX 4
const weapon_t piv_table[UID_MAX] = {
        bare_hand,
        short_sword,
        leather_shield,
        creative_sword
};
