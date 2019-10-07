//
// Created by Valentin on 10/6/2019.
//

#include "../../Header/core_game.h"

// may be non-static later on
static stat_t initialize_stats(void)
{
    stat_t new = {.experience = 0, .level = 1, .health = 10};

    return new;
}

charac_t initialize_player(void)
{
    charac_t p_new = {.p_cursor = {.x = 0, .y = 0}, .stat = initialize_stats()};

    return p_new;
}