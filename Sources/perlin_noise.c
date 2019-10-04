#include <time.h>
#include <stdlib.h>

static int SEED = 0;

static int hash[255] = {};

void define_hash(void)
{
    srand(time(NULL));
    for (int i = 0; i < 255; i++)
        hash[i] = rand() % 255;
}

int noise2(int x, int y)
{
    int tmp = hash[(y + SEED) % 256];
    return hash[(tmp + x) % 256];
}

float lin_inter(float x, float y, float s)
{
    return x + s * (y-x);
}

float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3-2*s));
}

float noise2d(float x, float y)
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
    define_hash();
    float xa = x*freq;
    float ya = y*freq;
    float amp = 1.0f;
    float fin = 0;
    float div = 0.0f;

    int i;
    for(i=0; i<depth; i++)
    {
        div += 256 * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin/div;
}
