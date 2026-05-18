#pragma once
#include <juce_dsp/juce_dsp.h>

namespace sintetizador_monofonico {

class LadderFilter {
public:

  enum class FilterMode { lowPass, highPass, bandPass };

  void prepare(double sampleRate)
  {
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = 512;
    spec.numChannels = 1;

    filter.prepare(spec);
    filter.reset();

    update();
  }

  void reset()
  {
    filter.reset();
  }

  float process(float inputSample)
  {
    float buffer = inputSample;

    float* channelData[] = { &buffer };

    juce::dsp::AudioBlock<float> block(channelData, 1, 1);
    juce::dsp::ProcessContextReplacing<float> context(block);

    filter.process(context);

    return buffer;
  }

  void setCutoff(float v)     { cutoff = v; update(); }
  void setResonance(float v)  { resonance = v; update(); }
  void setDrive(float v)      { drive = v; update(); }

  void setMode(FilterMode m)
  {
    currentMode = m;
    update();
  }

private:

  void update()
  {
    filter.setCutoffFrequencyHz(cutoff);
    filter.setResonance(resonance);
    filter.setDrive(drive);

    switch (currentMode)
    {
      case FilterMode::lowPass:
        filter.setMode(juce::dsp::LadderFilterMode::LPF24);
        break;

      case FilterMode::highPass:
        filter.setMode(juce::dsp::LadderFilterMode::HPF24);
        break;

      case FilterMode::bandPass:
        filter.setMode(juce::dsp::LadderFilterMode::BPF24);
        break;
    }
  }

private:

  juce::dsp::LadderFilter<float> filter;

  float cutoff = 1000.f;
  float resonance = 0.1f;
  float drive = 1.f;

  FilterMode currentMode = FilterMode::lowPass;
};

} // namespace sintetizador_monofonico