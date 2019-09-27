#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Header/room.h"
#include "../Header/shape.h"
#include "../Header/contourn.h"

// constructing map - this is a pre-made for test purpose!
char map_base[15][15] = {
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, OBST, FLOR, FLOR, FLOR, FLOR, FINI, FLOR, FLOR, FLOR},
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR},
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, OBST, FLOR, FLOR, FLOR, FLOR, OBST, FLOR, FLOR},
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, OBST, FLOR, FLOR, OBST, FLOR, FLOR, FLOR},
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, OBST, OBST, OBST, FLOR, OBST, FLOR},
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR},
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR},
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR},
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR},
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR},
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR},
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR},
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR},
        {FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR},
        {FLOR, FLOR, FLOR, FLOR, STAR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR},
};

void print_cell(room_t *room, unsigned int y, unsigned int x, line_t *line)
{
    for (unsigned int i = 0; i < line->size; i++) {
        if (line->pool[i].x == (int)x && line->pool[i].y == (int)y) {
            printf("\033[0;32m%c\033[0m ", room->room[y][x]);
            return;
        }
    }
    if (room->room[y][x] == OBST)
        printf("\033[0;31m%c\033[0m ", room->room[y][x]);
    else
        printf("%c ", room->room[y][x]);
}

// TODO: potentially use a file map + args
int main(void)
{
    // TODO: remove these manually start/finish to search them using a function instead
    point_t start = { .x = 4, .y = 14 };
    point_t finish = { .x = 11, .y = 0 };
    line_t diagonal = { .start = start, .finish = finish, .dx =  finish.x - start.x,
                        .dy= finish.y - start.y};
    point_t obst, next = {.x = -1, .y = -1};
	room_t main;
	bool success = false;

	main.room = malloc(sizeof(char *) * 15);
	main.width = 15;
	main.height = 15;
	for (int i = 0; i < 15; i++)
		main.room[i] = map_base[i];
    if (!get_line(&diagonal)) {
        printf("something went wrong\n");
        return 1;
    }
    obst = get_first_obst(&diagonal, start, finish, &main);
    check_fallback(&diagonal, &obst);
    next = obst;
    if (obst.x == -1 && obst.y == -1)
        success = true; // no obstacle, we can just process with the movements
    while (success == false) {
        if (diagonal.finish.x == next.x && diagonal.finish.y == next.y) {
            success = true;
        }
        get_order_position(&main, &diagonal, &next);
        obst = get_first_obst(&diagonal, start, finish, &main);
        diagonal.dx = finish.x - next.x;
        diagonal.dy = finish.y - next.y;
    }
    for (unsigned int i = 0; i < main.height; i++) {
        for (unsigned j = 0; j < main.width; j++) {
            print_cell(&main, i, j, &diagonal);
        }
        printf("\n");
    }
    free(main.room);
    free(diagonal.pool);
    return 0;
}

/**
putting here codes that is removed to try earlier parts of the program:
 */