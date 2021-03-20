//
// Created by Valentin on 3/18/2021.
//

#ifndef WFITA_REMASTER_INIT_H
#define WFITA_REMASTER_INIT_H

room_t recreate_room(room_t to_rebuild);
room_t initialize_room(const int width, const int height);
void init_core_game(core_game_t *core);

#endif //WFITA_REMASTER_INIT_H
