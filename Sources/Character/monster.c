//
// Created by Valentin on 10/6/2019.
//

#ifdef _WIN32
#include "../../Header/curses.h"
#else
#include <ncurses.h>
#endif

#include "../../Header/character.h"
#include "../../Header/path.h"

void move_monster(charac_t *monster, const int arr_size, WINDOW *win, point_t *camera)
{
    for (int i = 0; i < arr_size; i++) {
        if (monster[i].p_cursor.x >= camera->x && monster[i].p_cursor.x <= camera->x + getmaxx(win)) {
            if (monster[i].p_cursor.y >= camera->y && monster[i].p_cursor.y <= camera->y + getmaxy(win)) {
                wmove(win, monster[i].p_cursor.y - camera->y, monster[i].p_cursor.x - camera->x);
                waddch(win, monster[i].repr);
            }
        }
    }
}