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
        endwin();
        exit(0);
    }
    clear();
    refresh();
    print_room(core);
    wrefresh(core->game_screen);
}
