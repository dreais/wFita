//
// Created by Valentin on 3/20/2021.
//

#include "raylib.h"
#include "core_game.h"

static Rectangle player_frame = (Rectangle) {36.0f, 0.0f, 8.0f, 8.0f};
static Rectangle player_stretch = {0};
static Vector2 origin = {0};

void print_player(core_game_t *core, int zoom, unsigned int screen_h, unsigned int screen_w)
{
    player_stretch = (Rectangle) {player_stretch.x, player_stretch.y, zoom, zoom};
    point_t pos_temp = core->player.pos;
    int x_right_boundary = ROOM_MAX_WIDTH - (screen_w / 2) + 1;
    int y_right_boundary = ROOM_MAX_HEIGHT - (screen_h / 2) + 1;

    if (pos_temp.x >= 0 && pos_temp.x < (screen_w / 2) + 1) {
        player_stretch.x = (float) (core->player.pos.x * zoom);
    } else if (pos_temp.x >= x_right_boundary && pos_temp.x <= ROOM_MAX_WIDTH) {
        player_stretch.x = (float) (((core->player.pos.x - ROOM_MAX_WIDTH) + screen_w) * zoom);
    }
    if ((pos_temp.y >= 0 && pos_temp.y < (screen_h / 2) + 1)) {
        player_stretch.y = (float) core->player.pos.y * zoom;
    } else if (pos_temp.y >= y_right_boundary && pos_temp.y <= ROOM_MAX_HEIGHT) {
        player_stretch.y = (float) (((core->player.pos.y - ROOM_MAX_HEIGHT) + screen_h) * zoom);
    }
    DrawTexturePro(core->tilemap_color, player_frame, player_stretch, origin, 0, WHITE);
}
