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
	CTAGSampler();
	void setKick(String audioFile);
	void CTAGSampler::recycleSound(String audioFile, CTAGSamplerSound* oldSound, int midiNote);
	CTAGSamplerSound* CTAGSampler::prepareSound(String audioFile, int midiNote);
	CTAGSamplerSound* getCTAGSamplerSound(int index) const;
	CTAGSamplerVoice* getCTAGSamplerVoice(int index) const;
	typedef enum Sounds { KICK = 0, SNARE, CLAP }Sounds_t;
};