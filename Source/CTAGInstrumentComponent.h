#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PitchRateConversion.h"

class CTAGInstrumentComponent : public Component, public Button::Listener, public Slider::Listener
{
public:
	CTAGInstrumentComponent(JucesamplerAudioProcessor& p);
	~CTAGInstrumentComponent();

	void paint(Graphics& g) override;
	void resized() override;

	void buttonClicked(Button*) override;
	void sliderValueChanged(Slider* slider) override;
	PitchRateConversion pitchCalc;

private:
	friend class CTAGMainControls;
	
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
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> filterVelocityToggleAttach;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> volumeVelocityToggleAttach;

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
	ScopedPointer<Slider> pitchDummy;
	ScopedPointer<Label> pitchValLabel;
	ScopedPointer<ToggleButton> filterVelocityToggle;
	ScopedPointer<ToggleButton> volumeVelocityToggle;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CTAGInstrumentComponent)
};
