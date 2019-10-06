//
// Created by Valentin on 10/6/2019.
//

#include "../../Header/print.h"
#include "../../Header/room.h"
#include "../../Header/shape.h"
#include "../../Header/character.h"

#ifdef _WIN32
#include "../../Header/curses.h"
#else
#include <ncurses.h>
#endif

static WINDOW *stat;
static bool was_initialize = false;

static void initialize_stat_win(WINDOW *main_game)
{
    stat = newwin(LINES / 2, 50, 0, getmaxx(main_game) + 1);
}

void print_stats(WINDOW *main_game, const charac_t player)
{
    if (was_initialize == false)
        initialize_stat_win(main_game);
    wmove(stat, 0, 0);
    wprintw(stat, "Level=%d\nExp=%d\n", player.stat.level, player.stat.experience);
    wrefresh(stat);
}