//
// Created by Valentin on 3/19/2021.
//

#include "raylib.h"
#include "core_game.h"
#include "print.h"

// FOR TESTING PURPOSE
#include <stdio.h>
#include <conio.h>
#include <unistd.h>

static int zoom_value = 18;
static unsigned int TARGET_FPS = 10;

int game_loop(core_game_t *core)
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground((Color) {.r = 34, .g = 35, .b = 35, .a = 255});

        input_treat(core);
        if (IsKeyDown(KEY_KP_ADD)) {
            zoom_value += 2;
        } else if (IsKeyDown(KEY_KP_SUBTRACT)) {
            zoom_value = (zoom_value <= 2) ? 2 : zoom_value - 2;
        }

        display_textures(core, zoom_value);
        EndDrawing();

    }
    return 0;
}