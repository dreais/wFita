#include <time.h>
#include <stdlib.h>

static int SEED = 0;
static int size_map = 0;

//size could be define using a define before
// TODO: get size using main args

// TODO: using char instead of int might make it lighter for the program if the map is very huge, as the table is contained in the cache.
static int *hash = NULL;

void define_hash(const int size, time_t seed)
{
    size_map = size;
	srand(seed);
    hash = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        hash[i] = rand() % size;
    }
}

void free_hash(void)
{
    free(hash);
}

static int noise2(int x, int y)
{
    int tmp = hash[(y + SEED) % 256];
    return hash[(tmp + x) % 256];
}

static float lin_inter(float x, float y, float s)
{
    return x + s * (y-x);
}

static float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3-2*s));
}

static float noise2d(float x, float y)
{
    int x_int = (int) x;
    int y_int = (int) y;
    float x_frac = x - (float) x_int;
    float y_frac = y - (float) y_int;
    int s = noise2(x_int, y_int);
    int t = noise2(x_int+1, y_int);
    int u = noise2(x_int, y_int+1);
    int v = noise2(x_int+1, y_int+1);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);

    return smooth_inter(low, high, y_frac);
}

float perlin2d(float x, float y, float freq, int depth)
{
    float xa = x*freq;
    float ya = y*freq;
    float amp = 1.0f;
    float fin = 0;
    float div = 0.0f;
    int i;

    for(i=0; i<depth; i++)
    {
        div += (float)size_map * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }
    return fin/div;
}
