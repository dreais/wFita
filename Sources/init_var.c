//
// Created by Valentin on 10/4/2019.
//
#include <stdlib.h>
#include "../Header/room.h"

room_t initialize_room(const int width, const int height) {
    room_t main;
    int noise;

    define_hash(width);
    main.width = width;
    main.height = height;
    main.room = malloc(sizeof(char *) * main.height);
    for (unsigned int i = 0; i < main.height; i++) {
        main.room[i] = malloc(sizeof(char) * main.width);
        for (unsigned int j = 0; j < main.width; j++) {
            noise = (int)(10.0f * perlin2d(i, j, 0.1f, 4));
            main.room[i][j] = '0' + noise;
        }
    }
    return main;
}