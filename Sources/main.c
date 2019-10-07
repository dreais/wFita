#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include "../Header/curses.h"
#else
#include <ncurses.h>
#endif

#include "../Header/core_game.h"

bool use_color = false;
WINDOW *debug;

WINDOW *initialize_terminal(void)
{
    WINDOW *main_game;

    initscr();
    init_colors();
    noecho();
    cbreak();
    curs_set(0);
    main_game = newwin(LINES / 2 + (LINES / 3), ((COLS / 2) + ((COLS / 2) / 2))-2, 0, 0);
    keypad(main_game, TRUE);
    /// MISC
    debug = newwin(10, COLS, getmaxy(main_game), 0);
    ///
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
    core_game_t core;
    int key = 0;

    core.game_screen = initialize_terminal();
    core.c_room = initialize_room(300, 300);;
    core.player = initialize_player();
    core.camera = malloc(sizeof(point_t)*1);
    core.camera = &(point_t) {.x = 0, .y = 0};

    print_room(&core);
    print_stats(core.game_screen, core.player);
    wrefresh(core.game_screen);
    while (key != 'q') {
        key = wgetch(core.game_screen);
        main_loop(core.game_screen, core.c_room, &core.player, key, core.camera, &core);
        wrefresh(core.game_screen);
    }
    endwin();
    free_objects(core.c_room);
    return 0;
}

/**
putting here codes that is removed to try earlier parts of the program:
 */