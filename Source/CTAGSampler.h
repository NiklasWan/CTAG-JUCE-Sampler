/*
  ==============================================================================

    CTAGSampler.h
    Created: 16 Jul 2018 10:56:28pm
    Author:  nikla

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "CTAGSamplerSound.h"
#include "CTAGSamplerVoice.h"

class CTAGSampler : public Synthesiser
{

	AudioFormatManager formatManager;

public:
	void setup();
	void setInstrument(String audioFile, int midNote, int instrument);
	void recycleSound(String audioFile, CTAGSamplerSound* oldSound, int midiNote);
	CTAGSamplerSound* prepareSound(String audioFile, int midiNote);

	typedef enum Sounds { KICK = 0, SNARE, CLAP, TOM, CLHAT, PERC, OPHAT, CRASH, RIDE }Sounds_t;

	void noteOn(int midiChannel,
		int midiNoteNumber,
		float velocity) override;
};