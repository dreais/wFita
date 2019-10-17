//
// Created by Valentin on 10/4/2019.
//
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../Header/core_game.h"

static WINDOW *initialize_terminal(void)
{
	WINDOW *main_game;

	initscr();
	init_colors();
	noecho();
	cbreak();
	curs_set(0);
	main_game = newwin(LINES / 2 + (LINES / 3), ((COLS / 2) + ((COLS / 2) / 2))-2, 0, 0);
	curs_set(0);
	keypad(main_game, TRUE);
	return main_game;
}

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

void init_core_game(core_game_t *core)
{
	core->game_screen = initialize_terminal();
	core->floors = malloc(sizeof(floor_t) * MAX_FLOOR);
	core->floors[0].c_room = initialize_room(300, 300);
	core->player = initialize_player();
	core->camera = malloc(sizeof(point_t)*1);
	core->camera->x = 0;
	core->camera->y = 0;

	core->logs.logs = newwin(LINES - getmaxy(core->game_screen), COLS,
							 getmaxy(core->game_screen), 0);
	core->logs.buffer_size = (unsigned int) getmaxy(core->logs.logs);
	core->logs.index = 0;
	core->logs.buffer = malloc(sizeof(char *) * core->logs.buffer_size);
	// WINDOWS TYPE
	for (u_int i = 0; i < core->logs.buffer_size; i++) {
		core->logs.buffer[i] = malloc(sizeof(char) * getmaxx(core->logs.logs) - 1);
	}
	core->logs.buffer[0] = WELCOME;
	core->floors[0].stairs.repr =  181;
	core->floors[0].stairs.cursor.x = 50;
	core->floors[0].stairs.cursor.y = 50;
	core->current_stage = 0;
}