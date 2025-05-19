/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EQz3AudioProcessor::EQz3AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    UserParams[Gain] = 0.5f; 
    UserParams[LowGain] = 0.5f;
    UserParams[LowFreq] = 1.f; 
    UserParams[LowON] = 1.f;
    UserParams[MidGain] = 0.5f;
    UserParams[MidFreq] = 0.5f;
	UserParams[MidQ] = 0.4f;
    UserParams[MidON] = 1.f;
	UserParams[HighGain] = 0.5f;
	UserParams[HighFreq] = 1.f;
	UserParams[HighON] = 1.f;
	UserParams[PreAmp] = 0.f;
	UserParams[PreAmpON] = 1.f;
	UserParams[rmsL] = 0.f;
	UserParams[rmsR] = 0.f;
	UserParams[peakL] = 0.f;
	UserParams[peakR] = 0.f;

    UIUpdateFlag = true; // se cere update de la interfața grafică

	lastRMS[0] = 0.f;
	lastRMS[1] = 0.f;
	lastPeak[0] = 0.f;
	lastPeak[1] = 0.f; 

}

EQz3AudioProcessor::~EQz3AudioProcessor()
{
}

//==============================================================================
const juce::String EQz3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EQz3AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EQz3AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EQz3AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EQz3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EQz3AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EQz3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void EQz3AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EQz3AudioProcessor::getProgramName (int index)
{
    return {};
}

void EQz3AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EQz3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    dsp::ProcessSpec spec = { sampleRate, (uint32)samplesPerBlock, (uint32)getTotalNumOutputChannels() };
    
    LowBandFilter.prepare(spec);
    float lowCutF = UserParams[LowFreq] * 280.f + 20.f;
	float lowGain = UserParams[LowGain] * 32.f - 16.f;
    float q = 0.707 + (abs(lowGain) / 32.0f) * 0.65f;
    q += juce::jmap(lowCutF, 20.0f, 300.0f, -0.43f, 0.35f);
    q += (abs(UserParams[Gain] - 0.5f) + 0.1f) * 2.f;
    q = juce::jlimit(0.5f, 4.f, q);
    *LowBandFilter.state = *dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate,lowCutF,q, juce::Decibels::decibelsToGain(lowGain));
    LowBandFilter.reset();

	MidBandFilter.prepare(spec);
	float midCutF = UserParams[MidFreq] * 4750.f + 250.f;
	float midGain = UserParams[MidGain] * 32.f - 16.f;
	float qMid = UserParams[MidQ] * 4.f;
	*MidBandFilter.state = *dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, midCutF, qMid, juce::Decibels::decibelsToGain(midGain));
	MidBandFilter.reset();

    HighBandFilter.prepare(spec);
    float highCutF = UserParams[HighFreq] * 15500.f + 4500.f;
    float highGain = UserParams[HighGain] * 32.f - 16.f;
    float qHigh = 0.707 + (abs(highGain) / 32.0f) * 0.65f;
    qHigh += juce::jmap(highCutF, 4500.0f, 15500.0f, 0.35f, -0.57f);
    qHigh += (abs(UserParams[Gain] - 0.5f) + 0.1f) * 2.f;
    qHigh = juce::jlimit(0.5f, 4.f, qHigh);
    *HighBandFilter.state = *dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, highCutF, qHigh, juce::Decibels::decibelsToGain(highGain));
    HighBandFilter.reset();

    preampShaper.prepare(spec);

    // initialisation that you need..
}

void EQz3AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EQz3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EQz3AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();



    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    dsp::AudioBlock<float> block(buffer);

    float gaindb = UserParams[Gain] * 48.f - 24.f;
    float gainVal = powf(10.f, gaindb / 20.f);
        

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        // ..do something to the data...
		for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
		    
		}
    
    }
    if (UserParams[PreAmpON])  // Plugin is ACTIVE
    {
        if (UserParams[LowON])
            LowBandFilter.process(dsp::ProcessContextReplacing<float>(block));
        if (UserParams[MidON])
            MidBandFilter.process(dsp::ProcessContextReplacing<float>(block));
        if (UserParams[HighON])
            HighBandFilter.process(dsp::ProcessContextReplacing<float>(block));

        float preampAmount = UserParams[PreAmp];

        if (preampAmount <= 0.001f)
        {
            preampShaper.functionToUse = [](float x) { return x; };
        }
        else
        {
            float drive = preampAmount * 6.0f + 1.0f;
            float damp = preampAmount / 1.5f;

            // Estimate peak output at x ≈ 0.8
            float testX = 0.6f;
            float shapedPeak = std::tanh(testX * drive) * (1.0f - damp * testX * testX);
            float makeup = 1.0f / (shapedPeak + 1.0e-5f); // avoid division by zero

            preampShaper.functionToUse = [drive, damp, makeup](float x)
                {
                    float shaped = std::tanh(x * drive);
                    float softened = shaped * (1.0f - damp * x * x);

                    float hard = std::atan(x * drive * 1.5f);  // sharper saturation
                    float mixed = 0.65f * softened + 0.35f * hard;

                    return mixed * makeup;
                };

        }
        preampShaper.process(juce::dsp::ProcessContextReplacing<float>(block));
        buffer.applyGain(gainVal);
    }

  

    float tav = 0.125f;
    float kav = 1.f - expf(-2.2f / (tav * getSampleRate()));
    float tat = 0.0001f;
	float kat = 1.f - expf(-2.2f / (tat * getSampleRate()));
    float trt = 0.5f;
	float krt = 1.f - expf(-2.2f / (trt * getSampleRate()));

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        // ..do something to the data...
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
			float u = channelData[sample] * channelData[sample];
			lastRMS[channel] = (1.f - kav) * lastRMS[channel] + kav * u;
            if(abs(channelData[channel]) <= lastPeak[channel])
			    lastPeak[channel] = (1.f - krt) * lastPeak[channel];
			else
				lastPeak[channel] = (1.f - krt - kat) * lastPeak[channel] + kat * abs(channelData[channel]);
        }

    }
	UserParams[rmsL] = sqrtf(lastRMS[0]); 
	UserParams[rmsR] = sqrtf(lastRMS[1]);
	UserParams[peakL] = lastPeak[0];
	UserParams[peakR] = lastPeak[1];
    if (UserParams[rmsL] < powf(10.f, -100.f / 20.f))
            UserParams[rmsL] = 0;

    if (UserParams[rmsR] < powf(10.f, -100.f / 20.f))
            UserParams[rmsR] = 0;
    if (UserParams[peakL] < powf(10.f, -100.f / 20.f))
        UserParams[peakL] = 0;

    if (UserParams[peakR] < powf(10.f, -100.f / 20.f))
        UserParams[peakR] = 0;
    

}

//==============================================================================
bool EQz3AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EQz3AudioProcessor::createEditor()
{
    return new EQz3AudioProcessorEditor (this);
}

//==============================================================================

//==============================================================================
void EQz3AudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    XmlElement root("Root");
    XmlElement* el;

    el = root.createNewChildElement("Gain");
    el->addTextElement(String(UserParams[Gain]));

    el = root.createNewChildElement("LowGain");
    el->addTextElement(String(UserParams[LowGain]));

    el = root.createNewChildElement("LowFreq");
    el->addTextElement(String(UserParams[LowFreq]));

    el = root.createNewChildElement("LowON");
    el->addTextElement(String(UserParams[LowON]));

    el = root.createNewChildElement("MidGain");
    el->addTextElement(String(UserParams[MidGain]));

    el = root.createNewChildElement("MidFreq");
    el->addTextElement(String(UserParams[MidFreq]));

    el = root.createNewChildElement("MidQ");
    el->addTextElement(String(UserParams[MidQ]));

    el = root.createNewChildElement("MidON");
    el->addTextElement(String(UserParams[MidON]));

	el = root.createNewChildElement("HighGain");
	el->addTextElement(String(UserParams[HighGain]));

	el = root.createNewChildElement("HighFreq");
	el->addTextElement(String(UserParams[HighFreq]));

	el = root.createNewChildElement("HighON");
	el->addTextElement(String(UserParams[HighON]));

	el = root.createNewChildElement("PreAmp");
	el->addTextElement(String(UserParams[PreAmp]));

	el = root.createNewChildElement("PreAmpON");
	el->addTextElement(String(UserParams[PreAmpON]));

    copyXmlToBinary(root, destData);
}

void EQz3AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    static std::unique_ptr< XmlElement > pRoot = getXmlFromBinary(data, sizeInBytes);
    if (pRoot != NULL)
    {
        forEachXmlChildElement((*pRoot), pChild)
        {
            if (pChild->hasTagName("Gain"))
            {
                String text = pChild->getAllSubText();
                setParameter(Gain, text.getFloatValue());
			}
			else if (pChild->hasTagName("LowGain"))
			{
				String text = pChild->getAllSubText();
				setParameter(LowGain, text.getFloatValue());
			}
			else if (pChild->hasTagName("LowFreq"))
			{
				String text = pChild->getAllSubText();
				setParameter(LowFreq, text.getFloatValue());
			}
            else if (pChild->hasTagName("LowON"))
            {
                String text = pChild->getAllSubText();
                setParameter(LowON, text.getFloatValue());
            }
            else if (pChild->hasTagName("MidGain"))
            {
                String text = pChild->getAllSubText();
                setParameter(MidGain, text.getFloatValue());
            }
            else if (pChild->hasTagName("MidFreq"))
            {
                String text = pChild->getAllSubText();
                setParameter(MidFreq, text.getFloatValue());
			}
			else if (pChild->hasTagName("MidQ"))
			{
				String text = pChild->getAllSubText();
				setParameter(MidQ, text.getFloatValue());
			}
            else if (pChild->hasTagName("MidON"))
            {
                String text = pChild->getAllSubText();
                setParameter(MidON, text.getFloatValue());
            }
            else if (pChild->hasTagName("HighGain"))
            {
                String text = pChild->getAllSubText();
                setParameter(HighGain, text.getFloatValue());
            }
            else if (pChild->hasTagName("HighFreq"))
            {
                String text = pChild->getAllSubText();
                setParameter(HighFreq, text.getFloatValue());
			}
            else if (pChild->hasTagName("HighON"))
            {
                String text = pChild->getAllSubText();
                setParameter(HighON, text.getFloatValue());
            }
            else if (pChild->hasTagName("PreAmp"))
            {
                String text = pChild->getAllSubText();
                setParameter(PreAmp, text.getFloatValue());
            }
			else if (pChild->hasTagName("PreAmpON"))
			{
				String text = pChild->getAllSubText();
				setParameter(PreAmpON, text.getFloatValue());
			}

        }
        UIUpdateFlag = true;
    }
}

int EQz3AudioProcessor::getNumParameters()
{
    return totalNumParam;
}

float EQz3AudioProcessor::getParameter(int index)
{
    if (index < totalNumParam)
        return UserParams[index];
    else
        return 0.f;
}

void EQz3AudioProcessor::setParameter(int index, float newValue)
{
    float CutF,GainT, q;
    switch (index)
    {
    case Gain:
        UserParams[Gain] = newValue;
        break;
    case LowGain:
        UserParams[LowGain] = newValue;
        CutF = UserParams[LowFreq] * 280.f + 20.f;
        GainT = UserParams[LowGain] * 32.f - 16.f;
        q = 0.707 + (abs(GainT) / 32.0f) * 0.65f;
        q += juce::jmap(CutF, 20.0f, 300.0f, -0.43f, 0.35f);
        q += (abs(UserParams[PreAmp] - 0.5f) + 0.1f) * 2.f;
        q = juce::jlimit(0.5f, 4.f, q);
        *LowBandFilter.state = *dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(),CutF, q, juce::Decibels::decibelsToGain(GainT));
        break;
	case LowFreq:
		UserParams[LowFreq] = newValue;
        CutF = UserParams[LowFreq] * 280.f + 20.f;
        GainT = UserParams[LowGain] * 32.f - 16.f;
        q = 0.707 + (abs(GainT) / 32.0f) * 0.65f;
        q += juce::jmap(CutF, 20.0f, 300.0f, -0.43f, 0.35f);
        q += (abs(UserParams[PreAmp] - 0.5f) + 0.1f) * 2.f;
        q = juce::jlimit(0.5f, 4.f, q);
        *LowBandFilter.state = *dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(),CutF, q, juce::Decibels::decibelsToGain(GainT));
		break;
	case LowON:
		UserParams[LowON] = newValue;
		break;
	case MidGain:
		UserParams[MidGain] = newValue;
        CutF = UserParams[MidFreq] * 4750.f + 250.f;
        GainT = UserParams[MidGain] * 32.f - 16.f;
		q = UserParams[MidQ] * 4.f;
        *MidBandFilter.state = *dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(),CutF, q, juce::Decibels::decibelsToGain(GainT));
		break;
    case MidFreq:
        UserParams[MidFreq] = newValue;
        CutF = UserParams[MidFreq] * 4750.f + 250.f;
        GainT = UserParams[MidGain] * 32.f - 16.f;
        q = UserParams[MidQ] * 4.f;
        *MidBandFilter.state = *dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), CutF, q, juce::Decibels::decibelsToGain(GainT));
        break;
    case MidQ:
        UserParams[MidQ] = newValue;
        CutF = UserParams[MidFreq] * 4750.f + 250.f;
        GainT = UserParams[MidGain] * 32.f - 16.f;
        q = UserParams[MidQ] * 4.f;
        *MidBandFilter.state = *dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), CutF, q, juce::Decibels::decibelsToGain(GainT));
        break;
    case MidON:
        UserParams[MidON] = newValue;
        break;
	case HighGain:
		UserParams[HighGain] = newValue;
		CutF = UserParams[HighFreq] * 15500.f + 4500.f;
		GainT = UserParams[HighGain] * 32.f - 16.f;
		q = 0.707 + (abs(GainT) / 32.0f) * 0.65f;
		q += juce::jmap(CutF, 4500.0f, 15500.0f, -0.43f, 0.35f);
		q += (abs(UserParams[PreAmp] - 0.5f) + 0.1f) * 2.f;
		q = juce::jlimit(0.5f, 4.f, q);
		*HighBandFilter.state = *dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), CutF, q, juce::Decibels::decibelsToGain(GainT));
		break;
	case HighFreq:
		UserParams[HighFreq] = newValue;
		CutF = UserParams[HighFreq] * 15500.f + 4500.f;
		GainT = UserParams[HighGain] * 32.f - 16.f;
		q = 0.707 + (abs(GainT) / 32.0f) * 0.65f;
		q += juce::jmap(CutF, 4500.0f, 15500.0f, -0.43f, 0.35f);
		q += (abs(UserParams[PreAmp] - 0.5f) + 0.1f) * 2.f;
		q = juce::jlimit(0.5f, 4.f, q);
		*HighBandFilter.state = *dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), CutF, q, juce::Decibels::decibelsToGain(GainT));
		break;
	case HighON:
		UserParams[HighON] = newValue;
		break;
	case PreAmp:
		UserParams[PreAmp] = newValue;
		break;
	case PreAmpON:
		UserParams[PreAmpON] = newValue;
        CutF = UserParams[LowFreq] * 280.f + 20.f;
        GainT = UserParams[LowGain] * 32.f - 16.f;
        q = 0.707 + (abs(GainT) / 32.0f) * 0.65f;
        q += juce::jmap(CutF, 20.0f, 300.0f, -0.43f, 0.35f);
        q += (abs(UserParams[PreAmp] - 0.5f) + 0.1f) * 2.f;
        q = juce::jlimit(0.5f, 4.f, q);
        *LowBandFilter.state = *dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), CutF, q, juce::Decibels::decibelsToGain(GainT));
        CutF = UserParams[HighFreq] * 15500.f + 4500.f;
        GainT = UserParams[HighGain] * 32.f - 16.f;
        q = 0.707 + (abs(GainT) / 32.0f) * 0.65f;
        q += juce::jmap(CutF, 4500.0f, 15500.0f, -0.43f, 0.35f);
        q += (abs(UserParams[PreAmp] - 0.5f) + 0.1f) * 2.f;
        q = juce::jlimit(0.5f, 4.f, q);
        *HighBandFilter.state = *dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), CutF, q, juce::Decibels::decibelsToGain(GainT));
		break;
	case rmsL:
		UserParams[rmsL] = newValue;
		break;
	case rmsR:
		UserParams[rmsR] = newValue;
		break;
	case peakL:
		UserParams[peakL] = newValue;
		break;
	case peakR:
		UserParams[peakR] = newValue;
		break;
    default: return;
    }
    UIUpdateFlag = true; //Request UI update -- Some OSX hosts use alternate editors, this updates ours
}

const String EQz3AudioProcessor::getParameterName(int index)
{
    switch (index)
    {
    case Gain: return "Gain";
        break;
	case LowGain: return "LowGain";
		break;
	case LowFreq: return "LowFreq";
		break;
	case LowON: return "LowON";
		break;
	case MidGain: return "MidGain";
		break;
	case MidFreq: return "MidFreq";
		break;
	case MidQ: return "MidQ";
		break;
	case MidON: return "MidON";
		break;
	case HighGain: return "HighGain";
		break;
	case HighFreq: return "HighFreq";
		break;
	case HighON: return "HighON";
        break;
	case PreAmp: return "PreAmp";
		break;
	case PreAmpON: return "PreAmpON";
		break;;
    default:return String();
    }
}

const String EQz3AudioProcessor::getParameterText(int index)
{
    if (index >= 0 && index < totalNumParam)
        return String(UserParams[index]);
    else return String();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EQz3AudioProcessor();
}
