//
// Created by Valentin on 3/18/2021.
//

#ifndef WFITA_REMASTER_NOISE_H
#define WFITA_REMASTER_NOISE_H

#include <time.h>

void define_hash(const int size, time_t seed);
void free_hash(void);
float perlin2d(float x, float y, float freq, int depth);

#endif //WFITA_REMASTER_NOISE_H
