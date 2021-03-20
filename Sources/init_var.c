//
// Created by Valentin on 3/18/2021.
//

#include <stdlib.h>
#include "core_game.h"
#include "noise.h"

room_t recreate_room(room_t to_rebuild)
{
    room_t main_r;
    int noise;

    define_hash((int)to_rebuild.width, to_rebuild.seed);
    main_r.width = to_rebuild.width;
    main_r.height = to_rebuild.height;
    main_r.room = malloc(sizeof(char *) * main_r.height);
    for (unsigned int i = 0; i < main_r.height; i++) {
        main_r.room[i] = malloc(sizeof(char) * main_r.width);
        for (unsigned int j = 0; j < main_r.width; j++) {
            noise = (int)(10.0f * perlin2d(i, j, 0.1f, 4));
            main_r.room[i][j] = '0' + noise;
        }
    }
    to_rebuild.room = main_r.room;
    return to_rebuild;
}

room_t initialize_room(const int width, const int height) {
    room_t main_r;
    int noise;

    main_r.seed = time(NULL);
    define_hash(width, main_r.seed);
    main_r.width = width;
    main_r.height = height;
    main_r.room = malloc(sizeof(char *) * main_r.height);
    for (unsigned int i = 0; i < main_r.height; i++) {
        main_r.room[i] = malloc(sizeof(char) * main_r.width);
        for (unsigned int j = 0; j < main_r.width; j++) {
            noise = (int)(10.0f * perlin2d(i, j, 0.1f, 4)) * 10;

            if (noise > 0 && noise < 15) {
                main_r.room[i][j] = '~';
            } if (noise >= 15 && noise < 30) {
                main_r.room[i][j] = '.';
            } else if (noise >= 30 && noise < 50) {
                main_r.room[i][j] = ',';
            } else if (noise >= 50 && noise < 70) {
                main_r.room[i][j] = ';';
            } else {
                main_r.room[i][j] = '%';
            }
        }
    }
    return main_r;
}

void init_core_game(core_game_t *core)
{
    core->floors = malloc(sizeof(floor_t) * MAX_FLOOR);
    core->floors[0].c_room = initialize_room(ROOM_MAX_WIDTH, ROOM_MAX_HEIGHT);
    core->camera.x = 0;
    core->camera.y = 0;
    core->floors[0].stairs.repr =  181;
    core->floors[0].stairs.cursor.x = 50;
    core->floors[0].stairs.cursor.y = 50;
    core->current_stage = 0;
    core->player.pos = (point_t) {0, 0};
}