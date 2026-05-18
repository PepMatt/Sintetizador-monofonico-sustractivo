#pragma once
#include "sintetizador_monofonico/include/ParameterLayoutBuilder.h"

namespace sintetizador_monofonico {

PluginProcessor::PluginProcessor()
:
  apvts(*this,
        nullptr,
        "PARAMETERS",
        ParameterLayoutBuilder::create()),
  parameters(apvts)
{
  synth.addVoice(new MiniMoogVoice());
  synth.addSound(new MiniMoogSound());
}

void PluginProcessor::prepareToPlay(double sampleRate,
                                    int samplesPerBlock)
{
  synth.setCurrentPlaybackSampleRate(sampleRate);

  for (int i = 0; i < synth.getNumVoices(); ++i)
    if (auto* v =
        dynamic_cast<MiniMoogVoice*>(synth.getVoice(i)))
      v->prepare(sampleRate, samplesPerBlock);
}

void PluginProcessor::releaseResources()
{
}

void PluginProcessor::processBlock(
    juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midi)
{
  juce::ScopedNoDenormals noDenormals;

  for (int ch = getTotalNumInputChannels();
       ch < getTotalNumOutputChannels(); ++ch)
  {
    buffer.clear(ch, 0, buffer.getNumSamples());
  }

  const auto cutoff  = parameters.filterCutoff->load();
  const auto res     = parameters.filterResonance->load();
  const auto drive   = parameters.filterDrive->load();
  const auto mode    = parameters.filterMode->load();

  const auto osc2Detune = parameters.osc2Detune->load();
  const auto osc3Detune = parameters.osc3Detune->load();

  const auto osc1Wave = parameters.osc1Wave->load();
  const auto osc2Wave = parameters.osc2Wave->load();
  const auto osc3Wave = parameters.osc3Wave->load();

  const auto osc1Oct = parameters.osc1Oct->load();
  const auto osc2Oct = parameters.osc2Oct->load();
  const auto osc3Oct = parameters.osc3Oct->load();

  const auto attack  = parameters.attack->load();
  const auto decay   = parameters.decay->load();
  const auto sustain = parameters.sustain->load();
  const auto release = parameters.release->load();

  for (int i = 0; i < synth.getNumVoices(); ++i)
  {
    if (auto* voice =
        dynamic_cast<MiniMoogVoice*>(synth.getVoice(i)))
    {
      voice->setOscParameters(
          osc1Wave,
          osc2Wave,
          osc3Wave,
          osc1Oct,
          osc2Oct,
          osc3Oct,
          osc2Detune,
          osc3Detune);

      voice->setFilterParameters(
          cutoff,
          res,
          drive,
          mode);

      voice->setEnvelopeParameters(
          attack,
          decay,
          sustain,
          release);
    }
  }

  synth.renderNextBlock(
      buffer,
      midi,
      0,
      buffer.getNumSamples());
}

bool PluginProcessor::hasEditor() const
{
  return true;
}

juce::AudioProcessorEditor*
PluginProcessor::createEditor()
{
  return new juce::GenericAudioProcessorEditor(*this);
}

} // namespace sintetizador_monofonico

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new sintetizador_monofonico::PluginProcessor();
}