#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class CTAGInstrumentComponent : public Component, public Button::Listener
{
public:
	CTAGInstrumentComponent(JucesamplerAudioProcessor& p);
	~CTAGInstrumentComponent();

	void paint(Graphics& g) override;
	void resized() override;

	void buttonClicked(Button*) override;

private:
	static int counter;
	JucesamplerAudioProcessor& processor;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackAmpAttach;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayAmpAttach;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainAmpAttach;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseAmpAttach;

	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> filterToggleAttach;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> distortionToggleAttach;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttach;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> distortionValueAttach;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pitchValueAttach;

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

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CTAGInstrumentComponent)
};