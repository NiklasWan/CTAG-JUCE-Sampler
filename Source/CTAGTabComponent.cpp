#include "CTAGTabComponent.h"



CTAGTabComponent::CTAGTabComponent(JucesamplerAudioProcessor& p) : processor(p)
{
	tabbedComponent = new TabbedComponent(TabbedButtonBar::TabsAtTop);

	for(int i = 0; i < 9; i++)
	{
		instruments.add(new CTAGInstrumentComponent(p));
	}
	//Add all Tabs
	tabbedComponent->addTab(translate("MainControl"), Colours::lightgrey, new CTAGMainControls(p), true);
	tabbedComponent->addTab(translate("Kick"), Colours::lightgrey, instruments[0], true);
	tabbedComponent->addTab(translate("Snare"), Colours::lightgrey, instruments[1], true);
	tabbedComponent->addTab(translate("Clap"), Colours::lightgrey, instruments[2], true);
	tabbedComponent->addTab(translate("Tom"), Colours::lightgrey, instruments[3], true);
	tabbedComponent->addTab(translate("ClHat"), Colours::lightgrey, instruments[4], true);
	tabbedComponent->addTab(translate("Perc"), Colours::lightgrey, instruments[5], true);
	tabbedComponent->addTab(translate("OpHat"), Colours::lightgrey, instruments[6], true);
	tabbedComponent->addTab(translate("Crash"), Colours::lightgrey, instruments[7], true);
	tabbedComponent->addTab(translate("Ride"), Colours::lightgrey, instruments[8], true);

	tabbedComponent->setTabBarDepth(25);
	tabbedComponent->setCurrentTabIndex(0);

	setSize(600, 400);
	tabbedComponent->setBounds(0, 0, 600, 400);

	addAndMakeVisible(tabbedComponent);

	
}

CTAGTabComponent::~CTAGTabComponent()
{
	tabbedComponent = nullptr;
	instruments.clear();
}

void CTAGTabComponent::paint(Graphics& g)
{
	g.fillAll(Colour(0xff323e44));
}

void CTAGTabComponent::resized()
{
	
}

