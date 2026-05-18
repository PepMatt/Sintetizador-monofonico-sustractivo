#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include "MiniMoogVoice.h"
#include "MiniMoogSound.h"

namespace sintetizador_monofonico {

class PluginProcessor : public juce::AudioProcessor
{
public:
  // Objeto APVTS que gestiona el estado global
  juce::AudioProcessorValueTreeState apvts;

 PluginProcessor();

  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

  juce::AudioProcessorEditor* createEditor() override;
  bool hasEditor() const override;

  const juce::String getName() const override { return "Sintetizador Monofonico"; }

  double getTailLengthSeconds() const override { return 0.0; }

  bool acceptsMidi() const override { return true; }

  bool producesMidi() const override { return false; }

  int getNumPrograms() override { return 1; }

  int getCurrentProgram() override { return 0; }

  void setCurrentProgram(int) override {}

  const juce::String getProgramName(int) override { return {}; }

  void changeProgramName(int, const juce::String&) override {}

  void getStateInformation(juce::MemoryBlock&) override {}

  void setStateInformation(const void*, int) override {}
private:

  juce::Synthesiser synth;

  static juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};

}