#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../Header/room.h"
#include "../Header/shape.h"

#define FLOR '0'
#define OBST '1'
#define FINI '2'
#define STAR '3'

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

point_t get_first_obst(line_t* diagonal, point_t start, point_t finish)
{
	int sign_x = (start.x < finish.x) ? 1 : -1;
	int sign_y = (start.y < finish.y) ? 1 : -1;
	// this may change in the near future if we were to use dynamic array (which would be a
	// better change as we'll dynamically fill them)
	unsigned int width = sizeof(map_base) / sizeof(map_base[0]);
	unsigned int height = sizeof(map_base[0]) / sizeof(map_base[0][0]);

	for (unsigned int i = 0, x, y; i < diagonal->size; i++) {
		x = diagonal->pool[i].x;
		y = diagonal->pool[i].y;
		if (map_base[diagonal->pool[i].y][diagonal->pool[i].x] == OBST) {
			return (point_t) { .x = diagonal->pool[i].x, .y = diagonal->pool[i].y };
		} else if (diagonal->pool[i].x > 0 && diagonal->pool[i].y > 0) {
			if (sign_x == 1) {
				if (sign_y == 1) {
					if (x < width && y < height) {
						if (map_base[y + 1][x] == OBST && map_base[y][x + 1] == OBST) {
							return (point_t) { .x = x, .y = y };
						}
					}
				} else {
					if (x < width && y > 0) {
						if (map_base[y - 1][x] == OBST && map_base[y][x + 1] == OBST) {
							return (point_t) { .x = x, .y = y };
						}
					}
				}
			} else {
				if (sign_y == 1) {
					if (x > 0 && y < height) {
						if (map_base[y + 1][x] == OBST && map_base[y][x - 1] == OBST) {
							return (point_t) { .x = x, .y = y };
						}
					}
				} else {
					if (x > 0 && y > 0) {
						if (map_base[y - 1][x] == OBST && map_base[y][x - 1] == OBST) {
							return (point_t) { .x = x, .y = y };
						}
					}
				}
			}
		}
	}
	return (point_t) { .x = -1, .y = -1 };
}

int main(void)
{
    point_t start = { .x = 0, .y = 8 };
    point_t finish = { .x = 7, .y = 0 };
    line_t diagonal;
	point_t obst;

    if (!get_line(start, finish, &diagonal))
        printf("something went wrong\n");
	obst = get_first_obst(&diagonal, start, finish);
	if (obst.x == -1 && obst.y == -1)
		printf("no obst\n");
	else
		printf("first obst at x=%d    y=%d\n", obst.x, obst.y);
    return 0;
}