//
// Created by Valentin on 10/6/2019.
//

#ifdef _WIN32
#include "../../Header/curses.h"
#else
#include <ncurses.h>
#endif

#include "../../Header/character.h"
#include "../../Header/contourn.h"

void move_monster(charac_t *monster, const int arr_size, WINDOW *win)
{
    for (int i = 0; i < arr_size; i++) {
        monster[i].p_cursor = monster[i].path.path.pool[monster[i].path.index];
        wmove(win, monster[i].p_cursor.y, monster[i].p_cursor.x);
        waddch(win, monster[i].repr);
        free_path(monster[i].path);
    }
}