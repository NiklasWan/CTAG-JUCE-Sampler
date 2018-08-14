/*
  ==============================================================================

    CTAGSamplerVoice.h
    Created: 16 Jul 2018 10:56:49pm
    Author:  nikla

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "CTAGSamplerSound.h"
#include "EnvelopeGenerator.h"
#include "OnePoleFilter.h"

class CTAGSamplerVoice : public SamplerVoice
{
private:
	int pitchVal = 0;
	BigInteger midiNote;
	CEnvelopeGenerator env;
	CVAOnePoleFilter filter;
public:
	CEnvelopeGenerator & getEnvelope() { return env; }
	CVAOnePoleFilter& getFilter() { return filter; }
	bool canPlaySound(SynthesiserSound* sampSound) override;
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sampSound, int pitchWheel) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newValue) override;
	void controllerMoved(int controllerNumber, int newValue) override;
	void renderNextBlock(AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
	void setMidiNote(int note);
	bool canPlayCTAGSound(int note) const;
};

