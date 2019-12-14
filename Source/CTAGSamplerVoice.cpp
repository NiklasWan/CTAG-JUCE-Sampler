#include "CTAGSamplerVoice.h"


bool CTAGSamplerVoice::canPlaySound(SynthesiserSound* sampSound)
{
	return ((dynamic_cast<CTAGSamplerSound*>(sampSound)) != nullptr);
}


void CTAGSamplerVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound * sampSound, int pitchWheel)
{
	

	if (auto* sound = dynamic_cast<CTAGSamplerSound*> (sampSound))
	{
		
			pitchRatio = std::pow(2.0, ((midiNoteNumber - sound->midiRootNote) + pitchVal) / 12.0)
				* sound->sourceSampleRate / getSampleRate();

			sourceSamplePosition = 0.0;
			lgain = velocity;
			rgain = velocity;

			env.startEG();
			if (isVelocityFilterActive)
			{
				filterCutoff = filterLeft.cutoffControl;
				filterLeft.cutoffControl *= lgain;
				filterRight.cutoffControl *= rgain;
			}
		
		
	}
	else
	{
		jassertfalse; // this object can only play SamplerSounds!
	}
	
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
			if(isVelocityFilterActive)
				setCutoffFreq(filterCutoff);
		}

		else if (!allowTailOff && velocity == 1.0f)
		{
			
			if (env.canNoteOff())
				env.noteOff();
			if (isVelocityFilterActive)
				setCutoffFreq(filterCutoff);
		}
			
	

}

void CTAGSamplerVoice::renderNextBlock(AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
	
	
	if (auto* playingSound = dynamic_cast<CTAGSamplerSound*> (getCurrentlyPlayingSound().get()))
	{
		auto& data = *playingSound->getAudioData();
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

			//Envelope
			envVal = env.doEnvelope();
			l *= envVal;
			r *= envVal;

			//Apply Gain from Slider
			levelSlider = levelAmp.getNextValue();
			l *= levelSlider;
			r *= levelSlider;

			//Apply Pan 
			pan.setPosition(panAmp.getNextValue());
			l = pan.processLeftChannel(l);
			r = pan.processRightChannel(r);

			//Velocity Volume Modulation
			if(isVelocityVolumeActive)
			{
				l *= lgain;
				r *= rgain;
			}
			

			//WaveShaper
			setWaveShaperSymmetrical(shaperAmp.getNextValue());
			l = shaper.processSample(l);
			r = shaper.processSample(r);

			//Filter
			//Filter Velocity Modulation
			
			filterLeft.update();
			filterRight.update();
			l = filterLeft.doFilter(l);
			r = filterRight.doFilter(r);
			//Logger::outputDebugString("velocity left: " + std::to_string(lgain) + " filterCutoff: " + std::to_string(filterLeft.getCutofff()));


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
				if (isVelocityFilterActive)
					setCutoffFreq(filterCutoff);
				clearCurrentNote();
				break;
			}

			
		}
		
	}

}

void CTAGSamplerVoice::setMidiNote(int note) { midiNote.setBit(note); }

bool CTAGSamplerVoice::canPlayCTAGSound(int note) const { return midiNote[note]; }


void CTAGSamplerVoice::parameterChanged(const String &parameterID, float newValue) 
{
	if (parameterID == String("ampEnvAttack" + String(index)))
	{
		setEnvelopeAttack(newValue);

	}
	if (parameterID == String("ampEnvDecay" + String(index)))
	{
		setEnvelopeDecay(newValue);

	}
	if (parameterID == String("ampEnvSustain" + String(index)))
	{
		setEnvelopeSustain(newValue);

	}
	if (parameterID == String("ampEnvRelease" + String(index)))
	{
		setEnvelopeRelease(newValue);

	}
	if (parameterID == String("Filter ON/OFF" + String(index)))
	{
		setFilterActive(newValue);
	}
	if (parameterID == String("filterCutoff" + String(index)))
	{
		setCutoffFreq(newValue);
	}
	if (parameterID == String("Distortion ON/OFF" + String(index)))
	{
		setWaveShaperActive(newValue);
	}
	if (parameterID == String("distortionVal" + String(index)))
	{
		shaperAmp.setTargetValue(newValue);
		
	}
	if (parameterID == String("pitchVal" + String(index)))
	{
		pitchVal = newValue;
	}
	if (parameterID == String("vf" + String(index)))
	{
		isVelocityFilterActive = static_cast<bool>(newValue);
	}
	if (parameterID == String("vu" + String(index)))
	{
		isVelocityVolumeActive = static_cast<bool>(newValue);
	}
	if (parameterID == String("amp" + String(index)))
	{
		levelAmp.setTargetValue(newValue);
	}
	if (parameterID == String("pan" + String(index)))
	{
		panAmp.setTargetValue(newValue);
	}
}
