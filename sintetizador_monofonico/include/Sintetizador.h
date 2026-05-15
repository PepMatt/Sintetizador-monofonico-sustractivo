#pragma once
#include "Waveforms.h"

namespace sintetizador_monofonico {
class Sintetizador {

  public:
  enum class WaveformType : size_t {
    sine = 0 ,
    triangle = 1 ,
    saw = 2 ,
  };

  void setGain(float gain) {
    targetGain = juce::Decibels::decibelsToGain(gain);
  }

  void prepare(
        double sampleRate,
        int samplesPerBlock,
        int totalOutputChannels)
  {
    currentSampleRate = sampleRate;

    adsr.setSampleRate(sampleRate);

    adsrParams.attack = 0.1f;
    adsrParams.decay = 0.2f;
    adsrParams.sustain = 0.7f;
    adsrParams.release = 0.5f;

    adsr.setParameters(adsrParams);

    const juce::dsp::ProcessSpec processSpec{
      .sampleRate = sampleRate,
      .maximumBlockSize =
          static_cast<juce::uint32>(samplesPerBlock),
      .numChannels = 1u,
  };

    for (auto& oscillator : osc) {
      oscillator.prepare(processSpec);
      oscillator.setFrequency(currentFrequency);
    }

    synthBuffer.setSize(
        totalOutputChannels,
        samplesPerBlock);

    synthBuffer.clear();
  }

  void process(
        juce::AudioBuffer<float>& buffer,
        juce::MidiBuffer& midiMessages) noexcept
  {
    buffer.clear();
    const auto numSamples = buffer.getNumSamples();

    updateWaveform();

    for (const auto metadata : midiMessages)
    {
      const auto msg = metadata.getMessage();

      if (msg.isNoteOn())
      {
        currentFrequency =
            juce::MidiMessage::getMidiNoteInHertz(
                msg.getNoteNumber());

        for (auto& oscillator : osc) {
          oscillator.setFrequency(currentFrequency);
        }

        adsr.noteOn();
      }

      if (msg.isNoteOff())
      {
        adsr.noteOff();
      }
    }

    auto* leftChannel = buffer.getWritePointer(0);
    auto* rightChannel = buffer.getNumChannels() > 1
        ? buffer.getWritePointer(1)
        : nullptr;

    for (int sample = 0;
         sample < buffer.getNumSamples();
         ++sample)
    {
      float oscSample = getNextOscValue();

      oscSample *= adsr.getNextSample();

      leftChannel[sample] = oscSample;

      if (rightChannel != nullptr) {
        rightChannel[sample] = oscSample;
      }
    }
      buffer.applyGainRamp(0,numSamples,currentGain,targetGain );

    currentGain = targetGain;
  }
  void reset() noexcept
  {
    for (auto& oscillator : osc) {
      oscillator.reset();
    }

    adsr.reset();
  }

  void setWaveform(WaveformType waveform)
  {
    waveformToSet = waveform;
  }
// *********************************************************

private:
  float targetAttack;
  float targetDecay;
  float targetSustain;
  float targetRelease;
  float targetGain = 0;

  float currentGain = 0;

  float getNextOscValue() {
    return osc[juce::toUnderlyingType(currentWaveform)].processSample(0.f);
  }
  void updateWaveform() {
    if (currentWaveform != waveformToSet) {
      currentWaveform = waveformToSet;
    }
  }

  std::array<juce::dsp::Oscillator<float>, 3u> osc{
    juce::dsp::Oscillator<float>{
      [](float phase) -> float {
        return Waveforms::getSample(Waveforms::WaveformType::sine,phase);
      }
    },
    juce::dsp::Oscillator<float>{
      [](float phase) -> float {
        return Waveforms::getSample(Waveforms::WaveformType::triangle,phase);
      }
    },
    juce::dsp::Oscillator<float>{
      [](float phase) -> float {
        return Waveforms::getSample(Waveforms::WaveformType::saw,phase);
      }
    }
  };

  double currentSampleRate = 44100.0;

  float currentFrequency = 440.0f;

  // float phase = 0.0f;
  // float phaseIncrement = 0.0f;

  juce::AudioBuffer<float> synthBuffer;

  juce::ADSR adsr;
  juce::ADSR::Parameters adsrParams;
  WaveformType currentWaveform = WaveformType::sine;
  WaveformType waveformToSet = currentWaveform;

};


}