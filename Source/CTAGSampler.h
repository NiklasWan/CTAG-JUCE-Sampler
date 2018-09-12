/**
	The Sampler which handles all incoming midi messages and plays the corresponding sounds.



	@author Niklas Wantrupp
	@version v1.0 11/09/2018
*/


#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "CTAGSamplerSound.h"
#include "CTAGSamplerVoice.h"

class CTAGSampler : public Synthesiser, public AudioProcessorValueTreeState::Listener
{

	AudioFormatManager formatManager;
	File samplesFolder;
	StringArray instruments;
	bool isChokeGroupActive;
	/**
		This function is a private helper function to loadSamples() and loads a specific file into memory and adds it to the sounds array of CTAGSampler. 
	*/
	void addCTAGSound(String instrument, String filename, String kit);
public:
	//Override Methods
	void parameterChanged(const String &parameterID, float newValue) override;
	void noteOn(int midiChannel,
		int midiNoteNumber,
		float velocity) override;

	/**
		The setup function for the sampler. 
	*/

	void setup();


	/**
		This function enables you to load a drum kit. 
	*/
	void loadSamples(String kit, String rootNote);
	
	typedef enum Sounds { KICK = 0, SNARE, CLAP, TOM, CLHAT, PERC, OPHAT, CRASH, RIDE }Sounds_t;

	
};