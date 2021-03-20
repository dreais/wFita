//
// Created by Valentin on 3/18/2021.
//

#ifndef WFITA_REMASTER_CORE_GAME_H
#define WFITA_REMASTER_CORE_GAME_H

#include <time.h>
#include "raylib.h"

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    time_t seed;
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
    char** room;
} room_t;

typedef struct {
    point_t cursor;
    char repr;
} stairs_t;

typedef struct {
    stairs_t stairs;
    room_t c_room; // current
} floor_t;

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
    bool is_weapon_dual_hand;
    weapon_t left_hand;
    weapon_t right_hand;
    stat_t stat;
    point_t pos;
    char repr;
    line_t path; // ONLY USED IF MONSTER
} charac_t;

typedef struct {
    floor_t *floors;
    unsigned short current_stage;
    charac_t player;
    point_t camera;
//    charac_t *monster_arr;
    unsigned int size_monster_arr;
    Font font;
    Texture2D tilemap_color;
    Texture2D tilemap_mono;
    int zoom_value;
} core_game_t;

typedef struct {
    int key;
    void (*func)(core_game_t *);
} key_func;

#define MAX_FLOOR 100
#define ROOM_MAX_WIDTH 500
#define ROOM_MAX_HEIGHT 500

#define SIZE_KEY_ARRAY 4

int game_loop(core_game_t *core);
void input_treat(core_game_t *core);


#endif //WFITA_REMASTER_CORE_GAME_H
