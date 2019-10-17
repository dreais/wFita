#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../Header/core_game.h"

#ifdef _WIN32
bool use_color = false;
#else
bool use_color = true;
#endif

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
    core->floors = malloc(sizeof(floor_t) * MAX_FLOOR);
    core->floors[0].c_room = initialize_room(300, 300);
    core->player = initialize_player();
    core->camera = malloc(sizeof(point_t)*1);
    core->camera->x = 0;
    core->camera->y = 0;

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
    core->floors[0].stairs.repr =  181;
    core->floors[0].stairs.cursor.x = 50;
    core->floors[0].stairs.cursor.y = 50;
    core->current_stage = 0;
}

const char log_path[] = "output.log";
FILE *output;

static void get_log_file(void)
{
	output = fopen(log_path, "w+");
	if (output == NULL) {
		fprintf(stderr, "%s could not be opened.\n", log_path);
		return;
	}
	fprintf(output, "[INFO] Opening file to read/write, setting cursor at initial position.\n");
	fprintf(output, "[INFO] If you're reading this line, please don't mind it. Just some file opening :)\n");
	fprintf(output, "[INFO] Logfile named '%s' opened without issue\n", log_path);
}

int main(int argc, char **argv __attribute__((unused)))
{
#ifdef _WIN32
    HWND Console = GetConsoleWindow();
    SetWindowPos(Console, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN) - 10, GetSystemMetrics(SM_CYSCREEN) - 10, SWP_SHOWWINDOW);
#endif
    core_game_t core;
    int key = 0;

    get_log_file();
	if (argc > 1) {
		// TODO parsing properly options (if there is any)
	}
    init_core_game(&core);
    printw("%d\n", getmaxy(core.game_screen));
    refresh();
    getch();
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
