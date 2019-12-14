/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JucesamplerAudioProcessorEditor::JucesamplerAudioProcessorEditor (JucesamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), tabComponent(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	
    setSize (600, 400);
	addAndMakeVisible(tabComponent);
}

JucesamplerAudioProcessorEditor::~JucesamplerAudioProcessorEditor()
{
}

//==============================================================================
void JucesamplerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
}

void JucesamplerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
