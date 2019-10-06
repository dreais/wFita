//
// Created by Valentin on 10/6/2019.
//

#include "../Header/print.h"
#include "../Header/curses.h"
#include "../Header/room.h"
#include "../Header/shape.h"

void print_room(const room_t room, WINDOW *main_game, const point_t player_position)
{
    start_color();

    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    for (int i = 0; i < room.height; i++) {
        for (int j = 0, noise; j < room.width; j++) {
            noise = room.room[i][j] - 48;
            wmove(main_game, i, j);
            if (player_position.x == j && player_position.y == i) {
                wattron(main_game, A_BOLD);
                wprintw(main_game, "@");
                wattroff(main_game, A_BOLD);
            } else if (noise > 0 && noise < 3) {
                wattron(main_game, COLOR_PAIR(GREEN));
                wprintw(main_game, ".");
                wattroff(main_game, COLOR_PAIR(GREEN));
            } else if (noise >= 3 && noise < 5) {
                wattron(main_game, COLOR_PAIR(YELLOW));
                wprintw(main_game, ",");
                wattroff(main_game, COLOR_PAIR(YELLOW));
            } else if (noise >= 5 && noise < 7) {
                wprintw(main_game, ";");
            } else {
                wattron(main_game, COLOR_PAIR(WHITE));
                wprintw(main_game, "%%");
                wattroff(main_game, COLOR_PAIR(WHITE));
            }
        }
    }
}