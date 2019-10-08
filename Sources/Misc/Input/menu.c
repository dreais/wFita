//
// Created by Valentin on 10/8/2019.
//

#include <stdlib.h>
#include <string.h>
#include "../../../Header/core_game.h"

void quit_game(core_game_t *core)
{
    clear();
    move((LINES / 2) - 1, ((COLS) / 2) - (int) strlen(EXIT_MSG) / 2);
    printw(EXIT_MSG);
    refresh();
    if (getch() == 'q') {
        free(core->camera);
        free(core->monster_arr);
        delwin(core->game_screen);
        delwin(core->stat_screen);
        for (unsigned int i = 0; i < core->c_room.height; i++) {
            free(core->c_room.room[i]);
        }
        free(core->c_room.room);
        endwin();
        exit(0);
    }
    clear();
    refresh();
    print_room(core);
    wrefresh(core->game_screen);
}
