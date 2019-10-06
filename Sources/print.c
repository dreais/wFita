//
// Created by Valentin on 10/6/2019.
//

#include "../Header/print.h"
#include "../Header/curses.h"
#include "../Header/room.h"
#include "../Header/shape.h"

void adjust_camera(const room_t room, WINDOW *main_game, const point_t player_position, point_t *camera)
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
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);

    init_color(COLOR_LIGHT_GREEN, 0,686,0);
    init_pair(LIGHT_GREEN, COLOR_LIGHT_GREEN, COLOR_BLACK);

    init_color(COLOR_DARK_GREEN, 372,529,372);
    init_pair(DARK_GREEN, COLOR_DARK_GREEN, COLOR_BLACK);

    init_color(COLOR_GREY, 854,854,854);
    init_pair(GREY, COLOR_GREY, COLOR_BLACK);

}

void print_room(const room_t room, WINDOW *main_game, const point_t player_position, point_t *camera)
{
    point_t init = {.x = 0, .y = 0};

    start_color();

    // TODO adding more colors, variations for the grass for example
    init_colors();
    adjust_camera(room, main_game, player_position, camera);
    for (int i = camera->y; i < camera->y + (getmaxy(main_game) - 1); i++) {
        wmove(main_game, init.y++, 0);
        for (int j = camera->x, noise; j < camera->x + (getmaxx(main_game) - 2); j++) {
            noise = room.room[i][j] - 48;
            if (player_position.x == j && player_position.y == i) {
                wattron(main_game, A_BOLD);
                wprintw(main_game, "@");
                wattroff(main_game, A_BOLD);
            } else if (noise > 0 && noise < 3) {
                wattron(main_game, COLOR_PAIR(LIGHT_GREEN));
                wprintw(main_game, ".");
                wattroff(main_game, COLOR_PAIR(LIGHT_GREEN));
            } else if (noise >= 3 && noise < 5) {
                wattron(main_game, COLOR_PAIR(DARK_GREEN));
                wprintw(main_game, ",");
                wattroff(main_game, COLOR_PAIR(DARK_GREEN));
            } else if (noise >= 5 && noise < 7) {
                wattron(main_game, COLOR_PAIR(GREY));
                wprintw(main_game, ";");
                wattroff(main_game, COLOR_PAIR(GREY));
            } else {
                wattron(main_game, COLOR_PAIR(WHITE));
                wprintw(main_game, "%%");
                wattroff(main_game, COLOR_PAIR(WHITE));
            }
        }
    }
}