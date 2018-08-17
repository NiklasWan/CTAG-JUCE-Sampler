/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
static String doubleToString(double val) { return String(val); }
static double stringToDouble(String s){return std::stod(s.toStdString());}

static String boolToString(float val) { return (val == 1.0f) ? "active" : "inactive"; }
static bool stringToBool(String s) { return (s == "active") ? true : false; }

static String intToString(int val) { return String(val); }
static int stringToInt(String s) { return std::stoi(s.toStdString()); }

//==============================================================================
JucesamplerAudioProcessor::JucesamplerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	undoManager = new UndoManager();
	valueTree = new AudioProcessorValueTreeState(*this, undoManager);
	
	//Initialising Sampler
	sampler.setup();
	//Adding all Parameters to the Value Tree
	for(int i = 0; i < sampler.getNumVoices(); i++)
	{
		valueTree->createAndAddParameter(String("ampEnvAttack" + String(i)), "ampEnvAttack", "", NormalisableRange<float>(0.0f, 500.0f), 0.0f, doubleToString, stringToDouble);
		valueTree->createAndAddParameter(String("ampEnvDecay" + String(i)), "ampEnvDecay", "", NormalisableRange<float>(0.0f, 1000.0f), 0.0f, doubleToString, stringToDouble);
		valueTree->createAndAddParameter(String("ampEnvSustain" + String(i)), "ampEnvSustain", "", NormalisableRange<float>(0.0f, 1.0f), 1, doubleToString, stringToDouble);
		valueTree->createAndAddParameter(String("ampEnvRelease" + String(i)), "ampEnvRelease", "", NormalisableRange<float>(0.0f, 5000.0f), 1000.0f, doubleToString, stringToDouble);

		valueTree->createAndAddParameter(String("Filter ON/OFF" + String(i)), "Filter ON/OFF", "", NormalisableRange<float>(0, 1, 1), 0, boolToString, stringToBool);
		valueTree->createAndAddParameter(String("filterCutoff" + String(i)), "filterCutoff", "", NormalisableRange<float>(18.0f, 18000.0f, 0, 0.199f), 18000.0f, doubleToString, stringToDouble);

		valueTree->createAndAddParameter(String("Distortion ON/OFF" + String(i)), "Distortion ON/OFF", "", NormalisableRange<float>(0, 1, 1), 0, boolToString, stringToBool);
		valueTree->createAndAddParameter(String("distortionVal" + String(i)), "distortionVal", "", NormalisableRange<float>(0.2f, 5.0f), 0.2f, doubleToString, stringToDouble);

		valueTree->createAndAddParameter(String("pitchVal" + String(i)), "pitchVal", "", NormalisableRange<float>(-12, 12, 1), 0, intToString, stringToInt);
		if(auto* voice = dynamic_cast<CTAGSamplerVoice*>(sampler.getVoice(i)))
		{
			valueTree->addParameterListener(String("ampEnvAttack" + String(i)) , voice);
			valueTree->addParameterListener(String("ampEnvDecay" + String(i)), voice);
			valueTree->addParameterListener(String("ampEnvSustain" + String(i)), voice);
			valueTree->addParameterListener(String("ampEnvRelease" + String(i)), voice);

			valueTree->addParameterListener(String("Filter ON/OFF" + String(i)), voice);
			valueTree->addParameterListener(String("filterCutoff" + String(i)), voice);

			valueTree->addParameterListener(String("Distortion ON/OFF" + String(i)), voice);
			valueTree->addParameterListener(String("distortionVal" + String(i)), voice);

			valueTree->addParameterListener(String("pitchVal" + String(i)), voice);
		}
	}
	valueTree->state = ValueTree("CTAGSamplerParameters");
	
	
	


}

JucesamplerAudioProcessor::~JucesamplerAudioProcessor()
{
	undoManager = nullptr;
	valueTree = nullptr;
}

//==============================================================================
const String JucesamplerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JucesamplerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JucesamplerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JucesamplerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JucesamplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JucesamplerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JucesamplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JucesamplerAudioProcessor::setCurrentProgram (int index)
{
}

const String JucesamplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void JucesamplerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JucesamplerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	sampler.setCurrentPlaybackSampleRate(sampleRate);

	for(int i = 0; i < sampler.getNumVoices(); i++)
	{
		if(auto* voice = dynamic_cast<CTAGSamplerVoice*>(sampler.getVoice(i)))
		{
			voice->getEnvelope().setSampleRate(sampleRate);
			voice->getFilterLeft().setSampleRate(sampleRate);
			voice->getFilterRight().setSampleRate(sampleRate);
		}
	}
}

void JucesamplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JucesamplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JucesamplerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
	
	sampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool JucesamplerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JucesamplerAudioProcessor::createEditor()
{
    return new JucesamplerAudioProcessorEditor (*this);
}

//==============================================================================
void JucesamplerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	MemoryOutputStream stream(destData, false);
	valueTree->state.writeToStream(stream);
}

void JucesamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	ValueTree tree = ValueTree::readFromData(data, sizeInBytes);

	if(tree.isValid())
	{
		if(tree.hasType("CTAGSamplerParameters"))
		{
			valueTree->state = tree;
		}
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JucesamplerAudioProcessor();
}
