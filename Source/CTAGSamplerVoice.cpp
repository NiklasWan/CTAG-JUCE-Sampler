/*
  ==============================================================================

    CTAGSamplerVoice.cpp
    Created: 16 Jul 2018 10:56:49pm
    Author:  nikla

  ==============================================================================
*/

#include "CTAGSamplerVoice.h"
#include <string>

bool CTAGSamplerVoice::canPlaySound(SynthesiserSound* sampSound)
{
	return ((dynamic_cast<CTAGSamplerSound*>(sampSound)) != nullptr);
}


void CTAGSamplerVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound * sampSound, int pitchWheel)
{
	

	if (auto* sound = static_cast<CTAGSamplerSound*> (sampSound))
	{
		
			pitchRatio = std::pow(2.0, ((midiNoteNumber - sound->midiRootNote) + pitchVal) / 12.0)
				* sound->sourceSampleRate / getSampleRate();

			sourceSamplePosition = 0.0;
			lgain = velocity;
			rgain = velocity;

			//env.reset();
			env.startEG();
		
		
		
	}
	else
	{
		jassertfalse; // this object can only play SamplerSounds!
	}
	//SamplerVoice::startNote(midiNoteNumber, velocity, sampSound, pitchWheel);
}

void CTAGSamplerVoice::pitchWheelMoved(int newValue)
{
}

void CTAGSamplerVoice::controllerMoved(int controllerNumber, int newValue)
{
}

void CTAGSamplerVoice::stopNote(float velocity, bool allowTailOff)
{
		
		if (allowTailOff)
		{
			if (env.canNoteOff())
				env.noteOff();
		}
		else if(!allowTailOff && velocity == 0.0f)
		{
			env.shutDown();
			clearCurrentNote();
		}

		else if (!allowTailOff && velocity == 1.0f)
		{
			
			if (env.canNoteOff())
				env.noteOff();
		}
			
	

}

void CTAGSamplerVoice::renderNextBlock(AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
	//SamplerVoice::renderNextBlock(outputBuffer, startSample, numSamples);

	if (auto* playingSound = static_cast<CTAGSamplerSound*> (getCurrentlyPlayingSound().get()))
	{
		auto& data = *playingSound->data;
		const float* const inL = data.getReadPointer(0);
		const float* const inR = data.getNumChannels() > 1 ? data.getReadPointer(1) : nullptr;

		float* outL = outputBuffer.getWritePointer(0, startSample);
		float* outR = outputBuffer.getNumChannels() > 1 ? outputBuffer.getWritePointer(1, startSample) : nullptr;

		while (--numSamples >= 0)
		{
			auto pos = (int)sourceSamplePosition;
			auto alpha = (float)(sourceSamplePosition - pos);
			auto invAlpha = 1.0f - alpha;
			float envVal = 0.0f;
			// just using a very simple linear interpolation here..
			float l = (inL[pos] * invAlpha + inL[pos + 1] * alpha);
			float r = (inR != nullptr) ? (inR[pos] * invAlpha + inR[pos + 1] * alpha)
				: l;

			
			envVal = env.doEnvelope();
			l *= envVal;
			r *= envVal;

			if (outR != nullptr)
			{
				*outL++ += l;
				*outR++ += r;
			}
			else
			{
				*outL++ += (l + r) * 0.5f;
			}

			sourceSamplePosition += pitchRatio;

			if (env.getState() == 0 || sourceSamplePosition > playingSound->length)
			{
				clearCurrentNote();
				break;
			}
		}
	
		/*
		totalSamples -= numSamples;
		auto* leftData = outputBuffer.getWritePointer(0, startSample);
		auto* rightData = outputBuffer.getWritePointer(1, startSample);

		

		float envValue = 0.0f, currentLeft = 0.0f, currentRight = 0.0f;
		
		for (int sample = 0; sample < numSamples; sample++)
		{
			envValue = env.doEnvelope();

			currentLeft = leftData[sample];
			currentRight = rightData[sample];

			currentLeft *= envValue;
			currentRight *= envValue;

			outputBuffer.setSample(0, sample + startSample, currentLeft);
			outputBuffer.setSample(1, sample + startSample, currentRight);



		}
		if (env.getState() == 0 || totalSamples <= 0)
			clearCurrentNote();
		*/
	}

}

void CTAGSamplerVoice::setMidiNote(int note) { midiNote.setBit(note); }

bool CTAGSamplerVoice::canPlayCTAGSound(int note) const { return midiNote[note]; }
