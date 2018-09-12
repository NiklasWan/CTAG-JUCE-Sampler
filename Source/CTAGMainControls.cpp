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

#include "CTAGMainControls.h"
#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CTAGMainControls::CTAGMainControls (JucesamplerAudioProcessor &p)
    : processor(p), indexRootNote(0), indexKit(0), indexMode(0)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (kitLabel = new Label ("kitLabel",
                                             TRANS("Choose Drum-Kit:")));
    kitLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    kitLabel->setJustificationType (Justification::centredLeft);
    kitLabel->setEditable (false, false, false);
    kitLabel->setColour (TextEditor::textColourId, Colours::black);
    kitLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    kitLabel->setBounds (168, 160, 150, 24);

    addAndMakeVisible (kitComboBox = new ComboBox ("kitComboBox"));
    kitComboBox->setEditableText (false);
    kitComboBox->setJustificationType (Justification::centredLeft);
    kitComboBox->setTextWhenNothingSelected (String());
    kitComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    kitComboBox->addItem (TRANS("Kit 1"), 1);
    kitComboBox->addItem (TRANS("Kit 2"), 2);
    kitComboBox->addItem (TRANS("Kit 3"), 3);
    kitComboBox->addItem (TRANS("Kit 4"), 4);
    kitComboBox->addItem (TRANS("Kit 5"), 5);
    kitComboBox->addListener (this);

    kitComboBox->setBounds (176, 192, 104, 24);

    addAndMakeVisible (rootNoteLabel = new Label ("rootNoteLabel",
                                                  TRANS("Choose Root Note:\n")));
    rootNoteLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    rootNoteLabel->setJustificationType (Justification::centredLeft);
    rootNoteLabel->setEditable (false, false, false);
    rootNoteLabel->setColour (TextEditor::textColourId, Colours::black);
    rootNoteLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    rootNoteLabel->setBounds (304, 160, 150, 24);

    addAndMakeVisible (rootNoteComboBox = new ComboBox ("rootNoteComboBox"));
    rootNoteComboBox->setEditableText (false);
    rootNoteComboBox->setJustificationType (Justification::centredLeft);
    rootNoteComboBox->setTextWhenNothingSelected (String());
    rootNoteComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    rootNoteComboBox->addItem (TRANS("C"), 1);
    rootNoteComboBox->addItem (TRANS("C#"), 2);
    rootNoteComboBox->addItem (TRANS("D"), 3);
    rootNoteComboBox->addItem (TRANS("D#"), 4);
    rootNoteComboBox->addItem (TRANS("E"), 5);
    rootNoteComboBox->addItem (TRANS("F"), 6);
    rootNoteComboBox->addItem (TRANS("F#"), 7);
    rootNoteComboBox->addItem (TRANS("G"), 8);
    rootNoteComboBox->addItem (TRANS("G#"), 9);
    rootNoteComboBox->addItem (TRANS("A"), 10);
    rootNoteComboBox->addItem (TRANS("A#"), 11);
    rootNoteComboBox->addItem (TRANS("B"), 12);
    rootNoteComboBox->addListener (this);

    rootNoteComboBox->setBounds (312, 192, 104, 24);

    addAndMakeVisible (scaleComboBox = new ComboBox ("scaleComboBox"));
    scaleComboBox->setEditableText (false);
    scaleComboBox->setJustificationType (Justification::centredLeft);
    scaleComboBox->setTextWhenNothingSelected (String());
    scaleComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    scaleComboBox->addItem (TRANS("Chromatic"), 1);
    scaleComboBox->addItem (TRANS("Major"), 2);
    scaleComboBox->addItem (TRANS("Minor"), 3);
    scaleComboBox->addItem (TRANS("Melodic Minor"), 4);
    scaleComboBox->addItem (TRANS("Harmonic Minor"), 5);
    scaleComboBox->addSeparator();
    scaleComboBox->addListener (this);

    scaleComboBox->setBounds (240, 128, 104, 24);

    addAndMakeVisible (modeLabel = new Label ("modeLabel",
                                              TRANS("Choose Mode:")));
    modeLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    modeLabel->setJustificationType (Justification::centredLeft);
    modeLabel->setEditable (false, false, false);
    modeLabel->setColour (TextEditor::textColourId, Colours::black);
    modeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    modeLabel->setBounds (240, 104, 150, 24);

    addAndMakeVisible (loadSamplesButton = new TextButton ("loadSamplesButton"));
    loadSamplesButton->setButtonText (TRANS("Load Samples"));
    loadSamplesButton->addListener (this);

    loadSamplesButton->setBounds (224, 232, 150, 24);

	
    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 375);


    //[Constructor] You can add your own custom stuff here..
	chokeGroupActive = new ToggleButton("ChokeGroupActiveState");
	chokeGroupActive->setButtonText(translate("Activate Hat Choke Group"));
	chokeGroupActive->setBounds(215, 24, 150, 24);
	addAndMakeVisible(chokeGroupActive);

	chokeGroupActiveAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.getValueTree(), String("Choke ON/OFF"), *chokeGroupActive);
	kitComboBox->setSelectedId(1);
	rootNoteComboBox->setSelectedId(1);
	scaleComboBox->setSelectedId(1);
    //[/Constructor]
}

CTAGMainControls::~CTAGMainControls()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    kitLabel = nullptr;
    kitComboBox = nullptr;
    rootNoteLabel = nullptr;
    rootNoteComboBox = nullptr;
    scaleComboBox = nullptr;
    modeLabel = nullptr;
    loadSamplesButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CTAGMainControls::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CTAGMainControls::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CTAGMainControls::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == kitComboBox)
    {
        //[UserComboBoxCode_kitComboBox] -- add your combo box handling code here..
		indexKit = kitComboBox->getSelectedItemIndex();
        //[/UserComboBoxCode_kitComboBox]
    }
    else if (comboBoxThatHasChanged == rootNoteComboBox)
    {
        //[UserComboBoxCode_rootNoteComboBox] -- add your combo box handling code here..
		indexRootNote = rootNoteComboBox->getSelectedItemIndex();
		
        //[/UserComboBoxCode_rootNoteComboBox]
    }
    else if (comboBoxThatHasChanged == scaleComboBox)
    {
        //[UserComboBoxCode_scaleComboBox] -- add your combo box handling code here..
		indexMode = scaleComboBox->getSelectedItemIndex();
		if (auto e = dynamic_cast<JucesamplerAudioProcessorEditor*>(processor.getActiveEditor()))
		{
			Array<CTAGInstrumentComponent*>  views = e->tabComponent->getInstrumentViews();
			for (auto view : views)
			{
				if(scaleComboBox->getItemText(indexMode) == String("Chromatic"))
				{
					view->pitchSlider->setRange(-12, 12, 1);
				}
				else if(scaleComboBox->getItemText(indexMode) != String("Chromatic"))
				{
					view->pitchSlider->setRange(-7, 7, 1);
				}
				view->pitchCalc.setMode(indexMode);
			}
				
		}
        //[/UserComboBoxCode_scaleComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void CTAGMainControls::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == loadSamplesButton)
    {
        //[UserButtonCode_loadSamplesButton] -- add your button handler code here..
		loadSampleData();

		if (auto e = dynamic_cast<JucesamplerAudioProcessorEditor*>(processor.getActiveEditor()))
		{
			Array<CTAGInstrumentComponent*> views = e->tabComponent->getInstrumentViews();
			for (auto view : views)
			{
				view->pitchCalc.setRootNote(rootNoteComboBox->getItemText(indexRootNote));
				view->pitchValLabel->setText(rootNoteComboBox->getItemText(indexRootNote), NotificationType::sendNotification);
			}

		}
        //[/UserButtonCode_loadSamplesButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CTAGMainControls::loadSampleData()
{
	String kit, rootNote;

	kit = kitComboBox->getItemText(indexKit);

	rootNote = rootNoteComboBox->getItemText(indexRootNote);

	processor.getSampler().loadSamples(kit, rootNote);
	
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CTAGMainControls" componentName=""
                 parentClasses="public Component" constructorParams="JucesamplerAudioProcessor &amp;p"
                 variableInitialisers="processor(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="600"
                 initialHeight="375">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="kitLabel" id="1c34678571e2470a" memberName="kitLabel" virtualName=""
         explicitFocusOrder="0" pos="168 160 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Choose Drum-Kit:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="kitComboBox" id="9d3fccc99634147c" memberName="kitComboBox"
            virtualName="" explicitFocusOrder="0" pos="176 192 104 24" editable="0"
            layout="33" items="Kit 1&#10;Kit 2&#10;Kit 3&#10;Kit 4&#10;Kit 5"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="rootNoteLabel" id="336aa842460aa3ce" memberName="rootNoteLabel"
         virtualName="" explicitFocusOrder="0" pos="304 160 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Choose Root Note:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="rootNoteComboBox" id="8e1ad84455a193e0" memberName="rootNoteComboBox"
            virtualName="" explicitFocusOrder="0" pos="312 192 104 24" editable="0"
            layout="33" items="C&#10;C#&#10;D&#10;D#&#10;E&#10;F&#10;F#&#10;G&#10;G#&#10;A&#10;A#&#10;B"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="scaleComboBox" id="9f8da60e02761636" memberName="scaleComboBox"
            virtualName="" explicitFocusOrder="0" pos="240 128 104 24" editable="0"
            layout="33" items="Chromatic&#10;Major&#10;Minor&#10;Melodic Minor&#10;Harmonic Minor&#10;"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="modeLabel" id="8a3eaef7726954de" memberName="modeLabel"
         virtualName="" explicitFocusOrder="0" pos="240 104 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Choose Mode:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="loadSamplesButton" id="750d946c9952a21e" memberName="loadSamplesButton"
              virtualName="" explicitFocusOrder="0" pos="224 232 150 24" buttonText="Load Samples"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
