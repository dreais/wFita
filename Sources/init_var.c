//
// Created by Valentin on 10/4/2019.
//
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../Header/core_game.h"

__attribute__((unused)) static WINDOW *initialize_terminal(void)
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
    room_t main_r;
    int noise;

    define_hash(width);
	main_r.width = width;
	main_r.height = height;
	main_r.room = malloc(sizeof(char *) * main_r.height);
    for (unsigned int i = 0; i < main_r.height; i++) {
		main_r.room[i] = malloc(sizeof(char) * main_r.width);
        for (unsigned int j = 0; j < main_r.width; j++) {
            noise = (int)(10.0f * perlin2d(i, j, 0.1f, 4));
			main_r.room[i][j] = '0' + noise;
        }
    }
    return main_r;
}

void init_core_game(core_game_t *core)
{
#ifndef SNOW_ENABLED
	core->game_screen = initialize_terminal();

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
#endif
	core->floors = malloc(sizeof(floor_t) * MAX_FLOOR);
	core->floors[0].c_room = initialize_room(300, 300);
	core->player = initialize_player();
	core->camera = malloc(sizeof(point_t)*1);
	core->camera->x = 0;
	core->camera->y = 0;
	core->floors[0].stairs.repr =  181;
	core->floors[0].stairs.cursor.x = 50;
	core->floors[0].stairs.cursor.y = 50;
	core->current_stage = 0;
}

#include "../Header/snow/snow.h"

describe(room) {
	room_t room;

	room = initialize_room(50, 70);

	subdesc(room_init) {

		it("initialize 1 room with given width/height") {
			asserteq_int(room.height, 70);
			asserteq_int(room.width, 50);
		}

		it("allocated 1 array properly") {

		}
	}

	after_each() {
		for (unsigned int i = 0; i < room.height; i++) {
			free(room.room[i]);
		}
		free(room.room);
	}
}

describe(player) {
	charac_t player = initialize_player();

	it("has charac properly set") {
		asserteq_int(player.stat.level, 1);
	}
}

describe(core_game) {
	core_game_t core;

	init_core_game(&core);

	subdesc(pointer_set) {
		it("has pointers to all its elements") {
			assert(core.floors, "Doesn't have a floor pointer");
			assert(!core.monster_arr, "Doesn't have a monster array pointer");
			assert(core.camera, "Doesn't have a camera pointer");
		}
	}

	subdesc(floor_type) {

		it("is allocated of MAX_FLOOR size") {
			assert(core.floors, "It is not allocated");
		}

		it("created a room and has values") {
			unsigned int width, height;

			width = core.floors[0].c_room.width;
			height = core.floors[0].c_room.height;
			assert(core.floors[0].c_room.room, "floors[0].c_room.room is not allocated");
			assert(core.floors[0].c_room.room[0], "The first line of the room is not allocated");
			assert(core.floors[0].c_room.room[height - 1], "The last line of the room is not allocated");
			assert(core.floors[0].c_room.room[height - 1][width - 1], "The last cell of the room is empty");
		}
	}

	subdesc(camera) {
		it("is allocated") {
			assert(core.camera, "Camera is not allocated");
		}
	}
}