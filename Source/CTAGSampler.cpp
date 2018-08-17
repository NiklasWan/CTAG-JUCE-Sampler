/*
  ==============================================================================

    CTAGSampler.cpp
    Created: 16 Jul 2018 10:56:28pm
    Author:  nikla

  ==============================================================================
*/

#include "CTAGSampler.h"

#define NUM_VOICES 9

void CTAGSampler::setup()
{
	samplesFolder = File::getSpecialLocation(File::userDesktopDirectory).getChildFile("Samples");
	instruments = {"Kick", "Snare", "Clap", "Tom", "Perc", "OpHat", "ClHat", "Crash", "Ride"};
	for (int i = 0; i < NUM_VOICES; i++)
	{
		auto* voice = new CTAGSamplerVoice(i);

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
	/*
	setInstrument("Kick.wav", 36, KICK);
	setInstrument("Snare.wav", 38, SNARE);
	setInstrument("Clap.wav", 39, CLAP);
	setInstrument("Tom.wav", 41, TOM);
	setInstrument("ClHat.wav", 42, CLHAT);
	setInstrument("Perc.wav", 43, PERC);
	setInstrument("OpHat.wav", 46, OPHAT);
	setInstrument("Crash.wav", 49, CRASH);
	setInstrument("Ride.wav", 51, RIDE);*/
	loadSamples("Kit 1", "C");
}

void CTAGSampler::setInstrument(String audioFile, int midiNote, int instrument)
{
	// Is there an old Sound to be recycled?
	if (auto* oldSound = dynamic_cast<CTAGSamplerSound*>(getSound(instrument)))
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
	


	CTAGSamplerSound* newSound = prepareSound(audioFile, midiNote);

	
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
						//Logger::outputDebugString("Start Voice: " + std::to_string(i) + " with Sound: " + std::to_string(j));
						startVoice(voice, sound, midiChannel, midiNoteNumber, velocity);
					}
				}
			}
		}
	}
}

void CTAGSampler::loadSamples(String kit, String rootNote)
{
	String number = String( String(0) + String(0) + kit.trimCharactersAtStart("Kit "));
	
	const ScopedLock sl(lock);

	if(getNumSounds() != 0)
	{
		for(int i = 0; i < getNumSounds(); i++)
		{
			removeSound(i);
		}
	}
	

	
	for(int i = 0; i < instruments.size(); i++)
	{
		addCTAGSound(instruments[i], String(instruments[i] + "_" + number + "_" + rootNote + ".wav"), kit);
		
	}
	
	
	
}


void CTAGSampler::addCTAGSound(String instrument, String fileName, String kit)
{
	int midiNote;
	if(instrument == String("Kick"))
	{
		midiNote = 36;
	}
	else if( instrument == String("Snare"))
	{
		midiNote = 38;
	}
	else if(instrument == String ("Clap"))
	{
		midiNote = 39;
	}
	else if (instrument == String("Tom"))
	{
		midiNote = 41;
	}
	else if( instrument == String("ClHat"))
	{
		midiNote = 42;
	}
	else if (instrument == String("Perc"))
	{
		midiNote = 43;
	}
	else if(instrument == String("OpHat"))
	{
		midiNote = 46;
	}
	else if (instrument == String("Crash"))
	{
		midiNote = 49;
	}
	else if (instrument == String("Ride"))
	{
		midiNote = 51;
	}

	File* file = new File(samplesFolder.getChildFile(instrument).getChildFile(kit).getChildFile(fileName));
	
	//Logger::outputDebugString(file->getFullPathName());
	
	ScopedPointer<AudioFormatReader> fileReader = formatManager.createReaderFor(*file);
	BigInteger note;
	note.setBit(midiNote);

	addSound(new CTAGSamplerSound(instrument, *fileReader, note, midiNote, 0.0f, 10.0f, 10.0f));

	fileReader = nullptr;
	delete file;

	
}
