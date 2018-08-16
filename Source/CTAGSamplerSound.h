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
	
	CTAGSamplerSound(const String &name, AudioFormatReader &source, const BigInteger &midiNotes, int midiNoteForNormalPitch, double attackTimeSecs, double releaseTimeSecs, double maxSampleLengthSeconds) : SamplerSound(name, source, midiNotes, midiNoteForNormalPitch, attackTimeSecs, releaseTimeSecs, maxSampleLengthSeconds)  {}
	
};