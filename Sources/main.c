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
    curs_set(0);
    keypad(main_game, TRUE);
    /// MISC
    debug = newwin(10, COLS, getmaxy(main_game), 0);
    ///
    return main_game;
}

static void init_core_game(core_game_t *core)
{
    core->game_screen = initialize_terminal();
    core->c_room = initialize_room(300, 300);
    core->player = initialize_player();
    core->camera = malloc(sizeof(point_t)*1);
    core->camera = &(point_t) {.x = 0, .y = 0};

    core->logs.logs = newwin(LINES - getmaxy(core->game_screen), COLS,
            getmaxy(core->game_screen), 0);
    core->logs.buffer_size = (unsigned int) getmaxy(core->logs.logs);
    core->logs.index = 0;
    core->logs.buffer = malloc(sizeof(char *) * core->logs.buffer_size);
    // WINDOWS TYPE
    for (u_int i = 0; i < core->logs.buffer_size; i++) {
        core->logs.buffer[i] = malloc(sizeof(char) * getmaxx(core->logs.logs) - 1);
    }
    core->logs.buffer[0] = WELCOME;
}

int main(void)
{
#ifdef _WIN32
    HWND Console = GetConsoleWindow();
    SetWindowPos(Console, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN) - 10, GetSystemMetrics(SM_CYSCREEN) - 10, SWP_SHOWWINDOW);
#endif
    core_game_t core;
    int key = 0;

    init_core_game(&core);
    print_room(&core);
    print_stats(core.game_screen, core.player);
    wrefresh(core.game_screen);
    while (core.player.stat.state == alive) {
        key = wgetch(core.game_screen);
        main_loop(&core, key);
        wrefresh(core.game_screen);
    }
    if (core.player.stat.state == dead) {
        move((LINES / 2) - 1, ((COLS) / 2) - (int) strlen(YOU_DIED) / 2);
        printw(YOU_DIED);
        refresh();
        getch();
    }
    endwin();
    return 0;
}

/**
putting here codes that is removed to try earlier parts of the program:


 */