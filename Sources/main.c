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
            printf("\033[0;32m%c\033[0m ", room->room[y][x]);
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
        printf("\033[0;31m%c\033[0m ", room->room[y][x]);
    } else
        printf("%c ", room->room[y][x]);
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

float perlin2d(float x, float y, float freq, int depth);

int main(void)
{
    point_t start = { .x = 4, .y = 14 };
    point_t finish = { .x = 11, .y = 0 };
	room_t room = initialize_room();
	line_t line;

	line = create_path(start, finish, room);
	for (int i = 0; i < 60; i++) {
	    for (int j = 0; j < 200; j++) {
	        if ((int) (10.0f * perlin2d(j, i, 0.1, 4)) == 1)
	            printf(";");
	        else if ((int) (10.0f * perlin2d(j, i, 0.1, 4)) == 2)
	            printf(",");
	        else if ((int) (10.0f * perlin2d(j, i, 0.1, 4)) > 5 && (int) (10.0f * perlin2d(j, i, 0.1, 4)) < 7)
	            printf("%%");
	        else if ((int) (10.0f * perlin2d(j, i, 0.1, 4)) > 7)
	            printf("#");
	        else
	            printf(".");
	    }
	    printf("\n");
	}
    free(room.room);
    free(line.pool);
    getchar();
    return 0;
}

/**
putting here codes that is removed to try earlier parts of the program:
 */