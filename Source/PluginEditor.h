/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.12

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class EQz3AudioProcessorEditor  : public AudioProcessorEditor,
                                  public Timer,
                                  public juce::Slider::Listener,
                                  public juce::Button::Listener
{
public:
    //==============================================================================
    EQz3AudioProcessorEditor (EQz3AudioProcessor* ownerFilter);
    ~EQz3AudioProcessorEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback();
    EQz3AudioProcessor* getProcessor() const
    {
        return static_cast <EQz3AudioProcessor*>(getAudioProcessor());
    }
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    float peakL, peakR, rmsL, rmsR;
    class VUMeter : public juce::Component
    {
    public:
        float rms = -100.0f;  // In dB
        float peak = -100.0f; // In dB

        void setLevels(float newRms, float newPeak)
        {
            rms = juce::jlimit(-100.0f, 0.0f, newRms);
            peak = juce::jlimit(-100.0f, 0.0f, newPeak);
            repaint();
        }

        void paint(juce::Graphics& g) override
        {
            auto area = getLocalBounds().toFloat();
            g.setColour(juce::Colours::black);
            g.fillRect(area);

            // RMS bar
            float normRms = juce::jmap(rms, -100.0f, 0.0f, 0.0f, 1.0f);
            normRms = juce::jlimit(0.0f, 1.0f, normRms);
            float rmsHeight = area.getHeight() * normRms;

            g.setColour(juce::Colours::limegreen);
            g.fillRect(area.withTop(area.getBottom() - rmsHeight));

            // Peak line
            float normPeak = juce::jmap(peak, -100.0f, 0.0f, 0.0f, 1.0f);
            normPeak = juce::jlimit(0.0f, 1.0f, normPeak);
            float peakY = area.getBottom() - (area.getHeight() * normPeak);

            g.setColour(juce::Colours::yellow);
            g.drawLine(area.getX(), peakY, area.getRight(), peakY, 2.0f);
        }
    };
    VUMeter leftMeter, rightMeter;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> gainLabel;
    std::unique_ptr<juce::Slider> gainSlider;
    std::unique_ptr<juce::Label> LowGainLabel;
    std::unique_ptr<juce::Slider> LowGainSlider;
    std::unique_ptr<juce::Label> LowFreqLabel;
    std::unique_ptr<juce::Slider> LowFreqSlider;
    std::unique_ptr<juce::TextButton> LowBandBttn;
    std::unique_ptr<juce::Label> MidGainLabel;
    std::unique_ptr<juce::Slider> MidGainSlider;
    std::unique_ptr<juce::Label> MidFreqLabel;
    std::unique_ptr<juce::Slider> MidFreqSlider;
    std::unique_ptr<juce::TextButton> MidBandBttn;
    std::unique_ptr<juce::Label> MidQLabel;
    std::unique_ptr<juce::Slider> MidQSlider;
    std::unique_ptr<juce::Label> HighGainLabel;
    std::unique_ptr<juce::Slider> HighGainSlider;
    std::unique_ptr<juce::Label> HighFreqLabel;
    std::unique_ptr<juce::Slider> HighFreqSlider;
    std::unique_ptr<juce::TextButton> HighBandBttn;
    std::unique_ptr<juce::TextButton> GlobalBttn;
    std::unique_ptr<juce::Label> PreAmpLabel;
    std::unique_ptr<juce::Slider> PreAmpSlider;
    std::unique_ptr<juce::Label> LowGainValueLabel;
	std::unique_ptr<juce::Label> LowFreqValueLabel;
	std::unique_ptr<juce::Label> MidGainValueLabel;
	std::unique_ptr<juce::Label> MidFreqValueLabel;
	std::unique_ptr<juce::Label> MidQValueLabel;
	std::unique_ptr<juce::Label> HighGainValueLabel;
	std::unique_ptr<juce::Label> HighFreqValueLabel;
	std::unique_ptr<juce::Label> PreAmpValueLabel;
	std::unique_ptr<juce::Label> GainValueLabel;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQz3AudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

