//
// Created by Valentin on 10/6/2019.
//

#ifdef _WIN32
#include "../../Header/curses.h"
#else
#include <ncurses.h>
#endif

#include "../../Header/shape.h"

point_t verify_player_position(const point_t p_cursor, const room_t room)
{
    point_t new_pos = {.x = p_cursor.x, .y = p_cursor.y};

    if (new_pos.x < 0)
        new_pos.x = 0;
    else if (new_pos.x > room.width - 1)
        new_pos.x = (int) room.width - 1;
    if (new_pos.y < 0)
        new_pos.y = 0;
    else if (new_pos.y > room.height - 1)
        new_pos.y = (int) room.height - 1;
    return new_pos;
}

void input_treat(const int key, point_t *p_cursor)
{
    switch (key) {
        case KEY_LEFT:
            p_cursor->x--;
            break;
        case KEY_RIGHT:
            p_cursor->x++;
            break;
        case KEY_UP:
            p_cursor->y--;
            break;
        case KEY_DOWN:
            p_cursor->y++;
            break;
        default:
            break;
    }
}