/**
	A Sampler Voice Object, which is able to play a sampled sound.

	

	@author Niklas Wantrupp
	@version v1.0 11/09/2018
*/


#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "CTAGSamplerSound.h"
#include "EnvelopeGenerator.h"
#include "OnePoleFilter.h"
#include "WaveShaper.h"
#include "PanPos.h"

class CTAGSamplerVoice : public SamplerVoice,  public AudioProcessorValueTreeState::Listener
{
private:
	int pitchVal;
	BigInteger midiNote;
	EnvelopeGenerator env;
	VAOnePoleFilter filterLeft, filterRight;
	WaveShaper shaper;
	PanPos pan;
	int index;
	LinearSmoothedValue<double> shaperAmp, levelAmp, panAmp;
	double currSampRate;
	bool isVelocityFilterActive, isVelocityVolumeActive;
	//Variables from SamplerVoice Base Class
	double pitchRatio = 0;
	double sourceSamplePosition = 0;
	float lgain = 0, rgain = 0;
	double filterCutoff;
	double levelSlider;
public:
	
	//Constructor
	CTAGSamplerVoice(int i) : index(i), pitchVal(0), currSampRate(48000), levelSlider(1)
	{ 
		pan.setPosition(0.0);
		shaperAmp.reset(48000, 0.01);
		shaperAmp.setValue(0.2);
		levelAmp.reset(48000, 0.01);
		levelAmp.setValue(1.0);
		panAmp.reset(48000, 0.01);
		panAmp.setValue(0);
		isVelocityFilterActive = false;
		isVelocityVolumeActive = false;
	}

	//Override Methods
	void parameterChanged(const String &parameterID, float newValue) override;
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
		if (currSampRate != newRate && newRate != 0)
		{
			currSampRate = newRate;
			shaperAmp.reset(currSampRate, 0.01);
			levelAmp.reset(currSampRate, 0.01);
			panAmp.reset(currSampRate, 0.01);
			env.setSampleRate(currSampRate);
			filterLeft.setSampleRate(currSampRate);
			filterRight.setSampleRate(currSampRate);
		}
	}


	/**
	 
		Gets the envelope attached to the voice.
	*/

	EnvelopeGenerator & getEnvelope() { return env; }

	/**

		Gets the left filter attached to the voice.
	*/

	VAOnePoleFilter& getFilterLeft() { return filterLeft; }

	/**

		Gets the right filter attached to the voice.
	*/

	VAOnePoleFilter& getFilterRight() { return filterRight; }


	/**

		Sets the pitchValue of the voice.
	*/

	void setPitchVal(int pitch) { pitchVal = pitch; }

	/**

		Gets the pitchValue of the voice.
	*/

	int getPitchVal() { return pitchVal; }
	

	/**

		Sets the envelope attack time in msec.
	*/

	void setEnvelopeAttack(double time) { env.setAttackTime_mSec(time); }

	/**

		Sets the envelope decay time in msec.
	*/

	void setEnvelopeDecay(double time) { env.setDecayTime_mSec(time); }

	/**

		Sets the envelope sustain value.
	*/

	void setEnvelopeSustain(double sus) { env.setSustainLevel(sus); }

	/**

		Sets the envelope release time in msec.
	*/

	void setEnvelopeRelease(double time) { env.setReleaseTime_mSec(time); }

	/**

		Checks whether the filter is active or inactive.
	*/


	bool isFilterActive() { return filterLeft.isActive() && filterRight.isActive(); }
	
	/**

		Sets the filter to active state.
	*/

	void setFilterActive(bool val)
	{
		filterLeft.setActive(val);
		filterRight.setActive(val);
	}


	/**

		Sets the filter cutoff value.
	*/

	void setCutoffFreq(double cutoffFrequency)
	{
		filterLeft.cutoffControl = cutoffFrequency;
		filterRight.cutoffControl = cutoffFrequency;
	}

	/**

		Checks whether the waveshaper is active or not.
	*/

	bool isWaveShaperActive() { return shaper.isActive(); }

	/**

		Sets the active state of the wave shaper.
	*/

	void setWaveShaperActive(bool val) { shaper.setActive(val); }

	/**

		Sets the waveshaper symmetrical amplification.
	*/

	
	void setWaveShaperSymmetrical(double amp) { shaper.setAmplificationSymmetrical(amp); }
	
	

};

