//
// Created by Valentin on 10/6/2019.
//

#include "../../Header/core_game.h"
#include <math.h>

static WINDOW *stat;
static bool was_initialize = false;

static void initialize_stat_win(WINDOW *main_game)
{
    stat = newwin(LINES / 2, 50, 0, getmaxx(main_game) + 1);
}

static void health_bar(const int width, const charac_t player)
{
	float f_percentage = ((float)player.stat.health / (float)player.stat.max_health) * 100.0f;
	float f_progress_bar;

	for (int i = 1; i < width + 1; i++) {
		f_progress_bar = ((float)i / (float)width) * 100.0f;
		if (f_progress_bar <= f_percentage) {
			wattron(stat, COLOR_PAIR(RED));
			wprintw(stat, "|");
			wattroff(stat, COLOR_PAIR(RED));
		} else {
			wprintw(stat, "|");
		}
	}
}

void print_stats(WINDOW *main_game, const charac_t player)
{
    if (was_initialize == false)
        initialize_stat_win(main_game);
    wmove(stat, 0, 0);
    wclear(stat);
    wprintw(stat, "Level=%d\nExp=%d\nHealth=%d/%d\n", player.stat.level, player.stat.experience, player.stat.health,
            player.stat.max_health);
    wmove(stat, 2, 0);
	health_bar(getmaxx(stat), player);
    wrefresh(stat);
}