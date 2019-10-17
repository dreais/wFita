#include <stdio.h>
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

static unsigned long long iteration_n = 0;

int main(int argc, char **argv __attribute__((unused)))
{
#ifdef _WIN32
    HWND Console = GetConsoleWindow();
    SetWindowPos(Console, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN) - 10, GetSystemMetrics(SM_CYSCREEN) - 10, SWP_SHOWWINDOW);
#endif
    core_game_t core;
    int key = 0;

    get_log_file();
#ifdef _WIN32
	output_logs_str(PREFIX_DEBUG, "CXSCREEN=%d\n", GetSystemMetrics(SM_CXSCREEN) - 10);
	output_logs_str(PREFIX_DEBUG, "CYSCREEN=%d\n", GetSystemMetrics(SM_CYSCREEN) - 10);
#endif
	if (argc > 1) {
		// TODO parsing properly options (if there is any)
	}
    init_core_game(&core);
	output_logs_str(PREFIX_DEBUG, "Room width=%d\n", core.floors->c_room.width);
	output_logs_str(PREFIX_DEBUG, "Room height=%d\n", core.floors->c_room.height);
	output_logs_str(PREFIX_INFO, "Iteration number %llu\n", iteration_n++);
    print_room(&core);
    print_stats(core.game_screen, core.player);
    wrefresh(core.game_screen);
    while (core.player.stat.state == alive) {
    	output_logs_str(PREFIX_INFO, "Iteration number %llu\n", iteration_n++);
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
	close_file();
    endwin();
    return 0;
}

/**
putting here codes that is removed to try earlier parts of the program:


 */
