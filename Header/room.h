//
// Created by valentin on 21/09/2019.
//

#ifndef MAPGENERATION_ROOM_H
#define MAPGENERATION_ROOM_H

#define FLOR '0'
#define OBST '1'
#define FINI '2'
#define STAR '3'

typedef struct {
    unsigned int x;
    unsigned int y;
	unsigned int width;
	unsigned int height;
	char** room;
} room_t;

room_t initialize_room(void);

#endif //MAPGENERATION_ROOM_H
