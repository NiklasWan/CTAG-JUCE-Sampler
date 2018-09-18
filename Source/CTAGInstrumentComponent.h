#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PitchRateConversion.h"

class DecibelSlider;

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
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> panAttach;

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
	ScopedPointer<DecibelSlider> volumeSlider;
	ScopedPointer<Label> volumeLabel;
	ScopedPointer<Slider> levelDummy;
	ScopedPointer<Slider> panKnob;
	ScopedPointer<Label> panLabel;
	ScopedPointer<Label> panLeftLabel;
	ScopedPointer<Label> panRightLabel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CTAGInstrumentComponent)
};


class DecibelSlider : public Slider
{
public:
	DecibelSlider() {}

	double getValueFromText(const String& text) override
	{
		auto minusInfinitydB = -96.0;

		auto decibelText = text.upToFirstOccurrenceOf("dB", false, false).trim();   

		return decibelText.equalsIgnoreCase("-INF") ? minusInfinitydB
			: decibelText.getDoubleValue();  
	}

	String getTextFromValue(double value) override
	{
		return Decibels::toString(value);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DecibelSlider)
};