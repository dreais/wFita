#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../Header/room.h"
#include "../Header/shape.h"
#include "../Header/contourn.h"

// constructing map - this is a pre-made for test purpose!
char map_base[8][10] = {
		{FLOR, FLOR, FLOR, OBST, OBST, FLOR, FLOR, FLOR, FINI, FLOR},
		{FLOR, FLOR, FLOR, OBST, FLOR, OBST, FLOR, FLOR, FLOR, FLOR},
		{FLOR, FLOR, FLOR, FLOR, OBST, OBST, FLOR, FLOR, FLOR, FLOR},
		{FLOR, FLOR, FLOR, FLOR, FLOR, OBST, OBST, FLOR, FLOR, FLOR},
		{FLOR, FLOR, OBST, OBST, OBST, OBST, OBST, FLOR, FLOR, FLOR},
		{FLOR, FLOR, OBST, FLOR, FLOR, OBST, FLOR, FLOR, FLOR, FLOR},
		{FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR, FLOR},
		{STAR, FLOR, FLOR, FLOR, OBST, FLOR, FLOR, FLOR, FLOR, FLOR} };

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

	main.room = malloc(sizeof(char*) * 8);
	main.width = 10;
	main.height = 8;
	for (int i = 0; i < 8; i++)
		main.room[i] = map_base[i];
    if (!get_line(&diagonal)) {
        printf("something went wrong\n");
        return true ^ success;
    }
    for (int i = 0; i < diagonal.size; i++)
    {
        printf("x=%d\ty=%d\n", diagonal.pool[i].x,diagonal.pool[i].y);
    }
    return true ^ success;
}

/**
    while (success == false) {
        obst = get_first_obst(&diagonal, start, finish, &main);
        if (obst.x > 0 && obst.y > 0) {
            //set_diag(&diagonal, obst, &main);
        } else {
            //printf("bah yes\n");
            success = true;
        }
        // for testing purpose, we will exit the loop after one occurrence
        success = true;
 */