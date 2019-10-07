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
#include "../Header/core_game.h"

charac_t *monster;
static bool was_initialized = false;

/// DEBUG WINDOW. MIGHT GET REPLACED BY THE PARENT WINDOW LATER ON
extern WINDOW *debug;

static void create_monster_ptr(core_game_t *core)
{
    srand(time(NULL));
    core->monster_arr = malloc(sizeof(charac_t) * core->size_monster_arr);
    for (int i = 0; i < 10; i++) {
        core->monster_arr[i].stat = (stat_t) {.experience = -1, .level = 1, .health = 10};
        core->monster_arr[i].p_cursor.x = rand() % core->c_room.width;
        core->monster_arr[i].p_cursor.y = rand() % core->c_room.height;
        if (core->monster_arr[i].p_cursor.x == core->player.p_cursor.x)
            core->monster_arr[i].p_cursor.x = rand() % core->c_room.width;
        if (core->monster_arr[i].p_cursor.y == core->player.p_cursor.y)
            core->monster_arr[i].p_cursor.y = rand() % core->c_room.height;
        core->monster_arr[i].repr = 'M';
    }
    was_initialized = true;
}

static bool cell_occupied(const unsigned int arr_size, const unsigned int key, const point_t current)
{
    /// KEY IS ONLY USED WHEN A MONSTER IS BEING CHECKED. OTHERWISE, USE KEY > ARR_SIZE
    for (int i = 0; i < arr_size; i++) {
        if (i != key) {
            if (monster[i].p_cursor.x == current.x &&
            monster[i].p_cursor.y == current.y) {
                return true;
            }
            wmove(debug, i, 20);
            wprintw(debug, "monster[%d]:%d\t%d", i, monster[i].p_cursor.x, monster[i].p_cursor.y);
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
        if (cell_occupied(arr_size, i, monster[i].p_cursor) == true) {
            monster[i].p_cursor = old_tmp;
        }
    }
}

void main_loop(core_game_t *core, const int key)
{
    point_t old_p_cursor;

    if (was_initialized == false) {
        core->size_monster_arr = 10;
        create_monster_ptr(core);
        core->monster_arr = monster;
    }

    old_p_cursor = core->player.p_cursor;
    input_treat(key, &core->player.p_cursor);
    /// DEBUG
    wmove(debug, 0, 0);
    wprintw(debug, "%d\t%d\n%d\t%d\n", old_p_cursor.x, old_p_cursor.y, core->player.p_cursor.x, core->player.p_cursor.y);
    /// END DEBUG
    core->player.p_cursor = verify_player_position(core->player.p_cursor, core->c_room);
    if (cell_occupied(10, core->size_monster_arr, core->player.p_cursor) == true)
        core->player.p_cursor = old_p_cursor;
    print_room(core);
    update_path_monster(10, &core->player, core->c_room);
    move_monster(core);
    /// DEBUG
    wprintw(debug, "%d\t%d\n", core->player.p_cursor.x, core->player.p_cursor.y);
    wrefresh(debug);
    /// END DEBUG
}