#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../Header/room.h"
#include "../Header/shape.h"

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

int main(void)
{
    point_t start = { .x = 0, .y = 8 };
    point_t finish = { .x = 7, .y = 0 };
    line_t diagonal;
	point_t obst;
	room_t main;

	main.room = malloc(sizeof(char*) * 8);
	main.width = 10;
	main.height = 8;
	for (int i = 0; i < 8; i++)
		main.room[i] = map_base[i];
    if (!get_line(start, finish, &diagonal))
        printf("something went wrong\n");
	for (int i = 0; i < diagonal.size; i++)
		printf("%d   %d\n", diagonal.pool[i].x, diagonal.pool[i].y);
	obst = get_first_obst(&diagonal, start, finish, &main);
	printf("%d    %d\n", obst.x, obst.y);
    return 0;
}