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
    
    std::unique_ptr<DecibelSlider> volumeSlider;
    std::unique_ptr<Label> volumeLabel;
    std::unique_ptr<Slider> panKnob;
    std::unique_ptr<Label> panLabel;
    std::unique_ptr<Label> panLeftLabel;
    std::unique_ptr<Label> panRightLabel;
    std::unique_ptr<Slider> attackSlider;
    std::unique_ptr<Slider> decaySlider;
    std::unique_ptr<Slider> sustainSlider;
    std::unique_ptr<Slider> releaseSlider;
    std::unique_ptr<Label> amplitudeEnvelopeLabel;
    std::unique_ptr<Label> attackLabel;
    std::unique_ptr<Label> decayLabel;
    std::unique_ptr<Label> sustainLabel;
    std::unique_ptr<Label> releaseLabel;
    std::unique_ptr<ToggleButton> filterToggle;
    std::unique_ptr<ToggleButton> filterVelocityToggle;
    std::unique_ptr<ToggleButton> volumeVelocityToggle;
    std::unique_ptr<ToggleButton> distortionToggle;
    std::unique_ptr<Slider> filterSlider;
    std::unique_ptr<Slider> distortionSlider;
    std::unique_ptr<Label> pitchLabel;
    std::unique_ptr<Slider> pitchSlider;
    std::unique_ptr<Slider> pitchDummy;
    std::unique_ptr<Slider> levelDummy;
    std::unique_ptr<Label> pitchValLabel;
    
    
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAmpAttach;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAmpAttach;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainAmpAttach;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseAmpAttach;

	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> filterToggleAttach;
	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> distortionToggleAttach;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttach;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> distortionValueAttach;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> pitchValueAttach;
	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> filterVelocityToggleAttach;
	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> volumeVelocityToggleAttach;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> panAttach;

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
