//
// Created by Valentin on 10/8/2019.
//

#include "../../Header/core_game.h"

void print_logs(core_game_t *core)
{
    unsigned int count = core->logs.index;

    for (unsigned int i = 0; i < core->logs.index; i++) {
        if (count > 0) {
            wmove(core->logs.logs, i, 0);
            wprintw(core->logs.logs, "%s", core->logs.buffer[count--]);
        }
    }
    wrefresh(core->logs.logs);
    if (core->logs.index == core->logs.buffer_size - 1) {
        core->logs.index--;
    }
}