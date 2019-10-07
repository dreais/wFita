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

static bool was_initialized = false;

/// DEBUG WINDOW. MIGHT GET REPLACED BY THE PARENT WINDOW LATER ON
extern WINDOW *debug;

static void create_monster_ptr(core_game_t *core)
{
    srand(time(NULL));
    core->monster_arr = malloc(sizeof(charac_t) * core->size_monster_arr);
    for (int i = 0; i < core->size_monster_arr; i++) {
        core->monster_arr[i].stat = (stat_t) {.experience = -1, .level = 1, .health = 10};
        core->monster_arr[i].p_cursor.x = rand() % core->c_room.width;
        core->monster_arr[i].p_cursor.y = rand() % core->c_room.height;
        if (core->monster_arr[i].p_cursor.x == core->player.p_cursor.x)
            core->monster_arr[i].p_cursor.x = rand() % core->c_room.width;
        if (core->monster_arr[i].p_cursor.y == core->player.p_cursor.y)
            core->monster_arr[i].p_cursor.y = rand() % core->c_room.height;
        core->monster_arr[i].repr = 'M';
        core->monster_arr[i].stat.state = alive;
    }
    was_initialized = true;
}

static bool cell_occupied(core_game_t *core, const int index, const point_t current)
{
    /// KEY IS ONLY USED WHEN A MONSTER IS BEING CHECKED. OTHERWISE, USE KEY > ARR_SIZE
    for (unsigned int i = 0; i < core->size_monster_arr; i++) {
        if (i != index) {
            if (core->monster_arr[i].p_cursor.x == current.x &&
            core->monster_arr[i].p_cursor.y == current.y) {
                return true;
            }
        }
    }
    return false;
}

static bool point_equals(point_t first, point_t second)
{
    if (first.x == second.x && first.y == second.y) {
        return true;
    }
    return false;
}

static void update_path_monster(core_game_t *core)
{
    point_t old_tmp;

    for (unsigned int i = 0; i < core->size_monster_arr; i++) {
        if (core->monster_arr[i].stat.state == true) {
            old_tmp = core->monster_arr[i].p_cursor;
            core->monster_arr[i].p_cursor = search_next_cell(core->monster_arr[i].p_cursor, core->player.p_cursor,
                                                             core->c_room);
            if (point_equals(core->monster_arr[i].p_cursor, core->player.p_cursor)) {
                core->monster_arr[i].p_cursor = old_tmp;
                set_attack(&core->monster_arr[i], &core->player);
            }
            if (cell_occupied(core, (int) i, core->monster_arr[i].p_cursor) == true) {
                core->monster_arr[i].p_cursor = old_tmp;
            }
        }
    }
}

void main_loop(core_game_t *core, const int key)
{
    point_t old_p_cursor;

    if (was_initialized == false) {
        core->size_monster_arr = 10;
        create_monster_ptr(core);
    }
    old_p_cursor = core->player.p_cursor;
    input_treat(key, &core->player.p_cursor);
    core->player.p_cursor = verify_player_position(core->player.p_cursor, core->c_room);
    if (cell_occupied(core, core->size_monster_arr, core->player.p_cursor) == true) {
        core->player.p_cursor = old_p_cursor;
    }
    print_room(core);
    update_path_monster(core);
    move_monster(core);
    print_stats(core->game_screen, core->player);
}