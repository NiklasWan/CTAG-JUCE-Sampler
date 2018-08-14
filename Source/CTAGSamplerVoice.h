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
#include "WaveShaper.h"

class CTAGSamplerVoice : public SamplerVoice
{
private:
	int pitchVal = 0;
	BigInteger midiNote;
	CEnvelopeGenerator env;
	CVAOnePoleFilter filter;
	WaveShaper shaper;
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

	//Getter/Setter Pitch
	void setPitchVal(int pitch) { pitchVal = pitch; }
	int getPitchVal() { return pitchVal; }
	

	//Getter/Setter Envelope
	double getEnvelopeAttack() { return env.getAttackTime(); }
	double getEnvelopeDecay() { return env.getDecayTime(); }
	double getEnvelopeSustain() { return env.getSustainValue(); }
	double getEnvelopeRelease() { return env.getReleaseTime(); }

	void setEnvelopeAttack(double time) { env.setAttackTime_mSec(time); }
	void setEnvelopeDecay(double time) { env.setDecayTime_mSec(time); }
	void setEnvelopeSustain(double sus) { env.setSustainLevel(sus); }
	void setEnvelopeRelease(double time) { env.setReleaseTime_mSec(time); }

	//Geter/Setter Filter
	bool isFilterActive() { return filter.isActive(); }
	void setFilterActive(bool val) { filter.setActive(val); }

	double getCutoffFreq() { return filter.m_dFcControl; }
	double setCutoffFreq(double fc) { filter.m_dFcControl = fc; }

	//Getter/Setter Waveshaper
	bool isWaveShaperActive() { return shaper.isActive(); }
	void setWaveShaperActive(bool val) { shaper.setActive(val); }

	double getWaveShaperSymmetrical() { return shaper.getSymmetrical(); }
	double setWaveShaperSymmetrical(double amp) { shaper.setAmplificationSymmetrical(amp); }
};

