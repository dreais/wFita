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

#ifdef SNOW_ENABLED
#include "../Header/snow/snow.h"
snow_main();
#else

static unsigned long long iteration_n = 0;

#ifdef _WIN32
static bool resize_window_app(core_game_t *core)
{
	INPUT_RECORD input_rec[128];
	DWORD event_read;
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	char *tmp_first_line = truncate_map_line(core->floors[core->current_stage].c_room.room[0], getmaxx(core->game_screen));

	if (ReadConsoleInput(hStdin, input_rec, 128, &event_read)) {
		for (int i = 0; i < (int) event_read; i++) {
			if (input_rec[i].EventType == WINDOW_BUFFER_SIZE_EVENT) {
				output_logs_str(PREFIX_WARNING, "Console window has been resized\n");
				resize_term(0, 0);
				print_room(core);
				mvwprintw(core->game_screen, 0, 0, "%s", tmp_first_line);
				wrefresh(core->game_screen);
				refresh();
			}
		}
	}
	free(tmp_first_line);
	return true;
}
#endif

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
    print_room(&core);
    print_stats(core.game_screen, core.player);
    mvwprintw(core.game_screen, 0, 0, "%s", core.floors[0].c_room.room[0]);
    wrefresh(core.game_screen);
    while (core.player.stat.state == alive) {
#ifdef _WIN32
		resize_window_app(&core);
#endif
        key = wgetch(core.game_screen);
        main_loop(&core, key);
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
#endif