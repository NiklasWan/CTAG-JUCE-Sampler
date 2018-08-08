/*
  ==============================================================================

    CTAGSampler.cpp
    Created: 16 Jul 2018 10:56:28pm
    Author:  nikla

  ==============================================================================
*/

#include "CTAGSampler.h"
#define NUM_VOICES 2
CTAGSampler::CTAGSampler()
{
	
}

void CTAGSampler::setup()
{
	
	for (int i = 0; i < NUM_VOICES; i++)
	{
		addVoice(new CTAGSamplerVoice());
	}

	formatManager.registerBasicFormats();

	setInstrument("Kick.wav", 60, KICK);
	setInstrument("Snare.wav", 61, SNARE);
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

CTAGSamplerSound* CTAGSampler::getCTAGSamplerSound(int index) const
{
	return static_cast<CTAGSamplerSound*>(getSound(index));
}

CTAGSamplerVoice* CTAGSampler::getCTAGSamplerVoice(int index) const
{
	return static_cast<CTAGSamplerVoice*>(getVoice(index));
}