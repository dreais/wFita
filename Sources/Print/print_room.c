//
// Created by Valentin on 10/6/2019.
//

#include <stdlib.h>
#include <string.h>
#include "../../Header/core_game.h"

#ifdef _WIN32
#include "../../Header/curses.h"
#else
#include <ncurses.h>
#endif

extern bool use_color;

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
    init_pair(RED_BG, COLOR_RED, COLOR_RED);

    init_color(COLOR_LIGHT_GREEN, 0,686,0);
    init_pair(LIGHT_GREEN, COLOR_LIGHT_GREEN, COLOR_BLACK);

    init_color(COLOR_DARK_GREEN, 372,529,372);
    init_pair(DARK_GREEN, COLOR_DARK_GREEN, COLOR_BLACK);

    init_color(COLOR_GREY, 854,854,854);
    init_pair(GREY, COLOR_GREY, COLOR_BLACK);
    init_pair(GREY_BG, COLOR_GREY, COLOR_GREY);

    init_color(COLOR_BROWN, 1000,686,372);
    init_pair(BROWN, COLOR_BROWN, COLOR_BLACK);
}

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

typedef struct {
	char *colored_line;
	short COLOR_APPLY;
} shorten_str;

static char assign_repr_map(char int_repr)
{
	char repr;
	int noise = int_repr - 48;

	if (noise > 0 && noise < 3) {
		repr = '.';
	} else if (noise >= 3 && noise < 5) {
		repr = ',';
	} else if (noise >= 5 && noise < 7) {
		repr = ';';
	} else {
		repr = '%';
	}
	return repr;
}

static short color_condition(char repr)
{
	if (repr == '.') {
		return LIGHT_GREEN;
	} else if (repr == ',') {
		return DARK_GREEN;
	} else if (repr == ';') {
		return GREY;
	} else {
		return WHITE;
	}
}

static shorten_str *apply_color_lines(const char *str, int *nbr_str)
{
	shorten_str *colored_lines;
	int nbr_color = 1, j = 0;
	char tmp_value = str[0];

	for (int i = 0; i < (int) strlen(str); i++) {
		if (tmp_value != str[i]) {
			tmp_value = str[i];
			nbr_color++;
		}
	}
	tmp_value = str[0];
	colored_lines = malloc(sizeof(shorten_str) * nbr_color);
	for (int i = 0, size_str = 0; i < nbr_color; i++) {
		for (; j < (int) strlen(str); j++) {
			if (tmp_value == str[j]) {
				size_str++;
			} else {
				break;
			}
		}
		colored_lines[i].colored_line = malloc(sizeof(char) * (size_str) + 1);
		colored_lines[i].colored_line[size_str] = '\0';
		colored_lines[i].COLOR_APPLY = color_condition(tmp_value);
		for (int offset = 0; offset < size_str; offset++) {
			colored_lines[i].colored_line[offset] = str[(j - size_str) + offset];
		}
		tmp_value = str[j];
	}
	*nbr_str = nbr_color;
	return colored_lines;
}

char *truncate_map_line(const char *line, int size)
{
	char *truncated = malloc(sizeof(char) * (size + 1));

	truncated[size] = '\0';
	for (int i = 0; i < size; i++) {
		truncated[i] = assign_repr_map(line[i]);
	}
	return truncated;
}

void print_room(core_game_t *core)
{
    int counter = 0;
    shorten_str *colored_lines;
    int nbr_str = 0;
    char *tmp;

	wrefresh(core->game_screen);
    adjust_camera(core->floors[core->current_stage].c_room, core->game_screen, core->player.p_cursor, core->camera);
    if (use_color == true) {
		for (int i = core->camera->y, tmp_x; i < core->camera->y + (getmaxy(core->game_screen) - 1); i++) {
			wmove(core->game_screen, counter++, 0);
			for (int cnt = 0; cnt < getmaxx(core->game_screen); cnt++) {
				tmp[cnt] = assign_repr_map(core->floors[core->current_stage].c_room.room[i][core->camera->x + cnt]);
			}
			colored_lines = apply_color_lines(tmp, &nbr_str);
			for (int j = 0; j < nbr_str; j++) {
				wattron(core->game_screen, COLOR_PAIR(colored_lines[j].COLOR_APPLY));
				wprintw(core->game_screen, "%s", colored_lines[j].colored_line);
				wattroff(core->game_screen, COLOR_PAIR(colored_lines[j].COLOR_APPLY));
				free(colored_lines[j].colored_line);
			}
			free(tmp);
			free(colored_lines);
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
    } else {
        for (int i = core->camera->y, tmp_x; i < core->camera->y + (getmaxy(core->game_screen) - 1); i++) {
			wmove(core->game_screen, counter++, 0);
			tmp = truncate_map_line(core->floors[core->current_stage].c_room.room[i], getmaxx(core->game_screen));
			wprintw(core->game_screen, "%s\r\n", tmp);
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
    wrefresh(core->game_screen);
}