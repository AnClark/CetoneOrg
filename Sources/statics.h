#pragma once

typedef struct
{
	int offset[16];
} GENERATOR;

static constexpr int g_all_sizes[4] = {556, 441, 341, 225};
static constexpr int g_comb_sizes[8] = {1116, 1188, 1277, 1356, 1422, 1491, 1557, 1617};

extern float g_sine[SINE_SIZE * 3 * 128];
extern GENERATOR g_generators[61];

int irand();
void initStatics(float fs);

inline float spline(float t, float* ps)
{
    return (
		(((-t + 3.0f) * t - 3.0f) * t + 1.0f) * ps[0]
		+ (((3.0f * t - 6.0f) * t) * t + 4.0f) * ps[1]
		+ (((-3.0f * t + 3.0f) * t + 3.0f) * t + 1.0f) * ps[2]
		+ (t * t * t) * ps[3]
		) * (1.0f / 6.0f);
}
