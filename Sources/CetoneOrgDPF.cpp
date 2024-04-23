#include "CetoneOrg.h"

void CO::initParameter(uint32_t index, Parameter& parameter)
{
	parameter.hints |= kParameterIsAutomatable;

	// Fallback to classic VST 2.4 param range (0.0 ~ 1.0), to fit with Cetone's own param handlers.
	parameter.ranges.min = 0.0f;
	parameter.ranges.max = 1.0f;
	parameter.ranges.def = getParameter(index);

	// Must set parameter.symbol, this is the unique ID of each parameter.
	// If not set, you can neither save presets nor reset to factory default, in VST3 and CLAP!
	char buff[256];
	getParameterName(index, buff);
	parameter.symbol = String(buff).replace(' ', '_').replace('.', '_');
	parameter.name = String(buff);

#if 0
	switch (index) {
	case pPortaMode:

	case pOsc1Sync:
	case pOsc2Sync:
	case pOsc3Sync:

	case pOsc1Ring:
	case pOsc2Ring:
	case pOsc3Ring:

	case pLfo1Trig:
		parameter.hints |= kParameterIsBoolean;
		break;
	}
#endif
}

float CO::getParameterValue(uint32_t index) const
{
	return this->getParameter(index);
}

void CO::setParameterValue(uint32_t index, float value)
{
	this->setParameter(index, value);
}

void CO::activate()
{
	this->resume();
}

void CO::run(const float** inputs, float** outputs, uint32_t frames, const DISTRHO::MidiEvent* midiEvents, uint32_t midiEventCount)
{
	this->processEvents(midiEvents, midiEventCount);
	this->processReplacing((float**)inputs, outputs, frames);
}

void CO::sampleRateChanged(double newSampleRate)
{
	this->setSampleRate(newSampleRate);
}

void CO::bufferSizeChanged(int newBufferSize)
{
	this->setBlockSize(newBufferSize);
}