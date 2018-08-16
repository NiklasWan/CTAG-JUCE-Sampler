#include "CTAGTabComponent.h"


CTAGTabComponent::CTAGTabComponent(JucesamplerAudioProcessor& p) : processor(p)
{
	tabbedComponent = new TabbedComponent(TabbedButtonBar::TabsAtTop);

	//Add all Tabs
	tabbedComponent->addTab(translate("MainControl"), Colours::lightgrey, 0, false);
	tabbedComponent->addTab(translate("Kick"), Colours::lightgrey, new CTAGInstrumentComponent(p), true);
	tabbedComponent->addTab(translate("Snare"), Colours::lightgrey, new CTAGInstrumentComponent(p), true);
	tabbedComponent->addTab(translate("Clap"), Colours::lightgrey, new CTAGInstrumentComponent(p), true);
	tabbedComponent->addTab(translate("Tom"), Colours::lightgrey, new CTAGInstrumentComponent(p), true);
	tabbedComponent->addTab(translate("ClHat"), Colours::lightgrey, new CTAGInstrumentComponent(p), true);
	tabbedComponent->addTab(translate("Perc"), Colours::lightgrey, new CTAGInstrumentComponent(p), true);
	tabbedComponent->addTab(translate("OpHat"), Colours::lightgrey, new CTAGInstrumentComponent(p), true);
	tabbedComponent->addTab(translate("Crash"), Colours::lightgrey, new CTAGInstrumentComponent(p), true);
	tabbedComponent->addTab(translate("Ride"), Colours::lightgrey, new CTAGInstrumentComponent(p), true);

	tabbedComponent->setTabBarDepth(25);
	tabbedComponent->setCurrentTabIndex(1);

	tabbedComponent->setBounds(0, 0, 600, 400);

	addAndMakeVisible(tabbedComponent);

	setSize(600, 400);
}

CTAGTabComponent::~CTAGTabComponent()
{
	tabbedComponent = nullptr;
}

void CTAGTabComponent::paint(Graphics& g)
{
	g.fillAll(Colour(0xff323e44));
}

void CTAGTabComponent::resized()
{
	
}

