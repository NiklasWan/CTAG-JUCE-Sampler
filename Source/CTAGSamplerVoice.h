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

class CTAGSamplerVoice : public SamplerVoice,  public AudioProcessorValueTreeState::Listener
{
private:
	int pitchVal;
	BigInteger midiNote;
	CEnvelopeGenerator env;
	CVAOnePoleFilter filterLeft, filterRight;
	WaveShaper shaper;
	int index;
	LinearSmoothedValue<double> shaperAmp;
	double currSampRate;
public:
	CTAGSamplerVoice(int i) : index(i), pitchVal(0), currSampRate(48000)
	{ 
		shaperAmp.reset(48000, 0.01);
		shaperAmp.setValue(0.2);
	}
	CEnvelopeGenerator & getEnvelope() { return env; }
	CVAOnePoleFilter& getFilterLeft() { return filterLeft; }
	CVAOnePoleFilter& getFilterRight() { return filterRight; }
	bool canPlaySound(SynthesiserSound* sampSound) override;
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sampSound, int pitchWheel) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newValue) override;
	void controllerMoved(int controllerNumber, int newValue) override;
	void renderNextBlock(AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
	void setMidiNote(int note);
	bool canPlayCTAGSound(int note) const;
	void setCurrentPlaybackSampleRate(double newRate) override
	{
		SamplerVoice::setCurrentPlaybackSampleRate(newRate);
		if(currSampRate != newRate && newRate != 0)
		{
			currSampRate = newRate;
			shaperAmp.reset(currSampRate, 0.01);
			env.setSampleRate(currSampRate);
			filterLeft.setSampleRate(currSampRate);
			filterRight.setSampleRate(currSampRate);
		}
	}

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
	bool isFilterActive() { return filterLeft.isActive() && filterRight.isActive(); }
	void setFilterActive(bool val)
	{
		filterLeft.setActive(val);
		filterRight.setActive(val);
	}

	double getCutoffFreq() { return filterLeft.m_dFcControl; }
	void setCutoffFreq(double fc)
	{
		filterLeft.m_dFcControl = fc;
		filterRight.m_dFcControl = fc;
	}

	//Getter/Setter Waveshaper
	bool isWaveShaperActive() { return shaper.isActive(); }
	void setWaveShaperActive(bool val) { shaper.setActive(val); }

	double getWaveShaperSymmetrical() { return shaper.getSymmetrical(); }
	void setWaveShaperSymmetrical(double amp) { shaper.setAmplificationSymmetrical(amp); }
	
	void parameterChanged(const String &parameterID, float newValue) override;

};

