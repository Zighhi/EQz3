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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
EQz3AudioProcessorEditor::EQz3AudioProcessorEditor (EQz3AudioProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    gainLabel.reset(new juce::Label("Gain Label",
        TRANS("Output")));
    addAndMakeVisible(gainLabel.get());
    gainLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    gainLabel->setJustificationType(juce::Justification::centred);
    gainLabel->setEditable(false, false, false);
    gainLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    gainLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    gainSlider.reset(new juce::Slider("Gain Slider"));
    addAndMakeVisible(gainSlider.get());
    gainSlider->setRange(-24, 24, 0.1);
    gainSlider->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 40, 20);
    gainSlider->setDoubleClickReturnValue(true, 0.0f);
    gainSlider->addListener(this);

    LowGainLabel.reset(new juce::Label("Low Gain Label",
        TRANS("Gain\n")));
    addAndMakeVisible(LowGainLabel.get());
    LowGainLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    LowGainLabel->setJustificationType(juce::Justification::centred);
    LowGainLabel->setEditable(false, false, false);
    LowGainLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    LowGainLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    LowGainSlider.reset(new juce::Slider("Low Gain Slider"));
    addAndMakeVisible(LowGainSlider.get());
    LowGainSlider->setRange(-16, 16, 0.1);
    LowGainSlider->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    LowGainSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 40, 20);
    LowGainSlider->setDoubleClickReturnValue(true, 0.0f);
    LowGainSlider->addListener(this);

    LowFreqLabel.reset(new juce::Label("Low Freq Label",
        TRANS("\n"
            "Freq")));
    addAndMakeVisible(LowFreqLabel.get());
    LowFreqLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    LowFreqLabel->setJustificationType(juce::Justification::centred);
    LowFreqLabel->setEditable(false, false, false);
    LowFreqLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    LowFreqLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    LowFreqSlider.reset(new juce::Slider("Low Freq Slider"));
    addAndMakeVisible(LowFreqSlider.get());
    LowFreqSlider->setRange(20, 300, 1);
    LowFreqSlider->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    LowFreqSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 40, 20);
    LowFreqSlider->setSkewFactorFromMidPoint(100.0);
    LowFreqSlider->setDoubleClickReturnValue(true, 100.0);
    LowFreqSlider->addListener(this);

    LowBandBttn.reset(new juce::TextButton("Low Band Bttn"));
    addAndMakeVisible(LowBandBttn.get());
    LowBandBttn->setButtonText(TRANS("Bypass"));
    LowBandBttn->addListener(this);

    MidGainLabel.reset(new juce::Label("Mid Gain Label",
        TRANS("Gain\n")));
    addAndMakeVisible(MidGainLabel.get());
    MidGainLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    MidGainLabel->setJustificationType(juce::Justification::centred);
    MidGainLabel->setEditable(false, false, false);
    MidGainLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    MidGainLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    MidGainSlider.reset(new juce::Slider("Mid Gain Slider"));
    addAndMakeVisible(MidGainSlider.get());
    MidGainSlider->setRange(-16, 16, 0.1);
    MidGainSlider->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    MidGainSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 40, 20);
    MidGainSlider->setDoubleClickReturnValue(true, 0.0f);
    MidGainSlider->addListener(this);

    MidFreqLabel.reset(new juce::Label("Mid Freq Label",
        TRANS("Freq")));
    addAndMakeVisible(MidFreqLabel.get());
    MidFreqLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    MidFreqLabel->setJustificationType(juce::Justification::centred);
    MidFreqLabel->setEditable(false, false, false);
    MidFreqLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    MidFreqLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    MidFreqSlider.reset(new juce::Slider("Mid Freq Slider"));
    addAndMakeVisible(MidFreqSlider.get());
    MidFreqSlider->setRange(250, 5000, 1);
    MidFreqSlider->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    MidFreqSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 40, 20);
    MidFreqSlider->setSkewFactorFromMidPoint(1000.0);
    MidFreqSlider->setDoubleClickReturnValue(true, 1000.0);
    MidFreqSlider->addListener(this);

    MidBandBttn.reset(new juce::TextButton("Mid Band Bttn"));
    addAndMakeVisible(MidBandBttn.get());
    MidBandBttn->setButtonText(TRANS("Bypass"));
    MidBandBttn->addListener(this);

    MidQLabel.reset(new juce::Label("Mid Q Label",
        TRANS("Q")));
    addAndMakeVisible(MidQLabel.get());
    MidQLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    MidQLabel->setJustificationType(juce::Justification::centred);
    MidQLabel->setEditable(false, false, false);
    MidQLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    MidQLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    MidQSlider.reset(new juce::Slider("Mid Q Slider"));
    addAndMakeVisible(MidQSlider.get());
    MidQSlider->setRange(0.4, 4, 0.01);
    MidQSlider->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    MidQSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 40, 20);
    MidQSlider->setDoubleClickReturnValue(true, 1.0f);
    MidQSlider->addListener(this);

    HighGainLabel.reset(new juce::Label("High Gain Label",
        TRANS("Gain\n")));
    addAndMakeVisible(HighGainLabel.get());
    HighGainLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    HighGainLabel->setJustificationType(juce::Justification::centred);
    HighGainLabel->setEditable(false, false, false);
    HighGainLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    HighGainLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    HighGainSlider.reset(new juce::Slider("High Gain Slider"));
    addAndMakeVisible(HighGainSlider.get());
    HighGainSlider->setRange(-16, 16, 0.1);
    HighGainSlider->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    HighGainSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 40, 20);
    HighGainSlider->setDoubleClickReturnValue(true, 0.0f);
    HighGainSlider->addListener(this);

    HighFreqLabel.reset(new juce::Label("High Freq Label",
        TRANS("Freq")));
    addAndMakeVisible(HighFreqLabel.get());
    HighFreqLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    HighFreqLabel->setJustificationType(juce::Justification::centred);
    HighFreqLabel->setEditable(false, false, false);
    HighFreqLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    HighFreqLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    HighFreqSlider.reset(new juce::Slider("High Freq Slider"));
    addAndMakeVisible(HighFreqSlider.get());
    HighFreqSlider->setRange(4500, 20000, 1);
    HighFreqSlider->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    HighFreqSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 40, 20);
    HighFreqSlider->setSkewFactorFromMidPoint(9000.0);
    HighFreqSlider->setDoubleClickReturnValue(true, 9000.0);
    HighFreqSlider->addListener(this);

    HighBandBttn.reset(new juce::TextButton("High Band Bttn"));
    addAndMakeVisible(HighBandBttn.get());
    HighBandBttn->setButtonText(TRANS("Bypass"));
    HighBandBttn->addListener(this);

    GlobalBttn.reset(new juce::TextButton("Global Bttn"));
    addAndMakeVisible(GlobalBttn.get());
    GlobalBttn->setButtonText(TRANS("Bypass"));
    GlobalBttn->addListener(this);

    PreAmpLabel.reset(new juce::Label(" Pre Amp Label",
        TRANS("PreAmp")));
    addAndMakeVisible(PreAmpLabel.get());
    PreAmpLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    PreAmpLabel->setJustificationType(juce::Justification::centred);
    PreAmpLabel->setEditable(false, false, false);
    PreAmpLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    PreAmpLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    PreAmpLabel->setBounds(619, 20, 54, 24);

    PreAmpSlider.reset(new juce::Slider("PreAmp Slider"));
    addAndMakeVisible(PreAmpSlider.get());
    PreAmpSlider->setRange(0, 10, 0.1);
    PreAmpSlider->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    PreAmpSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 40, 20);
    PreAmpSlider->setDoubleClickReturnValue(true, 0.0f);
    PreAmpSlider->addListener(this);

    PreAmpSlider->setBounds(547, 60, 185, 82);



    const int knobSize = 100;
    const int labelHeight = 20;
    const int bandSpacingX = 50;
    const int offsetX = 15;
    const int offsetY = 15;

    const int rowTopY = offsetY;
    const int rowMidY = rowTopY + knobSize + labelHeight + 8;  // 8 px label spacing
    const int rowQY = rowMidY + knobSize + labelHeight + 8;

    const int buttonY = rowQY;


    LowGainSlider->setBounds(offsetX, rowTopY, knobSize, knobSize);
    LowGainLabel->setBounds(offsetX, rowTopY + knobSize, knobSize, labelHeight);

    LowFreqSlider->setBounds(offsetX, rowMidY, knobSize, knobSize);
    LowFreqLabel->setBounds(offsetX, rowMidY + knobSize, knobSize, labelHeight);

    int midX = offsetX + bandSpacingX * 2;

    MidGainSlider->setBounds(midX, rowTopY, knobSize, knobSize);
    MidGainLabel->setBounds(midX, rowTopY + knobSize, knobSize, labelHeight);

    MidFreqSlider->setBounds(midX + knobSize + 10, rowTopY, knobSize, knobSize);
    MidFreqLabel->setBounds(midX + knobSize + 10, rowTopY + knobSize, knobSize, labelHeight);

    MidQSlider->setBounds(midX + knobSize / 2 + 5, rowMidY, knobSize, knobSize);
    MidQLabel->setBounds(midX + knobSize / 2 + 5, rowMidY + knobSize, knobSize, labelHeight);

    int highX = offsetX + bandSpacingX * 6.25f;

    HighGainSlider->setBounds(highX, rowTopY, knobSize, knobSize);
    HighGainLabel->setBounds(highX, rowTopY + knobSize, knobSize, labelHeight);

    HighFreqSlider->setBounds(highX, rowMidY, knobSize, knobSize);
    HighFreqLabel->setBounds(highX, rowMidY + knobSize, knobSize, labelHeight);

    int fxX = offsetX + bandSpacingX * 8.5;

    PreAmpSlider->setBounds(fxX, rowTopY, knobSize, knobSize);
    PreAmpLabel->setBounds(fxX, rowTopY + knobSize, knobSize, labelHeight);

    gainSlider->setBounds(fxX, rowMidY, knobSize, knobSize);
    gainLabel->setBounds(fxX, rowMidY + knobSize, knobSize, labelHeight);

    int buttonWidth = 70;
    int buttonHeight = 24;

    LowBandBttn->setBounds(
        LowFreqSlider->getX() + (knobSize - buttonWidth) / 2,
        buttonY,
        buttonWidth,
        buttonHeight
    );

    MidBandBttn->setBounds(
        MidQSlider->getX() + (knobSize - buttonWidth) / 2,
        buttonY,
        buttonWidth,
        buttonHeight
    );

    HighBandBttn->setBounds(
        HighFreqSlider->getX() + (knobSize - buttonWidth) / 2,
        buttonY,
        buttonWidth,
        buttonHeight
    );

    GlobalBttn->setBounds(
        gainSlider->getX() + (knobSize - buttonWidth) / 2,
        buttonY,
        buttonWidth,
        buttonHeight
    );

    // Low Freq Value Label
    LowFreqValueLabel.reset(new juce::Label("LowFreqValueLabel", ""));
    addAndMakeVisible(LowFreqValueLabel.get());
    LowFreqValueLabel->setJustificationType(juce::Justification::centred);
    LowFreqValueLabel->setBounds(LowFreqSlider->getBounds());
    LowFreqValueLabel->setFont(juce::Font(14.0f));
    LowFreqValueLabel->setColour(juce::Label::textColourId, juce::Colours::white);
    LowFreqValueLabel->setInterceptsMouseClicks(false, false);

    // Low Gain Value Label
    LowGainValueLabel.reset(new juce::Label("LowGainValueLabel", ""));
    addAndMakeVisible(LowGainValueLabel.get());
    LowGainValueLabel->setJustificationType(juce::Justification::centred);
    LowGainValueLabel->setBounds(LowGainSlider->getBounds());
    LowGainValueLabel->setFont(juce::Font(14.0f));
    LowGainValueLabel->setColour(juce::Label::textColourId, juce::Colours::white);
    LowGainValueLabel->setInterceptsMouseClicks(false, false);

    // Mid Gain Value Label
    MidGainValueLabel.reset(new juce::Label("MidGainValueLabel", ""));
    addAndMakeVisible(MidGainValueLabel.get());
    MidGainValueLabel->setJustificationType(juce::Justification::centred);
    MidGainValueLabel->setBounds(MidGainSlider->getBounds());
    MidGainValueLabel->setFont(juce::Font(14.0f));
    MidGainValueLabel->setColour(juce::Label::textColourId, juce::Colours::white);
    MidGainValueLabel->setInterceptsMouseClicks(false, false);

    // Mid Freq Value Label
    MidFreqValueLabel.reset(new juce::Label("MidFreqValueLabel", ""));
    addAndMakeVisible(MidFreqValueLabel.get());
    MidFreqValueLabel->setJustificationType(juce::Justification::centred);
    MidFreqValueLabel->setBounds(MidFreqSlider->getBounds());
    MidFreqValueLabel->setFont(juce::Font(14.0f));
    MidFreqValueLabel->setColour(juce::Label::textColourId, juce::Colours::white);
    MidFreqValueLabel->setInterceptsMouseClicks(false, false);

    // Mid Q Value Label
    MidQValueLabel.reset(new juce::Label("MidQValueLabel", ""));
    addAndMakeVisible(MidQValueLabel.get());
    MidQValueLabel->setJustificationType(juce::Justification::centred);
    MidQValueLabel->setBounds(MidQSlider->getBounds());
    MidQValueLabel->setFont(juce::Font(14.0f));
    MidQValueLabel->setColour(juce::Label::textColourId, juce::Colours::white);
    MidQValueLabel->setInterceptsMouseClicks(false, false);

    // High Gain Value Label
    HighGainValueLabel.reset(new juce::Label("HighGainValueLabel", ""));
    addAndMakeVisible(HighGainValueLabel.get());
    HighGainValueLabel->setJustificationType(juce::Justification::centred);
    HighGainValueLabel->setBounds(HighGainSlider->getBounds());
    HighGainValueLabel->setFont(juce::Font(14.0f));
    HighGainValueLabel->setColour(juce::Label::textColourId, juce::Colours::white);
    HighGainValueLabel->setInterceptsMouseClicks(false, false);

    // High Freq Value Label
    HighFreqValueLabel.reset(new juce::Label("HighFreqValueLabel", ""));
    addAndMakeVisible(HighFreqValueLabel.get());
    HighFreqValueLabel->setJustificationType(juce::Justification::centred);
    HighFreqValueLabel->setBounds(HighFreqSlider->getBounds());
    HighFreqValueLabel->setFont(juce::Font(14.0f));
    HighFreqValueLabel->setColour(juce::Label::textColourId, juce::Colours::white);
    HighFreqValueLabel->setInterceptsMouseClicks(false, false);

    // PreAmp Value Label
    PreAmpValueLabel.reset(new juce::Label("PreAmpValueLabel", ""));
    addAndMakeVisible(PreAmpValueLabel.get());
    PreAmpValueLabel->setJustificationType(juce::Justification::centred);
    PreAmpValueLabel->setBounds(PreAmpSlider->getBounds());
    PreAmpValueLabel->setFont(juce::Font(14.0f));
    PreAmpValueLabel->setColour(juce::Label::textColourId, juce::Colours::white);
    PreAmpValueLabel->setInterceptsMouseClicks(false, false);

    // Output Gain Value Label
    GainValueLabel.reset(new juce::Label("GainValueLabel", ""));
    addAndMakeVisible(GainValueLabel.get());
    GainValueLabel->setJustificationType(juce::Justification::centred);
    GainValueLabel->setBounds(gainSlider->getBounds());
    GainValueLabel->setFont(juce::Font(14.0f));
    GainValueLabel->setColour(juce::Label::textColourId, juce::Colours::white);
    GainValueLabel->setInterceptsMouseClicks(false, false);


    addAndMakeVisible(leftMeter);
    addAndMakeVisible(rightMeter);
    //[UserPreSize]
    //[/UserPreSize]

    setSize (680, 310);


    //[Constructor] You can add your own custom stuff here..
    getProcessor()->RequestUIUpdate();
    startTimer(20);//starts timer with interval of 200mS
    //[/Constructor]
}

EQz3AudioProcessorEditor::~EQz3AudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    gainLabel = nullptr;
    gainSlider = nullptr;
    LowGainLabel = nullptr;
    LowGainSlider = nullptr;
    LowFreqLabel = nullptr;
    LowFreqSlider = nullptr;
    LowBandBttn = nullptr;
    MidGainLabel = nullptr;
    MidGainSlider = nullptr;
    MidFreqLabel = nullptr;
    MidFreqSlider = nullptr;
    MidBandBttn = nullptr;
    MidQLabel = nullptr;
    MidQSlider = nullptr;
    HighGainLabel = nullptr;
    HighGainSlider = nullptr;
    HighFreqLabel = nullptr;
    HighFreqSlider = nullptr;
    HighBandBttn = nullptr;
    GlobalBttn = nullptr;
    PreAmpLabel = nullptr;
    PreAmpSlider = nullptr;
    LowGainValueLabel = nullptr;
    LowFreqValueLabel = nullptr;
    MidGainValueLabel = nullptr;
    MidFreqValueLabel = nullptr;
    MidQValueLabel = nullptr;
    HighGainValueLabel = nullptr;
    HighFreqValueLabel = nullptr;
    PreAmpValueLabel = nullptr;
    GainValueLabel = nullptr;





    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void EQz3AudioProcessorEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff3b155f));

    //[UserPaint] Add your own custom painting code here..

    g.setColour(Colour(180, 160, 210));

    juce::Rectangle<int> lowSection = LowGainSlider->getBounds()
        .getUnion(LowFreqSlider->getBounds());
    lowSection.setBottom(lowSection.getBottom() + 60);
    g.drawRoundedRectangle(lowSection.toFloat(), 10.0f, 4.0f);

    juce::Rectangle<int> midSection = MidGainSlider->getBounds()
        .getUnion(MidFreqSlider->getBounds())
        .getUnion(MidQSlider->getBounds());
    midSection.setBottom(midSection.getBottom() + 60);
    g.drawRoundedRectangle(midSection.toFloat(), 10.0f, 4.0f);

    juce::Rectangle<int> highSection = HighGainSlider->getBounds()
        .getUnion(HighFreqSlider->getBounds());
    highSection.setBottom(highSection.getBottom() + 60);
    highSection.setX(midSection.getRight());
	highSection.setWidth(highSection.getWidth() + 5);
    g.drawRoundedRectangle(highSection.toFloat(), 10.0f, 4.0f);

    juce::Rectangle<int> fxSection = PreAmpSlider->getBounds()
        .getUnion(gainSlider->getBounds());
    fxSection.setBottom(fxSection.getBottom() + 60);
    fxSection.setX(highSection.getRight());
	fxSection.setWidth(fxSection.getWidth() + 20);
    g.drawRoundedRectangle(fxSection.toFloat(), 10.0f, 4.0f);

    juce::Rectangle<int> vuSection = leftMeter.getBounds()
        .getUnion(rightMeter.getBounds());
    //vuSection.setBottom(vuSection.getBottom() + 60);
    vuSection.setX(fxSection.getRight());
	vuSection.setY(fxSection.getY());
	vuSection.setBottom(fxSection.getBottom()); 
    vuSection.setWidth(vuSection.getWidth() + 45);
    g.drawRoundedRectangle(vuSection.toFloat(), 10.0f, 4.0f);
    //[/UserPaint]
}

void EQz3AudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..

    int meterTop = PreAmpValueLabel->getY() + 12;
    int meterBottom = GlobalBttn->getY() + GlobalBttn->getHeight()/2.f;
    int meterHeight = meterBottom - meterTop;

    int meterWidth = 35;
    int meterSpacing = 2;

    int meterX = getWidth() - meterWidth * 2 - meterSpacing - 35;

    leftMeter.setBounds(meterX, meterTop, meterWidth, meterHeight);
    rightMeter.setBounds(meterX + meterWidth + meterSpacing, meterTop, meterWidth, meterHeight);


    //[/UserResized]
}

void EQz3AudioProcessorEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    EQz3AudioProcessor* ourProcessor = getProcessor();
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == gainSlider.get())
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
        float gaindb = (float)gainSlider->getValue();
        ourProcessor->setParameter(EQz3AudioProcessor::Gain, (gaindb + 24.f) / 48.f);
        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == LowGainSlider.get())
    {
        //[UserSliderCode_LowGainSlider] -- add your slider handling code here..
        float normValue = (LowGainSlider->getValue() + 16.0f) / 32.0f;
		ourProcessor->setParameter(EQz3AudioProcessor::LowGain, normValue);
        //[/UserSliderCode_LowGainSlider]
    }
    else if (sliderThatWasMoved == LowFreqSlider.get())
    {
        //[UserSliderCode_LowFreqSlider] -- add your slider handling code here..
		ourProcessor->setParameter(EQz3AudioProcessor::LowFreq, (LowFreqSlider->getValue() - 20.f)/280.f);
        //[/UserSliderCode_LowFreqSlider]
    }
    else if (sliderThatWasMoved == MidGainSlider.get())
    {
        //[UserSliderCode_MidGainSlider] -- add your slider handling code here..
        float normValue = (MidGainSlider->getValue() + 16.0f) / 32.0f;
        ourProcessor->setParameter(EQz3AudioProcessor::MidGain, normValue);
        //[/UserSliderCode_MidGainSlider]
    }
    else if (sliderThatWasMoved == MidFreqSlider.get())
    {
        //[UserSliderCode_MidFreqSlider] -- add your slider handling code here..
        ourProcessor->setParameter(EQz3AudioProcessor::MidFreq, (MidFreqSlider->getValue() - 250.f)/4750.f);
        //[/UserSliderCode_MidFreqSlider]
    }
    else if (sliderThatWasMoved == MidQSlider.get())
    {
        //[UserSliderCode_MidQSlider] -- add your slider handling code here..
        ourProcessor->setParameter(EQz3AudioProcessor::MidQ, (MidQSlider->getValue()) / 4.f);
        //[/UserSliderCode_MidQSlider]
    }
    else if (sliderThatWasMoved == HighGainSlider.get())
    {
        //[UserSliderCode_HighGainSlider] -- add your slider handling code here..
		ourProcessor->setParameter(EQz3AudioProcessor::HighGain, (HighGainSlider->getValue() + 16.0f) / 32.0f);
        //[/UserSliderCode_HighGainSlider]
    }
    else if (sliderThatWasMoved == HighFreqSlider.get())
    {
        //[UserSliderCode_HighFreqSlider] -- add your slider handling code here..
		ourProcessor->setParameter(EQz3AudioProcessor::HighFreq, (HighFreqSlider->getValue() - 4500.f) / 15500.f);
        //[/UserSliderCode_HighFreqSlider]
    }
    else if (sliderThatWasMoved == PreAmpSlider.get())
    {
        //[UserSliderCode_PreAmpSlider] -- add your slider handling code here..
		ourProcessor->setParameter(EQz3AudioProcessor::PreAmp, PreAmpSlider->getValue() / 10.f);
        //[/UserSliderCode_PreAmpSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void EQz3AudioProcessorEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    EQz3AudioProcessor* ourProcessor = getProcessor();
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == LowBandBttn.get())
    {
        //[UserButtonCode_LowBandBttn] -- add your button handler code here..
        float val = ourProcessor->getParameter(EQz3AudioProcessor::LowON);
        val = val ? 0.f : 1.f;
        if (val)
        {
            LowBandBttn->setButtonText("LOW");
            LowBandBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(100, 60, 140));
        }
        else
        {
            LowBandBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(30, 10, 50));
        }
        ourProcessor->setParameter(EQz3AudioProcessor::LowON, val);
        //[/UserButtonCode_LowBandBttn]
    }
    else if (buttonThatWasClicked == MidBandBttn.get())
    {
        //[UserButtonCode_MidBandBttn] -- add your button handler code here..
        float val = ourProcessor->getParameter(EQz3AudioProcessor::MidON);
        val = val ? 0.f : 1.f;
        if (val)
        {
            MidBandBttn->setButtonText("MID");
            MidBandBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(100, 60, 140));
        }
        else
        {
            MidBandBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(30, 10, 50));
        }
        ourProcessor->setParameter(EQz3AudioProcessor::MidON, val);
        //[/UserButtonCode_MidBandBttn]
    }
    else if (buttonThatWasClicked == HighBandBttn.get())
    {
        //[UserButtonCode_HighBandBttn] -- add your button handler code here..
		float val = ourProcessor->getParameter(EQz3AudioProcessor::HighON);
		val = val ? 0.f : 1.f;
		if (val)
		{
			HighBandBttn->setButtonText("HIGH");
			HighBandBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(100, 60, 140));
		}
		else
		{
            HighBandBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(30, 10, 50));
		}
        ourProcessor->setParameter(EQz3AudioProcessor::HighON, val);
        //[/UserButtonCode_HighBandBttn]
    }
    else if (buttonThatWasClicked == GlobalBttn.get())
    {
        //[UserButtonCode_GlobalBttn] -- add your button handler code here..
        float val = ourProcessor->getParameter(EQz3AudioProcessor::PreAmpON);
        val = val ? 0.f : 1.f;
		if (val)
		{
			GlobalBttn->setButtonText("BYPASS");
			GlobalBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(100, 60, 140));
		}
		else
		{
            GlobalBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(30, 10, 50));
		}
        ourProcessor->setParameter(EQz3AudioProcessor::PreAmpON, val);
        //[/UserButtonCode_GlobalBttn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void EQz3AudioProcessorEditor::timerCallback()
{
    EQz3AudioProcessor* ourProcessor = getProcessor();

    if (ourProcessor->NeedsUIUpdate())
    {
        float gainNorm = ourProcessor->getParameter(EQz3AudioProcessor::Gain);
        float gaindb = gainNorm * 48.f - 24.f;
        gainSlider->setValue(gaindb, juce::dontSendNotification);


		LowGainSlider->setValue(32.f * ourProcessor->getParameter(EQz3AudioProcessor::LowGain) - 16.f, juce::dontSendNotification);
		LowFreqSlider->setValue(280.f * ourProcessor->getParameter(EQz3AudioProcessor::LowFreq) + 20.f, juce::dontSendNotification);

        float low_state = ourProcessor->getParameter(EQz3AudioProcessor::LowON);
        if (low_state)
        {
            LowBandBttn->setButtonText("LOW");
            LowBandBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(100, 60, 140));
        }
        else
        {
            LowBandBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(30, 10, 50));
        }

        MidGainSlider->setValue(32.f * ourProcessor->getParameter(EQz3AudioProcessor::MidGain) - 16.f, juce::dontSendNotification);
        MidFreqSlider->setValue(4750.f * ourProcessor->getParameter(EQz3AudioProcessor::MidFreq) + 250.f, juce::dontSendNotification);
        MidQSlider->setValue(4.f * ourProcessor->getParameter(EQz3AudioProcessor::MidQ), juce::dontSendNotification);

        float mid_state = ourProcessor->getParameter(EQz3AudioProcessor::MidON);
        if (mid_state)
        {
            MidBandBttn->setButtonText("MID");
            MidBandBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(100, 60, 140));
        }
        else
        {
            MidBandBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(30, 10, 50));
        }

		HighGainSlider->setValue(32.f * ourProcessor->getParameter(EQz3AudioProcessor::HighGain) - 16.f, juce::dontSendNotification);
		HighFreqSlider->setValue(15500.f * ourProcessor->getParameter(EQz3AudioProcessor::HighFreq) + 4500.f, juce::dontSendNotification);

		float high_state = ourProcessor->getParameter(EQz3AudioProcessor::HighON);
		if (high_state)
		{
            HighBandBttn->setButtonText("HIGH");
            HighBandBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(100, 60, 140));
		}
		else
		{
            HighBandBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(30, 10, 50));
		}

		PreAmpSlider->setValue(10.f * ourProcessor->getParameter(EQz3AudioProcessor::PreAmp), juce::dontSendNotification);

		float preamp_state = ourProcessor->getParameter(EQz3AudioProcessor::PreAmpON);
		if (preamp_state)
		{
            GlobalBttn->setButtonText("BYPASS");
            GlobalBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(100, 60, 140));
		}
        else
        {
            GlobalBttn->setColour(TextButton::ColourIds::buttonColourId, Colour(30, 10, 50));
        }

        LowGainValueLabel->setText(juce::String(LowGainSlider->getValue(), 1) + " dB", juce::dontSendNotification);
        LowFreqValueLabel->setText(juce::String((int)LowFreqSlider->getValue()) + " Hz", juce::dontSendNotification);
        MidGainValueLabel->setText(juce::String(MidGainSlider->getValue(), 1) + " dB", juce::dontSendNotification);
        MidFreqValueLabel->setText(juce::String((int)MidFreqSlider->getValue()) + " Hz", juce::dontSendNotification);
        MidQValueLabel->setText(juce::String(MidQSlider->getValue(), 2), juce::dontSendNotification);
        HighGainValueLabel->setText(juce::String(HighGainSlider->getValue(), 1) + " dB", juce::dontSendNotification);
        HighFreqValueLabel->setText(juce::String((int)HighFreqSlider->getValue()) + " Hz", juce::dontSendNotification);
        GainValueLabel->setText(juce::String(gainSlider->getValue(), 1) + " dB", juce::dontSendNotification);
        PreAmpValueLabel->setText(juce::String(PreAmpSlider->getValue(), 1), juce::dontSendNotification);


        ourProcessor->ClearUIUpdateFlag();
    }
    rmsL = 20 * log10(abs(ourProcessor->getParameter(EQz3AudioProcessor::rmsL)));
    rmsR = 20 * log10(abs(ourProcessor->getParameter(EQz3AudioProcessor::rmsL)));
    peakL = 20 * log10(abs(ourProcessor->getParameter(EQz3AudioProcessor::peakL)));
    peakR = 20 * log10(abs(ourProcessor->getParameter(EQz3AudioProcessor::peakR)));

    leftMeter.setLevels(rmsL,peakL);
    rightMeter.setLevels(rmsR,peakL);


}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="EQz3AudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="EQz3AudioProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="750" initialHeight="325">
  <BACKGROUND backgroundColour="ff3b155f"/>
  <LABEL name="Gain Label" id="fddfe07fbaa2a8a2" memberName="gainLabel"
         virtualName="" explicitFocusOrder="0" pos="613 161 54 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Gain Slider" id="efd124448e48553e" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="541 201 185 82" min="-24.0"
          max="24.0" int="0.1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Low Gain Label" id="7048486b8aa67a6e" memberName="LowGainLabel"
         virtualName="" explicitFocusOrder="0" pos="112 64 54 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Gain&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Low Gain Slider" id="b749f3055618a58d" memberName="LowGainSlider"
          virtualName="" explicitFocusOrder="0" pos="16 30 124 93" min="-16.0"
          max="16.0" int="0.1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Low Freq Label" id="2223044ca912022b" memberName="LowFreqLabel"
         virtualName="" explicitFocusOrder="0" pos="112 152 54 24" edTextCol="ff000000"
         edBkgCol="0" labelText="&#10;Freq" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Low Freq Slider" id="13e144f0dc3afc8" memberName="LowFreqSlider"
          virtualName="" explicitFocusOrder="0" pos="16 118 124 95" min="20.0"
          max="300.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TEXTBUTTON name="Low Band Bttn" id="11bcf43c2d2ca830" memberName="LowBandBttn"
              virtualName="" explicitFocusOrder="0" pos="67 208 22 16" buttonText="Bypass"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="Mid Gain Label" id="1f139689cd00ef49" memberName="MidGainLabel"
         virtualName="" explicitFocusOrder="0" pos="211 14 54 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Mid Gain&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Mid Gain Slider" id="a9cda1ceaf2d0b9f" memberName="MidGainSlider"
          virtualName="" explicitFocusOrder="0" pos="160 48 112 98" min="-16.0"
          max="16.0" int="0.1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Mid Freq Label" id="64a4cbc6ab773546" memberName="MidFreqLabel"
         virtualName="" explicitFocusOrder="0" pos="308 16 54 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Mid Freq" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Mid Freq Slider" id="bf1b61e5bbf7b8ab" memberName="MidFreqSlider"
          virtualName="" explicitFocusOrder="0" pos="236 56 185 82" min="250.0"
          max="5000.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TEXTBUTTON name="Mid Band Bttn" id="ca995a6d5ed01e57" memberName="MidBandBttn"
              virtualName="" explicitFocusOrder="0" pos="207 291 150 24" buttonText="Bypass"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="Mid Q Label" id="19436de1dbf65e07" memberName="MidQLabel"
         virtualName="" explicitFocusOrder="0" pos="259 156 54 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Mid Q" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Mid Q Slider" id="89b1fae6f3e0f4c2" memberName="MidQSlider"
          virtualName="" explicitFocusOrder="0" pos="187 196 185 82" min="0.4"
          max="4.0" int="0.01" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="High Gain Label" id="f9741b0df7b4aac7" memberName="HighGainLabel"
         virtualName="" explicitFocusOrder="0" pos="437 15 54 24" edTextCol="ff000000"
         edBkgCol="0" labelText="High Gain&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="High Gain Slider" id="fa7bbb5144bdf53f" memberName="HighGainSlider"
          virtualName="" explicitFocusOrder="0" pos="365 55 185 82" min="-16.0"
          max="16.0" int="0.1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="High Freq Label" id="7c7b0042f4f4807e" memberName="HighFreqLabel"
         virtualName="" explicitFocusOrder="0" pos="438 153 54 24" edTextCol="ff000000"
         edBkgCol="0" labelText="High Freq" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="High Freq Slider" id="16818ce0b203992f" memberName="HighFreqSlider"
          virtualName="" explicitFocusOrder="0" pos="366 193 185 82" min="4500.0"
          max="20000.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TEXTBUTTON name="High Band Bttn" id="48b26fc46e1fb752" memberName="HighBandBttn"
              virtualName="" explicitFocusOrder="0" pos="385 292 150 24" buttonText="Bypass"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Global Bttn" id="d459227fbaf039f9" memberName="GlobalBttn"
              virtualName="" explicitFocusOrder="0" pos="560 288 150 24" buttonText="Bypass"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name=" Pre Amp Label" id="d451d65e60038992" memberName="PreAmpLabel"
         virtualName="" explicitFocusOrder="0" pos="619 20 54 24" edTextCol="ff000000"
         edBkgCol="0" labelText="PreAmp" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="PreAmp Slider" id="5c0e0bc13a836a9a" memberName="PreAmpSlider"
          virtualName="" explicitFocusOrder="0" pos="547 60 185 82" min="0.0"
          max="10.0" int="0.1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

