//
// Created by Valentin on 10/6/2019.
//

#ifdef _WIN32
#include "../Header/curses.h"
#else
#include <ncurses.h>
#endif

#include <stdlib.h>
#include <time.h>
#include "../Header/room.h"
#include "../Header/character.h"
#include "../Header/print.h"

charac_t *monster;
static bool was_initialized = false;

extern WINDOW *debug;

static void create_monster_ptr(const room_t room, charac_t *player)
{
    srand(time(NULL));
    monster = malloc(sizeof(charac_t) * 10);
    for (int i = 0; i < 10; i++) {
        monster[i].stat = (stat_t) {.experience = -1, .level = 1, .health = 10};
        monster[i].p_cursor.x = rand() % room.width;
        monster[i].p_cursor.y = rand() % room.height;
        if (monster[i].p_cursor.x == player->p_cursor.x)
            monster[i].p_cursor.x = rand() % room.width;
        if (monster[i].p_cursor.y == player->p_cursor.y)
            monster[i].p_cursor.y = rand() % room.height;
        monster[i].repr = 'M';
    }
    was_initialized = true;
}

static bool cell_occupied(const int arr_size, const int current)
{
    for (int i = 0; i < arr_size; i++) {
        if (i != current) {
            if (monster[i].p_cursor.x == monster[current].p_cursor.x &&
            monster[i].p_cursor.y == monster[current].p_cursor.y) {
                return true;
            }
        }
    }
    return false;
}

static void update_path_monster(const int arr_size, charac_t *player, room_t room)
{
    point_t old_tmp;

    for (int i = 0; i < arr_size; i++) {
        old_tmp = monster[i].p_cursor;
        monster[i].p_cursor = search_next_cell(monster[i].p_cursor, player->p_cursor, room);
        if (cell_occupied(arr_size, i) == true) {
            monster[i].p_cursor = old_tmp;
        }
    }
}

void main_loop(WINDOW *win, const room_t room, charac_t *player, const int key, point_t *camera)
{
    if (was_initialized == false)
        create_monster_ptr(room, player);

    input_treat(key, &player->p_cursor);
    player->p_cursor = verify_player_position(player->p_cursor, room);
    print_room(room, win, player->p_cursor, camera);
    update_path_monster(10, player, room);
    move_monster(monster, 10, win, camera);
}