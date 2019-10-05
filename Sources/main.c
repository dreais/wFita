#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../Header/room.h"
#include "../Header/shape.h"
#include "../Header/contourn.h"

void print_cell(const room_t room, unsigned int y, unsigned int x, const line_t line)
{
#ifdef _WIN32
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int color;
#endif
    for (unsigned int i = 0; i < line.size; i++) {
        if (line.pool[i].x == (int)x && line.pool[i].y == (int)y) {
#ifdef unix
            printf("\033[0;32m%c\033[0m ", room.room[y][x]);
#else
            color = 2;
            SetConsoleTextAttribute(hConsole, color);
            printf("%c", room.room[y][x]);
#endif
            return;
        }
    }
    if (room.room[y][x] == OBST) {
#ifdef unix
        printf("\033[0;31m%c\033[0m ", room.room[y][x]);
    } else
        printf("%c ", room.room[y][x]);
#else
        color = 12;
        SetConsoleTextAttribute(hConsole, color);
        printf("%c", room.room[y][x]);
    } else {
        color = 15;
        SetConsoleTextAttribute(hConsole, color);
        printf("%c", room.room[y][x]);
    }
#endif

}

void print_room(const room_t room, const line_t line)
{
    for (unsigned int i = 0; i < room.height; i++) {
        for (unsigned j = 0; j < room.width; j++) {
            print_cell(room, i, j, line);
        }
        printf("\n");
    }
}

int main(void)
{
#ifdef _WIN32
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int color;
#endif
    point_t start = { .x = 4, .y = 14 };
    point_t finish = { .x = 11, .y = 0 };
	room_t room = initialize_room(300, 300);
	line_t line;

    line = create_path(start, finish, room);
    for (int i = 0; i < 65; i++) {
        for (int j = 0, noise; j < 230; j++) {
            noise = room.room[i][j] - 48;
            if (noise > 0 && noise < 3) {
#ifdef _WIN32
                color = 2;
                SetConsoleTextAttribute(hConsole, color);
#endif
                printf(".");
            } else if (noise >= 3 && noise < 5) {
#ifdef _WIN32
                color = 6;
                SetConsoleTextAttribute(hConsole, color);
#endif
                printf(",");
            } else if (noise >= 5 && noise < 7) {
#ifdef _WIN32
                color = 8;
                SetConsoleTextAttribute(hConsole, color);
#endif
                printf(";");
            } else {
#ifdef _WIN32
                color = 16;
                SetConsoleTextAttribute(hConsole, color);
#endif
                printf("%%");
            }
        }
         printf("\n");
    }
    // TODO proper freeing
    for (int i = 0; i < room.width; i++)
        free(room.room[i]);
    free(room.room);
    free(line.pool);
    free_hash();
    getchar();
    return 0;
}

/**
	line = create_path(start, finish, room);


putting here codes that is removed to try earlier parts of the program:
    for (int y = 0; y < 65; y++) {
        for (int x = 0, noise; x < 225; x++) {
            noise = (int) (perlin2d(x, y, 0.1f, 4)/10);
            if (noise > 0 && noise < 3)
                printf(".");
            else if (noise >= 3 && noise < 5)
                printf(",");
            else if (noise >= 5 && noise < 7)
                printf(";");
            else
                printf("%%");
        }
        printf("\n");
    }
 */