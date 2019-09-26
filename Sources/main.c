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
    for (int i = 0; i < diagonal.size; i++)
        printf("(%d ; %d)\n", diagonal.pool[i].x, diagonal.pool[i].y);
    obst = get_first_obst(&diagonal, start, finish, &main);
    check_fallback(&diagonal, &obst);
    next = obst;
    if (obst.x == -1 && obst.y == -1)
        success = true; // no obstacle, we can just process with the movements
    while (success == false) {
        get_order_position(&main, &diagonal, &next);
        obst = get_first_obst(&diagonal, start, finish, &main);
        if (obst.x == -1 && obst.y == -1)
            success = true; // no obstacle, we can just process with the movements
        success = true;
    }
    printf("%d\t%d\n", next.x, next.y);
    free(main.room);
    free(diagonal.pool);
    return 0;
}

/**
putting here codes that is removed to try earlier parts of the program:
 */