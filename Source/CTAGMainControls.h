/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CTAGMainControls  : public Component,
                          public ComboBox::Listener,
                          public Button::Listener
{
public:
    //==============================================================================
    CTAGMainControls (JucesamplerAudioProcessor &p);
    ~CTAGMainControls();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	JucesamplerAudioProcessor& processor;
	void loadSampleData();
	int indexRootNote, indexMode, indexKit;
	ScopedPointer<ToggleButton> chokeGroupActive;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> chokeGroupActiveAttachment;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> kitLabel;
    ScopedPointer<ComboBox> kitComboBox;
    ScopedPointer<Label> rootNoteLabel;
    ScopedPointer<ComboBox> rootNoteComboBox;
    ScopedPointer<ComboBox> scaleComboBox;
    ScopedPointer<Label> modeLabel;
    ScopedPointer<TextButton> loadSamplesButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CTAGMainControls)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
