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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "InstrumentView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
InstrumentView::InstrumentView ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (attackSlider = new Slider ("attackSlider"));
    attackSlider->setRange (0, 10, 0);
    attackSlider->setSliderStyle (Slider::LinearVertical);
    attackSlider->setTextBoxStyle (Slider::NoTextBox, false, 40, 20);
    attackSlider->addListener (this);

    attackSlider->setBounds (40, 120, 40, 136);

    addAndMakeVisible (decaySlider = new Slider ("decaySlider"));
    decaySlider->setRange (0, 10, 0);
    decaySlider->setSliderStyle (Slider::LinearVertical);
    decaySlider->setTextBoxStyle (Slider::NoTextBox, false, 40, 20);
    decaySlider->addListener (this);

    decaySlider->setBounds (88, 120, 40, 136);

    addAndMakeVisible (sustainSlider = new Slider ("sustainSlider"));
    sustainSlider->setRange (0, 10, 0);
    sustainSlider->setSliderStyle (Slider::LinearVertical);
    sustainSlider->setTextBoxStyle (Slider::NoTextBox, false, 40, 20);
    sustainSlider->addListener (this);

    sustainSlider->setBounds (136, 120, 40, 136);

    addAndMakeVisible (releaseSlider = new Slider ("releaseSlider"));
    releaseSlider->setRange (0, 10, 0);
    releaseSlider->setSliderStyle (Slider::LinearVertical);
    releaseSlider->setTextBoxStyle (Slider::NoTextBox, false, 40, 20);
    releaseSlider->addListener (this);

    releaseSlider->setBounds (184, 120, 40, 136);

    addAndMakeVisible (amplitudeEnvelopeLabel = new Label ("amplitudeEnvelopeLabel",
                                                           TRANS("Amplitude Envelope")));
    amplitudeEnvelopeLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    amplitudeEnvelopeLabel->setJustificationType (Justification::centredLeft);
    amplitudeEnvelopeLabel->setEditable (false, false, false);
    amplitudeEnvelopeLabel->setColour (TextEditor::textColourId, Colours::black);
    amplitudeEnvelopeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    amplitudeEnvelopeLabel->setBounds (48, 88, 150, 24);

    addAndMakeVisible (attackLabel = new Label ("attackLabel",
                                                TRANS("Attack")));
    attackLabel->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    attackLabel->setJustificationType (Justification::centred);
    attackLabel->setEditable (false, false, false);
    attackLabel->setColour (TextEditor::textColourId, Colours::black);
    attackLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    attackLabel->setBounds (40, 256, 48, 24);

    addAndMakeVisible (decayLabel = new Label ("decayLabel",
                                               TRANS("Decay")));
    decayLabel->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    decayLabel->setJustificationType (Justification::centred);
    decayLabel->setEditable (false, false, false);
    decayLabel->setColour (TextEditor::textColourId, Colours::black);
    decayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    decayLabel->setBounds (88, 256, 48, 24);

    addAndMakeVisible (sustainLabel = new Label ("sustainLabel",
                                                 TRANS("Sustain")));
    sustainLabel->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    sustainLabel->setJustificationType (Justification::centred);
    sustainLabel->setEditable (false, false, false);
    sustainLabel->setColour (TextEditor::textColourId, Colours::black);
    sustainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    sustainLabel->setBounds (136, 256, 48, 24);

    addAndMakeVisible (releaseLabel = new Label ("releaseLabel",
                                                 TRANS("Release")));
    releaseLabel->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    releaseLabel->setJustificationType (Justification::centred);
    releaseLabel->setEditable (false, false, false);
    releaseLabel->setColour (TextEditor::textColourId, Colours::black);
    releaseLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    releaseLabel->setBounds (184, 256, 48, 24);

    addAndMakeVisible (filterToggle = new ToggleButton ("filterToggle"));
    filterToggle->setButtonText (TRANS("Filter"));
    filterToggle->addListener (this);

    filterToggle->setBounds (272, 128, 150, 24);

    addAndMakeVisible (distortionToggle = new ToggleButton ("distortionToggle"));
    distortionToggle->setButtonText (TRANS("Distortion"));
    distortionToggle->addListener (this);

    distortionToggle->setBounds (368, 128, 150, 24);

    addAndMakeVisible (filterSlider = new Slider ("filterSlider"));
	filterSlider->setVisible(false);
    filterSlider->setRange (80, 18000, 0);
    filterSlider->setSliderStyle (Slider::Rotary);
    filterSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    filterSlider->addListener (this);

    filterSlider->setBounds (280, 160, 64, 88);

    addAndMakeVisible (distortionSlider = new Slider ("distortionSlider"));
	distortionSlider->setVisible(false);
    distortionSlider->setRange (0.2f, 5.0f, 0);
    distortionSlider->setSliderStyle (Slider::Rotary);
    distortionSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    distortionSlider->addListener (this);

    distortionSlider->setBounds (384, 160, 64, 88);

    addAndMakeVisible (pitchLabel = new Label ("pitchLabel",
                                               TRANS("Pitch")));
    pitchLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    pitchLabel->setJustificationType (Justification::centredLeft);
    pitchLabel->setEditable (false, false, false);
    pitchLabel->setColour (TextEditor::textColourId, Colours::black);
    pitchLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    pitchLabel->setBounds (504, 128, 72, 24);

    addAndMakeVisible (pitchSlider = new Slider ("pitchSlider"));
    pitchSlider->setRange (0, 10, 0);
    pitchSlider->setSliderStyle (Slider::IncDecButtons);
    pitchSlider->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    pitchSlider->addListener (this);

    pitchSlider->setBounds (488, 168, 80, 80);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 375);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

InstrumentView::~InstrumentView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    attackSlider = nullptr;
    decaySlider = nullptr;
    sustainSlider = nullptr;
    releaseSlider = nullptr;
    amplitudeEnvelopeLabel = nullptr;
    attackLabel = nullptr;
    decayLabel = nullptr;
    sustainLabel = nullptr;
    releaseLabel = nullptr;
    filterToggle = nullptr;
    distortionToggle = nullptr;
    filterSlider = nullptr;
    distortionSlider = nullptr;
    pitchLabel = nullptr;
    pitchSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void InstrumentView::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void InstrumentView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void InstrumentView::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == attackSlider)
    {
        //[UserSliderCode_attackSlider] -- add your slider handling code here..
        //[/UserSliderCode_attackSlider]
    }
    else if (sliderThatWasMoved == decaySlider)
    {
        //[UserSliderCode_decaySlider] -- add your slider handling code here..
        //[/UserSliderCode_decaySlider]
    }
    else if (sliderThatWasMoved == sustainSlider)
    {
        //[UserSliderCode_sustainSlider] -- add your slider handling code here..
        //[/UserSliderCode_sustainSlider]
    }
    else if (sliderThatWasMoved == releaseSlider)
    {
        //[UserSliderCode_releaseSlider] -- add your slider handling code here..
        //[/UserSliderCode_releaseSlider]
    }
    else if (sliderThatWasMoved == filterSlider)
    {
        //[UserSliderCode_filterSlider] -- add your slider handling code here..
        //[/UserSliderCode_filterSlider]
    }
    else if (sliderThatWasMoved == distortionSlider)
    {
        //[UserSliderCode_distortionSlider] -- add your slider handling code here..
        //[/UserSliderCode_distortionSlider]
    }
    else if (sliderThatWasMoved == pitchSlider)
    {
        //[UserSliderCode_pitchSlider] -- add your slider handling code here..
        //[/UserSliderCode_pitchSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void InstrumentView::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == filterToggle)
    {
        //[UserButtonCode_filterToggle] -- add your button handler code here..
		if (filterToggle->getToggleState())
			filterSlider->setVisible(true);
		if (!filterToggle->getToggleState())
			filterSlider->setVisible(false);
        //[/UserButtonCode_filterToggle]
		
    }
    else if (buttonThatWasClicked == distortionToggle)
    {
        //[UserButtonCode_distortionToggle] -- add your button handler code here..
		if (distortionToggle->getToggleState())
			distortionSlider->setVisible(true);
		if (!distortionToggle->getToggleState())
			distortionSlider->setVisible(false);
        //[/UserButtonCode_distortionToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="InstrumentView" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="375">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="attackSlider" id="2f4a4f4457015abd" memberName="attackSlider"
          virtualName="" explicitFocusOrder="0" pos="40 120 40 136" min="0.00000000000000000000"
          max="10.00000000000000000000" int="0.00000000000000000000" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="decaySlider" id="9839332d858913e3" memberName="decaySlider"
          virtualName="" explicitFocusOrder="0" pos="88 120 40 136" min="0.00000000000000000000"
          max="10.00000000000000000000" int="0.00000000000000000000" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="sustainSlider" id="268ab0e3d0649048" memberName="sustainSlider"
          virtualName="" explicitFocusOrder="0" pos="136 120 40 136" min="0.00000000000000000000"
          max="10.00000000000000000000" int="0.00000000000000000000" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="releaseSlider" id="5c248763a8d5199c" memberName="releaseSlider"
          virtualName="" explicitFocusOrder="0" pos="184 120 40 136" min="0.00000000000000000000"
          max="10.00000000000000000000" int="0.00000000000000000000" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <LABEL name="amplitudeEnvelopeLabel" id="2f079d94c5d68686" memberName="amplitudeEnvelopeLabel"
         virtualName="" explicitFocusOrder="0" pos="48 88 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Amplitude Envelope" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="attackLabel" id="a78a11db3ab1fc8" memberName="attackLabel"
         virtualName="" explicitFocusOrder="0" pos="40 256 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Attack" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
  <LABEL name="decayLabel" id="dae3ef3ceb6009fd" memberName="decayLabel"
         virtualName="" explicitFocusOrder="0" pos="88 256 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Decay" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
  <LABEL name="sustainLabel" id="e964aba77bef24f6" memberName="sustainLabel"
         virtualName="" explicitFocusOrder="0" pos="136 256 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sustain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
  <LABEL name="releaseLabel" id="8b565e61a4c3eaac" memberName="releaseLabel"
         virtualName="" explicitFocusOrder="0" pos="184 256 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Release" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="filterToggle" id="42c64cfd62a96d9c" memberName="filterToggle"
                virtualName="" explicitFocusOrder="0" pos="272 128 150 24" buttonText="Filter"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="distortionToggle" id="dfa7bd6f8d38f9c5" memberName="distortionToggle"
                virtualName="" explicitFocusOrder="0" pos="368 128 150 24" buttonText="Distortion"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="filterSlider" id="202d25b1971295af" memberName="filterSlider"
          virtualName="" explicitFocusOrder="0" pos="280 160 64 88" min="0.00000000000000000000"
          max="10.00000000000000000000" int="0.00000000000000000000" style="Rotary"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="distortionSlider" id="dbf28ed66a0739a6" memberName="distortionSlider"
          virtualName="" explicitFocusOrder="0" pos="384 160 64 88" min="0.00000000000000000000"
          max="10.00000000000000000000" int="0.00000000000000000000" style="Rotary"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <LABEL name="pitchLabel" id="7ce1a755cbb8841a" memberName="pitchLabel"
         virtualName="" explicitFocusOrder="0" pos="504 128 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pitch" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <SLIDER name="pitchSlider" id="9a49ee63feaf32f6" memberName="pitchSlider"
          virtualName="" explicitFocusOrder="0" pos="488 168 80 80" min="0.00000000000000000000"
          max="10.00000000000000000000" int="0.00000000000000000000" style="IncDecButtons"
          textBoxPos="TextBoxBelow" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
