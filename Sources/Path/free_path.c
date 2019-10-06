//
// Created by Valentin on 10/6/2019.
//

#include <stdlib.h>
#include "../../Header/contourn.h"


void free_path(path_t path)
{
    free(path.path.pool);
}