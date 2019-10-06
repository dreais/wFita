#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include "../Header/curses.h"
#else
#include <ncurses.h>
#endif

#include "../Header/room.h"
#include "../Header/shape.h"
#include "../Header/contourn.h"
#include "../Header/print.h" // printing rooms and stuff

bool use_color = false;

point_t verify_player_position(const point_t p_cursor, const room_t room)
{
    point_t new_pos = {.x = p_cursor.x, .y = p_cursor.y};

    if (new_pos.x < 0)
        new_pos.x = 0;
    else if (new_pos.x > room.width - 1)
        new_pos.x = (int) room.width - 1;
    if (new_pos.y < 0)
        new_pos.y = 0;
    else if (new_pos.y > room.height - 1)
        new_pos.y = (int) room.height - 1;
    return new_pos;
}

int main(void)
{
#ifdef _WIN32
    HWND Console = GetConsoleWindow();
    SetWindowPos(Console, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN) - 10, GetSystemMetrics(SM_CYSCREEN) - 10, SWP_SHOWWINDOW);
#endif
    initscr();
    WINDOW *main_game = newwin(LINES / 2 + (LINES / 3), COLS / 2 + (COLS / 2) / 2, 0, 0);
    point_t start = { .x = 4, .y = 14 };
    point_t finish = { .x = 11, .y = 0 };
    point_t p_cursor = {.x = 0, .y = 0};
    point_t camera = {.x = 0, .y = 0};
    room_t room = initialize_room(300, 300);
	line_t line;
    int key = 0;

    init_colors();
    noecho();
    cbreak();
    curs_set(0);
    keypad(main_game, TRUE);
    line = create_path(start, finish, room);
    print_room(room, main_game, p_cursor, &camera);
    wrefresh(main_game);
    while (key != 'q') {
        key = wgetch(main_game);
        switch (key) {
            case KEY_LEFT:
                p_cursor.x--;
                break;
            case KEY_RIGHT:
                p_cursor.x++;
                break;
            case KEY_UP:
                p_cursor.y--;
                break;
            case KEY_DOWN:
                p_cursor.y++;
                break;
            default:
                break;
        }
        p_cursor = verify_player_position(p_cursor, room);
        print_room(room, main_game, p_cursor, &camera);
        wmove(main_game, 0, 0);
        wprintw(main_game, "%d\t%d\n", camera.x, camera.y);
        wrefresh(main_game);
    }
    endwin();
    for (unsigned int i = 0; i < room.width; i++)
        free(room.room[i]);
    free(room.room);
    free(line.pool);
    free_hash();
    return 0;
}

/**
putting here codes that is removed to try earlier parts of the program:

if (player_position.x == j && player_position.y == i) {
wattron(main_game, A_BOLD);
wprintw(main_game, "@");
wattroff(main_game, A_BOLD);
}

 for (int j = camera.x, noise; j < camera.x + (getmaxx(main_game) - 2); j++) {
            noise = room.room[i][j] - 48;
            if (noise > 0 && noise < 3) {
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
 */