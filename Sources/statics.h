#pragma once

typedef struct
{
	int offset[16];
} GENERATOR;

static constexpr int g_all_sizes[4] = {556, 441, 341, 225};
static constexpr int g_comb_sizes[8] = {1116, 1188, 1277, 1356, 1422, 1491, 1557, 1617};

class GlobalStatics
{
public:
	float sineTable[SINE_SIZE * 3 * 128];
	GENERATOR generators[61];

	void initStatics(float fs);

private:
	float sampleRate { 0.0f };
};
