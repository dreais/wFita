#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include "../Header/curses.h"
#else
#include <ncurses.h>
#endif

#include "../Header/room.h"
#include "../Header/character.h"
#include "../Header/shape.h"
#include "../Header/contourn.h"
#include "../Header/core_game.h"
#include "../Header/print.h" // printing rooms and stuff

bool use_color = false;

WINDOW *initialize_terminal(void)
{
    WINDOW *main_game;

    initscr();
    init_colors();
    noecho();
    cbreak();
    curs_set(0);
    main_game = newwin(LINES / 2 + (LINES / 3), COLS / 2 + (COLS / 2) / 2, 0, 0);
    keypad(main_game, TRUE);
    return main_game;
}

void free_objects(room_t room)
{
    for (unsigned int i = 0; i < room.width; i++)
        free(room.room[i]);
    free(room.room);
    free_hash();
}

int main(void)
{
#ifdef _WIN32
    HWND Console = GetConsoleWindow();
    SetWindowPos(Console, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN) - 10, GetSystemMetrics(SM_CYSCREEN) - 10, SWP_SHOWWINDOW);
#endif
    WINDOW *main_game = initialize_terminal();
    charac_t player = initialize_player();
    point_t camera = {.x = 0, .y = 0};
    room_t room = initialize_room(300, 300);
    int key = 0;

    print_room(room, main_game, player.p_cursor, &camera);
    print_stats(main_game, player);
    wrefresh(main_game);
    while (key != 'q') {
        key = wgetch(main_game);
        main_loop(main_game, room, &player, key, &camera);
        wrefresh(main_game);
    }
    endwin();
    free_objects(room);
    return 0;
}

/**
putting here codes that is removed to try earlier parts of the program:
 */