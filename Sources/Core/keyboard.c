//
// Created by Valentin on 3/19/2021.
//

#include "raylib.h"
#include "core_game.h"

static void move_up(core_game_t *core)
{
    core->player.pos.y--;
    if (core->player.pos.y < 0)
        core->player.pos.y++;
}

static void move_down(core_game_t *core)
{
    core->player.pos.y++;
    if (core->player.pos.y == ROOM_MAX_HEIGHT)
        core->player.pos.y--;
}

static void move_left(core_game_t *core)
{
    core->player.pos.x--;
    if (core->player.pos.x < 0)
        core->player.pos.x++;
}

static void move_right(core_game_t *core)
{
    core->player.pos.x++;
    if (core->player.pos.x == ROOM_MAX_WIDTH)
        core->player.pos.x--;
}

static const key_func key_f[] = {
        {.key = KEY_UP, .func = &move_up},
        {.key = KEY_DOWN, .func = &move_down},
        {.key = KEY_LEFT, .func = &move_left},
        {.key = KEY_RIGHT, .func = &move_right},
};

void input_treat(core_game_t *core)
{
    for (int i = 0; i < SIZE_KEY_ARRAY; i++) {
        if (IsKeyDown(key_f[i].key)) {
            (key_f[i].func)(core);
        }
    }
}