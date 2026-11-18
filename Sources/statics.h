#pragma once

#include "defines.h"

typedef struct _GENERATOR
{
	int offset[16] { 0 };
} GENERATOR;

class GlobalStatics
{
public:
	float sineTable[SINE_SIZE * 3 * 128] { 0.0f };
	GENERATOR generators[61];

	void initStatics(float fs);

private:
	float sampleRate { 0.0f };
};
