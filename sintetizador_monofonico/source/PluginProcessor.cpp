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
  synth.clearVoices();

  synth.addVoice(new MiniMoogVoice());

  synth.clearSounds();
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

  // =========================================
  // LEER TODOS LOS PARÁMETROS
  // =========================================
  const auto params = parameters.get();

  // =========================================
  // ENVIAR PARÁMETROS A LAS VOCES
  // =========================================
  for (int i = 0; i < synth.getNumVoices(); ++i)
  {
    if (auto* voice =
        dynamic_cast<MiniMoogVoice*>(synth.getVoice(i)))
    {
      voice->setParameters(params);
    }
  }

  // =========================================
  // RENDER
  // =========================================
  synth.renderNextBlock(
      buffer,
      midi,
      0,
      buffer.getNumSamples());

  // =========================================
  // MASTER GAIN
  // =========================================
  buffer.applyGain(
      juce::Decibels::decibelsToGain(params.gain));
}
bool PluginProcessor::hasEditor() const
{
  return true;
}

juce::AudioProcessorEditor*
PluginProcessor::createEditor()
{
  // return new juce::GenericAudioProcessorEditor(*this);
  return new PluginEditor(*this);
}

void PluginProcessor::getStateInformation(juce::MemoryBlock& destData)
{
  auto state = apvts.copyState();

  juce::MemoryOutputStream stream(destData, false);

  JsonSerializer::saveToStream(state, stream);
}

void PluginProcessor::setStateInformation(const void* data, int sizeInBytes)
{
  juce::MemoryInputStream stream(data, static_cast<size_t>(sizeInBytes), false);

  juce::ValueTree state;

  auto result = JsonSerializer::loadFromStream(state, stream);

  if (result.failed())
    return;

  apvts.replaceState(state);
}
} // namespace sintetizador_monofonico

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new sintetizador_monofonico::PluginProcessor();
}