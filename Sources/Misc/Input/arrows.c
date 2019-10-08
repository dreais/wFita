//
// Created by Valentin on 10/8/2019.
//

#include "../../../Header/core_game.h"

void move_up(core_game_t *core)
{
    core->player.p_cursor.y--;
}

void move_down(core_game_t *core)
{
    core->player.p_cursor.y++;
}

void move_left(core_game_t *core)
{
    core->player.p_cursor.x--;
}

void move_right(core_game_t *core)
{
    core->player.p_cursor.x++;
}
