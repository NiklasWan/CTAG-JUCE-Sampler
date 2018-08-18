#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "CTAGInstrumentComponent.h"
#include "CTAGMainControls.h"

class CTAGTabComponent : public Component
{
public:
	CTAGTabComponent(JucesamplerAudioProcessor& p);
	~CTAGTabComponent();

	void paint(Graphics& g) override;
	void resized() override;

	TabbedComponent& getTabbedComponenet() { return *tabbedComponent; }
	Array<CTAGInstrumentComponent*> getInstrumentViews() { return instruments; }
private:
	JucesamplerAudioProcessor& processor;
	ScopedPointer<TabbedComponent> tabbedComponent;
	Array<CTAGInstrumentComponent*> instruments;
	

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CTAGTabComponent)
};