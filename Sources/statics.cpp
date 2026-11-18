#include "defines.h"
#include "statics.h"
#include <math.h>

void GlobalStatics::initStatics(float fs)
{
	int i, n, m;
	float sine[SINE_SIZE];
	float para[SINE_SIZE];
	float tri[SINE_SIZE];
	constexpr int offs[9] = { -12, -5, 0, 12, 19, 24, 28, 31, 36 };

	if(sampleRate == fs)
		return;

	sampleRate = fs;

	for(i = 0; i < 61; i++)
	{
		for(n = 0; n < 9; n++)
		{
			int v = i + 12 + offs[n];
			while(v > 88)
				v -= 12;
			generators[i].offset[n] = v;
		}
	}

	for(i = 0; i < SINE_SIZE; i++)
	{
		sine[i] = sinf(2.0f * PI * (float)i / SINE_SIZEf);
		para[i] = (PI * PI / 3.0f);
	}

	int harms = truncate((fs * 0.49f) / 5273.6f);
	// Guard: fs < ~10762.45 Hz makes harms == 0 (no harmonic fits below
	// Nyquist). Skip the window-width computation to avoid 0-division;
	// the loop below never runs in that case, so behavior is unchanged.
	float tharm = harms > 0 ? (PI * 0.5f) / (float)harms : 0.0f;

	float sign = -1.f;
    for (n = 0; n < harms; n++)
    {
        float t;
        int harmonic = n + 1;
        t = cosf((float)n * tharm);
        t *= t;
        t /= (float)(harmonic * harmonic);
        t *= 4.f * sign;

        for (m = 0; m < SINE_SIZE; m++)
            para[m] += t * sine[(m * harmonic + (SINE_SIZE / 4)) & (SINE_SIZE - 1)];
        sign = -sign;
    }
	float max = 0.0f;

    for (i = 0; i < SINE_SIZE; i++)
    {
        if (fabs(para[i]) > max)
            max = fabs(para[i]);
    }

    max /= 2.f;

    for (i = 0; i < SINE_SIZE; i++)
    {
        para[i] /= max;
        para[i] -= 1.f;
    }

	max = 1.0f / 2.25f;
	for(i = 0; i < SINE_SIZE; i++)
		tri[i] = (para[i] - para[(i + (SINE_SIZE / 2)) & (SINE_SIZE - 1)]) * max;

	for(i = 0; i < 128; i++)
	{
		float mix1 = (float)i / 127.0f;
		float mix0 = 1.0f - mix1;
		float *ptr = sineTable + i * SINE_SIZE * 3;

		for(n = 0; n < SINE_SIZE; n++)
		{
			ptr[n + SINE_SIZE] = 
				ptr[n + 2 * SINE_SIZE] = 
				ptr[n] = sine[n] * mix0 + tri[n] * mix1;
		}
	}
}
