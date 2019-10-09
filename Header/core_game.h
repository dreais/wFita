//
// Created by Valentin on 10/6/2019.
//

#ifndef MAPGENERATION_CORE_GAME_H
#define MAPGENERATION_CORE_GAME_H

#pragma once

#ifdef _WIN32
#include "curses.h"
#else
#include <ncurses.h>
#endif


/// ENUM TYPEDEFs
typedef enum {TOP, RIGHT, BOTTOM, LEFT} dir_name;


/// SHAPE TYPES
typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    unsigned int size;
    point_t start;
    point_t finish;
    point_t *pool;
    int dx, dy;
} line_t;

/// CHARACTER TYPES
typedef struct {
    unsigned int level;
    unsigned int experience;
    int health;
    int max_health;
    bool state;
} stat_t;

typedef unsigned long long w_UID;
typedef enum {LEFT_HAND, RIGHT_HAND, LEFT_RIGHT_HAND} wSlot_ID;
typedef struct {
    wSlot_ID slot; // weapon slot. self-explanatory
    w_UID piv_key; // unique identifier of the weapon
    char *name; // uses the piv_key previously defined to find in a pivot table the good weapon
    short dmg; // for dmg/def/crit, see Sources/Misc/Weapon/weapon_roll.c
    short def;
    float crit;
} weapon_t;

typedef enum {WEAPON, ARMOR, SPELL} eType; // equipment type
typedef struct {
    w_UID piv_key;
    wSlot_ID slot;
    eType eType;
} equipment_t;

typedef struct {
    equipment_t *equipment;
    unsigned short gold;
} inventory_t;

typedef struct {
    bool is_weapon_dual_hand;
    weapon_t left_hand;
    weapon_t right_hand;
    stat_t stat;
    point_t p_cursor;
    char repr;
    line_t path; // ONLY USED IF MONSTER
} charac_t;

/// ROOM TYPES
typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
    char** room;
} room_t;

/// CORE_GAME TYPES
typedef struct {
    unsigned int index;
    unsigned int buffer_size;
    char **buffer; // buffer[buffer_size]
    WINDOW *logs;
} g_logs;

typedef struct {
    point_t cursor;
    char repr;
} stairs_t;

typedef struct {
    stairs_t stairs;
    unsigned short current_stage;
    room_t c_room; // current
    charac_t player;
    point_t *camera;
    charac_t *monster_arr;
    unsigned int size_monster_arr;
    WINDOW *game_screen;
    WINDOW *stat_screen;
    g_logs logs;
} core_game_t;

typedef struct {
    int key;
    void (*func)(core_game_t *);
} key_func;

/**
 * COLORS DEFINITION
 * first define is the COLOR_PAIR key
 * second define is the index from the converted table (see "Sources" in the README)
 */
#define GREEN 1
#define YELLOW 2
#define WHITE 3
#define DARK_GREEN 4
#define LIGHT_GREEN 5
#define GREY 6
#define BROWN 7

#define COLOR_DARK_GREEN 22
#define COLOR_LIGHT_GREEN 119
#define COLOR_BROWN 215
#define COLOR_GREY 253
/// -------- END OF COLORS DEFINITION --------

#define alive true
#define dead false

#define YOU_DIED "You died. Press any key to exit!"
#define EXIT_MSG "You pressed 'q'. Press 'q' again to quit, or any other key to cancel."

/// -------- INCLUDES --------
#include "character.h"
#include "path.h"
#include "print.h"
#include "room.h"
#include "item_list.h"
#include "Keyboard/input.h"
/// --------------------------

/// -------- ITEM LIST --------
#define UID_MAX 4
const weapon_t piv_table[UID_MAX];
/// ---------------------------


/// -------- LOGS MSG --------
#define WELCOME "Welcome aboard, adventurer."
#define GOT_ATTACKED "You took a hit - it dealt %d damages."
#define BLOCKED "You blocked the attack to %d."
/// --------------------------

void main_loop(core_game_t *core, const int key);

#endif //MAPGENERATION_CORE_GAME_H