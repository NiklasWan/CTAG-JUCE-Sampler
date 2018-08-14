/*
  ==============================================================================

    CTAGSampler.cpp
    Created: 16 Jul 2018 10:56:28pm
    Author:  nikla

  ==============================================================================
*/

#include "CTAGSampler.h"
#include <string>
#define NUM_VOICES 9

void CTAGSampler::setup()
{
	
	for (int i = 0; i < NUM_VOICES; i++)
	{
		auto* voice = new CTAGSamplerVoice();

		switch(i)
		{
		case KICK:
			voice->setMidiNote(36);
			break;
		case SNARE:
			voice->setMidiNote(38);
			break;
		case CLAP:
			voice->setMidiNote(39);
			break;
		case TOM:
			voice->setMidiNote(41);
			break;
		case CLHAT:
			voice->setMidiNote(42);
			break;
		case PERC:
			voice->setMidiNote(43);
			break;
		case OPHAT:
			voice->setMidiNote(46);
			break;
		case CRASH:
			voice->setMidiNote(49);
			break;
		case RIDE:
			voice->setMidiNote(51);
			break;
		default:
			break;
		}
		
		addVoice(voice);
	}
	
	formatManager.registerBasicFormats();

	setInstrument("Kick.wav", 36, KICK);
	setInstrument("Snare.wav", 38, SNARE);
	setInstrument("Clap.wav", 39, CLAP);
	setInstrument("Tom.wav", 41, TOM);
	setInstrument("ClHat.wav", 42, CLHAT);
	setInstrument("Perc.wav", 43, PERC);
	setInstrument("OpHat.wav", 46, OPHAT);
	setInstrument("Crash.wav", 49, CRASH);
	setInstrument("Ride.wav", 51, RIDE);
	
}

void CTAGSampler::setInstrument(String audioFile, int midiNote, int instrument)
{
	// Is there an old Sound to be recycled?
	if (auto* oldSound = static_cast<CTAGSamplerSound*>(getSound(instrument)))
	{
		recycleSound(audioFile, oldSound, midiNote);
		return;
	}
	CTAGSamplerSound* newSound = prepareSound(audioFile, midiNote);
	addSound(newSound);
}

// Take Parameters of old Sound, destroy it and create new sound with same parameters

void CTAGSampler::recycleSound(String audioFile, CTAGSamplerSound* oldSound, int midiNote)
{
	CTAGSamplerSound::Parameter_t* params = oldSound->getParameters();


	CTAGSamplerSound* newSound = prepareSound(audioFile, midiNote);

	newSound->setParameters(params);
	removeSound(KICK);

	addSound(newSound);
}

// Create a new Sound

CTAGSamplerSound* CTAGSampler::prepareSound(String audioFile, int midiNote)
{
	File* file = new File(File::getCurrentWorkingDirectory().getChildFile(audioFile));

	ScopedPointer<AudioFormatReader> fileReader = formatManager.createReaderFor(*file);

	BigInteger note;
	note.setBit(midiNote);;

	return new CTAGSamplerSound(audioFile, *fileReader, note, midiNote, 0.0f, 10.0f, 10.0f);
}


void CTAGSampler::noteOn(int midiChannel,
	int midiNoteNumber,
	float velocity)
{
	const ScopedLock sl(lock);
	
	for(int j = 0; j < getNumSounds(); j++)
	{
		auto* sound = getSound(j);
		if(sound->appliesToNote(midiNoteNumber) && sound->appliesToChannel(midiChannel))
		{
			for(int i = 0; i < getNumVoices(); i++)
			{
				if(auto* voice = dynamic_cast<CTAGSamplerVoice*>(getVoice(i)))
				{
					if(voice->canPlayCTAGSound(midiNoteNumber) && voice->getCurrentlyPlayingSound())
					{
						stopVoice(voice, 0.0f, false);
					}
				}
			}

			for(int i = 0; i < getNumVoices(); i++)
			{
				if(auto* voice = dynamic_cast<CTAGSamplerVoice*> (getVoice(i)))
				{
					if(voice->canPlayCTAGSound(midiNoteNumber) && !voice->getCurrentlyPlayingSound())
					{
						Logger::outputDebugString("Start Voice: " + std::to_string(i) + " with Sound: " + std::to_string(j));
						startVoice(voice, sound, midiChannel, midiNoteNumber, velocity);
					}
				}
			}
		}
	}
}