//
// Created by Valentin on 10/8/2019.
//

/// THIS FILE CONTAINS SHARED FUNCTION BETWEEN CHARAC_T AS PLAYER AND CHARAC_T AS MONSTER
/// EX.: ATTACKING BASED ON STATS, TAKING DAMAGES,...

#include <stdlib.h>
#include "../../Header/core_game.h"

static unsigned int roll_attack(weapon_t w_attack)
{
    unsigned int damage = 0;
    int roll = rand() % (int)(w_attack.crit * 1000);
    float crit_rate = w_attack.crit + 1; // attack multiplier if critic succeeded

    if (roll >= (w_attack.crit * 1000)) {
        damage += w_attack.dmg * crit_rate;
    } else {
        damage += w_attack.dmg;
    }
    return damage;
}

static unsigned int roll_block(weapon_t shield)
{
    unsigned int block = 0;
    int roll = rand() % (int)(shield.crit * 1000);
    float crit_rate = shield.crit + 1;

    if (roll >= (shield.crit * 1000)) {
        block += (shield.def / 2) * crit_rate;
    } else {
        block += shield.def / 2;
    }
    return block;
}

void set_attack(charac_t *attacker, charac_t *defender)
{
    unsigned int d_block = roll_block(defender->left_hand);
    unsigned int a_damage = roll_attack(attacker->right_hand);

    defender->stat.health -= a_damage - d_block;
    if (defender->stat.health <= 0) {
        defender->stat.state = dead;
        defender->p_cursor.x = -1;
        defender->p_cursor.y = -1;
    }
}
