//
// Created by Valentin on 3/19/2021.
//

#include "raylib.h"
#include "core_game.h"
#include "print.h"

#include <stdio.h>

static void print_tile(char repr, Vector2 cursor, core_game_t *core, int zoom_value)
{
    Color transp = WHITE;
    Rectangle frame = (Rectangle) {.width = 8.0f, .height = 8.0f};
    Rectangle stretch = (Rectangle) {.width = zoom_value, .height = zoom_value};
    Texture2D to_use;

    if (repr == '~') {
        frame.x = 13.0f + (8.0f * 13.0f);
        frame.y = 10.0f + (8.0f * 10.0f);
        to_use = core->tilemap_color;
    } else if (repr == '.') {
        frame.width = 0.0f;
        frame.height = 0.0f;
        to_use = core->tilemap_color;
    } else if (repr == ',') {
        frame.x = 5.0f + (8.0f * 5.0f);
        frame.y = 4.0f + (8.0f * 4.0f);
        to_use = core->tilemap_color;
    } else if (repr == ';') {
        frame.x = 4.0f + (8.0f * 4.0f);
        frame.y = 4.0f + (8.0f * 4.0f);
        to_use = core->tilemap_color;
    } else {
        frame.x = 4.0f + (8.0f * 4.0f);
        frame.y = 4.0f + (8.0f * 4.0f);
        to_use = core->tilemap_mono;
    }
    stretch.x = cursor.x;
    stretch.y = cursor.y;
    DrawTexturePro(to_use, frame, stretch, (Vector2) {0.0f, 0.0f},0, transp);
}

static point_t correct_camera(int max_w, int max_h, point_t pos_player, point_t camera)
{
    point_t return_value = {0};

    if (pos_player.x < max_w / 2) {
        return_value.x = 0;
    } else if (pos_player.x > ROOM_MAX_WIDTH - (max_w / 2)) {
        return_value.x = camera.x;
    } else {
        return_value.x = pos_player.x - max_w / 2;
    }

    if (pos_player.y < max_h / 2) {
        return_value.y = 0;
    } else if (pos_player.y > ROOM_MAX_HEIGHT - (max_h / 2)) {
        return_value.y = camera.y;
    } else {
        return_value.y = pos_player.y - max_h / 2;
    }

    if (return_value.y + max_h >= ROOM_MAX_HEIGHT) {
        return_value.y--;
    }
    return return_value;
}

void display_textures(core_game_t *core, int zoom)
{
    unsigned int screen_h = (GetScreenHeight() / zoom >= ROOM_MAX_HEIGHT) ? ROOM_MAX_HEIGHT : GetScreenHeight() / zoom;
    unsigned int screen_w = (GetScreenWidth() / zoom >= ROOM_MAX_WIDTH) ? ROOM_MAX_WIDTH : GetScreenWidth() / zoom;

    screen_h = ((screen_h % 2) == 0) ? screen_h - 1 : screen_h;
    screen_w = ((screen_w % 2) == 0) ? screen_w - 1 : screen_w;
    core->camera = correct_camera(screen_w, screen_h, core->player.pos, core->camera);
    for (unsigned int i = 0 ; i < screen_h; i++) {
        char *line_tmp = core->floors[core->current_stage].c_room.room[i + core->camera.y];

        for (unsigned int j = 0 ; j < screen_w; j++) {
            char repr_tmp = line_tmp[j + core->camera.x];
            Vector2 draw_cursor = (Vector2) {.x = j * zoom, .y = i * zoom};

            print_tile(repr_tmp, draw_cursor, core, zoom);
        }
    }
    print_player(core, zoom, screen_h, screen_w);
    fprintf(stderr, "x:%d\ty:%d\n", core->player.pos.x, core->player.pos.y);
}
