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
#include "InstrumentView.h"
//[/Headers]

#include "MainWindow.h"



//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainWindow::MainWindow ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (25);
    tabbedComponent->addTab (TRANS("Main Control"), Colours::lightgrey, 0, false);
    tabbedComponent->addTab (TRANS("Kick"), Colours::lightgrey, new InstrumentView(), true);
    tabbedComponent->addTab (TRANS("Snare"), Colours::lightgrey, new InstrumentView(), true);
    tabbedComponent->addTab (TRANS("Clap"), Colours::lightgrey, new InstrumentView(), true);
    tabbedComponent->addTab (TRANS("Tom"), Colours::lightgrey, new InstrumentView(), true);
    tabbedComponent->addTab (TRANS("ClHat"), Colours::lightgrey, new InstrumentView(), true);
    tabbedComponent->addTab (TRANS("Perc"), Colours::lightgrey, new InstrumentView(), true);
    tabbedComponent->addTab (TRANS("OpHat"), Colours::lightgrey, new InstrumentView(), true);
    tabbedComponent->addTab (TRANS("Crash"), Colours::lightgrey, new InstrumentView(), true);
    tabbedComponent->addTab (TRANS("Ride"), Colours::lightgrey, new InstrumentView(), true);
    tabbedComponent->setCurrentTabIndex (0);

    tabbedComponent->setBounds (0, 0, 600, 400);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainWindow::~MainWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    tabbedComponent = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainWindow::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainWindow" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TABBEDCOMPONENT name="new tabbed component" id="f87b7c1d559b308b" memberName="tabbedComponent"
                   virtualName="" explicitFocusOrder="0" pos="0 0 600 400" orientation="top"
                   tabBarDepth="25" initialTab="0">
    <TAB name="Main Control" colour="ffd3d3d3" useJucerComp="0" contentClassName=""
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Kick" colour="ffd3d3d3" useJucerComp="0" contentClassName="InstrumentView"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Snare" colour="ffd3d3d3" useJucerComp="0" contentClassName="InstrumentView"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Clap" colour="ffd3d3d3" useJucerComp="0" contentClassName="InstrumentView"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Tom" colour="ffd3d3d3" useJucerComp="0" contentClassName="InstrumentView"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="ClHat" colour="ffd3d3d3" useJucerComp="0" contentClassName="InstrumentView"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Perc" colour="ffd3d3d3" useJucerComp="0" contentClassName="InstrumentView"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="OpHat" colour="ffd3d3d3" useJucerComp="0" contentClassName="InstrumentView"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Crash" colour="ffd3d3d3" useJucerComp="0" contentClassName="InstrumentView"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Ride" colour="ffd3d3d3" useJucerComp="0" contentClassName="InstrumentView"
         constructorParams="" jucerComponentFile=""/>
  </TABBEDCOMPONENT>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
