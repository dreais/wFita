//
// Created by Valentin on 10/6/2019.
//

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
        camera->y = camera->y;
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

void print_room(core_game_t *core)
{
    int counter = 0;

    adjust_camera(core->c_room, core->game_screen, core->player.p_cursor, core->camera);
    if (use_color == true) {
        for (int i = core->camera->y; i < core->camera->y + (getmaxy(core->game_screen) - 1); i++) {
            wmove(core->game_screen, counter++, 0);
            for (int j = core->camera->x, noise; j < core->camera->x + (getmaxx(core->game_screen) - 2); j++) {
                noise = core->c_room.room[i][j] - 48;
                if (core->player.p_cursor.x == j && core->player.p_cursor.y == i) {
                    wattron(core->game_screen, A_BOLD);
                    waddch(core->game_screen, '@');
                    wattroff(core->game_screen, A_BOLD);
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
        for (int i = core->camera->y; i < core->camera->y + (getmaxy(core->game_screen) - 1); i++) {
            wmove(core->game_screen, counter++, 0);
            for (int j = core->camera->x, noise; j < core->camera->x + (getmaxx(core->game_screen) - 2); j++) {
                noise = core->c_room.room[i][j] - 48;
                if (core->player.p_cursor.x == j && core->player.p_cursor.y == i) {
                    wattron(core->game_screen, A_BOLD);
                    wattron(core->game_screen, COLOR_PAIR(YELLOW));
                    waddch(core->game_screen, '@');
                    wattroff(core->game_screen, A_BOLD);
                    wattroff(core->game_screen, COLOR_PAIR(YELLOW));
                } else if (noise > 0 && noise < 3) {
                    waddch(core->game_screen, '.');
                } else if (noise >= 3 && noise < 5) {
                    waddch(core->game_screen, ',');
                } else if (noise >= 5 && noise < 7) {
                    waddch(core->game_screen, ';');
                } else {
                    waddch(core->game_screen, '%');
                }
            }
        }
    }
}