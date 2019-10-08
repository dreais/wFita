//
// Created by Valentin on 10/8/2019.
//

#include "../../Header/core_game.h"

#define SIZE_KEY_ARRAY 6

// TODO: could add a mask to determine what args to send
static const key_func key_f[] = {
        {.key = KEY_UP, .func = &move_up},
        {.key = KEY_DOWN, .func = &move_down},
        {.key = KEY_LEFT, .func = &move_left},
        {.key = KEY_RIGHT, .func = &move_right},
        {.key = 'q', .func = &quit_game},
        {.key = 'c', .func = &clear_logs}
};

void input_treat(const int key, core_game_t *core)
{
    for (int i = 0; i < SIZE_KEY_ARRAY; i++) {
        if (key == key_f[i].key) {
            (key_f[i].func)(core);
        }
    }
}