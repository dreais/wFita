//
// Created by Valentin on 10/6/2019.
//

#include <stdlib.h>
#include "../../Header/core_game.h"

#ifdef _WIN32
#include "../../Header/curses.h"
#else
#include <ncurses.h>
#endif

static void adjust_camera(const room_t room, WINDOW *main_game, const point_t player_position, point_t *camera)
{
    if (player_position.x < getmaxx(main_game) / 2) {
        camera->x = 0;
    } else if (player_position.x > room.width - (getmaxx(main_game) / 2) + 1) {
        camera->x = camera->x;
    } else {
        camera->x = player_position.x  - (getmaxx(main_game) / 2);
    }

    if (player_position.y < getmaxy(main_game) / 2) {
        camera->y = 0;
    } else if (player_position.y > room.height - (getmaxy(main_game) / 2) + 1) {
        return;
    } else {
        camera->y = player_position.y - (getmaxy(main_game) / 2);
    }
}

void init_colors(void)
{
    start_color();
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);

    init_color(COLOR_LIGHT_GREEN, 0,686,0);
    init_pair(LIGHT_GREEN, COLOR_LIGHT_GREEN, COLOR_BLACK);

    init_color(COLOR_DARK_GREEN, 372,529,372);
    init_pair(DARK_GREEN, COLOR_DARK_GREEN, COLOR_BLACK);

    init_color(COLOR_GREY, 854,854,854);
    init_pair(GREY, COLOR_GREY, COLOR_BLACK);

    init_color(COLOR_BROWN, 1000,686,372);
    init_pair(BROWN, COLOR_BROWN, COLOR_BLACK);
}

extern bool use_color;

static void print_colored_cell(WINDOW *to_print, char repr, short COLOR, int y, int x, bool bold)
{
	wmove(to_print, y, x);
	if (bold == true) {
		wattron(to_print, A_BOLD);
	}
	wattron(to_print, COLOR_PAIR(COLOR));
	waddch(to_print, repr);
	wattroff(to_print, COLOR_PAIR(COLOR));
	if (bold == true) {
		wattroff(to_print, A_BOLD);
	}
}

void print_room(core_game_t *core)
{
    int counter = 0;

    adjust_camera(core->floors[core->current_stage].c_room, core->game_screen, core->player.p_cursor, core->camera);
    if (use_color == true) {
        for (int i = core->camera->y; i < core->camera->y + (getmaxy(core->game_screen) - 1); i++) {
            wmove(core->game_screen, counter++, 0);
            for (int j = core->camera->x, noise; j < core->camera->x + (getmaxx(core->game_screen) - 2); j++) {
            	noise = core->floors[core->current_stage].c_room.room[i][j] - 48;
                if (core->player.p_cursor.x == j && core->player.p_cursor.y == i) {
                    wattron(core->game_screen, A_BOLD);
                    waddch(core->game_screen, '@');
                    wattroff(core->game_screen, A_BOLD);
                } else if (core->floors[core->current_stage].stairs.cursor.x == j && core->floors[core->current_stage].stairs.cursor.y == i) {
                    waddch(core->game_screen, core->floors[core->current_stage].stairs.repr);
                } else if (noise > 0 && noise < 3) {
                    wattron(core->game_screen, COLOR_PAIR(LIGHT_GREEN));
                    waddch(core->game_screen, '.');
                    wattroff(core->game_screen, COLOR_PAIR(LIGHT_GREEN));
                } else if (noise >= 3 && noise < 5) {
                    wattron(core->game_screen, COLOR_PAIR(DARK_GREEN));
                    waddch(core->game_screen, ',');
                    wattroff(core->game_screen, COLOR_PAIR(DARK_GREEN));
                } else if (noise >= 5 && noise < 7) {
                    wattron(core->game_screen, COLOR_PAIR(GREY));
                    waddch(core->game_screen, ';');
                    wattroff(core->game_screen, COLOR_PAIR(GREY));
                } else {
                    waddch(core->game_screen, '%');
                }
            }
        }
    } else {
        for (int i = core->camera->y, tmp_x; i < core->camera->y + (getmaxy(core->game_screen) - 1); i++) {
            wmove(core->game_screen, counter++, 0);
            char *tmp = malloc(sizeof(char) * getmaxx(core->game_screen));
			for (int cnt = 0; cnt < getmaxx(core->game_screen); cnt++)
				tmp[cnt] = core->floors[core->current_stage].c_room.room[i][core->camera->x + cnt];
			wprintw(core->game_screen, "%s", tmp);
			free(tmp);
			if (core->player.p_cursor.y == i) {
				tmp_x = core->player.p_cursor.x - core->camera->x;
				print_colored_cell(core->game_screen, '@', YELLOW, counter - 1, tmp_x, true);
			}
			if (core->floors[core->current_stage].stairs.cursor.y == i) {
				tmp_x = core->floors[core->current_stage].stairs.cursor.x;
				if (tmp_x >= core->camera->x && tmp_x <= core->camera->x + (getmaxx(core->game_screen) - 1)) {
					tmp_x = tmp_x - core->camera->x;
					print_colored_cell(core->game_screen, 181, WHITE, counter - 1, tmp_x, false);
				}
			}
        }
    }
}
//core->floors[core->current_stage].stairs.cursor.x == j && core->floors[core->current_stage].stairs.cursor.y == i