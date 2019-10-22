//
// Created by Valentin on 10/6/2019.
//

#ifndef MAPGENERATION_CORE_GAME_H
#define MAPGENERATION_CORE_GAME_H

#pragma once

#include <time.h>
#ifdef _WIN32
#include "curses.h"
#else
#include <ncurses.h>
#endif

/// ENUM TYPEDEFs
typedef enum {TOP, RIGHT, BOTTOM, LEFT} dir_name;

/**
 * @struct point_t
 * @brief Struct containing a coordinate with x and y axis
 */
typedef struct {
    int x;
    int y;
} point_t;

/**
 * @struct line_t
 * @brief DEPRECATED. PLEASE DO NOT USE FOR NOW
 */
typedef struct {
    unsigned int size;
    point_t start;
    point_t finish;
    point_t *pool;
    int dx, dy;
} line_t;

/// CHARACTER TYPES
/**
 * @struct stat_t
 * @brief Struct containing multiple stats
 * @details This structure can be used to store stats of a given character, be it the player, a NPC or an enemy.
 * If the experience variable is set for an enemy, when a player kill it, this'll be the amount given by the kill.
 */
typedef struct {
    unsigned int level; /// an unsigned integer with the level. Calculated based on the experience
    unsigned int experience; /// an unsigned integer containing the XP to be shown on the STAT WINDOW
    int health; /// player's/enemies' health at any point
    int max_health; /// player's/enemies' maximum health
    bool state; /// value is either "dead" or "alive"
} stat_t;

typedef unsigned long long w_UID;
typedef enum {LEFT_HAND, RIGHT_HAND, LEFT_RIGHT_HAND} wSlot_ID;
/**
 * @struct weapon_t
 * @brief Struct containing informations about a weapon. This is merely to create weapon with damage, def, etc
 */
typedef struct {
    wSlot_ID slot; /// left/right hand or both. This variable is to determine which slot.
    w_UID piv_key; /// the unique identifier of the weapon
    char *name; /// name of the weapon. snake_case with a piv_key, as example_example_001
    short dmg; /// damage the weapon deal. if this is a defensive piece of equipment, will be null or -1
    short def; /// defense of a defensive equipment. will be null or -1 if it's a weapon
    float crit; /// the critical rate the weapon/defensive equipment will have. the higher, the better chance you'll get of a critick!
} weapon_t;

typedef enum {WEAPON, ARMOR, SPELL} eType; // equipment type
/**
 * @struct equipment_t
 * @brief Struct containing IDs and type of a precise equipment
 */
typedef struct {
    w_UID piv_key;
    wSlot_ID slot;
    eType eType;
} equipment_t;

typedef struct {
    equipment_t *equipment;
    unsigned short gold;
} inventory_t;

/**
 * \struct charac_t
 * \brief Structure representing a character (player, NPC, enemy)
 * @var is_weapon_dual_hand
 * true if the character uses a dual weapon hand
 * @var left_hand
 * weapon_t being the left hand. note that if is_weapon_dual_hand true, left_hand == right_hand
 * @var right_hand
 * weapon_t being the right hand.
 * @var stat
 * stat_t containing a character's stats. enemies' XP will be the XP they're giving away when dying
 * @var p_cursor
 * position of a character contained as a point_t type
 * @var repr
 * representation of the character on the map
 */
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
/**
 * @struct room_t
 * @brief Struct containing some information about a specific room (the map itself), not a floor.
 */
typedef struct {
	time_t seed;
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
    char** room;
} room_t;

/**
 * @struct g_logs
 * @brief Struct containing the log WINDOW and its parameters
 */
typedef struct {
    unsigned int index;
    unsigned int buffer_size;
    char **buffer; // buffer[buffer_size]
    WINDOW *logs;
} g_logs;

/**
 * @struct stairs_t
 * @brief Struct containing the position and the character's representation of a stair (for a given floor)
 */
typedef struct {
    point_t cursor;
    char repr;
} stairs_t;

/**
 * @struct floor_t
 * @brief Struct containing the stair information, and the room_t variable.
 */
typedef struct {
    stairs_t stairs;
    room_t c_room; // current
} floor_t;

/**
 * @struct core_game_t
 * @brief Most important type - it contains every major information of the game
 */
typedef struct {
    floor_t *floors;
    unsigned short current_stage;
    charac_t player;
    point_t *camera;
    charac_t *monster_arr;
    unsigned int size_monster_arr;
    WINDOW *game_screen;
    WINDOW *stat_screen;
    g_logs logs;
} core_game_t;

/**
 * @struct key_func
 * @brief Struct used to link a key to a specific function
 */
typedef struct {
    int key;
    void (*func)(core_game_t *);
} key_func;

/**
 * COLORS DEFINITION
 * first define is the COLOR_PAIR key
 * second define is the index from the converted table (see "Sources" in the README)
 */
#define BLANK 0
#define GREEN 1
#define YELLOW 2
#define WHITE 3
#define DARK_GREEN 4
#define LIGHT_GREEN 5
#define GREY 6
#define BROWN 7
#define RED 8

#define RED_BG 9
#define GREY_BG 10

#define COLOR_DARK_GREEN 22
#define COLOR_LIGHT_GREEN 119
#define COLOR_BROWN 215
#define COLOR_GREY 253
/// -------- END OF COLORS DEFINITION --------

#define alive true
#define dead false

#define MAX_FLOOR 100

#define YOU_DIED "You died. Press any key to exit!"
#define EXIT_MSG "You pressed 'q'. Press 'q' again to quit, or any other key to cancel."

#define KEY_SPACE ' '

#define PREFIX_DEBUG "[DEBUG] "
#define PREFIX_INFO "[INFO] "
#define PREFIX_WARNING "[WARNING] "

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

/// -------- EXTERN VAR --------
/// ----------------------------

/// -------- LOGS MSG --------
#define WELCOME "Welcome aboard, adventurer."
#define GOT_ATTACKED "You took a hit - it dealt %d damages."
#define BLOCKED "You blocked the attack to %d."
/// --------------------------

void destroy_room(room_t *room);
void close_file(void);
void output_logs_str(const char prefix[], const char str[], ...);
void get_log_file(void);
void init_core_game(core_game_t *core);
void main_loop(core_game_t *core, int key);

#endif //MAPGENERATION_CORE_GAME_H