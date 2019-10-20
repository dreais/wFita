//
// Created by Valentin on 10/19/2019.
//

#include <stdlib.h>
#include "../Header/core_game.h"

void destroy_room(room_t *room)
{
	for (unsigned int i = 0; i < room->height; i++) {
		free(room->room[i]);
	}
	free(room->room);
}