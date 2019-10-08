//
// Created by Valentin on 10/8/2019.
//

#include "../../../Header/core_game.h"

void set_equip(charac_t *user, equipment_t to_equip)
{
    if (to_equip.eType == WEAPON) {
        user->is_weapon_dual_hand = (piv_table[to_equip.piv_key].slot > 1) ? true : false;
        if (user->is_weapon_dual_hand == true) {
            user->left_hand = piv_table[to_equip.piv_key];
            user->right_hand = piv_table[to_equip.piv_key];
        } else {
            if (to_equip.slot == LEFT_HAND) {
                user->left_hand = piv_table[to_equip.piv_key];
            } else {
                user->right_hand = piv_table[to_equip.piv_key];
            }
        }
    } else {
        // other equipment (not defined yet)
    }
}

void set_unequip(charac_t *user, equipment_t to_equip)
{

}