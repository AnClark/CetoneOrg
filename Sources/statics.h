#pragma once

#include "defines.h"

typedef struct
{
	int offset[16];
} GENERATOR;

class GlobalStatics
{
public:
	float sineTable[SINE_SIZE * 3 * 128];
	GENERATOR generators[61];

	void initStatics(float fs);

private:
	float sampleRate { 0.0f };
};
