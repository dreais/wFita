//
// Created by Valentin on 10/6/2019.
//

#ifndef MAPGENERATION_CHARACTER_H
#define MAPGENERATION_CHARACTER_H

#include "room.h"
#include "shape.h"

typedef struct {
    unsigned int level;
    unsigned int experience;
    int health;
} stat_t;

typedef struct {
    stat_t stat;
    point_t p_cursor;
} charac_t;

/// MOVEMENT.C
point_t verify_player_position(const point_t p_cursor, const room_t room);
void input_treat(const int key, point_t *p_cursor);

// PLAYER.C

charac_t initialize_player(void);

#endif //MAPGENERATION_CHARACTER_H
