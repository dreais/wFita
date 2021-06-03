#include "raylib.h"
#include "core_game.h"
#include "init.h"

int main(void)
{
    core_game_t core;
    const int screenWidth = 1600;
    const int screenHeight = 900;

    init_core_game(&core);
    InitWindow(screenWidth, screenHeight, "Fed in the Abyss");
    core.tilemap_color = LoadTexture("Resources/colored_tilemap.png");
    core.tilemap_mono = LoadTexture("Resources/monochrome_tilemap.png");
    core.font = LoadFont("Resources/VT323-Regular.ttf");
    SetTargetFPS(10);
    game_loop(&core);
    CloseWindow();
    return 0;
}
