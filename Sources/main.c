#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#ifdef _WIN32
#include <windows.h>
#include "../Header/curses.h"
#else
#include <ncurses.h>
#include <sys/ioctl.h>
#endif

#include "../Header/room.h"
#include "../Header/shape.h"
#include "../Header/contourn.h"

int main(void)
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND Console = GetConsoleWindow();
    SetWindowPos(Console, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN) - 10, GetSystemMetrics(SM_CYSCREEN) - 10, SWP_SHOWWINDOW);
    int color;
#endif
    point_t start = { .x = 4, .y = 14 };
    point_t finish = { .x = 11, .y = 0 };
    point_t cursor_pos = {.x = 0, .y = 0};
    room_t room = initialize_room(300, 300);
	line_t line;
    char c = 0;

    WINDOW *window = initscr();
    line = create_path(start, finish, room);
    for (int i = 0; i < 65; i++) {
        for (int j = 0, noise; j < 230; j++) {
            noise = room.room[i][j] - 48;
            move(i, j);
            if (noise > 0 && noise < 3) {
                printw(".");
            } else if (noise >= 3 && noise < 5) {
                printw(",");
            } else if (noise >= 5 && noise < 7) {
                printw(";");
            } else {
                printw("%%");
            }
        }
    }
    move(0, 0);
    for (int i = 0; i < room.width; i++)
        free(room.room[i]);
    free(room.room);
    free(line.pool);
    free_hash();
    getch();
    endwin();
    return 0;
}

/**
putting here codes that is removed to try earlier parts of the program:
 */