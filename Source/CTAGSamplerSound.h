/*
  ==============================================================================

    CTAGSamplerSound.h
    Created: 16 Jul 2018 10:57:03pm
    Author:  nikla

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeGenerator.h"

class CTAGSamplerSound : public SamplerSound
{
	
public:
	
	CTAGSamplerSound(const String &name, AudioFormatReader &source, const BigInteger &midiNotes, int midiNoteForNormalPitch, double attackTimeSecs, double releaseTimeSecs, double maxSampleLengthSeconds) : SamplerSound(name, source, midiNotes, midiNoteForNormalPitch, attackTimeSecs, releaseTimeSecs, maxSampleLengthSeconds) {params.env = new CEnvelopeGenerator(); }
	
	typedef struct
	{
		CEnvelopeGenerator* env;
	}Parameter_t;

	void setParameters(Parameter_t* params) { this->params = *params; }
	Parameter_t* getParameters() { return &params; }
	CEnvelopeGenerator& getEnvelopeGenerator() { return *params.env; }
private:
	Parameter_t params;
};