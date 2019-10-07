//
// Created by Valentin on 10/6/2019.
//

#ifdef _WIN32
#include "../../Header/curses.h"
#else
#include <ncurses.h>
#endif

#include "../../Header/core_game.h"

void move_monster(core_game_t *core)
{
    for (unsigned int i = 0; i < core->size_monster_arr; i++) {
        if (core->monster_arr[i].stat.state == true) {
            if (core->monster_arr[i].p_cursor.x >= core->camera->x &&
                core->monster_arr[i].p_cursor.x <= core->camera->x + getmaxx(core->game_screen)) {

                if (core->monster_arr[i].p_cursor.y >= core->camera->y &&
                    core->monster_arr[i].p_cursor.y <= core->camera->y + getmaxy(core->game_screen)) {

                    wmove(core->game_screen, core->monster_arr[i].p_cursor.y - core->camera->y,
                          core->monster_arr[i].p_cursor.x - core->camera->x);
                    waddch(core->game_screen, core->monster_arr[i].repr);
                }
            }
        }
    }
}