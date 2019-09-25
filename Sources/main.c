#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    line_t diagonal = { .start = start, .finish = finish };
	point_t obst;
	room_t main;
	bool success = false;

	main.room = malloc(sizeof(char*) * 15);
	main.width = 15;
	main.height = 15;
	for (int i = 0; i < 15; i++)
		main.room[i] = map_base[i];
    if (!get_line(&diagonal)) {
        printf("something went wrong\n");
        return true ^ success;
    }
    for (int i = 0; i < diagonal.size; i++) {
        printf("x=%d\ty=%d\n", diagonal.pool[i].x,diagonal.pool[i].y);
    }
    while (success == false) {
        obst = get_first_obst(&diagonal, start, finish, &main);
        printf("obst:\n%d\t%d\n", obst.x, obst.y);
        success = true;
    }
    return true ^ success;
}

/**
putting here codes that is removed to try earlier parts of the program:
 */