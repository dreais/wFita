//
// Created by valentin on 22/09/2019.
//

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "../../Header/shape.h"
#include "../../Header/room.h"

bool get_line(line_t *diagonal)
{
	float m, b;
	float* steps;
	point_t tmp_pt[2]; 
	int dx = diagonal->finish.x - diagonal->start.x;
    int dy = diagonal->finish.y - diagonal->start.y;
    float step = 0;
    unsigned int counter = 0;

    diagonal->pool = malloc(sizeof(point_t) * 1);
    diagonal->pool[0] = (point_t) { .x = -1, .y = -1 };

    if (dx == 0) {
        step = (float) copysign(1, dy);
        for (int i = 0; i != dy; i += (int) step);
        // TODO: return the pt_pool
        return true;
    }
    m = (float)dy / ((float)dx);
    b = (float)(diagonal->start.y) - m * (float)(diagonal->start.x);
    step = 1.0f / ((float)fmax(abs(dx), abs(dy)));

    float tmp = (float)(diagonal->finish.x + 1) / step;
    tmp++;
    float x = ((float)diagonal->start.x + 1.0f) / step;
    steps = (float*) malloc(sizeof(float) * fabsf(fabsf(x) - fabsf(tmp)) + 2); // last is -1.0
    for (unsigned int i = 0; round((double)x) != round((double)tmp); x = x + copysign(1, dx)) {
        steps[counter] = x * step;
        float y = (m * steps[counter] + b);
        if (counter > 0) {
            tmp_pt[1].x = tmp_pt[0].x;
            tmp_pt[1].y = tmp_pt[0].y;
			tmp_pt[0].x = (int)floor(steps[counter]);
			tmp_pt[0].y = (int)floor(y);
            if (tmp_pt[0].x != tmp_pt[1].x) {
                diagonal->pool = realloc(diagonal->pool, sizeof(point_t) * (i  + 1));
                if (!diagonal->pool)
                    return false;
                diagonal->pool[i++] = tmp_pt[0];
                diagonal->size = i;
				if (diagonal->pool[i - 1].x == finish.x && diagonal->pool[i - 1].y == finish.y) {
					return true;
				}
            }
            else if (tmp_pt[0].y != tmp_pt[1].y) {
                diagonal->pool = realloc(diagonal->pool, sizeof(point_t) * (i  + 1));
                if (!diagonal->pool)
                    return false;
                diagonal->pool[i++] = tmp_pt[0];
                diagonal->size = i;
				if (diagonal->pool[i - 1].x == finish.x && diagonal->pool[i - 1].y == finish.y) {
					return true;
				}
            }
        } else {
            tmp_pt[0].x = (int)round(steps[counter]);
            tmp_pt[0].y = (int)round(y);
            diagonal->pool = realloc(diagonal->pool, sizeof(point_t) * (i  + 1));
            if (!diagonal->pool)
                return false;
            diagonal->pool[i++] = tmp_pt[0];
            diagonal->size = i;
        }
        counter++;
    }
    return true;
}

point_t get_first_obst(line_t* diagonal, point_t start, point_t finish, room_t *room)
{
	int sign_x = (start.x < finish.x) ? 1 : -1;
	int sign_y = (start.y < finish.y) ? 1 : -1;
	unsigned int width = room->width;
	unsigned int height = room->height;

	for (unsigned int i = 0, x, y; i < diagonal->size; i++) {
		x = diagonal->pool[i].x;
		y = diagonal->pool[i].y;
		if (room->room[diagonal->pool[i].y][diagonal->pool[i].x] == OBST) {
			return (point_t) { .x = diagonal->pool[i].x, .y = diagonal->pool[i].y };
		}
		else if (diagonal->pool[i].x > 0 && diagonal->pool[i].y > 0) {
			if (sign_x == 1) {
				if (sign_y == 1) {
					if (x < width && y < height) {
						if (room->room[y + 1][x] == OBST && room->room[y][x + 1] == OBST) {
							return (point_t) { .x = x, .y = y };
						}
					}
				}
				else {
					if (x < width && y > 0) {
						if (room->room[y - 1][x] == OBST && room->room[y][x + 1] == OBST) {
							return (point_t) { .x = x, .y = y };
						}
					}
				}
			}
			else {
				if (sign_y == 1) {
					if (x > 0 && y < height) {
						if (room->room[y + 1][x] == OBST && room->room[y][x - 1] == OBST) {
							return (point_t) { .x = x, .y = y };
						}
					}
				}
				else {
					if (x > 0 && y > 0) {
						if (room->room[y - 1][x] == OBST && room->room[y][x - 1] == OBST) {
							return (point_t) { .x = x, .y = y };
						}
					}
				}
			}
		}
	}
	return (point_t) { .x = -1, .y = -1 };
}

bool set_diag(line_t *diagonal, point_t obst, room_t *room)
{
    short sign_x = (short)copysign(1.0f, (double)diagonal->finish.x - diagonal->start.x);
    short sign_y = (short)copysign(1.0f, (double)diagonal->finish.y - diagonal->start.y);
    point_t tmp[2];

    // new diagonal ALWAYS goes in the contrary sense of ONE of the current sign. ex:
    // sign_x == -1 && sign_y == -1 THEN new_diag_sign_x == 1 && new_diag_sign_y == -1 (or == -1 && == 1)
    printf("%d\n", sign_x);
    printf("%d\n", sign_y);
    diagonal->start = obst;
    if (sign_x != sign_y) {
        tmp[0].x = 0;
        tmp[1].y = room->width - 1;
    } else {
        tmp[0].y = room->height - 1;
        tmp[1].x = 0;
    }

    printf("current x = %d\n", diagonal->start.x);
    for (int x = diagonal->start.x; x != tmp[0].x; x += (-1 * sign_x)) {
        printf("%d\n", x);
    }
    return true;
}