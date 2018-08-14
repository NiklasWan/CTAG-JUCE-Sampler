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
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class InstrumentView  : public Component,
                        public Slider::Listener,
                        public Button::Listener
{
public:
    //==============================================================================
    InstrumentView ();
    ~InstrumentView();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> attackSlider;
    ScopedPointer<Slider> decaySlider;
    ScopedPointer<Slider> sustainSlider;
    ScopedPointer<Slider> releaseSlider;
    ScopedPointer<Label> amplitudeEnvelopeLabel;
    ScopedPointer<Label> attackLabel;
    ScopedPointer<Label> decayLabel;
    ScopedPointer<Label> sustainLabel;
    ScopedPointer<Label> releaseLabel;
    ScopedPointer<ToggleButton> filterToggle;
    ScopedPointer<ToggleButton> distortionToggle;
    ScopedPointer<Slider> filterSlider;
    ScopedPointer<Slider> distortionSlider;
    ScopedPointer<Label> pitchLabel;
    ScopedPointer<Slider> pitchSlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstrumentView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
