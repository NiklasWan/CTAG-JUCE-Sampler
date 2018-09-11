/**
	A Sampler Sound Object, which is able to hold a sampled sound.



	@author Niklas Wantrupp
	@version v1.0 12/09/2018
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


class CTAGSamplerSound : public SamplerSound
{
private:
	int midiRootNote = 0;
	int length = 0;
	double sourceSampleRate;
public:
	friend class CTAGSamplerVoice;
	CTAGSamplerSound(const String &name, AudioFormatReader &source, const BigInteger &midiNotes, int midiNoteForNormalPitch, double attackTimeSecs, double releaseTimeSecs, double maxSampleLengthSeconds) : SamplerSound(name, source, midiNotes, midiNoteForNormalPitch, attackTimeSecs, releaseTimeSecs, maxSampleLengthSeconds),
	sourceSampleRate(source.sampleRate), length(source.lengthInSamples), midiRootNote(midiNoteForNormalPitch){}
	
};